#include "stager.hpp"
#include "components.hpp"
#include "rhi/gpu_context.hpp"
#include "rhi/render_packet.hpp"

#include <memory>
#include <mutex>

#include <entt/entt.hpp>

namespace CTNM {

Stager::~Stager() {}

void Stager::stage(entt::registry &registry, const RHI::GPU_Context &context) {
  const auto entities =
      registry.view<Components::Sphere_AABB, Components::Transform>();

  for (const auto &e : entities) {
    /* Create bounding box */
    const auto &[bbox, transform] =
        registry.get<Components::Sphere_AABB, Components::Transform>(e);

    const std::lock_guard<std::mutex> lock(m_mtx);
    if (m_packets.find(e) !=
        m_packets.end()) { // For entities that already have associated packets
      m_packets[e]->smart_update(context, bbox, transform);
    } else { // For new entities
      m_packets[e] =
          std::make_unique<RHI::Render_Packet_AABB>(context, bbox, transform);
    }
  }

  /* Ensure cleanup of decomission packets syncs with GPU */
  m_inflight.fetch_add(1, std::memory_order_relaxed);
  std::shared_ptr<Stager> self = shared_from_this();
  context.cmd_buff->addCompletedHandler([self](MTL::CommandBuffer * /*cmd*/) {
    const std::lock_guard<std::mutex> lock(self->m_mtx);
    for (auto packet : self->m_packets_decomissioned)
      self->m_packets.erase(packet);

    self->m_packets_decomissioned.clear();
    self->m_inflight.fetch_sub(1, std::memory_order_relaxed);
  });
}

const std::unordered_map<entt::entity, std::unique_ptr<RHI::Render_Packet>> &
Stager::get_render_packets() const {
  return m_packets;
}

void Stager::callback_bbox_destroyed(entt::registry &registry, entt::entity e) {
  const std::lock_guard<std::mutex> lock(m_mtx);
  m_packets_decomissioned.push_back(e);
}

bool Stager::is_idle() const {
  return m_inflight.load(std::memory_order_relaxed) == 0;
}

void Stager::wait_until_idle() const {
  while (!is_idle())
    continue;
}

std::mutex &Stager::get_mutex() { return m_mtx; }

} // namespace CTNM
