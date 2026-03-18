#pragma once

#include <cmath>
#include <limits>

#include <simd/simd.h>

namespace CTNM::Math {

using vec_f3 = simd::float3;
using vec_f4 = simd::float4;

inline bool approx_eq(const float a, const float b) {
  return std::fabs(a - b) < std::numeric_limits<float>::epsilon();
}

inline float magnitude(const vec_f3 &vec) { return simd_length(vec); }

inline float magnitude(const vec_f4 &vec) { return simd_length(vec); }

inline vec_f3 normalize(const vec_f3 &vec) { return simd_normalize(vec); }

inline vec_f4 normalize(const vec_f4 &vec) { return simd_normalize(vec); }

} // namespace CTNM::Math
