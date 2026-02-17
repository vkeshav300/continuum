#include "stager.hpp"
#include "components.hpp"
#include "rhi/gpu_context.hpp"
#include "rhi/render_packet.hpp"

#include <memory>
#include <mutex>

#include <entt/entt.hpp>

namespace CTNM {

/**
 * @brief Destroy the Stager and release its owned resources.
 *
 * This default destructor allows member objects (packets, mutex, counters) to
 * be cleaned up by their own destructors.
 */
Stager::~Stager() {}

/**
 * @brief Updates or creates render packets for entities that have a bounding
 * sphere and transform, and schedules GPU-synchronized cleanup of packets
 * marked for decommission.
 *
 * Processes all registry entities with Components::Sphere_AABB and
 * Components::Transform: existing per-entity render packets are updated,
 * missing packets are created, and a completion handler is attached to the
 * provided GPU context's command buffer to remove decomissioned packets and
 * decrement the internal in-flight counter once the GPU work finishes.
 *
 * @param registry EnTT registry containing entity components to stage.
 * @param context GPU context whose command buffer is used to attach the
 * completion handler and to initialize/update render packets.
 */
void Stager::stage(entt::registry &registry, const RHI::GPU_Context &context) {
  const auto entities =
      registry.view<Components::Sphere_AABB, Components::Transform>();

  /* Calculate dt (time since last staging) */
  const auto now = std::chrono::steady_clock::now();
  const bool first_staging = m_ct == 0;
  m_dt = now - m_tp_last;
  m_tp_last = now;

  for (const auto &e : entities) {
    /* Create bounding box */
    const auto &[bbox, transform] =
        registry.get<Components::Sphere_AABB, Components::Transform>(e);

    const std::lock_guard<std::mutex> lock(m_mtx);

    /* Temporary movement simulation */
    if (!first_staging)
      transform.pos.x += m_dt.count();

    if (m_packets.find(e) !=
        m_packets.end()) { // For entities that already have associated packets
      m_packets[e]->smart_update(context, bbox, transform);
    } else { // For new entities
      m_packets[e] =
          std::make_unique<RHI::Render_Packet_AABB>(context, bbox, transform);
    }
  }

  /* Ensure cleanup of decomission packets syncs with GPU */
  std::shared_ptr<Stager> self;
  {
    const std::lock_guard<std::mutex> lock(m_mtx);
    m_inflight.fetch_add(1, std::memory_order_relaxed);
    self = shared_from_this();
  }

  context.cmd_buff->addCompletedHandler([self](MTL::CommandBuffer * /*cmd*/) {
    {
      const std::lock_guard<std::mutex> lock(self->m_mtx);
      for (auto packet : self->m_packets_decomissioned)
        self->m_packets.erase(packet);

      self->m_packets_decomissioned.clear();
      self->m_inflight.fetch_sub(1, std::memory_order_relaxed);
    }
    self->m_cv.notify_all();
  });

  m_ct++;
}

/**
 * @brief Provide read-only access to the current mapping of entities to render
 * packets.
 *
 * @return const std::unordered_map<entt::entity,
 * std::unique_ptr<RHI::Render_Packet>>& A const reference to the internal map
 * that associates each entity with its owned `RHI::Render_Packet`.
 */
const std::unordered_map<entt::entity, std::unique_ptr<RHI::Render_Packet>> &
Stager::get_render_packets() const {
  return m_packets;
}

/**
 * @brief Marks an entity's render packet for decommissioning.
 *
 * Adds the given entity to the internal list of packets to remove; the entry
 * will be removed later when the GPU command buffer signals completion.
 * This operation is performed under internal synchronization.
 *
 * @param registry Registry the entity belongs to (unused but provided as
 * callback context).
 * @param e Entity whose render packet should be scheduled for removal.
 */
void Stager::callback_bbox_destroyed(entt::registry &registry, entt::entity e) {
  const std::lock_guard<std::mutex> lock(m_mtx);
  m_packets_decomissioned.push_back(e);
}

/**
 * @brief Indicates whether the stager has no in-flight staging operations.
 *
 * @return `true` if there are no in-flight staging operations, `false`
 * otherwise.
 */
bool Stager::is_idle() const {
  return m_inflight.load(std::memory_order_relaxed) == 0;
}

/**
 * @brief Blocks until the stager has no in-flight operations.
 */
void Stager::wait_until_idle() const {
  std::unique_lock<std::mutex> lock(m_mtx);
  m_cv.wait(lock, [this] { return is_idle(); });
}

/**
 * @brief Accesses the Stager's internal mutex used to synchronize packet state.
 *
 * Provides a reference to the internal mutex that protects the stager's
 * internal data structures (e.g., packet maps and decommission lists).
 *
 * @return std::mutex& Reference to the internal mutex.
 */
std::mutex &Stager::get_mutex() { return m_mtx; }

} // namespace CTNM
