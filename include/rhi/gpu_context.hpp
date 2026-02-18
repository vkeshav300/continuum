#pragma once

#ifdef __APPLE__

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

struct GPU_Context {
  MTL::Device *device = nullptr;
  MTL::CommandBuffer *cmd_buff = nullptr;
  MTL::AccelerationStructureCommandEncoder *ce_as = nullptr;
};

} // namespace CTNM::RHI

#endif
