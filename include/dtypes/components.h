#pragma once

#include "vectors.h"

#include <cstdint>

namespace CTNM::Components {

struct Transform {
  vec_f3 pos; // Position
  vec_f3 scl; // Scale
  vec_f4 rtn; // Rotation
};

enum Bounding_Box_Style : uint8_t { Sphere = 0 };

struct Bounding_Box {
  float d;
  uint8_t style;
};

} // namespace CTNM::Components
