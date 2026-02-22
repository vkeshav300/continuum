#include "rhi/gpu_interface.hpp"
#include "rhi/bridges.hpp"
#include "rhi/mtl_ptr.hpp"
#include "window.hpp"

#include <memory>
#include <stdexcept>

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <GLFW/glfw3.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI {

GPU_Interface::GPU_Interface(std::shared_ptr<Window> win)
    : m_win(win), m_pool_full(NS::AutoreleasePool::alloc()->init()),
      m_device(MTL::CreateSystemDefaultDevice()),
      m_layer(CA::MetalLayer::layer()->retain()) {
  if (!m_device.exists())
    throw std::runtime_error("Critical: MTL::CreateSystemDefaultDevice");

  if (!m_device->supportsFamily(MTL::GPUFamilyMetal4))
    throw std::runtime_error("Critical: device does not support Metal 4");

  if (!m_device->supportsRaytracing())
    throw std::runtime_error("Critical: device does not support raytracing");

  const FB_Size fb_size = win->get_fb_size();
  m_layer->setDevice(m_device.get());
  m_layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
  // m_layer->setFramebufferOnly(true); // Set true for deferred rendering
  m_layer->setDrawableSize(CGSizeMake(fb_size.w, fb_size.h));
  m_win_ns = Bridges::get_ns_win(m_win->get_exposed_win(), m_layer.get());
}

GPU_Interface::~GPU_Interface() {
  if (m_win)
    Bridges::detach_ns_win(m_win->get_exposed_win());
}

} // namespace CTNM::RHI
