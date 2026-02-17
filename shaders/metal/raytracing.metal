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
  float4 pos [[position]];
  float2 uv;
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

  float3 color = float3(0.0f, 0.0f, 0.0f);
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

  /* Factor in focal length (FOV) */
  const float focal = cam.fl;
  const float3 ray_dir =
      normalize(ndc.x * right + ndc.y * up + focal * forward);

  raytracing::ray ray;
  ray.origin = float3(cam.pos);
  ray.direction = ray_dir;
  ray.min_distance = 0.01f;
  ray.max_distance = 1000.0f;

  if (has_scene != 0u) {
    raytracing::intersector<raytracing::instancing> intersector;
    intersector.assume_geometry_type(raytracing::geometry_type::bounding_box);
    const raytracing::intersection_result<raytracing::instancing> hit =
        intersector.intersect(ray, as, ift);

    if (hit.type != raytracing::intersection_type::none)
      color = float3(1.0f, 0.8f, 0.3f);
  }

  out_tex.write(float4(color, 1.0f), tid);
}

/*
 * Current system uses a raytracing kernel which outputs a texture.
 * v_present renders a fullscreen triangle which covers the screen.
 * f_present sets the texture of the triangle to the raytraced-renderd output.
 */
vertex Present_Varyings v_present(uint vid [[vertex_id]]) {
  constexpr float2 pos[3] = {float2(-1.0f, -1.0f), float2(3.0f, -1.0f),
                             float2(-1.0f, 3.0f)};
  constexpr float2 uv[3] = {float2(0.0f, 1.0f), float2(2.0f, 1.0f),
                            float2(0.0f, -1.0f)};
  Present_Varyings out;
  out.pos = float4(pos[vid], 0.0f, 1.0f);
  out.uv = uv[vid];
  return out;
}

fragment float4 f_present(Present_Varyings in [[stage_in]],
                          texture2d<float, access::sample> src_tex
                          [[texture(0)]]) {
  constexpr sampler s(coord::normalized, address::clamp_to_edge,
                      filter::nearest);
  return src_tex.sample(s, in.uv);
}

// [[kernel]]
// void raytracer(raytracing::primitive_acceleration_structure as [[buffer(0)]],
// uint2 tid [[thread_position_in_grid]]) {
// /* Generate ray */
// raytracing::ray ray = generate_ray(tid);
//
// /* Generate intersector */
// raytracing::intersector<> intersector;
//
// /* Intersect */
// raytracing::intersection_result<> intersection = intersector.intersect(ray,
// as);
// }
