#pragma once

#include "rhi/gpu_context.hpp"
#include "rhi/render_packet.hpp"

#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <unordered_map>

#include <entt/entt.hpp>

namespace CTNM {

constexpr uint32_t IDLE_TIMEOUT = 2000;

class Stager {
public:
  Stager() = default;
  ~Stager() = default;

  void stage(RHI::GPU_Context gpu_context, const entt::registry &reg);

  const std::unordered_map<entt::entity, RHI::Render_Packet> &
  get_render_packets() const;
  void decommission_packet(const entt::entity e);
  void attach_decommissioned_packets(const uint32_t frame_id);
  void clear_decommissioned_packets(const uint32_t frame_id);

  std::mutex &get_mutex();
  void wait_until_idle();

private:
  std::unordered_map<entt::entity, RHI::Render_Packet> m_packets;
  std::vector<entt::entity> m_packets_decommissioned;
  std::unordered_map<uint32_t, std::vector<entt::entity>>
      m_frame_to_packets_decommissioned;
  std::mutex m_mtx;
  std::condition_variable m_cv;
  int m_inflight = 0;
};

} // namespace CTNM
