#include "rhi/gpu_interface.hpp"
#include "rhi/bridges.hpp"
#include "rhi/gpu_context.hpp"
#include "rhi/render_packet.hpp"

#include <cstdint>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include <entt/entt.hpp>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <GLFW/glfw3.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <simd/simd.h>

namespace CTNM::RHI {

/**
 * @brief Construct a macOS Metal renderer and create its GLFW window and layer.
 *
 * Initializes the system Metal device and CAMetalLayer, configures GLFW for
 * Cocoa, creates a window sized to the given dimensions, registers GLFW error
 * and framebuffer-size callbacks, sets the Metal layer's device, pixel format,
 * and drawable size, and obtains the corresponding NSWindow bridge.
 *
 * @param width Initial window framebuffer width in pixels.
 * @param height Initial window framebuffer height in pixels.
 *
 * @throws std::runtime_error If GLFW fails to initialize or the window cannot
 * be created.
 */
GPU_Interface::GPU_Interface(const uint16_t &width, const uint16_t &height)
    : m_device(MTL::CreateSystemDefaultDevice()),
      m_layer(CA::MetalLayer::layer()) {
  /* Window */
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_COCOA);
  glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_TRUE);

  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

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

  m_ns_window = Bridges::get_ns_window(m_window, m_layer);

  /* Metal */
  m_library = m_device->newDefaultLibrary();

  /* Loads shaders (no shaders currently present)
  if (!m_library)
    throw std::runtime_error("Failed to load library");
    */

  m_cmd_queue = m_device->newCommandQueue();
}

/**
 * @brief Cleans up renderer resources and shuts down the platform/graphics
 * subsystems.
 *
 * Destroys the GLFW window if one exists, terminates the GLFW library, and
 * releases owned Metal objects (command queue, library, device).
 */
GPU_Interface::~GPU_Interface() {
  if (m_window)
    glfwDestroyWindow(m_window);

  glfwTerminate();

  m_cmd_queue->release();
  m_library->release();
  m_device->release();
}

void GPU_Interface::error_callback(const int code, const char *description) {
  throw std::runtime_error("GLFW error callback with code " +
                           std::to_string(code) + ", " +
                           std::string(description));
}

void GPU_Interface::framebuffer_size_callback(GLFWwindow *window,
                                              const int width,
                                              const int height) {
  reinterpret_cast<GPU_Interface *>(glfwGetWindowUserPointer(window))
      ->resize_framebuffer(width, height);
}

void GPU_Interface::resize_framebuffer(const int width, const int height) {
  if (m_layer) {
    m_layer->setDrawableSize(CGSizeMake(width, height));
    next_drawable();
  }
}

GPU_Context GPU_Interface::get_gpu_context() const {
  return {m_device, m_as_cmd_enc};
}

void GPU_Interface::next_drawable() { m_drawable = m_layer->nextDrawable(); }

uint8_t GPU_Interface::render(
    const std::unordered_map<entt::entity, std::unique_ptr<Render_Packet>>
        &render_packets) {
  next_drawable();
  if (!m_drawable)
    return Return_Code::Skip;

  m_cmd_buff = m_cmd_queue->commandBuffer();

  m_as_cmd_enc = m_cmd_buff->accelerationStructureCommandEncoder();

  for (const auto &[_, packet] : render_packets) {
  }

  m_cmd_buff->presentDrawable(m_drawable);
  m_as_cmd_enc->endEncoding();
  m_cmd_buff->commit();

#ifdef DEBUG
  m_cmd_buff->waitUntilCompleted();
#endif

  return Return_Code::Normal;
}

void GPU_Interface::poll_events() const { glfwPollEvents(); }

bool GPU_Interface::should_close() const {
  return glfwWindowShouldClose(m_window);
}

} // namespace CTNM::RHI

#endif
