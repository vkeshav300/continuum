#include "math_utils.hpp"

#include <cmath>
#include <limits>

/**
 * @brief Checks whether two float values are equal within the precision of a single-precision float.
 *
 * Compares the absolute difference of the values against the smallest representable difference for `float`.
 *
 * @param a First value to compare.
 * @param b Second value to compare.
 * @return `true` if the absolute difference between `a` and `b` is less than the single-precision float epsilon, `false` otherwise.
 */
bool approx_eq(const float a, const float b) {
  return std::fabs(a - b) < std::numeric_limits<float>::epsilon();
}

#ifdef __APPLE__

/**
 * @brief Computes the Euclidean length of a 3-component float vector.
 *
 * @param vec 3-component float vector to measure.
 * @return float Euclidean length (magnitude) of the vector.
 */
float magnitude(const vec_f3 &vec) { return simd_length(vec); }

/**
 * @brief Computes the Euclidean length of a 4-component vector.
 *
 * @param vec Input 4-component vector.
 * @return float The Euclidean magnitude (length) of `vec`.
 */
float magnitude(const vec_f4 &vec) { return simd_length(vec); }

/**
 * @brief Produces a unit-length vector pointing in the same direction as vec.
 *
 * @param vec Vector to normalize.
 * @return vec_f3 Vector with length equal to 1 pointing in the same direction as `vec`.
 */
vec_f3 normalize(const vec_f3 &vec) { return simd_normalize(vec); }

/**
 * @brief Normalize a 4-component vector to unit length.
 *
 * @param vec Vector to normalize.
 * @return vec_f4 Unit-length vector pointing in the same direction as `vec` when `vec` has non-zero length.
 */
vec_f4 normalize(const vec_f4 &vec) { return simd_normalize(vec); }

#endif
