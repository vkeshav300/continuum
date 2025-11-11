#pragma once

#include "vectors.h"

namespace CTNM::Components {

struct Transform {
  vec_f3 position;
};

struct Bounding_Box {
  vec_f3 min;
  vec_f3 max;
};

} // namespace CTNM::Components
