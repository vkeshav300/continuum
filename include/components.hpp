#pragma once

#include "math_utils.hpp"

namespace CTNM::Components {

struct Transform {
  vec_f3 p = {0.0f, 0.0f, 0.0f};       // Position
  vec_f3 s = {1.0f, 1.0f, 1.0f};       // Scale
  vec_f4 r = {0.0f, 0.0f, 0.0f, 0.0f}; // Rotation
};

struct Physics {
  vec_f3 v = {0.0f, 0.0f, 0.0f}; // Velocity
};

struct AABB {
  float r = 1.0f; // Radius
};

struct Surface {
  color c = {0.0f, 0.0f, 255.0f};
};

struct Camera {
  vec_f3 p = {-5.0f, 0.0f, 0.0f}; // Position
  vec_f3 fp = {0.0f, 0.0f, 0.0f}; // Focused position
  float fov = 120.0f;
};

} // namespace CTNM::Components
