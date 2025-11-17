#pragma once

#ifdef __APPLE__

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

struct GPU_Context {
  MTL::Device *device = nullptr;
  MTL::AccelerationStructureCommandEncoder *as_cmd_enc = nullptr;
};

} // namespace CTNM::RHI

#endif
