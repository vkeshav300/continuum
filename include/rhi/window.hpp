#pragma once

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <GLFW/glfw3.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI {

class Window {
private:
  GLFWwindow *m_window;
  NS::Window *m_ns_window;

  CA::MetalLayer *m_layer;
  CA::MetalDrawable *m_drawable;

  static void framebuffer_size_callback(GLFWwindow *window, const int width,
                                        const int height);

  void resize_framebuffer(const int width, const int height);

public:
  Window(MTL::Device *device, int width, int height);
  ~Window();

  bool should_close() const;
  void poll_events() const;

  CA::MetalLayer *get_metal_layer() const;

  CA::MetalDrawable *get_metal_drawable() const;
  void next_drawable();
  bool drawable();
};

} // namespace CTNM::RHI

#endif
