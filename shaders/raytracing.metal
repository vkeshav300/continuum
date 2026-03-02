#include "rhi/gpu_types.hpp"

#include <metal_raytracing>
#include <metal_stdlib>

using namespace metal;
using namespace CTNM::RHI::GPU_Types;

kernel void
k_raytracer(constant Raytracing_Params &config [[buffer(0)]],
            constant Camera &cam [[buffer(1)]],
            raytracing::intersection_function_table<raytracing::instancing> ift
            [[buffer(2)]],
            raytracing::instance_acceleration_structure tlas [[buffer(3)]],
            texture2d<float, access::write> out_tex [[texture(0)]],
            uint2 tid [[thread_position_in_grid]]) {
  /* Ensure thread is inside rendered area */
  if (tid.x >= out_tex.get_width() || tid.y >= out_tex.get_height())
    return;

  float3 color = float3(0.0f, 0.0f, 0.0f); // Void = black by default
  const float2 uv =
      (float2(tid) + 0.5f) / float2(out_tex.get_width(), out_tex.get_height());
  float2 ndc = float2(uv.x * 2.0f - 1.0f, 1.0f - uv.y * 2.0f);
  const float aspect = float(out_tex.get_width()) / float(out_tex.get_height());
  ndc.x *= aspect;

  /* Factor in camera direction */
  float3 forward = normalize(float3(cam.dir));
  if (all(forward == float3(0.0f)))
    forward = float3(0.0f, 0.0f, 1.0f);

  float3 world_up = float3(0.0f, 1.0f, 0.0f);
  if (fabs(dot(forward, world_up)) > 0.999f)
    world_up = float3(1.0f, 0.0f, 0.0f);

  float3 right = normalize(cross(forward, world_up));
  float3 up = normalize(cross(right, forward));

  /* Factor in focal length (responsible for FOV) */
  const float focal = cam.fl;
  const float3 ray_dir =
      normalize(ndc.x * right + ndc.y * up + focal * forward);

  raytracing::ray ray;
  ray.origin = float3(cam.p);
  ray.direction = ray_dir;
  ray.min_distance = 0.01f;
  ray.max_distance = 1000.0f;

  if (config.has_scene == false) { // No renderable objects
    out_tex.write(float4(color, 1.0f), tid);
    return;
  }

  raytracing::intersector<raytracing::instancing> intersector;
  intersector.assume_geometry_type(raytracing::geometry_type::bounding_box);
  const raytracing::intersection_result<raytracing::instancing> hit =
      intersector.intersect(ray, tlas, ift);

  if (hit.type == raytracing::intersection_type::none) {
    out_tex.write(float4(color, 1.0f), tid);
    return;
  }

  color = float3(255.0f, 0.0f, 0.0f);
  // const uint iid = hit.instance_id;
  // color = surfaces[iid].c;

  out_tex.write(float4(color, 1.0f), tid);
}
