#include "math_utils.hpp"

#include <cmath>
#include <limits>

bool approx_eq(const float a, const float b) {
  return std::fabs(a - b) < std::numeric_limits<float>::epsilon();
}

float magnitude(const vec_f3 &vec) { return simd_length(vec); }

float magnitude(const vec_f4 &vec) { return simd_length(vec); }

vec_f3 normalize(const vec_f3 &vec) { return simd_normalize(vec); }

vec_f4 normalize(const vec_f4 &vec) { return simd_normalize(vec); }
