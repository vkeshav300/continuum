#pragma once

#include <GLFW/glfw3.h>

namespace CTNM {

struct FB_Size {
  int w;
  int h;
};

class Window {
public:
  Window(const FB_Size &size);
  ~Window();

  GLFWwindow *get_exposed_win() const;

  bool should_close() const;
  void poll_events() const;

  FB_Size get_fb_size() const;

private:
  GLFWwindow *m_win;
  FB_Size m_fb_size;

  static void cb_fb_resized(GLFWwindow *_win, const int w, const int h);
  void resize_fb(const FB_Size &fb_size);
};

} // namespace CTNM
