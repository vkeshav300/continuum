#pragma once

#include "math_utils.hpp"

namespace CTNM::Components {

struct Transform {
  vec_f3 p = {0.0f, 0.0f, 0.0f};       // Position
  vec_f3 s = {1.0f, 1.0f, 1.0f};       // Scale
  vec_f4 r = {0.0f, 0.0f, 0.0f, 0.0f}; // Rotation
  vec_f3 v = {0.0f, 0.0f, 0.0f};       // Velocity
};

struct Sphere_AABB {
  float r = 1.0f;
};

struct Camera {
  vec_f3 pos = {-5.0f, 0.0f, 0.0f};
  vec_f3 fpos = {0.0f, 0.0f, 0.0f}; // Point to focus camera at
  float fov = 120.0f;
};

} // namespace CTNM::Components
