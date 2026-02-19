#pragma once
#include "gpu_context.hpp"
#include "mtl_ptr.hpp"
#include "render_packet.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

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

class GPU_Interface {
private:
  /* Window interface */
  GLFWwindow *m_window = nullptr;
  NS::Window *m_window_ns = nullptr;
  int m_fb_width = 0, m_fb_height = 0; // Framebuffer width, height

  /* Metal */
  MTL_Ptr<NS::AutoreleasePool> m_pool_full =
      nullptr; // Full-scope autorelease pool

  MTL_Ptr<MTL::Device> m_device = nullptr;
  MTL_Ptr<MTL::CommandQueue> m_cmd_queue = nullptr;
  MTL_Ptr<MTL::CommandBuffer> m_cmd_buff = nullptr;

  MTL_Ptr<CA::MetalLayer> m_layer = nullptr;
  MTL_Ptr<CA::MetalDrawable> m_drawable = nullptr;
  MTL_Ptr<MTL::Texture> m_tex_rt = nullptr;

  MTL_Ptr<MTL::AccelerationStructureCommandEncoder> m_ce_as = nullptr;
  MTL_Ptr<MTL::ComputeCommandEncoder> m_ce_comp = nullptr;
  MTL_Ptr<MTL::RenderCommandEncoder> m_ce_rndr = nullptr;

  MTL_Ptr<MTL::Buffer> m_buff_cam = nullptr;
  MTL_Ptr<MTL::Buffer> m_buff_scene = nullptr;
  MTL_Ptr<MTL::Buffer> m_buff_tlas_instances = nullptr;
  MTL_Ptr<MTL::Buffer> m_buff_scratch = nullptr;

  MTL_Ptr<MTL::Library> m_lib = nullptr;
  MTL_Ptr<MTL::Function> m_fn_k_rt = nullptr; // Kernel raytracer function
  MTL_Ptr<MTL::Function> m_fn_v_present = nullptr;
  MTL_Ptr<MTL::Function> m_fn_f_present = nullptr;
  MTL_Ptr<MTL::Function> m_fn_i_sphere =
      nullptr; // Sphere intersection function
  MTL_Ptr<MTL::FunctionHandle> m_fnh_i_sphere = nullptr;

  MTL_Ptr<MTL::ComputePipelineState> m_ps_rt = nullptr; // Raytracing pipeline
  MTL_Ptr<MTL::RenderPipelineState> m_ps_present = nullptr;
  MTL_Ptr<MTL::IntersectionFunctionTable> m_ift = nullptr;

  MTL_Ptr<MTL::AccelerationStructure> m_tlas = nullptr;
  MTL_Ptr<MTL::InstanceAccelerationStructureDescriptor> m_tlas_desc = nullptr;
  std::vector<MTL::AccelerationStructure *> m_tlas_blas_handles;
  std::vector<entt::entity> m_tlas_entities;
  bool m_rebuild = true;
  size_t m_tlas_instance_capacity = 0;

  void mtl_load();
  void mtl_create_buffs();
  void mtl_create_pipelines();
  void ensure_rt_target(const NS::UInteger width, const NS::UInteger height);

  static void glfw_error_callback(const int code, const char *description);
  static void glfw_framebuffer_size_callback(GLFWwindow *window,
                                             const int width, const int height);
  void glfw_resize_framebuffer(const int width, const int height);
  void glfw_create_window(const uint16_t &widht, const uint16_t &height);

  void create_tlas(
      const std::unordered_map<entt::entity, std::unique_ptr<Render_Packet>>
          &render_packets);

public:
  GPU_Interface(const uint16_t &width, const uint16_t &height);
  ~GPU_Interface();

  void cycle_gpu_context();
  GPU_Context get_gpu_context() const;

  void next_drawable();

  uint8_t
  render(const std::unordered_map<entt::entity, std::unique_ptr<Render_Packet>>
             &render_packets,
         std::mutex &mtx, const entt::registry &registry);

  bool should_close() const;
  void poll_events() const;
};

} // namespace CTNM::RHI

#endif
