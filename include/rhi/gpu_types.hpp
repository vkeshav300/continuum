#pragma once

namespace CTNM::RHI::GPU_Types {

#ifdef __METAL_VERSION__

using gpu_vec_f3 = packed_float3;

struct Present_Vertex_Out {
  float4 p [[position]];
  float2 uv;
};

struct Intersection_Result {
  bool accept [[accept_intersection]];
  float d [[distance]];
};

struct AABB {
  gpu_vec_f3 min;
  gpu_vec_f3 max;
};

#else

#endif

} // namespace CTNM::RHI::GPU_Types
