#pragma once
#include "gpu_context.hpp"
#include "render_packet.hpp"

#include <cstdint>
#include <memory>
#include <unordered_map>

#include <entt/entt.hpp>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <GLFW/glfw3.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI {

enum Return_Code : uint8_t {
  Normal = 0,
  Skip,
  Fatal,
};

class GPU_Interface {
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
  MTL::AccelerationStructureCommandEncoder *m_as_cmd_enc;

  static void error_callback(const int code, const char *description);

  static void framebuffer_size_callback(GLFWwindow *window, const int width,
                                        const int height);

  void resize_framebuffer(const int width, const int height);

public:
  GPU_Interface(const uint16_t &width, const uint16_t &height);
  ~GPU_Interface();

  GPU_Context get_gpu_context() const;

  void next_drawable();

  uint8_t
  render(const std::unordered_map<entt::entity, std::unique_ptr<Render_Packet>>
             &render_packets);

  bool should_close() const;
  void poll_events() const;
};

} // namespace CTNM::RHI

#endif
