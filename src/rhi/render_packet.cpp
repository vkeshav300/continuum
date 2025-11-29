#include "rhi/render_packet.hpp"
#include "components.hpp"
#include "math_utils.hpp"
#include "rhi/gpu_context.hpp"
#include "rhi/mtl_ptr.hpp"

#include <cstring>

#ifdef __APPLE__

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <simd/simd.h>

static inline MTL::AxisAlignedBoundingBox
to_mtl_aabb(const CTNM::Components::Sphere_AABB &bbox) {
  MTL::AxisAlignedBoundingBox aabb;
  aabb.min = {-bbox.r, -bbox.r, -bbox.r};
  aabb.max = {bbox.r, bbox.r, bbox.r};

  return aabb;
}

static inline MTL::PackedFloat4x3
to_mtl_transformations_matrix(const CTNM::Components::Transform &transform) {
  vector_float3 axis =
      vector_float3{transform.rtn.x, transform.rtn.y, transform.rtn.z};
  const bool degenerate_axis = approx_eq(simd::length(axis), 0.0f);
  if (!degenerate_axis)
    axis = simd::normalize(axis);

  const float angle = degenerate_axis ? 0.0f : transform.rtn.w;
  const vector_float3 safe_axis =
      degenerate_axis ? vector_float3{1.0f, 0.0f, 0.0f} : axis;

  simd_quatf quat = simd_quaternion(angle, safe_axis);
  matrix_float3x3 rotation = simd_matrix3x3(quat);

  rotation.columns[0] *= transform.scl.x;
  rotation.columns[1] *= transform.scl.y;
  rotation.columns[2] *= transform.scl.z;

  const MTL::PackedFloat3 p_col_0{rotation.columns[0].x, rotation.columns[0].y,
                                  rotation.columns[0].z},
      p_col_1{rotation.columns[1].x, rotation.columns[1].y,
              rotation.columns[1].z},
      p_col_2{rotation.columns[2].x, rotation.columns[2].y,
              rotation.columns[2].z},
      p_col_3{transform.pos.x, transform.pos.y, transform.pos.z};

  return MTL::PackedFloat4x3{p_col_0, p_col_1, p_col_2, p_col_3};
}

namespace CTNM::RHI {

Render_Packet::~Render_Packet() = default;

Render_Packet_AABB::Render_Packet_AABB(
    const GPU_Context &context, const CTNM::Components::Sphere_AABB &bbox,
    const CTNM::Components::Transform &transform) {
  /* Create bounding box buffer */
  m_aabb_buff = context.device->newBuffer(sizeof(MTL::AxisAlignedBoundingBox),
                                          MTL::ResourceStorageModeShared);

  /* Create build scratch buffer */
  create_blas_desc(bbox);
  MTL::AccelerationStructureSizes sizes =
      context.device->accelerationStructureSizes(m_blas_desc.get());

  m_scratch_buff = context.device->newBuffer(sizes.buildScratchBufferSize,
                                             MTL::ResourceStorageModePrivate);

  /* Create acceleration structure */
  m_blas = context.device->newAccelerationStructure(m_blas_desc.get());

  context.as_cmd_enc->buildAccelerationStructure(
      m_blas.get(), m_blas_desc.get(), m_scratch_buff.get(), 0);

  /* Transformations */
  m_transformations = to_mtl_transformations_matrix(transform);
}

Render_Packet_AABB::~Render_Packet_AABB() {}

const MTL_Ptr<MTL::AccelerationStructure> &Render_Packet_AABB::get_as() const {
  return m_blas;
}

void Render_Packet_AABB::create_blas_desc(
    const CTNM::Components::Sphere_AABB &bbox) {
  m_blas_desc.smart_release();

  /* Create geometry descriptor */
  m_aabb = to_mtl_aabb(bbox);
  std::memcpy(m_aabb_buff->contents(), &m_aabb,
              sizeof(m_aabb)); // Copy aabb to buffer

  MTL_Ptr<MTL::AccelerationStructureBoundingBoxGeometryDescriptor> geom_desc =
      MTL::AccelerationStructureBoundingBoxGeometryDescriptor::alloc()->init();
  geom_desc->setBoundingBoxBuffer(m_aabb_buff.get());
  geom_desc->setBoundingBoxCount(1);
  geom_desc->setOpaque(true);

  MTL::AccelerationStructureGeometryDescriptor *geom_descs[] = {
      geom_desc.get()};
  MTL_Ptr<NS::Array> geom_array = NS::Array::array(
      reinterpret_cast<NS::Object **>(geom_descs),
      1); // m_blas_desc->setGeometryDescriptors requires NS::Array which can
          // only be composed of NS::Objects, so reinterpret cast is used

  /* Create acceleration structure descriptor */
  MTL::PrimitiveAccelerationStructureDescriptor *m_blas_desc =
      MTL::PrimitiveAccelerationStructureDescriptor::alloc()->init();
  m_blas_desc->setGeometryDescriptors(geom_array.get());
  m_blas_desc->setUsage(MTL::AccelerationStructureUsageRefit);
}

bool Render_Packet_AABB::needs_refit(
    const CTNM::Components::Sphere_AABB &bbox_new) const {
  /* If the bounding box has changed, object needs refit
   * approx_eq is used to prevent refitting with negligable changes in
   * bounding box size
   * */
  MTL::AxisAlignedBoundingBox aabb_new = to_mtl_aabb(bbox_new);
  return !(approx_eq(m_aabb.min.x, aabb_new.min.x) &&
           approx_eq(m_aabb.max.x, aabb_new.max.x) &&
           approx_eq(m_aabb.min.y, aabb_new.min.y) &&
           approx_eq(m_aabb.max.y, aabb_new.max.y) &&
           approx_eq(m_aabb.min.z, aabb_new.min.z) &&
           approx_eq(m_aabb.max.z, aabb_new.max.z));
}

void Render_Packet_AABB::refit(const GPU_Context &context,
                               const CTNM::Components::Sphere_AABB &bbox) {
  create_blas_desc(bbox);
  MTL_Ptr<MTL::AccelerationStructure> blas_new = nullptr;
  context.as_cmd_enc->refitAccelerationStructure(
      m_blas.get(), m_blas_desc.get(), blas_new.get(), m_scratch_buff.get(), 0);

  m_blas->release();
  m_blas = blas_new;
}

void Render_Packet_AABB::smart_update(
    const GPU_Context &context, const CTNM::Components::Sphere_AABB &bbox,
    const CTNM::Components::Transform &transform) {
  if (needs_refit(bbox))
    refit(context, bbox);

  update_transformations(transform);
}

void Render_Packet_AABB::update_transformations(
    const CTNM::Components::Transform &transform) {
  m_transformations = to_mtl_transformations_matrix(transform);
}

MTL::PackedFloat4x3 Render_Packet_AABB::get_transformations() const {
  return m_transformations;
}

} // namespace CTNM::RHI

#endif
