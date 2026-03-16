#include "rhi/gpu_types.hpp"

#include <metal_raytracing>
#include <metal_stdlib>

using namespace metal;
using namespace CTNM::RHI::GPU_Types;

[[kernel]] void k_raytracer(constant Raytracing_Params &config [[buffer(0)]],
                            constant Camera &cam [[buffer(1)]],
                            raytracing::instance_acceleration_structure tlas
                            [[buffer(2)]],
                            texture2d<float, access::write> out_tex
                            [[texture(0)]],
                            uint2 tid [[thread_position_in_grid]]) {
  /* Ensure thread is inside rendered area */
  if (tid.x >= out_tex.get_width() || tid.y >= out_tex.get_height())
    return;

  const float2 size = float2(out_tex.get_width(), out_tex.get_height()),
               uv = (float2(tid) + 0.5f) / size, ndc = uv * 2.0f - 1.0f;
  const float aspect = size.x / size.y;
  const float2 film = float2(ndc.x * aspect * 0.5f, -ndc.y * 0.5f);
  const float3 forward = normalize(float3(cam.dir)),
               world_up = abs(forward.y) > 0.999f ? float3(0.0f, 0.0f, 1.0f)
                                                  : float3(0.0f, 1.0f, 0.0f),
               right = normalize(cross(world_up, forward)),
               up = cross(forward, right);

  raytracing::ray ray;
  ray.origin = float3(cam.p);
  ray.direction = normalize(forward * cam.fl + right * film.x + up * film.y);
  ray.min_distance = 0.01f;
  ray.max_distance = 1000.0f;

  raytracing::intersector<raytracing::instancing> intersector;
  const raytracing::intersection_result<raytracing::instancing> result =
      intersector.intersect(ray, tlas);
  float3 color = float3(0.0f);

  if (result.type == raytracing::intersection_type::triangle) {
    color = float3(1.0f, 0.0f, 0.0f);
  }

  out_tex.write(float4(color, 1.0f), tid);
}
