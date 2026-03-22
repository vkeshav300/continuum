#pragma once

#include "../math_utils.hpp"
#include "gpu_types.hpp"

#include <Metal/Metal.hpp>

namespace CTNM::RHI::Utils {

inline GPU_Types::vec_pf3 vf3_to_vpf3(const Math::vec_f3 &vf3) {
  return GPU_Types::vec_pf3{vf3.x, vf3.y, vf3.z};
}

}; // namespace CTNM::RHI::Utils
