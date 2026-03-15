#pragma once

#include <cstdint>

#include "mtl_ptr.hpp"

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

constexpr uint32_t MAX_FRAMES_INFLIGHT = 3;

struct GPU_Context {
  uint32_t slot = 0;
  bool skip_frame = false;
  MTL_Shared<MTL::Device> device = nullptr;
  MTL_Shared<MTL4::ComputeCommandEncoder> ce_as = nullptr;
  MTL_Shared<MTL::ResidencySet> rset = nullptr;
};

} // namespace CTNM::RHI
