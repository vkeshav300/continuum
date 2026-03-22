#include "rhi/render_packet.hpp"
#include "components.hpp"
#include "math_utils.hpp"
#include "rhi/gpu_context.hpp"
#include "rhi/gpu_types.hpp"
#include "rhi/utils.hpp"

#include <cstdint>
#include <cstring>

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <simd/simd.h>

namespace CTNM::RHI {

Render_Packet::Render_Packet(GPU_Context &gpu_context,
                             const Components::Transform &transform,
                             Components::Mesh &mesh,
                             const Components::Surface &surface) {
  for (auto &as_context : m_as_contexts) {
    as_context.as_desc =
        MTL4::PrimitiveAccelerationStructureDescriptor::alloc()->init();
    as_context.as_desc->setUsage(MTL::AccelerationStructureUsageRefit);
  }

  update(gpu_context, transform, mesh, surface);
}

void Render_Packet::subfn_update_write_transform(
    const uint32_t slot, const Components::Transform &transform) {
  /* Apply position offset */
  CTNM::Math::vec_f3 axis =
      CTNM::Math::vec_f3{transform.r.x, transform.r.y, transform.r.z};
  const bool degenerate =
      CTNM::Math::approx_eq(CTNM::Math::magnitude(axis), 0.0f);
  if (!degenerate)
    axis = CTNM::Math::normalize(axis);

  /* Apply rotation */
  const float angle = degenerate ? 0.0f : transform.r.w;
  const CTNM::Math::vec_f3 safe_axis =
      degenerate ? CTNM::Math::vec_f3{1.0f, 0.0f, 0.0f} : axis;

  const simd_quatf quat = simd_quaternion(angle, safe_axis);
  matrix_float3x3 rotation = simd_matrix3x3(quat);

  /* Apply scale */
  rotation.columns[0] *= transform.s.x;
  rotation.columns[1] *= transform.s.y;
  rotation.columns[2] *= transform.s.z;

  /* Pack */
  const MTL::PackedFloat3 p_col_0{rotation.columns[0].x, rotation.columns[0].y,
                                  rotation.columns[0].z},
      p_col_1{rotation.columns[1].x, rotation.columns[1].y,
              rotation.columns[1].z},
      p_col_2{rotation.columns[2].x, rotation.columns[2].y,
              rotation.columns[2].z},
      p_col_3{transform.p.x, transform.p.y, transform.p.z};

  /* Write */
  m_as_contexts[slot].transform =
      MTL::PackedFloat4x3{p_col_0, p_col_1, p_col_2, p_col_3};
}

void Render_Packet::subfn_update_write_surface(
    const uint32_t slot, const Components::Surface &surface) {
  AS_Context &as_context = m_as_contexts[slot];
  as_context.surface.color = Utils::vf3_to_vpf3(surface.color);
  as_context.surface.albedo = Utils::vf3_to_vpf3(surface.albedo);
  as_context.surface.ambient = surface.ambient;
  as_context.surface.emission_strength = surface.emission_strength;
  as_context.surface.reflectivity = surface.reflectivity;
  as_context.surface.roughness = surface.roughness;
  as_context.surface.specular_power = surface.specular_power;
  as_context.surface.flags = surface.flags;
}

void Render_Packet::subfn_update_write_vertex_normals(Components::Mesh &mesh) {
  for (size_t i = 0; i < mesh.indicies.size(); i += 3) {
    const uint32_t i0 = mesh.indicies[i], i1 = mesh.indicies[i + 1],
                   i2 = mesh.indicies[i + 2];
    Components::Vertex &v0 = mesh.verticies[i0], v1 = mesh.verticies[i1],
                       v2 = mesh.verticies[i2];
    const Math::vec_f3 e1 = v1.p - v0.p, e2 = v2.p - v0.p,
                       nf = Math::approx_eq(Math::magnitude(e1), 0) ||
                                    Math::approx_eq(Math::magnitude(e2), 0)
                                ? Math::vec_f3{0.0f, 0.0f, 0.0f}
                                : Math::cross(e1, e2);
    v0.n = Math::normalize(v0.n + nf);
    v1.n = Math::normalize(v1.n + nf);
    v2.n = Math::normalize(v2.n + nf);
  }
}

void Render_Packet::subfn_update_build_as(GPU_Context &gpu_context,
                                          AS_Context &as_context,
                                          const Components::Mesh &mesh) {
  as_context.as_built = false;
  as_context.revision = mesh.revision;

  /* Set geometry */
  as_context.buff_verticies = gpu_context.device->newBuffer(
      mesh.verticies.data(), mesh.verticies.size() * sizeof(Components::Vertex),
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

  MTL4::AccelerationStructureTriangleGeometryDescriptor *as_geom_descs[] = {
      as_context.as_geom_desc.get()};
  NS::Array *as_geom_desc_array =
      NS::Array::array(reinterpret_cast<NS::Object **>(as_geom_descs), 1);
  as_context.as_desc->setGeometryDescriptors(as_geom_desc_array);

  /* Build AS */
  if (!gpu_context.ce_as.exists())
    return;

  const MTL::AccelerationStructureSizes sizes =
      gpu_context.device->accelerationStructureSizes(as_context.as_desc.get());

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
}

void Render_Packet::update(GPU_Context &gpu_context,
                           const Components::Transform &transform,
                           Components::Mesh &mesh,
                           const Components::Surface &surface) {
  MTL_Unique<NS::AutoreleasePool> pool_limited =
      NS::AutoreleasePool::alloc()->init();
  AS_Context &as_context = m_as_contexts[gpu_context.slot];

  subfn_update_write_transform(gpu_context.slot, transform);
  subfn_update_write_surface(gpu_context.slot, surface);

  if (build_required(gpu_context.slot, mesh)) {
    subfn_update_write_vertex_normals(mesh);
    subfn_update_build_as(gpu_context, as_context, mesh);
  }
}

bool Render_Packet::build_required(const uint32_t slot,
                                   const Components::Mesh &mesh) const {
  const AS_Context &as_context = m_as_contexts[slot];
  return !as_context.as_built || as_context.revision != mesh.revision;
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
