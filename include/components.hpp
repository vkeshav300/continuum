#pragma once

#include "math_utils.hpp"

namespace CTNM::Components {

struct Transform {
  vec_f3 pos; // Position
  vec_f3 scl; // Scale
  vec_f4 rtn; // Rotation
};

struct Sphere_AABB {
  float r;
};

struct Camera {
  vec_f3 pos;
  vec_f3 fpos; // Point to focus camera at
};

} // namespace CTNM::Components
