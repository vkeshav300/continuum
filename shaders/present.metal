#include "rhi/gpu_types.hpp"
#include <metal_raytracing>
#include <metal_stdlib>

using namespace CTNM;
using namespace RHI;
using namespace GPU_Types;
using namespace metal;

vertex Present_Vertex_Out v_present(uint vid [[vertex_id]]) {
  constexpr float2 p[3] = {float2(-1.0f, -1.0f), float2(3.0f, -1.0f),
                           float2(-1.0f, 3.0f)};
  constexpr float2 uv[3] = {float2(0.0f, 1.0f), float2(2.0f, 1.0f),
                            float2(0.0f, -1.0f)};
  Present_Vertex_Out out;
  out.p = float4(p[vid], 0.0f, 1.0f);
  out.uv = uv[vid];
  return out;
}

fragment float4 f_present(Present_Vertex_Out in [[stage_in]],
                          texture2d<float, access::sample> tex_rt
                          [[texture(0)]]) {
  constexpr sampler s(coord::normalized, address::clamp_to_edge,
                      filter::nearest);
  return tex_rt.sample(s, in.uv);
}
