#include "rhi/render_packet.hpp"
#include "dtypes/components.h"
#include "rhi/gpu_context.hpp"

#include <cmath>
#include <cstring>

/* Allow for small variations in values */
static inline bool approx_eq(const float a, const float b, const float eps) {
  return std::fabs(a - b) < eps;
}

#ifdef __APPLE__

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

namespace CTNM::RHI {

Render_Packet::~Render_Packet() = default;

Render_Packet_AABB::Render_Packet_AABB(
    const GPU_Context &context, const CTNM::Components::Bounding_Box &bbox) {
  /* Create bounding box buffer */
  m_aabb = to_mtl_aabb(bbox);
  m_aabb_buff = context.device->newBuffer(sizeof(MTL::AxisAlignedBoundingBox),
                                          MTL::ResourceStorageModeShared);
  std::memcpy(m_aabb_buff->contents(), &m_aabb,
              sizeof(m_aabb)); // Copy aabb to buffer

  /* Create geometry descriptor */
  MTL::AccelerationStructureBoundingBoxGeometryDescriptor *geom_desc =
      MTL::AccelerationStructureBoundingBoxGeometryDescriptor::alloc()->init();
  geom_desc->setBoundingBoxBuffer(m_aabb_buff);
  geom_desc->setBoundingBoxCount(1);
  geom_desc->setOpaque(true);

  /* Create acceleration structure descriptor */
  MTL::PrimitiveAccelerationStructureDescriptor *blas_desc =
      MTL::PrimitiveAccelerationStructureDescriptor::alloc()->init();

  /* Attach geometry descriptor */
  MTL::AccelerationStructureGeometryDescriptor *geom_descs[] = {geom_desc};
  NS::Array *geom_array = NS::Array::array(
      reinterpret_cast<NS::Object **>(geom_descs),
      1); // blas_desc->setGeometryDescriptors requires NS::Array which can
          // only be composed of NS::Objects, so reinterpret cast is used
  blas_desc->setGeometryDescriptors(geom_array);
  blas_desc->setUsage(MTL::AccelerationStructureUsageRefit);

  /* Create build scratch buffer */
  MTL::AccelerationStructureSizes sizes =
      context.device->accelerationStructureSizes(blas_desc);

  m_scratch_buff = context.device->newBuffer(sizes.buildScratchBufferSize,
                                             MTL::ResourceStorageModePrivate);

  /* Create acceleration structure */
  m_blas = context.device->newAccelerationStructure(blas_desc);

  context.as_cmd_enc->buildAccelerationStructure(m_blas, blas_desc,
                                                 m_scratch_buff, 0);

  geom_desc->release();
}

MTL::AxisAlignedBoundingBox Render_Packet_AABB::to_mtl_aabb(
    const CTNM::Components::Bounding_Box &bbox) const {
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

bool Render_Packet_AABB::needs_refit(
    const CTNM::Components::Bounding_Box &bbox_new) const {
  /* If the bounding box has changed, object needs refit
   * approx_eq is used to prevent refitting with negligable changes in bounding
   * box size
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
  /* Create bounding box buffer */
  m_aabb = to_mtl_aabb(bbox);
  m_aabb_buff = context.device->newBuffer(sizeof(MTL::AxisAlignedBoundingBox),
                                          MTL::ResourceStorageModeShared);
  std::memcpy(m_aabb_buff->contents(), &m_aabb,
              sizeof(m_aabb)); // Copy aabb to buffer

  /* Create geometry descriptor */
  MTL::AccelerationStructureBoundingBoxGeometryDescriptor *geom_desc =
      MTL::AccelerationStructureBoundingBoxGeometryDescriptor::alloc()->init();
  geom_desc->setBoundingBoxBuffer(m_aabb_buff);
  geom_desc->setBoundingBoxCount(1);
  geom_desc->setOpaque(true);

  /* Create acceleration structure descriptor */
  MTL::PrimitiveAccelerationStructureDescriptor *blas_desc =
      MTL::PrimitiveAccelerationStructureDescriptor::alloc()->init();

  /* Attach geometry descriptor */
  MTL::AccelerationStructureGeometryDescriptor *geom_descs[] = {geom_desc};
  NS::Array *geom_array = NS::Array::array(
      reinterpret_cast<NS::Object **>(geom_descs),
      1); // blas_desc->setGeometryDescriptors requires NS::Array which can
          // only be composed of NS::Objects, so reinterpret cast is used
  blas_desc->setGeometryDescriptors(geom_array);
  blas_desc->setUsage(MTL::AccelerationStructureUsageRefit);

  /* Refit acceleration structure */
  MTL::AccelerationStructure *blas_new;
  context.as_cmd_enc->refitAccelerationStructure(m_blas, blas_desc, blas_new,
                                                 m_scratch_buff, 0);
  m_blas = blas_new;

  geom_desc->release();
}

void Render_Packet_AABB::smart_refit(
    const GPU_Context &context, const CTNM::Components::Bounding_Box &bbox) {
  if (needs_refit(bbox))
    refit(context, bbox);
}

} // namespace CTNM::RHI

#endif
