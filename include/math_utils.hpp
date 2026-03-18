#pragma once

#include <algorithm>
#include <cmath>

#include <simd/simd.h>

namespace CTNM::Math {

using vec_f3 = simd::float3;
using vec_f4 = simd::float4;

inline bool approx_eq(const float a, const float b) {
  constexpr float abs_tol = 1e-6f;
  constexpr float rel_tol = 1e-5f;
  const float diff = std::fabs(a - b);
  const float tolerance =
      std::max(abs_tol, rel_tol * std::max(std::fabs(a), std::fabs(b)));
  return diff <= tolerance;
}

inline float magnitude(const vec_f3 &vec) { return simd_length(vec); }

inline float magnitude(const vec_f4 &vec) { return simd_length(vec); }

inline vec_f3 normalize(const vec_f3 &vec) { return simd_normalize(vec); }

inline vec_f4 normalize(const vec_f4 &vec) { return simd_normalize(vec); }

} // namespace CTNM::Math
