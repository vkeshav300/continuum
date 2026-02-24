#include "rhi/render_packet.hpp"
#include "components.hpp"
#include "rhi/gpu_context.hpp"

#include <cstring>
#include <utility>

#include <Foundation/Foundation.hpp>
#include <Metal/MTL4AccelerationStructure.hpp>
#include <Metal/Metal.hpp>
#include <simd/simd.h>

namespace CTNM::RHI {

static inline MTL::AxisAlignedBoundingBox
get_mtl_aabb(const CTNM::Components::AABB &bbox) {
  MTL::AxisAlignedBoundingBox aabb;
  aabb.min = {-bbox.r, -bbox.r, -bbox.r};
  aabb.max = {bbox.r, bbox.r, bbox.r};

  return aabb;
}

static inline MTL::PackedFloat4x3
get_mtl_transform(const CTNM::Components::Transform &transform) {
  vector_float3 axis =
      vector_float3{transform.r.x, transform.r.y, transform.r.z};
  const bool degenerate_axis = approx_eq(simd::length(axis), 0.0f);
  if (!degenerate_axis)
    axis = simd::normalize(axis);

  const float angle = degenerate_axis ? 0.0f : transform.r.w;
  const vector_float3 safe_axis =
      degenerate_axis ? vector_float3{1.0f, 0.0f, 0.0f} : axis;

  const simd_quatf quat = simd_quaternion(angle, safe_axis);
  matrix_float3x3 rotation = simd_matrix3x3(quat);

  rotation.columns[0] *= transform.s.x;
  rotation.columns[1] *= transform.s.y;
  rotation.columns[2] *= transform.s.z;

  const MTL::PackedFloat3 p_col_0{rotation.columns[0].x, rotation.columns[0].y,
                                  rotation.columns[0].z},
      p_col_1{rotation.columns[1].x, rotation.columns[1].y,
              rotation.columns[1].z},
      p_col_2{rotation.columns[2].x, rotation.columns[2].y,
              rotation.columns[2].z},
      p_col_3{transform.p.x, transform.p.y, transform.p.z};

  return MTL::PackedFloat4x3{p_col_0, p_col_1, p_col_2, p_col_3};
}

Render_Packet::Render_Packet(GPU_Context &gpu_context,
                             const Components::Transform &transform,
                             const Components::AABB &bbox) {
  for (auto &as_context : m_as_contexts) {
    as_context.buff_aabb = gpu_context.device->newBuffer(
        sizeof(MTL::AxisAlignedBoundingBox), MTL::ResourceStorageModeShared);

    as_context.aabb = get_mtl_aabb(bbox);
    as_context.has_aabb = true;
    std::memcpy(as_context.buff_aabb->contents(), &as_context.aabb,
                sizeof(MTL::AxisAlignedBoundingBox));

    MTL_Unique<MTL4::AccelerationStructureBoundingBoxGeometryDescriptor>
        as_geom_desc =
            MTL4::AccelerationStructureBoundingBoxGeometryDescriptor::alloc()
                ->init();
    as_geom_desc->setBoundingBoxBuffer(
        MTL4::BufferRange::Make(as_context.buff_aabb->gpuAddress(),
                                sizeof(MTL::AxisAlignedBoundingBox)));
    as_geom_desc->setBoundingBoxCount(1);
    as_geom_desc->setOpaque(true);
    as_geom_desc->setIntersectionFunctionTableOffset(0); // 0 = Sphere

    MTL4::AccelerationStructureBoundingBoxGeometryDescriptor *as_geom_descs[] =
        {as_geom_desc.get()};
    NS::Array *as_geom_desc_array =
        NS::Array::array(reinterpret_cast<NS::Object **>(as_geom_descs), 1);

    as_context.as_desc =
        MTL4::PrimitiveAccelerationStructureDescriptor::alloc()->init();
    as_context.as_desc->setGeometryDescriptors(as_geom_desc_array);
    as_context.as_desc->setUsage(MTL::AccelerationStructureUsageRefit);
  }

  update(gpu_context, transform, bbox);
}

void Render_Packet::update(GPU_Context &gpu_context,
                           const Components::Transform &transform,
                           const Components::AABB &bbox) {
  if (!gpu_context.ce_as.exists())
    return;

  m_transform = get_mtl_transform(transform);

  AS_Context &as_context = m_as_contexts[gpu_context.slot];
  const MTL::AxisAlignedBoundingBox aabb = get_mtl_aabb(bbox);
  const bool refit =
      !as_context.has_aabb || needs_refit(as_context.aabb, aabb);
  as_context.aabb = aabb;
  as_context.has_aabb = true;
  std::memcpy(as_context.buff_aabb->contents(), &as_context.aabb,
              sizeof(MTL::AxisAlignedBoundingBox));

  if (!as_context.as_built) {
    const MTL::AccelerationStructureSizes sizes =
        gpu_context.device->accelerationStructureSizes(as_context.as_desc.get());
    as_context.buff_scratch = gpu_context.device->newBuffer(
        sizes.buildScratchBufferSize, MTL::ResourceStorageModePrivate);
    as_context.as = gpu_context.device->newAccelerationStructure(
        sizes.accelerationStructureSize);

    gpu_context.ce_as->buildAccelerationStructure(
        as_context.as.get(), as_context.as_desc.get(),
        MTL4::BufferRange::Make(as_context.buff_scratch->gpuAddress(),
                                sizes.buildScratchBufferSize));
    as_context.as_built = true;
    return;
  }

  if (refit) {
    MTL::AccelerationStructureSizes sizes =
        gpu_context.device->accelerationStructureSizes(as_context.as_desc.get());
    if (as_context.buff_scratch->length() < sizes.refitScratchBufferSize)
      as_context.buff_scratch = gpu_context.device->newBuffer(
          sizes.refitScratchBufferSize, MTL::ResourceStorageModePrivate);

    MTL4::BufferRange buff_r_scratch = MTL4::BufferRange::Make(
        as_context.buff_scratch->gpuAddress(), sizes.refitScratchBufferSize);

    if (sizes.accelerationStructureSize == as_context.as->size())
      gpu_context.ce_as->refitAccelerationStructure(
          as_context.as.get(), as_context.as_desc.get(), as_context.as.get(),
          buff_r_scratch); // In-place refit
    else {
      MTL_Unique<MTL::AccelerationStructure> as_new =
          gpu_context.device->newAccelerationStructure(
              sizes.accelerationStructureSize);
      gpu_context.ce_as->refitAccelerationStructure(
          as_context.as.get(), as_context.as_desc.get(), as_new.get(),
          buff_r_scratch);

      as_context.as = std::move(as_new);
    }
  }
}

bool Render_Packet::needs_refit(
    const MTL::AxisAlignedBoundingBox &current_aabb,
    const MTL::AxisAlignedBoundingBox &new_aabb) const {
  return !(current_aabb.min.x == new_aabb.min.x &&
           current_aabb.min.y == new_aabb.min.y &&
           current_aabb.min.z == new_aabb.min.z &&
           current_aabb.max.x == new_aabb.max.x &&
           current_aabb.max.y == new_aabb.max.y &&
           current_aabb.max.z == new_aabb.max.z);
}

} // namespace CTNM::RHI
