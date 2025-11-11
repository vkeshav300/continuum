#include "rhi/renderer.hpp"
#include "rhi/bridges.hpp"

#include <cstdint>
#include <stdexcept>
#include <string>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <GLFW/glfw3.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI {

Renderer::Renderer(const uint16_t &width, const uint16_t &height)
    : m_device(MTL::CreateSystemDefaultDevice()),
      m_layer(CA::MetalLayer::layer()) {
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_COCOA);
  glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_TRUE);

  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  m_window = glfwCreateWindow(width, height, "Continuum", nullptr, nullptr);

  if (!m_window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create window");
  }

  glfwSetWindowUserPointer(m_window, this);
  glfwSetErrorCallback(error_callback);
  glfwSetFramebufferSizeCallback(
      m_window, framebuffer_size_callback); // Executed upon window resizing

  int fb_width, fb_height;
  glfwGetFramebufferSize(m_window, &fb_width, &fb_height);
  m_layer->setDevice(m_device);
  m_layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
  m_layer->setDrawableSize(CGSizeMake(fb_width, fb_height));

  m_ns_window = bridges::get_ns_window(m_window, m_layer);
}

Renderer::~Renderer() {
  glfwTerminate();

  m_cmd_queue->release();
  m_library->release();
  m_device->release();
}

void Renderer::error_callback(const int code, const char *description) {
  throw std::runtime_error("[GLFW]\t[CODE " + std::to_string(code) + "] " +
                           std::string(description));
}

void Renderer::framebuffer_size_callback(GLFWwindow *window, const int width,
                                         const int height) {
  reinterpret_cast<Renderer *>(glfwGetWindowUserPointer(window))
      ->resize_framebuffer(width, height);
}

void Renderer::resize_framebuffer(const int width, const int height) {
  if (m_layer) {
    m_layer->setDrawableSize(CGSizeMake(width, height));
    m_drawable = m_layer->nextDrawable();
  }
}
void Renderer::stage() {
  m_library = m_device->newDefaultLibrary();

  /* Loads shaders (no shaders currently present)
  if (!m_library)
    throw std::runtime_error("Failed to load library");
    */

  m_cmd_queue = m_device->newCommandQueue();
}

void Renderer::render_current_drawable() {}

void Renderer::render_to_preview() {
  while (!glfwWindowShouldClose(m_window)) {
    NS::AutoreleasePool *pool =
        NS::AutoreleasePool::alloc()
            ->init(); // Automatically releases objc pointers within scope

    m_drawable = m_layer->nextDrawable(); // Cycle to next drawable frame
    if (!m_drawable) {
      pool->release();
      continue;
    }

    m_cmd_buffer = m_cmd_queue->commandBuffer();

    render_current_drawable();

    m_cmd_buffer->presentDrawable(m_drawable);
    // end render command encoder encoding
    m_cmd_buffer->commit();

#ifdef DEBUG
    m_cmd_buffer->waitUntilCompleted();
#endif

    pool->release();
    glfwPollEvents();
  }
}

} // namespace CTNM::RHI

#endif
