#include "rhi/window.hpp"
#include "rhi/bridges.hpp"

#include <stdexcept>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <GLFW/glfw3.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI {

/**
 * @brief Initialize a platform Window and attach a Metal layer for rendering.
 *
 * Constructs a Window configured to use the given Metal device and initial
 * pixel dimensions; the Window will manage an underlying platform window,
 * a CA::MetalLayer configured for BGRA8Unorm, and an initial drawable size
 * matching the supplied dimensions.
 *
 * @param device Pointer to the Metal device used by the window's Metal layer.
 * @param width Initial window width in pixels.
 * @param height Initial window height in pixels.
 *
 * @throws std::runtime_error If `device` is null, if GLFW fails to initialize,
 * or if the platform window cannot be created.
 */
Window::Window(MTL::Device *device, const int width, const int height)
    : m_window(nullptr), m_ns_window(nullptr), m_layer(CA::MetalLayer::layer()),
      m_drawable(nullptr) {
  if (!device)
    throw std::runtime_error("Null device provided");

  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

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

/**
 * @brief Destroy the Window and release platform resources.
 *
 * Releases the current Metal drawable and layer if present, destroys the GLFW window, and terminates GLFW.
 */
Window::~Window() {
  if (m_window) {
    glfwDestroyWindow(m_window);
    m_window = nullptr;
  }

  if (m_drawable) {
    m_drawable->release();
    m_drawable = nullptr;
  }

  if (m_layer) {
    m_layer->release();
    m_layer = nullptr;
  }

  glfwTerminate();
}

/**
 * @brief Indicates whether the window has been requested to close.
 *
 * @return `true` if the window has been requested to close, `false` otherwise.
 */
bool Window::should_close() { return glfwWindowShouldClose(m_window); }

/**
 * @brief Processes pending window events and dispatches their callbacks.
 *
 * Polls the platform event queue and invokes any registered GLFW event handlers
 * (input, window, and other callbacks) so the application can respond to user
 * and system events.
 */
void Window::poll_events() { glfwPollEvents(); }

/**
 * @brief Dispatches a GLFW framebuffer resize notification to the associated Window instance.
 *
 * Looks up the Window pointer stored in the GLFW window's user pointer and forwards the new
 * framebuffer dimensions so the Window can update its drawable size.
 *
 * @param window GLFW window whose user pointer holds the associated Window instance.
 * @param width  New framebuffer width in pixels.
 * @param height New framebuffer height in pixels.
 */
void Window::framebuffer_size_callback(GLFWwindow *window, const int width,
                                       const int height) {
  Window *win = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (win)
    win->resize_framebuffer(width, height);
}

/**
 * @brief Update the Metal layer's drawable size to the given framebuffer
 * dimensions and refresh the current drawable.
 *
 * If a Metal layer is present, sets its drawable size to the specified width
 * and height (in pixels) and replaces the stored drawable with the layer's next
 * drawable.
 *
 * @param width Framebuffer width in pixels.
 * @param height Framebuffer height in pixels.
 */
void Window::resize_framebuffer(const int width, const int height) {
  if (m_layer) {
    m_layer->setDrawableSize(CGSizeMake(width, height));
    m_drawable = m_layer->nextDrawable();
  }
}

/**
 * @brief Retrieves the Metal layer associated with this window.
 *
 * @return CA::MetalLayer* Pointer to the window's CA::MetalLayer, or `nullptr`
 * if no layer is set.
 */
CA::MetalLayer *Window::get_metal_layer() const { return m_layer; }

/**
 * @brief Gets the current Metal drawable used for rendering.
 *
 * @return CA::MetalDrawable* Pointer to the current drawable, or nullptr if none is available.
 */
CA::MetalDrawable *Window::get_metal_drawable() const { return m_drawable; }

/**
 * @brief Acquire and store the next drawable from the Metal layer for rendering.
 *
 * Retrieves the layer's next drawable and updates the window's stored drawable
 * so subsequent rendering targets the newly acquired drawable.
 */
void Window::next_drawable() { m_drawable = m_layer->nextDrawable(); }

/**
 * @brief Check whether a Metal drawable is currently available.
 *
 * @returns `true` if a Metal drawable is available, `false` otherwise.
 */
bool Window::drawable() { return m_drawable != nullptr; }

} // namespace CTNM::RHI

#endif