#include "stager.hpp"
#include "components.hpp"
#include "rhi/gpu_context.hpp"
#include "rhi/render_packet.hpp"

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

    if (m_packets.find(e) !=
        m_packets.end()) { // For entities that already have associated packets
      m_packets[e]->smart_update(context, bbox, transform);
    } else { // For new entities
      m_packets[e] =
          std::make_unique<RHI::Render_Packet_AABB>(context, bbox, transform);
    }
  }

  /* Ensure cleanup of decomission packets syncs with GPU */
  context.cmd_buff->addCompletedHandler([this](MTL::CommandBuffer *cmd) {
    const std::lock_guard<std::mutex> lock(m_mtx_cleanup);
    for (auto packet : m_packets_decomissioned)
      m_packets.erase(packet);

    m_packets_decomissioned.clear();
  });
}

const std::unordered_map<entt::entity, std::unique_ptr<RHI::Render_Packet>> &
Stager::get_render_packets() const {
  return m_packets;
}

void Stager::callback_bbox_destroyed(entt::registry &registry, entt::entity e) {
  m_packets_decomissioned.push_back(e);
}

} // namespace CTNM
