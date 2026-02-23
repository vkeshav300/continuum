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

fragment float4 f_present(Present_Vertex_Out in [[stage_in]]) {
  const float2 uv = clamp(in.uv, float2(0.0f), float2(1.0f));
  return float4(uv.x, uv.y, 0.25f + 0.5f * uv.x, 1.0f);
}
