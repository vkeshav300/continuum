#include "rhi/gpu_interface.hpp"
#include "beacon.hpp"
#include "rhi/bridges.hpp"
#include "rhi/mtl_ptr.hpp"
#include "rhi/render_packet.hpp"
#include "window.hpp"

#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <unordered_map>

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <GLFW/glfw3.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <entt/entt.hpp>

namespace CTNM::RHI {

GPU_Interface::GPU_Interface(std::shared_ptr<Window> win)
    : m_win(win), m_pool_full(NS::AutoreleasePool::alloc()->init()),
      m_device(MTL::CreateSystemDefaultDevice()),
      m_layer(CA::MetalLayer::layer()->retain()) {
  if (!m_device.exists())
    throw std::runtime_error("Critical: MTL::CreateSystemDefaultDevice");

  if (!m_device->supportsFamily(MTL::GPUFamilyMetal4))
    throw std::runtime_error("Critical: device does not support Metal 4");

  if (!m_device->supportsRaytracing())
    throw std::runtime_error("Critical: device does not support raytracing");

  m_pool_limited = NS::AutoreleasePool::alloc()->init();

  const FB_Size fb_size = m_win->get_fb_size();
  m_layer->setDevice(m_device.get());
  m_layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
  // m_layer->setFramebufferOnly(true); // Set true for deferred rendering
  m_layer->setDrawableSize(CGSizeMake(fb_size.w, fb_size.h));
  if (NS::Window *ns_win =
          Bridges::get_ns_win(m_win->get_exposed_win(), m_layer.get())) {
    m_win_ns = ns_win->retain();
  }

  m_win->on_fb_resized().connect<&GPU_Interface::cb_fb_resized>(*this);

  m_cmd_q = m_device->newMTL4CommandQueue();
  if (!m_cmd_q.exists())
    throw std::runtime_error("Failed: MTL::Device::newMTL4CommandQueue");

  for (auto &frame : m_frame_contexts) {
    frame.cmd_alloc = m_device->newCommandAllocator();
    if (!frame.cmd_alloc.exists())
      throw std::runtime_error("Failed: MTL::Device::newCommandAllocator()");
  }

  m_lib = m_device->newDefaultLibrary();
  if (!m_lib.exists())
    throw std::runtime_error("Failed: MTL::Device::newDefaultLibrary");

  m_fns["v_present"] = m_lib->newFunction(
      NS::String::string("v_present", NS::StringEncoding::UTF8StringEncoding));
  m_fns["f_present"] = m_lib->newFunction(
      NS::String::string("f_present", NS::StringEncoding::UTF8StringEncoding));

  for (const auto &[_, fn] : m_fns)
    if (!fn.exists())
      throw std::runtime_error("Failed: MTL::Library::newFunction");

  NS::Error *err = nullptr;
  MTL_Unique<MTL4::ArgumentTableDescriptor> argt_rndr_desc =
      MTL4::ArgumentTableDescriptor::alloc()->init();
  argt_rndr_desc->setMaxBufferBindCount(1);
  argt_rndr_desc->setMaxTextureBindCount(0);
  argt_rndr_desc->setMaxSamplerStateBindCount(0);
  m_argt_rndr = m_device->newArgumentTable(argt_rndr_desc.get(), &err);
  if (!m_argt_rndr.exists())
    throw std::runtime_error("Failed: MTL::Device::newArgumentTable");

  m_pool_limited.smart_release();

  MTL_Unique<MTL::RenderPipelineDescriptor> present_ps_desc =
      MTL::RenderPipelineDescriptor::alloc()->init();
  present_ps_desc->setVertexFunction(m_fns["v_present"].get());
  present_ps_desc->setFragmentFunction(m_fns["f_present"].get());
  present_ps_desc->colorAttachments()->object(0)->setPixelFormat(
      MTL::PixelFormatBGRA8Unorm);
  m_ps_present = m_device->newRenderPipelineState(present_ps_desc.get(), &err);
  if (!m_ps_present.exists())
    throw std::runtime_error("Failed: MTL::Device::newRenderPipelineState");

  m_rp_desc = MTL4::RenderPassDescriptor::alloc()->init();
  m_rp_desc->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
  m_rp_desc->colorAttachments()->object(0)->setClearColor(
      MTL::ClearColor::Make(0.08, 0.12, 0.18, 1.0));
  m_rp_desc->colorAttachments()->object(0)->setStoreAction(
      MTL::StoreActionStore);
}

void GPU_Interface::cb_fb_resized(const FB_Size fb_size) {
  if (m_layer.exists())
    m_layer->setDrawableSize(CGSizeMake(fb_size.w, fb_size.h));
}

GPU_Interface::~GPU_Interface() {
  for (auto &frame : m_frame_contexts) { // Wait for all GPU work to complete
    std::unique_lock<std::mutex> lock(frame.mtx);
    frame.cv.wait(lock, [&frame] { return frame.ready; });
  }

  if (m_win) {
    m_win->on_fb_resized().disconnect<&GPU_Interface::cb_fb_resized>(*this);
    Bridges::detach_ns_win(m_win->get_exposed_win());
  }
}

uint8_t GPU_Interface::render(
    const std::unordered_map<entt::entity, Render_Packet> &render_packets,
    std::mutex &packet_mtx) {
  /* Cycle to next preparable frame */
  const uint32_t slot = m_next_frame;
  m_next_frame = (m_next_frame + 1) % MAX_FRAMES_INFLIGHT;
  Frame_Context &frame = m_frame_contexts[slot];
  {
    std::unique_lock<std::mutex> lock(frame.mtx);
    frame.cv.wait(lock, [&frame] { return frame.ready; });
    frame.ready = false;
  }
  const std::function<void(bool)> free_frame([&frame](const bool end_cmd_buff) {
    std::lock_guard<std::mutex> lock(frame.mtx);
    if (frame.drawable.exists())
      frame.drawable.smart_release();

    if (frame.cmd_buff.exists() && end_cmd_buff)
      frame.cmd_buff->endCommandBuffer();

    if (frame.cmd_buff.exists())
      frame.cmd_buff.smart_release();

    frame.ready = true;
    frame.cv.notify_one();
  });

  if (CA::MetalDrawable *drawable = m_layer->nextDrawable())
    frame.drawable = drawable->retain();

  if (!frame.drawable.exists()) {
    free_frame(false);
    return Result::Skip;
  }

  frame.cmd_buff = m_device->newCommandBuffer();
  if (!frame.cmd_buff.exists()) {
    free_frame(false);
    return Result::Skip;
  }

  frame.cmd_buff->beginCommandBuffer(frame.cmd_alloc.get());

  m_rp_desc->colorAttachments()->object(0)->setTexture(
      frame.drawable->texture());

  if (MTL4::RenderCommandEncoder *encoder =
          frame.cmd_buff->renderCommandEncoder(m_rp_desc.get())) {
    m_ce_rndr = encoder->retain();
  }

  if (!m_ce_rndr.exists()) {
    free_frame(true);
    return Result::Skip;
  }

  m_ce_rndr->setRenderPipelineState(m_ps_present.get());
  m_ce_rndr->setArgumentTable(m_argt_rndr.get(), MTL::RenderStageFragment);
  m_ce_rndr->drawPrimitives(MTL::PrimitiveTypeTriangle, NS::UInteger(0),
                            NS::UInteger(3));
  m_ce_rndr->endEncoding();
  m_ce_rndr.smart_release();

  frame.cmd_buff->endCommandBuffer();
  MTL_Unique<MTL4::CommitOptions> commit_opts =
      MTL4::CommitOptions::alloc()->init();
  Beacon<uint32_t> &bec_gpu_completed = m_bec_gpu_completed;
  const std::function<void(MTL4::CommitFeedback *)> cb_feedback(
      [&frame, free_frame, &bec_gpu_completed, slot](MTL4::CommitFeedback *) {
        frame.cmd_alloc->reset();
        free_frame(false);
        bec_gpu_completed.fire(slot);
      });
  commit_opts->addFeedbackHandler(cb_feedback);

  const MTL4::CommandBuffer *bufs[] = {frame.cmd_buff.get()};
  m_cmd_q->commit(bufs, 1, commit_opts.get());
  frame.cmd_buff.smart_release();

  m_cmd_q->signalDrawable(frame.drawable.get());
  frame.drawable->present();

  m_bec_cpu_completed.fire(slot);

  return Result::Normal;
}

Beacon<uint32_t> &GPU_Interface::on_cpu_completed() {
  return m_bec_cpu_completed;
}

Beacon<uint32_t> &GPU_Interface::on_gpu_completed() {
  return m_bec_gpu_completed;
}

} // namespace CTNM::RHI
