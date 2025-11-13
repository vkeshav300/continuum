#include "stager.hpp"
#include "components.h"
#include "rhi/gpu_context.hpp"
#include "rhi/render_packet.hpp"

#include <entt/entt.hpp>

namespace CTNM {

Stager::~Stager() {}

void Stager::callback_bbox_destroyed(entt::registry &registry, entt::entity e) {
  m_render_packets.erase(e);
}

void Stager::stage(entt::registry &registry, const RHI::GPU_Context &context) {
  const auto entities = registry.view<Components::Bounding_Box>();

  for (const auto &e : entities) {
    /* Create bounding box */
    const Components::Bounding_Box &bbox =
        registry.get<Components::Bounding_Box>(e);

    if (m_render_packets.find(e) !=
        m_render_packets
            .end()) { // For entities that already have associated packets
      m_render_packets[e]->smart_refit(context, bbox);
    } else { // For new entities
      m_render_packets[e] =
          std::make_unique<RHI::Render_Packet_AABB>(context, bbox);
    }
  }
}

const std::unordered_map<entt::entity, std::unique_ptr<RHI::Render_Packet>> &
Stager::get_render_packets() const {
  return m_render_packets;
}

} // namespace CTNM
