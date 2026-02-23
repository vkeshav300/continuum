#include "rhi/render_packet.hpp"
#include "components.hpp"

#include <Metal/Metal.hpp>
#include <simd/simd.h>

namespace CTNM::RHI {

static inline MTL::PackedFloat4x3
get_mtl_transform(const CTNM::Components::Transform &transform) {
  vector_float3 axis =
      vector_float3{transform.r.x, transform.r.y, transform.r.z};
  const bool degenerate_axis = approx_eq(simd::length(axis), 0.0f);
  if (!degenerate_axis)
    axis = simd::normalize(axis);

  const float angle = degenerate_axis ? 0.0f : transform.r.w;
  const vector_float3 safe_axis =
      degenerate_axis ? vector_float3{1.0f, 0.0f, 0.0f} : axis;

  const simd_quatf quat = simd_quaternion(angle, safe_axis);
  matrix_float3x3 rotation = simd_matrix3x3(quat);

  rotation.columns[0] *= transform.s.x;
  rotation.columns[1] *= transform.s.y;
  rotation.columns[2] *= transform.s.z;

  const MTL::PackedFloat3 p_col_0{rotation.columns[0].x, rotation.columns[0].y,
                                  rotation.columns[0].z},
      p_col_1{rotation.columns[1].x, rotation.columns[1].y,
              rotation.columns[1].z},
      p_col_2{rotation.columns[2].x, rotation.columns[2].y,
              rotation.columns[2].z},
      p_col_3{transform.p.x, transform.p.y, transform.p.z};

  return MTL::PackedFloat4x3{p_col_0, p_col_1, p_col_2, p_col_3};
}

Render_Packet::Render_Packet(const Components::Transform &transform)
    : m_transform(get_mtl_transform(transform)) {}

void Render_Packet::update(const Components::Transform &transform) {
  m_transform = get_mtl_transform(transform);
}

} // namespace CTNM::RHI
