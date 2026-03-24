#pragma once

#include <cstdint>

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

constexpr uint32_t MAX_FRAMES_INFLIGHT = 3;

struct GPU_Context {
  uint32_t slot = 0;
  bool skip_frame = false;
  MTL::Device *device = nullptr;
  MTL4::ComputeCommandEncoder *ce_as = nullptr;
  MTL::ResidencySet *rset = nullptr;
};

} // namespace CTNM::RHI
