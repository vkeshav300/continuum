#pragma once

#include "../components.hpp"
#include "gpu_context.hpp"
#include "gpu_types.hpp"

#include <array>
#include <cstdint>
#include <unordered_map>

#include <Metal/Metal.hpp>
#include <entt/entt.hpp>

namespace CTNM::RHI {

struct AS_Context {
  bool as_built = false;
  uint64_t revision = 0;

  MTL::PackedFloat4x3 transform;
  GPU_Types::Surface surface;

  MTL_Unique<MTL::Buffer> buff_verticies = nullptr;
  MTL_Unique<MTL::Buffer> buff_indicies = nullptr;
  MTL_Unique<MTL::Buffer> buff_scratch = nullptr;

  MTL_Unique<MTL4::AccelerationStructureTriangleGeometryDescriptor>
      as_geom_desc = nullptr;
  MTL_Unique<MTL4::PrimitiveAccelerationStructureDescriptor> as_desc = nullptr;
  MTL_Unique<MTL::AccelerationStructure> as = nullptr;
};

class Render_Packet {
public:
  Render_Packet(GPU_Context &gpu_context,
                const Components::Transform &transform, Components::Mesh &mesh,
                const Components::Surface &surface);
  ~Render_Packet() = default;

  void update(GPU_Context &gpu_context, const Components::Transform &transform,
              Components::Mesh &mesh, const Components::Surface &surface);
  bool build_required(const uint32_t slot, const Components::Mesh &mesh) const;

  const MTL::AccelerationStructure *get_as(const uint32_t slot) const;
  const MTL::PackedFloat4x3 &get_transform(const uint32_t slot) const;
  const GPU_Types::Surface &get_surface(const uint32_t slot) const;

private:
  std::array<AS_Context, MAX_FRAMES_INFLIGHT> m_as_contexts;

  void subfn_update_write_transform(const uint32_t slot,
                                    const Components::Transform &transform);
  void subfn_update_write_surface(const uint32_t slot,
                                  const Components::Surface &surface);
  void subfn_update_write_vertex_normals(Components::Mesh &mesh);
  void subfn_update_build_as(GPU_Context &gpu_context, AS_Context &as_context,
                             const Components::Mesh &mesh);
};

using packet_umap = std::unordered_map<entt::entity, Render_Packet>;

} // namespace CTNM::RHI
