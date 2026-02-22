#pragma once

#include "../window.hpp"
#include "mtl_ptr.hpp"

#include <memory>

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <GLFW/glfw3.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI {

class GPU_Interface {
public:
  GPU_Interface(std::shared_ptr<Window> win);
  ~GPU_Interface();

private:
  std::shared_ptr<Window> m_win;
  MTL_Ptr<NS::Window> m_win_ns = nullptr;

  MTL_Ptr<NS::AutoreleasePool> m_pool_full = nullptr, m_pool_limited = nullptr;

  MTL_Ptr<MTL::Device> m_device = nullptr;
  MTL_Ptr<CA::MetalLayer> m_layer = nullptr;
  MTL_Ptr<CA::MetalDrawable> m_drawable = nullptr;
};

}; // namespace CTNM::RHI
