#include "rhi/window.hpp"
#include "rhi/bridges.hpp"

#include <stdexcept>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <GLFW/glfw3.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI {

Window::Window(MTL::Device *device, const int width, const int height)
    : m_layer(CA::MetalLayer::layer()) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  m_window = glfwCreateWindow(width, height, "Continuum", nullptr, nullptr);

  if (!m_window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create window");
  }

  glfwSetWindowUserPointer(m_window, this);
  glfwSetFramebufferSizeCallback(
      m_window, framebuffer_size_callback); // Executed upon window resizing

  int fb_width, fb_height;
  glfwGetFramebufferSize(m_window, &fb_width, &fb_height);
  m_layer->setDevice(device);
  m_layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
  m_layer->setDrawableSize(CGSizeMake(fb_width, fb_height));

  m_ns_window = bridges::get_ns_window(m_window, m_layer);
}

Window::~Window() { glfwTerminate(); }

bool Window::should_close() { return glfwWindowShouldClose(m_window); }

void Window::poll_events() { glfwPollEvents(); }

void Window::framebuffer_size_callback(GLFWwindow *window, const int width,
                                       const int height) {
  reinterpret_cast<Window *>(glfwGetWindowUserPointer(window))
      ->resize_framebuffer(width, height);
}

void Window::resize_framebuffer(const int width, const int height) {
  if (m_layer) {
    m_layer->setDrawableSize(CGSizeMake(width, height));
    m_drawable = m_layer->nextDrawable();
  }
}

CA::MetalLayer *Window::get_metal_layer() const { return m_layer; }

CA::MetalDrawable *Window::get_metal_drawable() const { return m_drawable; }

void Window::next_drawable() { m_drawable = m_layer->nextDrawable(); }

bool Window::drawable() {
  if (m_drawable)
    return true;

  return false;
}

} // namespace CTNM::RHI

#endif
