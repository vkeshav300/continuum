#pragma once

#ifdef __APPLE__

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

struct GPU_Context {
  MTL::Device *device;
  MTL::AccelerationStructureCommandEncoder *as_cmd_enc;
};

} // namespace CTNM::RHI

#endif
