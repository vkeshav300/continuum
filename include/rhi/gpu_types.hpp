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

  vector_float3 p;
  vector_float3 dir;
  float fl;

#else

  vec_f3 p;
  vec_f3 dir; // GPU processing is easier with point and direction
  float fl;   // Focal length

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

  vector_float3 center;
  float r;

#else

  vec_f3 center;
  float r;

#endif
};

struct Surface {
#ifdef __METAL_VERSION__

  vector_float3 c;

#else

  color c;

#endif
};

#ifdef __METAL_VERSION__

struct Sphere_Bounding_Box_Intersection_Result {
  bool accept [[accept_intersection]];
  float dist [[distance]];
};

struct Ray_Payload {
  vector_float3 color;
};

struct Present_Varyings {
  vector_float4 p [[position]];
  vector_float2 uv;
};

#endif

} // namespace GPU_Types
} // namespace RHI
} // namespace CTNM
