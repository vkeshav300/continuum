#include "rhi/attachments.hpp"

#include <cmath>
#include <cstring>

/* Allow for small variations in values */
static inline bool approx_eq(const float a, const float b, const float eps) {
  return std::fabs(a - b) < eps;
}

namespace CTNM::Components {

#ifdef __APPLE__

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

void Metal_Attachment::build_blas(
    MTL::Device *device, MTL::AccelerationStructureCommandEncoder *as_cmd_enc,
    const MTL::AxisAlignedBoundingBox &aabb) {
  /* Create bounding box buffer */
  m_aabb = aabb;
  m_aabb_buff = device->newBuffer(sizeof(MTL::AxisAlignedBoundingBox),
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
  m_blas_desc = MTL::PrimitiveAccelerationStructureDescriptor::alloc()->init();

  /* Attach geometry descriptor */
  MTL::AccelerationStructureGeometryDescriptor *geom_descs[] = {geom_desc};
  NS::Array *geom_array = NS::Array::array(
      reinterpret_cast<NS::Object **>(geom_descs),
      1); // blas_desc->setGeometryDescriptors requires NS::Array which can
          // only be composed of NS::Objects, so reinterpret cast is used
  m_blas_desc->setGeometryDescriptors(geom_array);
  m_blas_desc->setUsage(MTL::AccelerationStructureUsageRefit);

  /* Create build scratch buffer */
  MTL::AccelerationStructureSizes sizes =
      device->accelerationStructureSizes(m_blas_desc);

  m_scratch_buff = device->newBuffer(sizes.buildScratchBufferSize,
                                     MTL::ResourceStorageModePrivate);

  /* Create acceleration structure */
  m_blas = device->newAccelerationStructure(m_blas_desc);

  as_cmd_enc->buildAccelerationStructure(m_blas, m_blas_desc, m_scratch_buff,
                                         0);

  geom_desc->release();
};

void Metal_Attachment::refit_blas(
    MTL::Device *device, MTL::AccelerationStructureCommandEncoder *as_cmd_enc) {
  /* Create new geometry descriptor */
  MTL::AccelerationStructureBoundingBoxGeometryDescriptor *geom_desc =
      MTL::AccelerationStructureBoundingBoxGeometryDescriptor::alloc()->init();
  geom_desc->setBoundingBoxBuffer(m_aabb_buff);
  geom_desc->setBoundingBoxCount(1);
  geom_desc->setOpaque(true);

  /* Attach new geometry descriptor */
  MTL::AccelerationStructureGeometryDescriptor *geom_descs[] = {geom_desc};
  NS::Array *geom_array =
      NS::Array::array(reinterpret_cast<NS::Object **>(geom_descs), 1);
  m_blas_desc->setGeometryDescriptors(geom_array);

  /* Refit acceleration structure */
  MTL::AccelerationStructure *blas_new;
  as_cmd_enc->refitAccelerationStructure(m_blas, m_blas_desc, blas_new,
                                         m_scratch_buff, 0);
  if (m_blas)
    m_blas->release();
  m_blas = blas_new;

  geom_desc->release();
}

MTL::AccelerationStructure *Metal_Attachment::get_blas() const {
  return m_blas;
}

bool Metal_Attachment::needs_refit(
    const MTL::AxisAlignedBoundingBox &new_aabb) const {
  /* If the bounding box has changed, object needs refit
   * approx_eq is used to prevent refitting with negligable changes in bounding
   * box size
   * */
  return !(approx_eq(m_aabb.min.x, new_aabb.min.x) &&
           approx_eq(m_aabb.max.x, new_aabb.max.x) &&
           approx_eq(m_aabb.min.y, new_aabb.min.y) &&
           approx_eq(m_aabb.max.y, new_aabb.max.y) &&
           approx_eq(m_aabb.min.z, new_aabb.min.z) &&
           approx_eq(m_aabb.max.z, new_aabb.max.z));
}

Metal_Attachment::~Metal_Attachment() {
  if (m_blas_desc)
    m_blas_desc->release();
}

#endif

} // namespace CTNM::Components
