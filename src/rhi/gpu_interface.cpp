#include "rhi/gpu_interface.hpp"
#include "event.hpp"
#include "rhi/bridges.hpp"
#include "rhi/gpu_context.hpp"
#include "rhi/gpu_types.hpp"
#include "rhi/mtl_ptr.hpp"
#include "rhi/render_packet.hpp"
#include "window.hpp"

#include <cstdint>
#include <cstring>
#include <functional>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <GLFW/glfw3.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <entt/entt.hpp>

namespace CTNM::RHI {

void GPU_Interface::cb_fb_resized(const FB_Size fb_size) {
  if (m_layer.exists())
    m_layer->setDrawableSize(CGSizeMake(fb_size.w, fb_size.h));
}

GPU_Interface::GPU_Interface(std::shared_ptr<Window> win)
    : m_win(std::move(win)), m_pool_full(NS::AutoreleasePool::alloc()->init()),
      m_device(MTL::CreateSystemDefaultDevice()),
      m_layer(CA::MetalLayer::layer()->retain()) {
  if (!m_device.exists())
    throw std::runtime_error("Critical: MTL::CreateSystemDefaultDevice");

  if (!m_device->supportsFamily(MTL::GPUFamilyMetal4))
    throw std::runtime_error("Critical: device does not support Metal 4");

  if (!m_device->supportsRaytracing())
    throw std::runtime_error("Critical: device does not support raytracing");

  MTL_Unique<NS::AutoreleasePool> pool_limited =
      NS::AutoreleasePool::alloc()->init();

  const FB_Size fb_size = m_win->get_fb_size();
  m_layer->setDevice(m_device.get());
  m_layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
  m_layer->setFramebufferOnly(true);
  m_layer->setDrawableSize(CGSizeMake(fb_size.w, fb_size.h));
  if (NS::View *metal_view =
          Bridges::attach_ns_win(m_win->get_exposed_win(), m_layer.get())) {
    m_metal_view_ns = metal_view;
  }

  m_win->on_fb_resized().connect<&GPU_Interface::cb_fb_resized>(*this);

  m_cmd_q = m_device->newMTL4CommandQueue();
  if (!m_cmd_q.exists())
    throw std::runtime_error("Failed: MTL::Device::newMTL4CommandQueue");

  NS::Error *err = nullptr;
  MTL_Unique<MTL4::ArgumentTableDescriptor> argt_rt_desc =
      MTL4::ArgumentTableDescriptor::alloc()->init();
  argt_rt_desc->setMaxBufferBindCount(4);
  argt_rt_desc->setMaxTextureBindCount(1);
  argt_rt_desc->setMaxSamplerStateBindCount(0);

  MTL_Unique<MTL4::ArgumentTableDescriptor> argt_rndr_desc =
      MTL4::ArgumentTableDescriptor::alloc()->init();
  argt_rndr_desc->setMaxBufferBindCount(0);
  argt_rndr_desc->setMaxTextureBindCount(1);
  argt_rndr_desc->setMaxSamplerStateBindCount(0);

  for (auto &frame : m_frame_contexts) {
    frame.cmd_alloc = m_device->newCommandAllocator();
    if (!frame.cmd_alloc.exists())
      throw std::runtime_error("Failed: MTL::Device::newCommandAllocator()");

    frame.tlas_desc =
        MTL4::InstanceAccelerationStructureDescriptor::alloc()->init();
    frame.tlas_desc->setInstanceDescriptorType(
        MTL::AccelerationStructureInstanceDescriptorTypeIndirect);
    frame.tlas_desc->setInstanceDescriptorStride(
        sizeof(MTL::IndirectAccelerationStructureInstanceDescriptor));
    frame.tlas_desc->setUsage(MTL::AccelerationStructureUsageRefit);

    frame.tlas_sizes_desc =
        MTL::InstanceAccelerationStructureDescriptor::alloc()->init();
    frame.tlas_sizes_desc->setInstanceDescriptorType(
        MTL::AccelerationStructureInstanceDescriptorTypeIndirect);
    frame.tlas_sizes_desc->setInstanceDescriptorStride(
        sizeof(MTL::IndirectAccelerationStructureInstanceDescriptor));
    frame.tlas_sizes_desc->setUsage(MTL::AccelerationStructureUsageRefit);

    frame.buff_cam = m_device->newBuffer(sizeof(GPU_Types::Camera),
                                         MTL::ResourceStorageModeShared);
    frame.buff_rt_params = m_device->newBuffer(
        sizeof(GPU_Types::Raytracing_Params), MTL::ResourceStorageModeShared);

    frame.tex_rt_desc = MTL::TextureDescriptor::alloc()->init();
    frame.tex_rt_desc->setTextureType(MTL::TextureType2D);
    frame.tex_rt_desc->setPixelFormat(MTL::PixelFormatRGBA8Unorm);
    frame.tex_rt_desc->setMipmapLevelCount(1);
    frame.tex_rt_desc->setStorageMode(MTL::StorageModePrivate);
    frame.tex_rt_desc->setUsage(MTL::TextureUsageShaderRead |
                                MTL::TextureUsageShaderWrite);

    frame.argt_rt = m_device->newArgumentTable(argt_rt_desc.get(), &err);
    if (!frame.argt_rt.exists())
      throw std::runtime_error("Failed: MTL::Device::newArgumentTable, rt");

    frame.argt_rndr = m_device->newArgumentTable(argt_rndr_desc.get(), &err);
    if (!frame.argt_rndr.exists())
      throw std::runtime_error("Failed: MTL::Device::newArgumentTable, rndr");
  }

  m_lib = m_device->newDefaultLibrary();
  if (!m_lib.exists())
    throw std::runtime_error("Failed: MTL::Device::newDefaultLibrary");

  for (const std::string fn_name :
       {"v_present", "f_present", "k_raytracer", "i_sphere"}) {
    m_fns[fn_name] = m_lib->newFunction(NS::String::string(
        fn_name.data(), NS::StringEncoding::UTF8StringEncoding));
    if (!m_fns[fn_name].exists())
      throw std::runtime_error(
          std::string("Failed: MTL::Library::newFunction, ") + fn_name);
  }

  MTL_Unique<MTL::ComputePipelineDescriptor> ps_rt_desc =
      MTL::ComputePipelineDescriptor::alloc()->init();
  ps_rt_desc->setComputeFunction(m_fns["k_raytracer"].get());

  MTL_Unique<MTL::LinkedFunctions> linked_fns =
      MTL::LinkedFunctions::alloc()->init();
  NS::Object *linked_ifs[] = {m_fns["i_sphere"].get()};
  NS::Array *linked_ifs_array = NS::Array::array(linked_ifs, 1);
  linked_fns->setFunctions(linked_ifs_array);
  ps_rt_desc->setLinkedFunctions(linked_fns.get());

  m_ps_rt = m_device->newComputePipelineState(
      ps_rt_desc.get(), MTL::PipelineOptionNone, nullptr, &err);
  if (!m_ps_rt.exists())
    throw std::runtime_error("Failed: MTL::Device::newComputePipelineState");

  MTL_Unique<MTL::IntersectionFunctionTableDescriptor> ift_desc =
      MTL::IntersectionFunctionTableDescriptor::alloc()->init();
  ift_desc->setFunctionCount(1);
  m_ift = m_ps_rt->newIntersectionFunctionTable(ift_desc.get());
  if (!m_ift.exists())
    throw std::runtime_error(
        "Failed: MTL::ComputePipelineState::newIntersectionFunctionTable");

  MTL_Unique<MTL::FunctionHandle> fnh_i_sphere =
      m_ps_rt->functionHandle(m_fns["i_sphere"].get());
  if (!fnh_i_sphere.exists())
    throw std::runtime_error(
        "Failed: MTL::ComputePipelineState::functionHandle");
  m_ift->setFunction(fnh_i_sphere.get(), 0);

  MTL_Unique<MTL::RenderPipelineDescriptor> ps_present_desc =
      MTL::RenderPipelineDescriptor::alloc()->init();
  ps_present_desc->setVertexFunction(m_fns["v_present"].get());
  ps_present_desc->setFragmentFunction(m_fns["f_present"].get());
  ps_present_desc->colorAttachments()->object(0)->setPixelFormat(
      MTL::PixelFormatBGRA8Unorm);
  m_ps_present = m_device->newRenderPipelineState(ps_present_desc.get(), &err);
  if (!m_ps_present.exists())
    throw std::runtime_error("Failed: MTL::Device::newRenderPipelineState");

  m_rp_desc = MTL4::RenderPassDescriptor::alloc()->init();
  m_rp_desc->setDefaultRasterSampleCount(1);
  m_rp_desc->setRenderTargetArrayLength(1);
  m_rp_desc->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
  m_rp_desc->colorAttachments()->object(0)->setClearColor(
      MTL::ClearColor::Make(0.08, 0.12, 0.18, 1.0));
  m_rp_desc->colorAttachments()->object(0)->setStoreAction(
      MTL::StoreActionStore);
}

GPU_Interface::~GPU_Interface() {
  for (auto &frame : m_frame_contexts) { // Wait for all GPU work to complete
    std::unique_lock<std::mutex> lock(frame.mtx);
    frame.cv.wait(lock, [&frame] { return frame.ready; });
  }

  if (m_win) {
    m_win->on_fb_resized().disconnect<&GPU_Interface::cb_fb_resized>(*this);
    Bridges::detach_ns_win(m_metal_view_ns.get());
  }
}

void GPU_Interface::free_current_frame(const bool end_cmd_buff) {
  Frame_Context &frame = m_frame_contexts[m_slot];
  std::lock_guard<std::mutex> lock(frame.mtx);
  if (frame.drawable.exists())
    frame.drawable.smart_release();

  if (frame.cmd_buff.exists() && end_cmd_buff)
    frame.cmd_buff->endCommandBuffer();

  if (frame.cmd_buff.exists())
    frame.cmd_buff.smart_release();

  frame.ready = true;
  frame.cv.notify_one();
}

void GPU_Interface::cycle_frame() {
  MTL_Unique<NS::AutoreleasePool> pool_limited =
      NS::AutoreleasePool::alloc()->init();

  m_slot = m_next_frame;
  m_next_frame = (m_next_frame + 1) % MAX_FRAMES_INFLIGHT;
  Frame_Context &frame = m_frame_contexts[m_slot];
  {
    std::unique_lock<std::mutex> lock(frame.mtx);
    frame.cv.wait(lock, [&frame] { return frame.ready; });
    frame.ready = skip_frame = false;
  }

  if (CA::MetalDrawable *drawable = m_layer->nextDrawable())
    frame.drawable = drawable->retain();

  if (!frame.drawable.exists()) {
    free_current_frame();
    skip_frame = true;
    return;
  }

  frame.cmd_buff = m_device->newCommandBuffer();
  if (!frame.cmd_buff.exists()) {
    free_current_frame();
    skip_frame = true;
    return;
  }

  frame.cmd_buff->beginCommandBuffer(frame.cmd_alloc.get());
  frame.label = "Frame " + std::to_string(m_win->get_frame_num());
  frame.cmd_buff->setLabel(
      NS::String::string(frame.label.c_str(), NS::UTF8StringEncoding));
}

GPU_Context GPU_Interface::get_gpu_context() {
  MTL_Unique<NS::AutoreleasePool> pool_limited =
      NS::AutoreleasePool::alloc()->init();

  if (skip_frame)
    return GPU_Context{m_slot, skip_frame, nullptr, nullptr};

  if (!m_ce_as.exists()) {
    if (MTL4::ComputeCommandEncoder *ce_as =
            m_frame_contexts[m_slot].cmd_buff->computeCommandEncoder())
      m_ce_as = ce_as;
  }

  return GPU_Context{m_slot, skip_frame, m_device, m_ce_as};
}

void GPU_Interface::render(
    const std::unordered_map<entt::entity, Render_Packet> &render_packets,
    std::mutex &packet_mtx, const uint64_t packet_revision,
    const entt::registry &reg) {
  MTL_Unique<NS::AutoreleasePool> pool_limited =
      NS::AutoreleasePool::alloc()->init();

  if (skip_frame)
    return;

  Frame_Context &frame =
      m_frame_contexts[m_slot]; // Frame is already cycled when render is called

  // --- Process tlas ---
  const bool rebuild_tlas =
      packet_revision != frame.revision || !frame.tlas_built;
  frame.revision = packet_revision;
  size_t n_packets;

  {
    const std::lock_guard<std::mutex> lock(packet_mtx);
    n_packets = render_packets.size();
    if (rebuild_tlas)
      frame.buff_as_instances = m_device->newBuffer(
          n_packets *
              sizeof(MTL::IndirectAccelerationStructureInstanceDescriptor),
          MTL::ResourceStorageModeShared);

    MTL::IndirectAccelerationStructureInstanceDescriptor *asi_descs =
        static_cast<MTL::IndirectAccelerationStructureInstanceDescriptor *>(
            frame.buff_as_instances->contents());

    size_t iid = 0;
    for (const auto &[_, packet] : render_packets) {
      MTL::IndirectAccelerationStructureInstanceDescriptor &asi_desc =
          asi_descs[iid];
      asi_desc.accelerationStructureID = packet.get_as(m_slot)->gpuResourceID();
      asi_desc.userID = iid++;
      asi_desc.transformationMatrix = packet.get_transform();
      asi_desc.options = MTL::AccelerationStructureInstanceOptionOpaque;
      asi_desc.mask = 0xFF;
      asi_desc.intersectionFunctionTableOffset = 0;
    }
  }

  frame.tlas_desc->setInstanceCount(static_cast<NS::UInteger>(n_packets));
  frame.tlas_desc->setInstanceDescriptorBuffer(MTL4::BufferRange::Make(
      frame.buff_as_instances->gpuAddress(),
      n_packets *
          sizeof(MTL::IndirectAccelerationStructureInstanceDescriptor)));

  frame.tlas_sizes_desc->setInstanceCount(static_cast<NS::UInteger>(
      n_packets)); // For some reason Metal doesn't accept MTL4 descriptors for
                   // as sizing, so legacy descriptor must be used in addtion

  frame.tlas_sizes_desc->setInstanceDescriptorBuffer(
      frame.buff_as_instances.get());
  frame.tlas_sizes_desc->setInstanceDescriptorBufferOffset(0);

  const MTL::AccelerationStructureSizes sizes =
      m_device->accelerationStructureSizes(frame.tlas_sizes_desc.get());

  if (rebuild_tlas) {
    frame.buff_scratch = m_device->newBuffer(sizes.buildScratchBufferSize,
                                             MTL::ResourceStorageModePrivate);
    frame.tlas =
        m_device->newAccelerationStructure(sizes.accelerationStructureSize);
    m_ce_as->buildAccelerationStructure(
        frame.tlas.get(), frame.tlas_desc.get(),
        MTL4::BufferRange::Make(frame.buff_scratch->gpuAddress(),
                                sizes.buildScratchBufferSize));
    frame.tlas_built = true;
  } else {
    if (frame.buff_scratch->length() != sizes.refitScratchBufferSize)
      frame.buff_scratch = m_device->newBuffer(sizes.refitScratchBufferSize,
                                               MTL::ResourceStorageModePrivate);

    const MTL4::BufferRange buff_r_scratch = MTL4::BufferRange::Make(
        frame.buff_scratch->gpuAddress(), sizes.refitScratchBufferSize);

    if (frame.tlas->size() == sizes.accelerationStructureSize)
      m_ce_as->refitAccelerationStructure(
          frame.tlas.get(), frame.tlas_desc.get(), frame.tlas.get(),
          buff_r_scratch); // In-place refit
    else {
      MTL_Unique<MTL::AccelerationStructure> tlas_new =
          m_device->newAccelerationStructure(sizes.accelerationStructureSize);
      m_ce_as->refitAccelerationStructure(frame.tlas.get(),
                                          frame.tlas_desc.get(), tlas_new.get(),
                                          buff_r_scratch);

      if (tlas_new.exists())
        frame.tlas = std::move(tlas_new);
    }
  }

  m_ce_as->endEncoding();
  m_ce_as.smart_release();

  // --- Ensure validity of raytracing target texture ---
  MTL::Texture *drawable_tex = frame.drawable->texture();
  const NS::UInteger width = drawable_tex->width(),
                     height = drawable_tex->height();
  if (width == 0 || height == 0) {
    free_current_frame(true);
    return;
  }

  if (!frame.tex_rt.exists() || frame.tex_rt->width() != width ||
      frame.tex_rt->height() != height) {
    frame.tex_rt_desc->setWidth(width);
    frame.tex_rt_desc->setHeight(height);
    frame.tex_rt = m_device->newTexture(frame.tex_rt_desc.get());
    if (!frame.tex_rt.exists()) {
      free_current_frame(true);
      return;
    }
  }

  // --- Load buffers ---
  const auto &_cam_view = reg.view<Components::Camera>();
  if (_cam_view.empty()) {
    free_current_frame(true);
    return;
  }

  const GPU_Types::Raytracing_Params params{frame.tlas.exists() ? 1u : 0u};
  std::memcpy(frame.buff_rt_params->contents(), &params,
              sizeof(GPU_Types::Raytracing_Params));

  const Components::Camera &_cam =
      reg.get<Components::Camera>(_cam_view.front());
  GPU_Types::Camera cam;
  const vec_f3 dir = _cam.fp - _cam.p;
  cam.p = MTL::PackedFloat3{_cam.p.x, _cam.p.y, _cam.p.z};
  cam.dir = MTL::PackedFloat3{dir.x, dir.y, dir.z};
  cam.fl = 1.0f / (2.0f * tanf((_cam.fov * M_PI / 180.0f) / 2.0f));
  std::memcpy(frame.buff_cam->contents(), &cam, sizeof(GPU_Types::Camera));

  frame.argt_rt->setAddress(frame.buff_rt_params->gpuAddress(), 0);
  frame.argt_rt->setAddress(frame.buff_cam->gpuAddress(), 1);
  frame.argt_rt->setResource(
      m_ift.exists() ? m_ift->gpuResourceID() : MTL::ResourceID(0), 2);
  frame.argt_rt->setResource(frame.tlas.exists() ? frame.tlas->gpuResourceID()
                                                 : MTL::ResourceID(0),
                             3);
  frame.argt_rt->setTexture(frame.tex_rt->gpuResourceID(), 0);

  if (MTL4::ComputeCommandEncoder *ce_rt =
          frame.cmd_buff->computeCommandEncoder())
    m_ce_rt = ce_rt->retain();
  else {
    free_current_frame(true);
    return;
  }

  m_ce_rt->barrierAfterQueueStages(MTL::StageAccelerationStructure,
                                   MTL::StageDispatch,
                                   MTL4::VisibilityOptionDevice);
  m_ce_rt->setComputePipelineState(m_ps_rt.get());
  m_ce_rt->setArgumentTable(frame.argt_rt.get());

  const NS::UInteger tg_width = m_ps_rt->threadExecutionWidth();
  const NS::UInteger tg_height = std::max<NS::UInteger>(
      1, m_ps_rt->maxTotalThreadsPerThreadgroup() / tg_width);
  const MTL::Size grid =
      MTL::Size(frame.tex_rt->width(), frame.tex_rt->height(), 1);
  const MTL::Size tg =
      MTL::Size(tg_width, std::min<NS::UInteger>(tg_height, 8), 1);
  m_ce_rt->dispatchThreads(grid, tg);

  m_ce_rt->endEncoding();
  m_ce_rt.smart_release();

  m_rp_desc->setRenderTargetWidth(width);
  m_rp_desc->setRenderTargetHeight(height);
  m_rp_desc->setDefaultRasterSampleCount(drawable_tex->sampleCount());
  m_rp_desc->setRenderTargetArrayLength(
      std::max<NS::UInteger>(1, drawable_tex->arrayLength()));
  m_rp_desc->colorAttachments()->object(0)->setTexture(drawable_tex);

  frame.argt_rndr->setTexture(frame.tex_rt->gpuResourceID(), 0);

  if (MTL4::RenderCommandEncoder *ce_rndr =
          frame.cmd_buff->renderCommandEncoder(m_rp_desc.get())) {
    m_ce_rndr = ce_rndr->retain();
  } else {
    free_current_frame(true);
    return;
  }

  m_ce_rndr->setLabel(
      NS::String::string(frame.label.c_str(), NS::UTF8StringEncoding));
  m_ce_rndr->barrierAfterQueueStages(MTL::StageDispatch, MTL::StageFragment,
                                     MTL4::VisibilityOptionDevice);
  m_ce_rndr->setRenderPipelineState(m_ps_present.get());
  m_ce_rndr->setArgumentTable(frame.argt_rndr.get(), MTL::RenderStageFragment);
  m_ce_rndr->drawPrimitives(MTL::PrimitiveTypeTriangle, NS::UInteger(0),
                            NS::UInteger(3));
  m_ce_rndr->endEncoding();
  m_ce_rndr.smart_release();

  frame.cmd_buff->endCommandBuffer();
  MTL_Unique<MTL4::CommitOptions> commit_opts =
      MTL4::CommitOptions::alloc()->init();
  Event<uint32_t> &ev_gpu_completed = m_ev_gpu_completed;
  const uint32_t slot = m_slot;
  const std::function<void(MTL4::CommitFeedback *)> cb_feedback(
      [&frame, &ev_gpu_completed, slot](MTL4::CommitFeedback *) {
        frame.cmd_alloc->reset();

        std::lock_guard<std::mutex> lock(frame.mtx);
        if (frame.drawable.exists())
          frame.drawable.smart_release();

        if (frame.cmd_buff.exists())
          frame.cmd_buff.smart_release();

        frame.ready = true;
        frame.cv.notify_one();

        ev_gpu_completed.fire(slot);
      });
  commit_opts->addFeedbackHandler(cb_feedback);

  const MTL4::CommandBuffer *bufs[] = {frame.cmd_buff.get()};
  m_cmd_q->commit(bufs, 1, commit_opts.get());
  frame.cmd_buff.smart_release();

  m_cmd_q->signalDrawable(frame.drawable.get());
  frame.drawable->present();

  m_ev_cpu_completed.fire(slot);
}

Event<uint32_t> &GPU_Interface::on_cpu_completed() {
  return m_ev_cpu_completed;
}

Event<uint32_t> &GPU_Interface::on_gpu_completed() {
  return m_ev_gpu_completed;
}

} // namespace CTNM::RHI
