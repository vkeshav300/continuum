#include "window.hpp"
#include "event.hpp"

#include <chrono>
#include <cstdint>
#include <stdexcept>
#include <thread>

#include <GLFW/glfw3.h>

namespace CTNM {

Window::Window(const FB_Size &fb_size,
               const std::chrono::milliseconds target_frame_len)
    : m_target_frame_len(target_frame_len) {
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_COCOA);
  if (!glfwInit())
    throw std::runtime_error("Critical: glfwInit");

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  m_win = glfwCreateWindow(fb_size.w, fb_size.h, "Continuum", nullptr, nullptr);
  if (!m_win) {
    glfwTerminate();
    throw std::runtime_error("Critical to create window");
  }

  glfwSetWindowUserPointer(m_win, this);
  glfwSetFramebufferSizeCallback(
      m_win,
      cb_fb_resized); // Executed upon window resizing
  glfwGetFramebufferSize(m_win, &m_fb_size.w, &m_fb_size.h);
}

void Window::cb_fb_resized(GLFWwindow *_win, const int w, const int h) {
  Window *win = reinterpret_cast<Window *>(glfwGetWindowUserPointer(_win));
  if (!win)
    return;

  win->resize_fb(FB_Size{w, h});
  win->on_fb_resized().fire(FB_Size{w, h});
}

void Window::resize_fb(const FB_Size &fb_size) { m_fb_size = fb_size; }

Event<FB_Size> &Window::on_fb_resized() { return m_ev_fb_resized; }

Window::~Window() {
  if (m_win) {
    glfwSetFramebufferSizeCallback(m_win, nullptr);
    glfwSetWindowUserPointer(m_win, nullptr);
    glfwDestroyWindow(m_win);
    m_win = nullptr;
  }

  glfwTerminate();
}

GLFWwindow *Window::get_exposed_win() const { return m_win; }

bool Window::should_close() const { return glfwWindowShouldClose(m_win); }

void Window::poll_events() const { glfwPollEvents(); }

FB_Size Window::get_fb_size() const { return m_fb_size; }

void Window::start_frame() {
  m_frame_start = std::chrono::steady_clock::now();
  m_frame_num++;
}

void Window::end_frame() const {
  poll_events();

  const auto elapsed = std::chrono::steady_clock::now() - m_frame_start;
  if (elapsed < m_target_frame_len)
    std::this_thread::sleep_for(m_target_frame_len - elapsed);
}

uint64_t Window::get_frame_num() const { return m_frame_num; }

} // namespace CTNM
