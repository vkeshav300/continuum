#pragma once

#include "../components.hpp"
#include "gpu_context.hpp"
#include "gpu_types.hpp"

#include <array>
#include <cstdint>

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

struct AS_Context {
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

  bool as_built = false;
};

class Render_Packet {
public:
  Render_Packet(GPU_Context &gpu_context,
                const Components::Transform &transform,
                const Components::Mesh &mesh,
                const Components::Surface &surface);
  ~Render_Packet() = default;

  void update(GPU_Context &gpu_context, const Components::Transform &transform,
              const Components::Mesh &mesh, const Components::Surface &surface);
  bool needs_rebuild(const uint32_t slot, const Components::Mesh &mesh) const;

  const MTL::AccelerationStructure *get_as(const uint32_t slot) const;
  const MTL::PackedFloat4x3 &get_transform(const uint32_t slot) const;
  const GPU_Types::Surface &get_surface(const uint32_t slot) const;

private:
  std::array<AS_Context, MAX_FRAMES_INFLIGHT> m_as_contexts;
};

} // namespace CTNM::RHI
