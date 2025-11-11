#pragma once

#include "vectors.h"

struct Transform {
  vec_f3 position;
};

struct Bounding_Box {
  vec_f3 min;
  vec_f3 max;
};
