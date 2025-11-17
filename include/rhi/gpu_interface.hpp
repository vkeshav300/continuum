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
  GLFWwindow *m_window = nullptr;
  NS::Window *m_ns_window = nullptr;

  /* Metal rendering */
  CA::MetalLayer *m_layer = nullptr;
  CA::MetalDrawable *m_drawable = nullptr;

  MTL::Device *m_device = nullptr;
  MTL::Library *m_library = nullptr;
  MTL::CommandQueue *m_cmd_queue = nullptr;
  MTL::CommandBuffer *m_cmd_buff = nullptr;
  MTL::AccelerationStructureCommandEncoder *m_as_cmd_enc = nullptr;
  bool m_cmd_buff_commited = false, m_encoding_ended = false;

  static void error_callback(const int code, const char *description);

  static void framebuffer_size_callback(GLFWwindow *window, const int width,
                                        const int height);

  void resize_framebuffer(const int width, const int height);

public:
  GPU_Interface(const uint16_t &width, const uint16_t &height);
  ~GPU_Interface();

  void cycle_gpu_context();
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
