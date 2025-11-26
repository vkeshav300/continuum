#include "rhi/bridges.hpp"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI::Bridges {

NS::Window *get_ns_window(GLFWwindow *window, CA::MetalLayer *layer) {
  NSWindow *_window = glfwGetCocoaWindow(window);
  _window.contentView.layer = (__bridge CALayer *)layer;
  _window.contentView.wantsLayer = YES;
  return (__bridge NS::Window *)_window;
}

} // namespace CTNM::RHI::Bridges

#endif
