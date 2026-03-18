#include "rhi/render_packet.hpp"
#include "components.hpp"
#include "math_utils.hpp"
#include "rhi/gpu_context.hpp"
#include "rhi/gpu_types.hpp"

#include <cstdint>
#include <cstring>
#include <utility>

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <simd/simd.h>

namespace CTNM::RHI {

static inline MTL::PackedFloat4x3
get_mtl_transform(const CTNM::Components::Transform &transform) {
  CTNM::Math::vec_f3 axis =
      CTNM::Math::vec_f3{transform.r.x, transform.r.y, transform.r.z};
  const bool degenerate_axis =
      CTNM::Math::approx_eq(CTNM::Math::magnitude(axis), 0.0f);
  if (!degenerate_axis)
    axis = CTNM::Math::normalize(axis);

  const float angle = degenerate_axis ? 0.0f : transform.r.w;
  const CTNM::Math::vec_f3 safe_axis =
      degenerate_axis ? CTNM::Math::vec_f3{1.0f, 0.0f, 0.0f} : axis;

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
                             const Components::Mesh &mesh,
                             const Components::Surface &surface) {
  for (auto &as_context : m_as_contexts) {
    as_context.as_desc =
        MTL4::PrimitiveAccelerationStructureDescriptor::alloc()->init();
    as_context.as_desc->setUsage(MTL::AccelerationStructureUsageRefit);
  }

  update(gpu_context, transform, mesh, surface);
}

void Render_Packet::update(GPU_Context &gpu_context,
                           const Components::Transform &transform,
                           const Components::Mesh &mesh,
                           const Components::Surface &surface) {
  MTL_Unique<NS::AutoreleasePool> pool_limited =
      NS::AutoreleasePool::alloc()->init();
  AS_Context &as_context = m_as_contexts[gpu_context.slot];

  as_context.transform = get_mtl_transform(transform);
  as_context.surface = GPU_Types::Surface{
      GPU_Types::vec_pf3{surface.col.x, surface.col.y, surface.col.z}};

  const bool rebuild =
      !as_context.as_built || needs_rebuild(gpu_context.slot, mesh);

  if (rebuild) {
    as_context.revision = mesh.revision;
    as_context.buff_verticies = gpu_context.device->newBuffer(
        mesh.verticies.data(),
        mesh.verticies.size() * sizeof(Components::Vertex),
        MTL::ResourceStorageModeShared);
    as_context.buff_indicies = gpu_context.device->newBuffer(
        mesh.indicies.data(), mesh.indicies.size() * sizeof(uint32_t),
        MTL::ResourceStorageModeShared);

    as_context.as_geom_desc =
        MTL4::AccelerationStructureTriangleGeometryDescriptor::alloc()->init();
    as_context.as_geom_desc->setTriangleCount(mesh.indicies.size() / 3);
    as_context.as_geom_desc->setVertexFormat(MTL::AttributeFormatFloat3);
    as_context.as_geom_desc->setVertexStride(sizeof(Components::Vertex));
    as_context.as_geom_desc->setVertexBuffer(
        MTL4::BufferRange::Make(as_context.buff_verticies->gpuAddress(),
                                as_context.buff_verticies->length()));
    as_context.as_geom_desc->setIndexType(MTL::IndexTypeUInt32);
    as_context.as_geom_desc->setIndexBuffer(
        MTL4::BufferRange::Make(as_context.buff_indicies->gpuAddress(),
                                as_context.buff_indicies->length()));
  }

  MTL4::AccelerationStructureTriangleGeometryDescriptor *as_geom_descs[] = {
      as_context.as_geom_desc.get()};
  NS::Array *as_geom_desc_array =
      NS::Array::array(reinterpret_cast<NS::Object **>(as_geom_descs), 1);
  as_context.as_desc->setGeometryDescriptors(as_geom_desc_array);

  if (!gpu_context.ce_as.exists())
    return;

  const MTL::AccelerationStructureSizes sizes =
      gpu_context.device->accelerationStructureSizes(as_context.as_desc.get());

  if (rebuild) {
    as_context.buff_scratch = gpu_context.device->newBuffer(
        sizes.buildScratchBufferSize, MTL::ResourceStorageModePrivate);
    as_context.as = gpu_context.device->newAccelerationStructure(
        sizes.accelerationStructureSize);

    gpu_context.rset->addAllocation(as_context.buff_verticies.get());
    gpu_context.rset->addAllocation(as_context.buff_indicies.get());
    gpu_context.rset->addAllocation(as_context.buff_scratch.get());
    gpu_context.rset->addAllocation(as_context.as.get());
    gpu_context.rset->commit();

    gpu_context.ce_as->buildAccelerationStructure(
        as_context.as.get(), as_context.as_desc.get(),
        MTL4::BufferRange::Make(as_context.buff_scratch->gpuAddress(),
                                sizes.buildScratchBufferSize));

    as_context.as_built = true;
  } else {
    if (as_context.buff_scratch->length() < sizes.refitScratchBufferSize)
      as_context.buff_scratch = gpu_context.device->newBuffer(
          sizes.refitScratchBufferSize, MTL::ResourceStorageModePrivate);

    const MTL4::BufferRange buff_r_scratch = MTL4::BufferRange::Make(
        as_context.buff_scratch->gpuAddress(), sizes.refitScratchBufferSize);

    if (as_context.as->size() < sizes.accelerationStructureSize) {
      MTL_Unique<MTL::AccelerationStructure> as_new =
          gpu_context.device->newAccelerationStructure(
              sizes.accelerationStructureSize);
      gpu_context.rset->addAllocation(as_context.buff_verticies.get());
      gpu_context.rset->addAllocation(as_context.buff_indicies.get());
      gpu_context.rset->addAllocation(as_context.buff_scratch.get());
      gpu_context.rset->addAllocation(as_context.as.get());
      gpu_context.rset->addAllocation(as_new.get());
      gpu_context.rset->commit();
      gpu_context.ce_as->refitAccelerationStructure(
          as_context.as.get(), as_context.as_desc.get(), as_new.get(),
          buff_r_scratch);
      as_context.as = std::move(as_new);
    } else {
      gpu_context.rset->addAllocation(as_context.buff_verticies.get());
      gpu_context.rset->addAllocation(as_context.buff_indicies.get());
      gpu_context.rset->addAllocation(as_context.buff_scratch.get());
      gpu_context.rset->addAllocation(as_context.as.get());
      gpu_context.rset->commit();
      gpu_context.ce_as->refitAccelerationStructure(
          as_context.as.get(), as_context.as_desc.get(), as_context.as.get(),
          buff_r_scratch);
    }
  }
}

bool Render_Packet::needs_rebuild(const uint32_t slot,
                                  const Components::Mesh &mesh) const {
  return !(m_as_contexts[slot].revision == mesh.revision);
}

const MTL::AccelerationStructure *
Render_Packet::get_as(const uint32_t slot) const {
  return m_as_contexts[slot].as.get();
}

const MTL::PackedFloat4x3 &
Render_Packet::get_transform(const uint32_t slot) const {
  return m_as_contexts[slot].transform;
}

const GPU_Types::Surface &
Render_Packet::get_surface(const uint32_t slot) const {
  return m_as_contexts[slot].surface;
}

} // namespace CTNM::RHI
