#pragma once

#include "rhi/defines.hpp"
#include "rhi/render_packet.hpp"

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <unordered_map>
#include <vector>

#include <entt/entt.hpp>

namespace CTNM {

class Stager {
public:
  Stager() = default;
  ~Stager() = default;

  void stage(RHI::GPU_Context &gpu_context, entt::registry &reg);

  RHI::packet_umap &get_render_packets();
  void decommission_packet(const entt::entity e);
  void attach_decommissioned_packets(const uint32_t frame_id);
  void clear_decommissioned_packets(const uint32_t frame_id);

  uint64_t get_revision() const;
  std::mutex &get_mutex();
  void wait_until_idle();

private:
  RHI::packet_umap m_packets;
  std::unordered_map<uint32_t, std::vector<entt::entity>>
      m_frame_to_packets_decommissioned;
  std::vector<entt::entity> m_packets_decommissioned;

  std::mutex m_mtx;
  std::condition_variable m_cv;
  std::atomic<uint64_t> m_revision = 0;
  int m_inflight = 0; // Always protected by mutex, no need for atomic
};

} // namespace CTNM
