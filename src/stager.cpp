#include "stager.hpp"
#include "rhi/render_packet.hpp"

#include <mutex>
#include <unordered_map>

#include <entt/entt.hpp>

namespace CTNM {

void Stager::stage(const entt::registry &reg) {
  const auto &renderable_entities =
      reg.view<Components::AABB, Components::Transform>();

  std::lock_guard<std::mutex> lock(m_mtx);
  for (const auto e : renderable_entities) {
    const auto &[bbox, transform] =
        reg.get<Components::AABB, Components::Transform>(e);

    auto it = m_packets.find(e);
    if (it != m_packets.end())
      it->second.update(transform);
    else
      m_packets.emplace(e, transform);
  }
}

const std::unordered_map<entt::entity, RHI::Render_Packet> &
Stager::get_render_packets() const {
  return m_packets;
}

void Stager::decommission_packet(const entt::entity e) {
  const std::lock_guard<std::mutex> lock(m_mtx);
  m_packets_decommissioned.push_back(e);
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

  for (const auto packet : it->second)
    m_packets.erase(packet);

  m_frame_to_packets_decommissioned.erase(it);
}

std::mutex &Stager::get_mutex() { return m_mtx; }

} // namespace CTNM
