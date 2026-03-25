#include "rhi/gpu_types.hpp"

#include <metal_raytracing>
#include <metal_stdlib>

using namespace metal;

[[kernel]] void k_raytracer(
    constant CTNM::RHI::GPU_Types::Raytracing_Config &config [[buffer(0)]],
    constant CTNM::RHI::GPU_Types::Camera &cam [[buffer(1)]],
    raytracing::instance_acceleration_structure tlas [[buffer(2)]],
    constant CTNM::RHI::GPU_Types::Lookup *lookups [[buffer(3)]],
    constant CTNM::RHI::GPU_Types::Vertex *verticies [[buffer(4)]],
    constant uint *indicies [[buffer(5)]],
    constant CTNM::RHI::GPU_Types::Surface *surfaces [[buffer(6)]],
    constant CTNM::RHI::GPU_Types::Emissive_Data *emissives [[buffer(7)]],
    texture2d<float, access::write> out_tex [[texture(0)]],
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
  ray.min_distance = config.t_min;
  ray.max_distance = config.t_max;

  raytracing::intersector<raytracing::instancing> intersector;
  const raytracing::intersection_result<raytracing::instancing> result =
      intersector.intersect(ray, tlas);
  float3 color = config.color_bkg;

  if (result.type == raytracing::intersection_type::triangle) {
    const uint iid = result.instance_id;
    // const float t = result.distance;

    color = surfaces[iid].color;
  }

  out_tex.write(float4(color, 1.0f), tid);
}
