#pragma once

#include "rhi/gpu_context.hpp"
#include "rhi/render_packet.hpp"

#include <memory>
#include <unordered_map>

#include <entt/entt.hpp>

namespace CTNM {

class Stager {
private:
  std::unordered_map<entt::entity, std::unique_ptr<RHI::Render_Packet>>
      m_render_packets;

public:
  Stager() = default;
  ~Stager();

  void stage(entt::registry &registry, const RHI::GPU_Context &context);
  void clean_up(entt::entity e);

  const std::unordered_map<entt::entity, std::unique_ptr<RHI::Render_Packet>> &
  get_render_packets() const;

  void callback_bbox_destroyed(entt::registry &registry, entt::entity e);
};

} // namespace CTNM
