#pragma once

#include "vectors.h"

#include <cstdint>

namespace CTNM::Components {

struct Transform {
  vec_f3 pos;
};

enum Bounding_Box_Style : uint8_t { Sphere = 0 };

struct Bounding_Box {
  float d;
  uint8_t style;
};

} // namespace CTNM::Components
