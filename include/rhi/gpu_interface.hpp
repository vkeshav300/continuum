#pragma once

#include "../window.hpp"
#include "beacon.hpp"
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

enum Result : uint8_t {
  Normal = 0,
  Skip = 1,
};

static constexpr uint32_t MAX_FRAMES_INFLIGHT = 3;

struct Frame_Context {
  MTL_Unique<MTL4::CommandBuffer> cmd_buff = nullptr;
  MTL_Unique<MTL4::CommandAllocator> cmd_alloc = nullptr;
  MTL_Unique<CA::MetalDrawable> drawable = nullptr;
  bool ready = true;
  std::mutex mtx;
  std::condition_variable cv;
};

class GPU_Interface {
public:
  GPU_Interface(std::shared_ptr<Window> win);
  ~GPU_Interface();

  uint8_t render(const std::unordered_map<entt::entity, Render_Packet> &packets,
                 std::mutex &packet_mtx);

  Beacon<uint32_t> &on_cpu_completed();
  Beacon<uint32_t> &on_gpu_completed();

private:
  std::shared_ptr<Window> m_win;
  MTL_Unique<NS::Window> m_win_ns = nullptr;

  MTL_Unique<NS::AutoreleasePool> m_pool_full = nullptr,
                                  m_pool_limited = nullptr;

  MTL_Unique<MTL::Device> m_device = nullptr;
  MTL_Unique<CA::MetalLayer> m_layer = nullptr;

  MTL_Unique<MTL4::CommandQueue> m_cmd_q = nullptr;
  MTL_Unique<MTL4::CommandBuffer> m_cmd_buf = nullptr;

  std::array<Frame_Context, MAX_FRAMES_INFLIGHT> m_frame_contexts;
  uint32_t m_next_frame = 0;

  MTL_Unique<MTL::Library> m_lib = nullptr;
  std::unordered_map<std::string, MTL_Unique<MTL::Function>> m_fns;

  MTL_Unique<MTL::RenderPipelineState> m_ps_present = nullptr;
  MTL_Unique<MTL4::RenderPassDescriptor> m_rp_desc = nullptr;

  MTL_Unique<MTL4::ArgumentTable> m_argt_rndr = nullptr;

  MTL_Unique<MTL4::RenderCommandEncoder> m_ce_rndr = nullptr;

  Beacon<uint32_t> m_bec_cpu_completed, m_bec_gpu_completed;

  void cb_fb_resized(const FB_Size fb_size);
};

}; // namespace CTNM::RHI
