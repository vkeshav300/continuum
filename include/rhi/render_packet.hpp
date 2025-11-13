#pragma once

#include "../dtypes/components.h"
#include "gpu_context.hpp"

#include <entt/entt.hpp>

#ifdef __APPLE__

#include <Metal/Metal.hpp>

static inline bool approx_eq(const float a, const float b,
                             const float eps = 1e-4f);

namespace CTNM::RHI {

class Render_Packet {
public:
  virtual ~Render_Packet() = 0;

  virtual bool
  needs_refit(const CTNM::Components::Bounding_Box &bbox) const = 0;
  virtual void refit(const GPU_Context &context,
                     const CTNM::Components::Bounding_Box &bbox) = 0;
  virtual void smart_refit(const GPU_Context &context,
                           const CTNM::Components::Bounding_Box &bbox) = 0;
};

class Render_Packet_AABB : public Render_Packet {
private:
  MTL::AxisAlignedBoundingBox m_aabb;
  MTL::AccelerationStructure *m_blas = nullptr;
  MTL::Buffer *m_aabb_buff = nullptr;
  MTL::Buffer *m_scratch_buff = nullptr;

  MTL::AxisAlignedBoundingBox
  to_mtl_aabb(const CTNM::Components::Bounding_Box &bbox) const;

public:
  Render_Packet_AABB(const GPU_Context &context,
                     const CTNM::Components::Bounding_Box &bbox);

  bool needs_refit(const CTNM::Components::Bounding_Box &bbox) const override;
  void refit(const GPU_Context &context,
             const CTNM::Components::Bounding_Box &bbox) override;
  void smart_refit(const GPU_Context &context,
                   const CTNM::Components::Bounding_Box &bbox) override;
};

} // namespace CTNM::RHI

#endif
