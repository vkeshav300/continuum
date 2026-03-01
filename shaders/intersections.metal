#include "rhi/gpu_types.hpp"

#include <metal_raytracing>
#include <metal_stdlib>

using namespace metal;
using namespace CTNM::RHI::GPU_Types;

[[intersection(bounding_box, raytracing::instancing)]]
Intersection_Result i_sphere(float3 origin [[origin]], float3 dir [[direction]],
                             uint primitive_id [[primitive_id]],
                             float dist_min [[min_distance]],
                             float dist_max [[max_distance]],
                             const device AABB *bboxes [[primitive_data]]) {
  Intersection_Result result;
  result.accept = false;
  result.d = dist_max;

  const AABB bbox = bboxes[primitive_id];
  const float3 center = 0.5f * (bbox.min + bbox.max), oc = origin - center,
               half_extent = 0.5f * (bbox.max - bbox.min);
  const float r = half_extent.x, a = dot(dir, dir),
              b = 2.0f * dot(oc, dir), c = dot(oc, oc) - r * r,
              disc = b * b - 4.0f * a * c;
  if (disc >= 0.0f && a != 0.0f) {
    const float t = (-b - sqrt(disc)) / (2.0f * a);
    result.d = t;
    result.accept = t >= dist_min && t <= dist_max;
  }

  return result;
}
