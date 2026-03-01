#pragma once

#include "../components.hpp"
#include "gpu_context.hpp"

#include <array>
#include <cstdint>

#include <Metal/MTL4AccelerationStructure.hpp>
#include <Metal/Metal.hpp>

namespace CTNM::RHI {

static inline MTL::AxisAlignedBoundingBox
get_mtl_aabb(const CTNM::Components::AABB &bbox);

static inline MTL::PackedFloat4x3
get_mtl_transform(const CTNM::Components::Transform &transform);

struct AS_Context {
  MTL::AxisAlignedBoundingBox aabb{};

  MTL_Unique<MTL::Buffer> buff_aabb = nullptr;
  MTL_Unique<MTL::Buffer> buff_scratch = nullptr;

  MTL_Unique<MTL::PrimitiveAccelerationStructureDescriptor> as_sizes_desc =
      nullptr;
  MTL_Unique<MTL4::PrimitiveAccelerationStructureDescriptor> as_desc = nullptr;
  MTL_Unique<MTL::AccelerationStructure> as = nullptr;

  bool as_built = false, has_aabb = false;
};

class Render_Packet {
public:
  Render_Packet(GPU_Context &gpu_context,
                const Components::Transform &transform,
                const Components::AABB &bbox);
  ~Render_Packet() = default;

  void update(GPU_Context &gpu_context, const Components::Transform &transform,
              const Components::AABB &bbox);
  bool needs_refit(const MTL::AxisAlignedBoundingBox &current_aabb,
                   const MTL::AxisAlignedBoundingBox &new_aabb) const;

  const MTL::AccelerationStructure *get_as(const uint32_t slot) const;
  const MTL::PackedFloat4x3 &get_transform() const;

private:
  MTL::PackedFloat4x3 m_transform;
  std::array<AS_Context, MAX_FRAMES_INFLIGHT> m_as_contexts;
};

} // namespace CTNM::RHI
