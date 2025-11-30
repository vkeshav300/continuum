#include <metal_raytracing>
#include <metal_stdlib>

using namespace metal;

struct Ray_Payload {
  vector_float3 color;
};

kernel void k_raytracer(raytracing::primitive_acceleration_structure as
                        [[buffer(0)]],
                        uint2 tid [[thread_position_in_grid]]) {}

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
