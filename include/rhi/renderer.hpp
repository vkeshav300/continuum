#pragma once

#include <cstdint>

#include <entt/entt.hpp>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <GLFW/glfw3.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI {

class Renderer {
private:
  /* Window interface */
  GLFWwindow *m_window;
  NS::Window *m_ns_window;

  /* Metal rendering */
  CA::MetalLayer *m_layer;
  CA::MetalDrawable *m_drawable;

  MTL::Device *m_device;
  MTL::Library *m_library;
  MTL::CommandQueue *m_cmd_queue;
  MTL::CommandBuffer *m_cmd_buff;

  static void error_callback(const int code, const char *description);

  static void framebuffer_size_callback(GLFWwindow *window, const int width,
                                        const int height);

  void resize_framebuffer(const int width, const int height);

public:
  Renderer(const uint16_t &width, const uint16_t &height);
  ~Renderer();

  bool should_close() const;
  void poll_events() const;

  void next_drawable();
  bool drawable();

  void stage(entt::registry &registry);
  void render_current_drawable(entt::registry &registry);
  void render_to_preview(entt::registry &registry);
};

} // namespace CTNM::RHI

#endif
