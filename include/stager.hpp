#pragma once

#include "rhi/gpu_context.hpp"
#include "rhi/render_packet.hpp"

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#include <entt/entt.hpp>

namespace CTNM {

class Stager : public std::enable_shared_from_this<Stager> {
private:
  std::unordered_map<entt::entity, std::unique_ptr<RHI::Render_Packet>>
      m_packets;
  std::vector<entt::entity> m_packets_decomissioned;

  mutable std::mutex m_mtx;
  mutable std::condition_variable m_cv;
  std::atomic<int> m_inflight = 0;

public:
  /**
 * @brief Constructs a Stager with empty packet storage and default synchronization state.
 *
 * Initializes internal containers as empty and the in-flight counter to zero.
 */
Stager() = default;
  ~Stager();

  void stage(entt::registry &registry, const RHI::GPU_Context &context);

  const std::unordered_map<entt::entity, std::unique_ptr<RHI::Render_Packet>> &
  get_render_packets() const;

  void callback_bbox_destroyed(entt::registry &registry, entt::entity e);

  bool is_idle() const;
  void wait_until_idle() const;

  std::mutex &get_mutex();
};

} // namespace CTNM
