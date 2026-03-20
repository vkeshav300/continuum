#pragma once

#define ATTR_OVERLOADABLE __attribute__((__overloadable__))

#include <algorithm>
#include <cmath>

#include <simd/simd.h>

namespace CTNM::Math {

using vec_f2 = simd::float2;
using vec_f3 = simd::float3;
using vec_f4 = simd::float4;

ATTR_OVERLOADABLE inline bool approx_eq(const float a, const float b) {
  constexpr float abs_tol = 1e-6f;
  constexpr float rel_tol = 1e-5f;
  const float diff = std::fabs(a - b);
  const float tolerance =
      std::max(abs_tol, rel_tol * std::max(std::fabs(a), std::fabs(b)));
  return diff <= tolerance;
}

template <typename T> ATTR_OVERLOADABLE inline float magnitude(const T &v) {
  return simd_length(v);
}

template <typename T> ATTR_OVERLOADABLE inline T normalize(const T &v) {
  return simd_normalize(v);
}

ATTR_OVERLOADABLE inline vec_f3 cross(const vec_f3 &v1, const vec_f3 &v2) {
  return simd_cross(v1, v2);
}

} // namespace CTNM::Math
