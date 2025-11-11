#include "rhi/attachments.hpp"

#include <cstring>

namespace CTNM::Components {

#ifdef __APPLE__

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

void Metal_Attachment::build_blas(
    MTL::Device *device, MTL::AccelerationStructureCommandEncoder *blas_cmd_enc,
    MTL::AxisAlignedBoundingBox &aabb) {
  /* Create bounding box buffer */
  m_aabb_buff = device->newBuffer(sizeof(MTL::AxisAlignedBoundingBox),
                                  MTL::ResourceStorageModeShared);
  std::memcpy(m_aabb_buff->contents(), &aabb,
              sizeof(aabb)); // Copy aabb to buffer

  /* Create geometry descriptor */
  MTL::AccelerationStructureBoundingBoxGeometryDescriptor *geom_desc =
      MTL::AccelerationStructureBoundingBoxGeometryDescriptor::alloc()->init();
  geom_desc->setBoundingBoxBuffer(m_aabb_buff);
  geom_desc->setBoundingBoxCount(1);

  /* Create acceleration structure descriptor */
  m_blas_desc = MTL::PrimitiveAccelerationStructureDescriptor::alloc()->init();

  /* Attach geometry descriptor */
  MTL::AccelerationStructureGeometryDescriptor *geom_descs[] = {geom_desc};
  NS::Array *geom_array = NS::Array::array(
      reinterpret_cast<NS::Object **>(geom_descs),
      1); // blas_desc->setGeometryDescriptors requires NS::Array which can
          // only be composed of NS::Objects, so reinterpret cast is used
  m_blas_desc->setGeometryDescriptors(geom_array);

  /* Create build scratch buffer */
  MTL::AccelerationStructureSizes sizes =
      device->accelerationStructureSizes(m_blas_desc);

  m_scratch_buff = device->newBuffer(sizes.buildScratchBufferSize,
                                     MTL::ResourceStorageModePrivate);

  /* Create acceleration structure */
  m_blas = device->newAccelerationStructure(m_blas_desc);

  blas_cmd_enc->buildAccelerationStructure(m_blas, m_blas_desc, m_scratch_buff,
                                           0);

  geom_desc->release();
};

void Metal_Attachment::refit_blas() {}

MTL::AccelerationStructure *Metal_Attachment::get_blas() const {
  return m_blas;
}

Metal_Attachment::~Metal_Attachment() {
  if (m_blas_desc)
    m_blas_desc->release();
}

#endif

}; // namespace CTNM::Components
