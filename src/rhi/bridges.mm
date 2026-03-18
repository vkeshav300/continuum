#include "rhi/bridges.hpp"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#ifdef __APPLE__

#import <AppKit/AppKit.h>

#include <AppKit/AppKit.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI::Bridges {

NS::View *attach_ns_win(GLFWwindow *win, CA::MetalLayer *layer) {
  NSWindow *_win = glfwGetCocoaWindow(win);
  if (!_win || !_win.contentView)
    return nullptr;

  NSView *metal_view = [[NSView alloc] initWithFrame:_win.contentView.bounds];
  metal_view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;
  metal_view.wantsLayer = YES;
  metal_view.layer = (__bridge CALayer *)layer;
  metal_view.layer.frame = metal_view.bounds;
  metal_view.layer.contentsScale = _win.backingScaleFactor;

  [_win.contentView addSubview:metal_view];
  return (__bridge NS::View *)metal_view;
}

void detach_ns_win(NS::View *metal_view) {
  NSView *_metal_view = (__bridge NSView *)metal_view;
  if (!_metal_view)
    return;

  _metal_view.layer = nil;
  [_metal_view removeFromSuperview];
}

} // namespace CTNM::RHI::Bridges

#endif
