#pragma once

#include "../math_utils.hpp"

namespace CTNM::RHI::GPU_Types {

struct Camera {
  vec_f3 pos;
  vec_f3 dir; // GPU processing is easier with point and direction
};

} // namespace CTNM::RHI::GPU_Types
