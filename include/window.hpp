#pragma once

#include "event.hpp"

#include <chrono>
#include <cstdint>

#include <GLFW/glfw3.h>

namespace CTNM {

struct FB_Size {
  int w;
  int h;
};

class Window {
public:
  Window(const FB_Size &size, const std::chrono::milliseconds target_frame_len);
  ~Window();

  GLFWwindow *get_exposed_win() const;

  bool should_close() const;
  void poll_events() const;

  FB_Size get_fb_size() const;
  Event<FB_Size> &on_fb_resized();

  void start_frame();
  void end_frame() const;
  uint64_t get_frame_num() const;

private:
  GLFWwindow *m_win;
  uint64_t m_frame_num = 0;

  FB_Size m_fb_size;
  Event<FB_Size> m_ev_fb_resized;

  std::chrono::milliseconds m_target_frame_len;
  std::chrono::time_point<std::chrono::steady_clock> m_frame_start;

  static void cb_fb_resized(GLFWwindow *_win, const int w, const int h);
  void resize_fb(const FB_Size &fb_size);
};

} // namespace CTNM
