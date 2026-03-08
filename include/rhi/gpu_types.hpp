#pragma once

#ifndef __METAL_VERSION__

#include <cstdint>

#include <Metal/Metal.hpp>

#endif

namespace CTNM::RHI::GPU_Types {

struct Raytracing_Params {
  uint32_t has_scene;
};

#ifdef __METAL_VERSION__

using gpu_vec_pf3 = packed_float3;

struct Present_Vertex_Out {
  float4 p [[position]];
  float2 uv;
};

struct Intersection_Result {
  bool accept [[accept_intersection]];
  float d [[distance]];
};

struct AABB {
  gpu_vec_pf3 min;
  gpu_vec_pf3 max;
};

struct Camera {
  gpu_vec_pf3 p;
  gpu_vec_pf3 dir;
  float fl;
};

#else

struct Camera {
  MTL::PackedFloat3 p;
  MTL::PackedFloat3 dir;
  float fl; // Focal length
};

#endif

} // namespace CTNM::RHI::GPU_Types
