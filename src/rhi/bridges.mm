#include "rhi/bridges.hpp"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI::Bridges {

NS::Window *get_ns_window(GLFWwindow *window, CA::MetalLayer *layer) {
  NSWindow *_window = glfwGetCocoaWindow(window);
  _window.contentView.wantsLayer = YES;
  _window.contentView.layer = (__bridge CALayer *)layer;
  return (__bridge NS::Window *)_window;
}

void detach_ns_window_layer(GLFWwindow *window) {
  NSWindow *_window = glfwGetCocoaWindow(window);
  if (!_window || !_window.contentView)
    return;

  _window.contentView.layer = nil;
  _window.contentView.wantsLayer = NO;
}

} // namespace CTNM::RHI::Bridges

#endif
