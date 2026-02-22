#include "window.hpp"

#include <stdexcept>

#include <GLFW/glfw3.h>

namespace CTNM {

Window::Window(const FB_Size &fb_size) {
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_COCOA);
  if (!glfwInit())
    throw std::runtime_error("Failed: glfwInit");

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  m_win = glfwCreateWindow(fb_size.w, fb_size.h, "Continuum", nullptr, nullptr);
  if (!m_win) {
    glfwTerminate();
    throw std::runtime_error("Failed to create window");
  }

  glfwSetWindowUserPointer(m_win, this);
  glfwSetFramebufferSizeCallback(
      m_win,
      cb_fb_resized); // Executed upon window resizing
  glfwGetFramebufferSize(m_win, &m_fb_size.w, &m_fb_size.h);
}

void Window::cb_fb_resized(GLFWwindow *_win, const int w, const int h) {
  Window *win = reinterpret_cast<Window *>(glfwGetWindowUserPointer(_win));
}

void Window::resize_fb(const FB_Size &fb_size) { m_fb_size = fb_size; }

Window::~Window() {
  if (m_win) {
    glfwSetFramebufferSizeCallback(m_win, nullptr);
    glfwSetWindowUserPointer(m_win, nullptr);
    glfwDestroyWindow(m_win);
    m_win = nullptr;
  }

  glfwTerminate();
}

bool Window::should_close() const { return glfwWindowShouldClose(m_win); }

void Window::poll_events() const { glfwPollEvents(); }

} // namespace CTNM
