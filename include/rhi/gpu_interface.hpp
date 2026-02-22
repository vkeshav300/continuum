#pragma once

#include "mtl_ptr.hpp"

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

class GPU_Interface {
public:
  GPU_Interface() {}
  ~GPU_Interface() {}

private:
  MTL_Ptr<MTL::Device> m_device = nullptr;
};

}; // namespace CTNM::RHI
