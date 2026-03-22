#pragma once

#ifndef __METAL_VERSION__

#include <cstdint>

#include <Metal/Metal.hpp>

#endif

namespace CTNM::RHI::GPU_Types {

#ifdef __METAL_VERSION__

using vec_pf3 = packed_float3;

struct Present_Vertex_Out {
  float4 p [[position]];
  float2 uv;
};

#else

using vec_pf3 = MTL::PackedFloat3;

#endif

struct Raytracing_Config {
  uint32_t has_scene, max_bounces, emissive_count;
  float ambient_intensity, t_min, t_max, shadow_bias;
  vec_pf3 color_bkg, color_ambient;
};

struct Camera {
  vec_pf3 p, dir;
  float fl; // Focal length
};

struct Surface {
  vec_pf3 color, albedo;
  float ambient, emission_strength, reflectivity, roughness, specular_power;
  uint32_t flags;
};

struct Emissive_Data {
  uint32_t instance_id; // Used to index surface buffer
  vec_pf3 p_ws;         // Position (world space)
};

} // namespace CTNM::RHI::GPU_Types
