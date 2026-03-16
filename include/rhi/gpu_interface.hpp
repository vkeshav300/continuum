#pragma once

#include "../window.hpp"
#include "event.hpp"
#include "gpu_context.hpp"
#include "mtl_ptr.hpp"
#include "render_packet.hpp"

#include <array>
#include <condition_variable>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <GLFW/glfw3.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <entt/entt.hpp>

namespace CTNM::RHI {

struct Frame_Context {
  MTL_Unique<MTL4::CommandBuffer> cmd_buff = nullptr;
  MTL_Unique<MTL4::CommandAllocator> cmd_alloc = nullptr;
  MTL_Unique<CA::MetalDrawable> drawable = nullptr;
  MTL_Shared<MTL::ResidencySet> rset = nullptr;

  MTL_Unique<MTL::Buffer> buff_scratch = nullptr;
  MTL_Unique<MTL::Buffer> buff_as_instances = nullptr;
  MTL_Unique<MTL::Buffer> buff_as_instance_ct = nullptr;
  MTL_Unique<MTL::Buffer> buff_cam = nullptr;
  MTL_Unique<MTL::Buffer> buff_rt_params = nullptr;
  MTL_Unique<MTL::Buffer> buff_rt_args = nullptr;

  MTL_Unique<MTL::TextureDescriptor> tex_rt_desc = nullptr;
  MTL_Unique<MTL::Texture> tex_rt = nullptr;
  MTL_Unique<MTL4::ArgumentTable> argt_rt = nullptr;
  MTL_Unique<MTL4::ArgumentTable> argt_rndr = nullptr;

  MTL_Unique<MTL4::IndirectInstanceAccelerationStructureDescriptor> tlas_desc =
      nullptr;
  MTL_Unique<MTL::IndirectInstanceAccelerationStructureDescriptor>
      tlas_sizes_desc = nullptr;
  MTL_Unique<MTL::AccelerationStructure> tlas = nullptr;

  bool ready = true, tlas_built = false;
  uint64_t revision = 0;
  std::mutex mtx;
  std::condition_variable cv;
  std::string label;
};

class GPU_Interface {
public:
  GPU_Interface(std::shared_ptr<Window> win);
  ~GPU_Interface();

  void cycle_frame();
  GPU_Context get_gpu_context();
  void render(const std::unordered_map<entt::entity, Render_Packet> &packets,
              std::mutex &packet_mtx, const uint64_t packet_revision,
              const entt::registry &reg);

  Event<uint32_t> &on_cpu_completed();
  Event<uint32_t> &on_gpu_completed();

private:
  std::shared_ptr<Window> m_win;

  MTL_Unique<NS::View> m_metal_view_ns = nullptr;
  MTL_Unique<NS::AutoreleasePool> m_pool_full = nullptr;

  MTL_Unique<CA::MetalLayer> m_layer = nullptr;
  MTL_Unique<MTL::ResidencySet> m_rset_layer = nullptr;

  MTL_Shared<MTL::Device> m_device = nullptr;
  MTL_Unique<MTL::Library> m_lib = nullptr;
  MTL_Unique<MTL::ArgumentEncoder> m_ae_rt = nullptr;
  MTL_Unique<MTL::RenderPipelineState> m_ps_present = nullptr;
  MTL_Unique<MTL::ComputePipelineState> m_ps_rt = nullptr;

  MTL_Unique<MTL4::CommandQueue> m_cmd_q = nullptr;
  MTL_Unique<MTL4::RenderPassDescriptor> m_rp_desc = nullptr;
  MTL_Unique<MTL4::RenderCommandEncoder> m_ce_rndr = nullptr;
  MTL_Unique<MTL4::ComputeCommandEncoder> m_ce_rt = nullptr;
  MTL_Shared<MTL4::ComputeCommandEncoder> m_ce_as = nullptr;

  std::unordered_map<std::string, MTL_Unique<MTL::Function>> m_fns;

  Event<uint32_t> m_ev_cpu_completed, m_ev_gpu_completed;
  std::array<Frame_Context, MAX_FRAMES_INFLIGHT> m_frame_contexts;
  uint32_t m_slot = 0, m_next_frame = 0;
  bool skip_frame = false;

  void cb_fb_resized(const FB_Size fb_size);

  void free_current_frame(const bool end_cmd_buff = false);
};

}; // namespace CTNM::RHI
