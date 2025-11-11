#pragma once

/**
 * Attachments are rendering-api specific information which are associated with
 * entities
 */

#ifdef __APPLE__

#include <Metal/Metal.hpp>

namespace CTNM::Components {

struct Metal_Attachment {
  MTL::AccelerationStructure *m_blas = nullptr;
  MTL::Buffer *m_aabb_buff = nullptr;
  MTL::PrimitiveAccelerationStructureDescriptor *m_blas_desc = nullptr;
  MTL::Buffer *m_scratch_buff = nullptr;
  bool m_refit_required = false;

  void build_blas(MTL::Device *device,
                  MTL::AccelerationStructureCommandEncoder *blas_cmd_enc,
                  MTL::AxisAlignedBoundingBox &aabb);
  void refit_blas();

  MTL::AccelerationStructure *get_blas() const;

  ~Metal_Attachment();
};

}; // namespace CTNM::Components

#endif
