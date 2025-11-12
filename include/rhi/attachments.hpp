#pragma once

/**
 * Attachments are rendering-api specific information which are associated with
 * entities
 */

#ifdef __APPLE__

#include <Metal/Metal.hpp>

static inline bool approx_eq(const float a, const float b,
                             const float eps = 1e-4f);

namespace CTNM::Components {

struct Metal_Attachment {
  MTL::AccelerationStructure *m_blas = nullptr;
  MTL::AxisAlignedBoundingBox m_aabb;
  MTL::Buffer *m_aabb_buff = nullptr;
  MTL::PrimitiveAccelerationStructureDescriptor *m_blas_desc = nullptr;
  MTL::Buffer *m_scratch_buff = nullptr;
  bool m_refit_required = false;

  void build_blas(MTL::Device *device,
                  MTL::AccelerationStructureCommandEncoder *as_cmd_enc,
                  const MTL::AxisAlignedBoundingBox &aabb);
  void refit_blas(MTL::Device *device,
                  MTL::AccelerationStructureCommandEncoder *as_cmd_enc);

  MTL::AccelerationStructure *get_blas() const;
  bool needs_refit(const MTL::AxisAlignedBoundingBox &new_aabb) const;

  ~Metal_Attachment();
};

}; // namespace CTNM::Components

#endif
