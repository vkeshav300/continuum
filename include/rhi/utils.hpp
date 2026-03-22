#pragma once

#include "../math_utils.hpp"
#include "gpu_types.hpp"

#include <Metal/Metal.hpp>

namespace CTNM::RHI::Utils {

inline GPU_Types::vec_pf3 pack(const Math::vec_f3 &vec) {
  return GPU_Types::vec_pf3{vec.x, vec.y, vec.z};
}

}; // namespace CTNM::RHI::Utils
