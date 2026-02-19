#include "rhi/gpu_types.hpp"
#include <metal_raytracing>
#include <metal_stdlib>

using namespace CTNM;
using namespace RHI;
using namespace GPU_Types;
using namespace metal;

struct Ray_Payload {
  vector_float3 color;
};

struct Present_Varyings {
  vector_float4 pos [[position]];
  vector_float2 uv;
};

kernel void
k_raytracer(raytracing::instance_acceleration_structure as [[buffer(0)]],
            constant Camera &cam [[buffer(1)]],
            constant uint &has_scene [[buffer(2)]],
            raytracing::intersection_function_table<raytracing::instancing> ift
            [[buffer(3)]],
            texture2d<float, access::write> out_tex [[texture(0)]],
            uint2 tid [[thread_position_in_grid]]) {
  /* Ensure thread is inside rendered area */
  if (tid.x >= out_tex.get_width() || tid.y >= out_tex.get_height())
    return;

  vector_float3 color =
      vector_float3(0.0f, 0.0f, 0.0f); // Void = black by default
  const vector_float2 uv =
      (vector_float2(tid) + 0.5f) /
      vector_float2(out_tex.get_width(), out_tex.get_height());
  vector_float2 ndc = vector_float2(uv.x * 2.0f - 1.0f, 1.0f - uv.y * 2.0f);
  const float aspect = float(out_tex.get_width()) / float(out_tex.get_height());
  ndc.x *= aspect;

  /* Factor in camera direction */
  vector_float3 forward = normalize(vector_float3(cam.dir));
  if (all(forward == vector_float3(0.0f)))
    forward = vector_float3(0.0f, 0.0f, 1.0f);

  vector_float3 world_up = vector_float3(0.0f, 1.0f, 0.0f);
  if (fabs(dot(forward, world_up)) > 0.999f)
    world_up = vector_float3(1.0f, 0.0f, 0.0f);

  vector_float3 right = normalize(cross(forward, world_up));
  vector_float3 up = normalize(cross(right, forward));

  /* Factor in focal length (responsible for FOV) */
  const float focal = cam.fl;
  const vector_float3 ray_dir =
      normalize(ndc.x * right + ndc.y * up + focal * forward);

  raytracing::ray ray;
  ray.origin = vector_float3(cam.pos);
  ray.direction = ray_dir;
  ray.min_distance = 0.01f;
  ray.max_distance = 1000.0f;

  if (has_scene == 0u) // No renderable objects
    out_tex.write(vector_float4(color, 1.0f), tid);

  raytracing::intersector<raytracing::instancing> intersector;
  intersector.assume_geometry_type(raytracing::geometry_type::bounding_box);
  const raytracing::intersection_result<raytracing::instancing> hit =
      intersector.intersect(ray, as, ift);

  if (hit.type != raytracing::intersection_type::none)
    color = vector_float3(1.0f, 0.8f, 0.3f);

  out_tex.write(vector_float4(color, 1.0f), tid);
}

/*
 * Current system uses a raytracing kernel which outputs a texture.
 * v_present renders a fullscreen triangle which covers the screen.
 * f_present sets the texture of the triangle to the raytraced-renderd output.
 */
vertex Present_Varyings v_present(uint vid [[vertex_id]]) {
  constexpr vector_float2 pos[3] = {vector_float2(-1.0f, -1.0f),
                                    vector_float2(3.0f, -1.0f),
                                    vector_float2(-1.0f, 3.0f)};
  constexpr vector_float2 uv[3] = {vector_float2(0.0f, 1.0f),
                                   vector_float2(2.0f, 1.0f),
                                   vector_float2(0.0f, -1.0f)};
  Present_Varyings out;
  out.pos = vector_float4(pos[vid], 0.0f, 1.0f);
  out.uv = uv[vid];
  return out;
}

fragment vector_float4 f_present(Present_Varyings in [[stage_in]],
                          texture2d<float, access::sample> src_tex
                          [[texture(0)]]) {
  constexpr sampler s(coord::normalized, address::clamp_to_edge,
                      filter::nearest);
  return src_tex.sample(s, in.uv);
}
