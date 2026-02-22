// #include "rhi/gpu_types.hpp"
// #include <metal_raytracing>
// #include <metal_stdlib>
// 
// using namespace metal;
// using namespace CTNM;
// using namespace RHI;
// using namespace GPU_Types;
// 
// [[intersection(bounding_box, raytracing::instancing)]]
// Sphere_Bounding_Box_Intersection_Result sphere_intersection(
    // vector_float3 origin [[origin]], vector_float3 direction [[direction]],
    // uint primitive_id [[primitive_id]], float min_dist [[min_distance]],
    // float max_dist [[max_distance]],
    // const device Bounding_Box *bounding_boxes [[primitive_data]]) {
  // Sphere_Bounding_Box_Intersection_Result result;
  // (void)primitive_id;
  // (void)bounding_boxes;
// 
  // const vector_float3 center = vector_float3(0.0f, 0.0f, 0.0f);
  // const float r = 1.0f;
  // const vector_float3 oc = origin - center;
// 
  // float a = dot(direction, direction);
  // float b = 2 * dot(oc, direction);
  // float c = dot(oc, oc) - r * r;
  // float disc = b * b - 4 * a * c;
  // if (disc <= 0.0f || a == 0.0f) {
    // result.accept = false;
  // } else {
    // result.dist = (-b - sqrt(disc)) / (2 * a);
    // result.accept = result.dist >= min_dist && result.dist <= max_dist;
  // }
// 
  // return result;
// }
