#include "rhi/bridges.hpp"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI::Bridges {

NS::Window *get_ns_win(GLFWwindow *win, CA::MetalLayer *layer) {
  NSWindow *_win = glfwGetCocoaWindow(win);
  _win.contentView.wantsLayer = YES;
  _win.contentView.layer = (__bridge CALayer *)layer;
  return (__bridge NS::Window *)_win;
}

void detach_ns_win(GLFWwindow *win) {
  NSWindow *_win = glfwGetCocoaWindow(win);
  if (!_win || !_win.contentView)
    return;

  _win.contentView.layer = nil;
  _win.contentView.wantsLayer = NO;
}

} // namespace CTNM::RHI::Bridges

#endif
