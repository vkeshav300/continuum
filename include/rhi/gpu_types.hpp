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

using vec_pf3 = packed_float3;

struct Present_Vertex_Out {
  float4 p [[position]];
  float2 uv;
};

#else

using vec_pf3 = MTL::PackedFloat3;

#endif

struct Camera {
  vec_pf3 p;
  vec_pf3 dir;
  float fl; // Focal length
};

struct Surface {
  vec_pf3 col;
};

} // namespace CTNM::RHI::GPU_Types
