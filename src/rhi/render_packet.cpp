#include "rhi/render_packet.hpp"
#include "components.hpp"
#include "math_utils.hpp"
#include "rhi/gpu_context.hpp"
#include "rhi/mtl_ptr.hpp"

#include <cmath>
#include <cstring>

#ifdef __APPLE__

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <simd/simd.h>

static inline MTL::AxisAlignedBoundingBox
to_mtl_aabb(const CTNM::Components::Bounding_Box &bbox) {
  MTL::AxisAlignedBoundingBox aabb;
  switch (bbox.style) {
  case CTNM::Components::Bounding_Box_Style::Sphere:
    aabb.min = {-bbox.d, -bbox.d, -bbox.d};
    aabb.max = {bbox.d, bbox.d, bbox.d};
    break;

  default:
    throw std::runtime_error("Invalid bounding box style");
  };

  return aabb;
}

static inline MTL::PackedFloat4x3
to_mtl_transformations_matrix(const CTNM::Components::Transform &transform) {
  /* Create quaternion for rotation
   * Quaternion: (real, imaginary) -> (qw, qv)
   * */
  vector_float3 axis =
      vector_float3{transform.rtn.x, transform.rtn.y, transform.rtn.z};
  axis = approx_eq(simd::length(axis), 0) ? vector_float3{0.0f, 0.0f, 0.0f}
                                          : simd::normalize(axis);
  const float half = 0.5 * transform.rtn.w, qw = std::cosf(half);
  const vector_float3 qv = axis * std::sinf(half);

  /* Convert quaterion into 3x3 rotation matrix (column-major) */
  const float xx = qv.x * qv.x, yy = qv.y * qv.y, zz = qv.z * qv.z,
              xy = qv.x * qv.y, xz = qv.x * qv.z, yz = qv.y * qv.z,
              wx = qw * qv.x, wy = qw * qv.y, wz = qw * qv.z;

  vector_float3 col_0{1.0f - 2.0f * (yy + zz), 2.0f * (xy + wz),
                      2.0f * (xz - wy)},
      col_1{2.0f * (xy - wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz + wx)},
      col_2{2.0f * (xz + wy), 2.0f * (yz - wx), 1.0f - 2.0f * (xx + yy)};

  /* Apply scale */
  col_0 *= transform.scl.x;
  col_1 *= transform.scl.y;
  col_2 *= transform.scl.z;

  /* Convert to packed float matrix (add translation column) */
  const MTL::PackedFloat3 p_col_0{col_0.x, col_0.y, col_0.z},
      p_col_1{col_1.x, col_1.y, col_1.z}, p_col_2{col_2.x, col_2.y, col_2.z},
      p_col_3{transform.pos.x, transform.pos.y, transform.pos.z};

  return MTL::PackedFloat4x3{p_col_0, p_col_1, p_col_2, p_col_3};
}

namespace CTNM::RHI {

Render_Packet::~Render_Packet() = default;

Render_Packet_AABB::Render_Packet_AABB(
    const GPU_Context &context, const CTNM::Components::Bounding_Box &bbox,
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
    const CTNM::Components::Bounding_Box &bbox) {
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
    const CTNM::Components::Bounding_Box &bbox_new) const {
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
                               const CTNM::Components::Bounding_Box &bbox) {
  create_blas_desc(bbox);
  MTL_Ptr<MTL::AccelerationStructure> blas_new = nullptr;
  context.as_cmd_enc->refitAccelerationStructure(
      m_blas.get(), m_blas_desc.get(), blas_new.get(), m_scratch_buff.get(), 0);

  m_blas->release();
  m_blas = blas_new;
}

void Render_Packet_AABB::smart_update(
    const GPU_Context &context, const CTNM::Components::Bounding_Box &bbox,
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
