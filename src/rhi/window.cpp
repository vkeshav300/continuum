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
 * @brief Create and initialize a platform window with an associated Metal
 * layer.
 *
 * Constructs a Window by initializing GLFW, creating an API-less GLFW window
 * titled "Continuum", registering a framebuffer resize callback, configuring
 * the Metal layer with the provided device and an BGRA8Unorm pixel format,
 * setting the layer's drawable size to the current framebuffer dimensions, and
 * obtaining the corresponding NS window handle.
 *
 * @param device Pointer to the Metal device used by the window's Metal layer.
 * @param width Initial window width in pixels.
 * @param height Initial window height in pixels.
 *
 * @throws std::runtime_error If the GLFW window could not be created.
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
 * Ensures GLFW is shut down and associated GLFW resources are released.
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
 * @brief Handle GLFW framebuffer resize events for the associated Window.
 *
 * Looks up the Window instance stored in the GLFW window's user pointer and
 * updates its framebuffer size to match the given dimensions.
 *
 * @param window GLFW window whose framebuffer was resized; must have this
 * Window instance stored as its user pointer.
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
 * @brief Return the current Metal drawable used for rendering.
 *
 * @return CA::MetalDrawable* Pointer to the current drawable, or `nullptr` if
 * no drawable is available.
 */
CA::MetalDrawable *Window::get_metal_drawable() const { return m_drawable; }

/**
 * @brief Advance the internal drawable to the next available drawable from the
 * Metal layer.
 *
 * Updates the Window's stored drawable reference to the layer's next drawable
 * so subsequent rendering operations use the newly acquired drawable.
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
