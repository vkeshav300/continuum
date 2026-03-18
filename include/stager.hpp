#pragma once

#include "rhi/gpu_context.hpp"
#include "rhi/render_packet.hpp"

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <unordered_map>
#include <vector>

#include <entt/entt.hpp>

namespace CTNM {

constexpr uint32_t IDLE_TIMEOUT = 2000;

class Stager {
public:
  Stager() = default;
  ~Stager() = default;

  void stage(RHI::GPU_Context &gpu_context, const entt::registry &reg);

  std::unordered_map<entt::entity, RHI::Render_Packet> &get_render_packets();
  void decommission_packet(const entt::entity e);
  void attach_decommissioned_packets(const uint32_t frame_id);
  void clear_decommissioned_packets(const uint32_t frame_id);

  uint64_t get_revision() const;
  std::mutex &get_mutex();
  void wait_until_idle();

private:
  std::unordered_map<entt::entity, RHI::Render_Packet> m_packets;
  std::unordered_map<uint32_t, std::vector<entt::entity>>
      m_frame_to_packets_decommissioned;
  std::vector<entt::entity> m_packets_decommissioned;

  std::mutex m_mtx;
  std::condition_variable m_cv;
  std::atomic<uint64_t> m_revision = 0;
  int m_inflight = 0; // Always protected by m_mtx, no need for atomic
};

} // namespace CTNM
