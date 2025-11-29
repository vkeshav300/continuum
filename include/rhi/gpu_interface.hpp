#pragma once
#include "gpu_context.hpp"
#include "mtl_ptr.hpp"
#include "render_packet.hpp"

#include <cstdint>
#include <memory>
#include <unordered_map>

#include <GLFW/glfw3.h>
#include <entt/entt.hpp>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI {

enum Return_Code : uint8_t {
  Normal = 0,
  Skip,
  Fatal,
};

struct Dispatch_Size {
  MTL::Size grid;
  MTL::Size tg;
};

class GPU_Interface {
private:
  /* Window interface */
  GLFWwindow *m_window = nullptr;
  NS::Window *m_ns_window = nullptr;

  /* Metal rendering */
  MTL_Ptr<CA::MetalLayer> m_layer = nullptr;
  MTL_Ptr<CA::MetalDrawable> m_drawable = nullptr;

  MTL_Ptr<MTL::Device> m_device = nullptr;

  MTL_Ptr<MTL::Library> m_lib = nullptr;
  MTL_Ptr<MTL::Function> m_raytracer_fn = nullptr;
  MTL_Ptr<MTL::ComputePipelineState> m_raytracing_ps = nullptr;

  MTL_Ptr<MTL::CommandQueue> m_cmd_queue = nullptr;
  MTL_Ptr<MTL::CommandBuffer> m_cmd_buff = nullptr;
  MTL_Ptr<MTL::AccelerationStructureCommandEncoder> m_as_cmd_enc = nullptr;
  MTL_Ptr<MTL::ComputeCommandEncoder> m_comp_cmd_enc = nullptr;
  MTL_Ptr<MTL::Buffer> m_cam_buff = nullptr, m_img_out_buff = nullptr;

  static void glfw_error_callback(const int code, const char *description);
  static void glfw_framebuffer_size_callback(GLFWwindow *window,
                                             const int width, const int height);
  void glfw_resize_framebuffer(const int width, const int height);

public:
  GPU_Interface(const uint16_t &width, const uint16_t &height);
  ~GPU_Interface();

  void cycle_gpu_context();
  GPU_Context get_gpu_context() const;

  void next_drawable();

  uint8_t
  render(const std::unordered_map<entt::entity, std::unique_ptr<Render_Packet>>
             &render_packets,
         const entt::registry &registry);

  bool should_close() const;
  void poll_events() const;
};

} // namespace CTNM::RHI

#endif
