#pragma once

#include "../components.hpp"
#include "gpu_context.hpp"
#include "gpu_types.hpp"
#include "mtl_ptr.hpp"

#include <entt/entt.hpp>

#ifdef __APPLE__

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <simd/simd.h>

namespace CTNM::RHI {

enum IFN_IDX : NS::UInteger { Sphere = 0 };

class Render_Packet {
public:
  virtual ~Render_Packet() = 0;

  const virtual MTL_Ptr<MTL::AccelerationStructure> &get_as() const = 0;
  const virtual NS::UInteger get_ifn_idx() const = 0;

  virtual void smart_update(const GPU_Context &context,
                            const CTNM::Components::AABB &bbox,
                            const CTNM::Components::Transform &transform,
                            const CTNM::Components::Surface &surface) = 0;

  virtual bool needs_refit(const CTNM::Components::AABB &bbox) const = 0;
  virtual void refit(const GPU_Context &context,
                     const CTNM::Components::AABB &bbox) = 0;

  virtual void
  update_transformations(const CTNM::Components::Transform &transform) = 0;
  virtual MTL::PackedFloat4x3 get_transformations() const = 0;

  virtual void update_surface(const CTNM::Components::Surface &surface) = 0;
  virtual const GPU_Types::Surface &get_surface() const = 0;
};

class Render_Packet_AABB : public Render_Packet {
private:
  MTL::AxisAlignedBoundingBox m_aabb;
  MTL_Ptr<MTL::PrimitiveAccelerationStructureDescriptor> m_blas_desc = nullptr;
  MTL_Ptr<MTL::AccelerationStructure> m_blas = nullptr;
  MTL_Ptr<MTL::Buffer> m_buff_aabb = nullptr;
  MTL_Ptr<MTL::Buffer> m_buff_scratch = nullptr;

  MTL::PackedFloat4x3 m_transformations;
  NS::UInteger m_ifn_idx;
  GPU_Types::Surface m_surface;

  void create_blas_desc(const CTNM::Components::AABB &bbox);

public:
  Render_Packet_AABB(const GPU_Context &context,
                     const CTNM::Components::AABB &bbox,
                     const CTNM::Components::Transform &transform,
                     const CTNM::Components::Surface &surface);
  ~Render_Packet_AABB();

  const MTL_Ptr<MTL::AccelerationStructure> &get_as() const override;
  const NS::UInteger get_ifn_idx() const override;

  void smart_update(const GPU_Context &context,
                    const CTNM::Components::AABB &bbox,
                    const CTNM::Components::Transform &transform,
                    const CTNM::Components::Surface &surface) override;

  bool needs_refit(const CTNM::Components::AABB &bbox) const override;
  void refit(const GPU_Context &context,
             const CTNM::Components::AABB &bbox) override;

  void
  update_transformations(const CTNM::Components::Transform &transform) override;
  MTL::PackedFloat4x3 get_transformations() const override;

  void update_surface(const CTNM::Components::Surface &surface) override;
  const GPU_Types::Surface &get_surface() const override;
};

} // namespace CTNM::RHI

#endif
