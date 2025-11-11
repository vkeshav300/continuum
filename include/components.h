#pragma once

#include "vectors.h"

struct Transform {
  vec_f3 position;
};

struct Sphere_Bounding_Box {
  vec_f3 min;
  vec_f3 max;
};
