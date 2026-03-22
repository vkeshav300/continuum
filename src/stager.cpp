#include "stager.hpp"
#include "rhi/gpu_context.hpp"
#include "rhi/render_packet.hpp"

#include <mutex>
#include <unordered_map>

#include <entt/entt.hpp>

namespace CTNM {

void Stager::stage(RHI::GPU_Context &gpu_context, const entt::registry &reg) {
  const auto &renderable_entities =
      reg.view<Components::Mesh, Components::Transform, Components::Surface>();

  std::lock_guard<std::mutex> lock(m_mtx);
  bool packet_added = false;
  for (const auto e : renderable_entities) {
    const auto &[mesh, transform, surface] =
        reg.get<Components::Mesh, Components::Transform, Components::Surface>(
            e);

    const auto it = m_packets.find(e);
    if (it != m_packets.end())
      it->second.update(gpu_context, transform, mesh, surface);
    else {
      const bool result =
          m_packets.try_emplace(e, gpu_context, transform, mesh, surface)
              .second;

      if (!packet_added && result)
        packet_added = true;
    }
  }

  if (packet_added)
    m_revision.fetch_add(1);
}

std::unordered_map<entt::entity, RHI::Render_Packet> &
Stager::get_render_packets() {
  return m_packets;
}

void Stager::decommission_packet(const entt::entity e) {
  const std::lock_guard<std::mutex> lock(m_mtx);
  m_packets_decommissioned.push_back(e);
  m_inflight++;
  m_cv.notify_one();
}

void Stager::attach_decommissioned_packets(const uint32_t frame_id) {
  const std::lock_guard<std::mutex> lock(m_mtx);
  if (m_packets_decommissioned.empty())
    return;

  std::vector<entt::entity> &packets =
      m_frame_to_packets_decommissioned[frame_id];
  packets.insert(packets.end(), m_packets_decommissioned.begin(),
                 m_packets_decommissioned.end());
  m_packets_decommissioned.clear();
}

void Stager::clear_decommissioned_packets(const uint32_t frame_id) {
  const std::lock_guard<std::mutex> lock(m_mtx);
  const auto it = m_frame_to_packets_decommissioned.find(frame_id);
  if (it == m_frame_to_packets_decommissioned.end())
    return;

  const size_t n_packets = it->second.size();
  if (n_packets == 0)
    return;

  for (const auto packet : it->second)
    m_packets.erase(packet);

  m_frame_to_packets_decommissioned.erase(it);
  m_inflight -= n_packets;
  m_revision.fetch_add(1);
  m_cv.notify_one();
}

uint64_t Stager::get_revision() const { return m_revision.load(); }

std::mutex &Stager::get_mutex() { return m_mtx; }

void Stager::wait_until_idle() {
  std::unique_lock<std::mutex> lock(m_mtx);
  m_cv.wait(lock, [&]() { return m_inflight == 0; });
}

} // namespace CTNM
