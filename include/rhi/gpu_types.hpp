#pragma once

#ifndef __METAL_VERSION__

#include "../math_utils.hpp"
#include <simd/simd.h>

#else

#include <metal_stdlib>
using namespace metal;

#endif

/* Nested namespace declarations only added in C++17, but Metal 3 shaders are
 * based off of C++14 */
namespace CTNM {
namespace RHI {
namespace GPU_Types {

struct Camera {
#ifdef __METAL_VERSION__

  packed_float3 pos;
  packed_float3 dir;

#else

  vec_f3 pos;
  vec_f3 dir; // GPU processing is easier with point and direction

#endif
};

struct Bounding_Box {
#ifdef __METAL_VERSION__

  packed_float3 min;
  packed_float3 max;

#else

  vec_f3 min;
  vec_f3 max;

#endif
};

struct Sphere {
#ifdef __METAL_VERSION__

  packed_float3 center;
  float r;

#else

  vec_f3 center;
  float r;

#endif
};

} // namespace GPU_Types
} // namespace RHI
} // namespace CTNM
