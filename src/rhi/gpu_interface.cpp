#include "rhi/gpu_interface.hpp"
#include "math_utils.hpp"
#include "rhi/bridges.hpp"
#include "rhi/gpu_context.hpp"
#include "rhi/gpu_types.hpp"
#include "rhi/mtl_ptr.hpp"
#include "rhi/render_packet.hpp"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include <GLFW/glfw3.h>
#include <entt/entt.hpp>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <simd/simd.h>

namespace CTNM::RHI {

GPU_Interface::GPU_Interface(const uint16_t &width, const uint16_t &height)
    : m_pool_full(NS::AutoreleasePool::alloc()->init()),
      m_device(MTL::CreateSystemDefaultDevice()),
      m_layer(CA::MetalLayer::layer()->retain()) {
  glfw_create_window(width, height);
  mtl_load();
  mtl_create_buffs();
  mtl_create_pipelines();
}

void GPU_Interface::glfw_error_callback(const int code,
                                        const char *description) {
  throw std::runtime_error("GLFW error (" + std::to_string(code) +
                           "): " + std::string(description));
}

void GPU_Interface::glfw_framebuffer_size_callback(GLFWwindow *window,
                                                   const int width,
                                                   const int height) {
  reinterpret_cast<GPU_Interface *>(glfwGetWindowUserPointer(window))
      ->glfw_resize_framebuffer(width, height);
}

void GPU_Interface::glfw_resize_framebuffer(const int width, const int height) {
  if (m_layer.get()) {
    m_layer->setDrawableSize(CGSizeMake(width, height));
    next_drawable();
  }
}

void GPU_Interface::glfw_create_window(const uint16_t &width,
                                       const uint16_t &height) {
  /* Initialize GLFW */
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_COCOA);
  glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_TRUE);
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

  /* Create GLFW window */
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  m_window = glfwCreateWindow(width, height, "Continuum", nullptr, nullptr);
  if (!m_window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create window");
  }

  /* Window setup */
  glfwSetWindowUserPointer(m_window, this);
  glfwSetErrorCallback(glfw_error_callback);
  glfwSetFramebufferSizeCallback(
      m_window,
      glfw_framebuffer_size_callback); // Executed upon window resizing

  /* Window binding with Metal */
  glfwGetFramebufferSize(m_window, &m_fb_width, &m_fb_height);
  m_layer->setDevice(m_device.get());
  m_layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
  m_layer->setFramebufferOnly(true);
  m_layer->setDrawableSize(CGSizeMake(m_fb_width, m_fb_height));

  m_window_ns = Bridges::get_ns_window(m_window, m_layer.get());
}

void GPU_Interface::mtl_load() {
  m_lib = m_device->newDefaultLibrary();
  if (!m_lib.get())
    throw std::runtime_error("Failed to load default library");

  m_cmd_queue = m_device->newCommandQueue();
}

void GPU_Interface::mtl_create_buffs() {
  m_buff_cam = m_device->newBuffer(sizeof(GPU_Types::Camera),
                                   MTL::ResourceStorageModeShared);
  m_buff_scene =
      m_device->newBuffer(sizeof(uint32_t), MTL::ResourceStorageModeShared);
}

void GPU_Interface::mtl_create_pipelines() {
  MTL_Ptr<NS::AutoreleasePool> pool = NS::AutoreleasePool::alloc()->init();

  /* Load functions */
  m_fn_k_rt = m_lib->newFunction(NS::String::string(
      "k_raytracer", NS::StringEncoding::UTF8StringEncoding));
  if (!m_fn_k_rt.get())
    throw std::runtime_error("Failed to find k_raytracer in default library");

  m_fn_v_present = m_lib->newFunction(
      NS::String::string("v_present", NS::StringEncoding::UTF8StringEncoding));
  if (!m_fn_v_present.get())
    throw std::runtime_error("Failed to find v_present in default library");

  m_fn_f_present = m_lib->newFunction(
      NS::String::string("f_present", NS::StringEncoding::UTF8StringEncoding));
  if (!m_fn_f_present.get())
    throw std::runtime_error("Failed to find f_present in default library");

  m_fn_i_sphere = m_lib->newFunction(NS::String::string(
      "sphere_intersection", NS::StringEncoding::UTF8StringEncoding));
  if (!m_fn_i_sphere.get())
    throw std::runtime_error(
        "Failed to find sphere_intersection function in default library");

  /* Create raytracing pipeline state */
  MTL_Ptr<MTL::ComputePipelineDescriptor> m_raytracing_ps_desc =
      MTL::ComputePipelineDescriptor::alloc()->init();
  m_raytracing_ps_desc->setComputeFunction(m_fn_k_rt.get());

  MTL_Ptr<MTL::LinkedFunctions> linked_fns =
      MTL::LinkedFunctions::alloc()->init();
  constexpr NS::UInteger linked_if_count = 1;
  NS::Object *linked_ifs[linked_if_count]{m_fn_i_sphere.get()};
  NS::Array *linked_if_array = NS::Array::array(linked_ifs, linked_if_count);
  linked_fns->setFunctions(linked_if_array);
  m_raytracing_ps_desc->setLinkedFunctions(linked_fns.get());

  NS::Error *err = nullptr;
  m_ps_rt = m_device->newComputePipelineState(
      m_raytracing_ps_desc.get(), MTL::PipelineOptionNone, nullptr, &err);
  if (!m_ps_rt.get())
    throw std::runtime_error(
        "Failed to create raytracing compute pipeline state");

  /* Create intersection function table (ift) */
  MTL_Ptr<MTL::IntersectionFunctionTableDescriptor> ift_desc =
      MTL::IntersectionFunctionTableDescriptor::alloc()->init();
  ift_desc->setFunctionCount(1);

  m_ift = m_ps_rt->newIntersectionFunctionTable(ift_desc.get());
  if (!m_ift.get())
    throw std::runtime_error("Failed to allocate intersection function table");

  m_fnh_i_sphere = m_ps_rt->functionHandle(m_fn_i_sphere.get());
  if (!m_fnh_i_sphere.get())
    throw std::runtime_error(
        "Failed to create function handle for sphere_intersection");

  m_fnh_i_sphere->retain();
  m_ift->setFunction(m_fnh_i_sphere.get(), IFN_IDX::Sphere);

  /* Create present render pipeline state */
  MTL_Ptr<MTL::RenderPipelineDescriptor> present_ps_desc =
      MTL::RenderPipelineDescriptor::alloc()->init();
  present_ps_desc->setVertexFunction(m_fn_v_present.get());
  present_ps_desc->setFragmentFunction(m_fn_f_present.get());
  present_ps_desc->colorAttachments()->object(0)->setPixelFormat(
      MTL::PixelFormatBGRA8Unorm);

  m_ps_present = m_device->newRenderPipelineState(present_ps_desc.get(), &err);
  if (!m_ps_present.get())
    throw std::runtime_error("Failed to create present render pipeline state");
}

GPU_Interface::~GPU_Interface() {
  if (m_window) {
    glfwDestroyWindow(m_window);
    m_window = nullptr;
    m_window_ns = nullptr;
  }

  glfwTerminate();
}

void GPU_Interface::cycle_gpu_context() {
  m_ce_as.smart_release();
  m_cmd_buff.smart_release();

  m_cmd_buff.set_mark(false);
  m_ce_as.set_mark(false);
  m_cmd_buff = m_cmd_queue->commandBuffer()->retain();
  m_ce_as = m_cmd_buff->accelerationStructureCommandEncoder()->retain();
}

GPU_Context GPU_Interface::get_gpu_context() const {
  return {m_device.get(), m_cmd_buff.get(), m_ce_as.get()};
}

void GPU_Interface::next_drawable() {
  m_drawable = m_layer->nextDrawable()->retain();
}

void GPU_Interface::ensure_rt_target(const NS::UInteger width,
                                     const NS::UInteger height) {
  /* Check if texture parameters are valid of if texture already exists with
   * correct width and height */
  if (width == 0 || height == 0)
    return;

  if (m_tex_rt.get() && m_tex_rt->width() == width &&
      m_tex_rt->height() == height)
    return;

  /* Create texture if not */
  MTL_Ptr<MTL::TextureDescriptor> tex_desc =
      MTL::TextureDescriptor::alloc()->init();
  tex_desc->setTextureType(MTL::TextureType2D);
  tex_desc->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
  tex_desc->setWidth(width);
  tex_desc->setHeight(height);
  tex_desc->setMipmapLevelCount(1);
  tex_desc->setStorageMode(MTL::StorageModePrivate);
  tex_desc->setUsage(MTL::TextureUsageShaderRead |
                     MTL::TextureUsageShaderWrite);

  m_tex_rt = m_device->newTexture(tex_desc.get());
  if (!m_tex_rt.get())
    throw std::runtime_error(
        "Failed to allocate offscreen ray tracing texture");
}

uint8_t GPU_Interface::render(
    const std::unordered_map<entt::entity, std::unique_ptr<Render_Packet>>
        &render_packets,
    std::mutex &mtx, const entt::registry &registry) {
  const std::lock_guard<std::mutex> lock_guard(
      mtx); // Avoid reading render packets while map is being mutated
  MTL_Ptr<NS::AutoreleasePool> pool = NS::AutoreleasePool::alloc()->init();

  next_drawable();
  if (!m_drawable.get())
    return Return_Code::Skip;

  ensure_rt_target(m_drawable->texture()->width(),
                   m_drawable->texture()->height());
  if (!m_tex_rt.get())
    return Return_Code::Skip;

  if (!m_ce_as.get() || !m_cmd_buff.get())
    cycle_gpu_context();

  if (!render_packets.empty())
    create_tlas(render_packets);
  else
    m_tlas.smart_release();

  m_ce_as->endEncoding();
  m_ce_as.set_mark(true);

  /* Gather camera data */
  const CTNM::Components::Camera &cam = registry.get<CTNM::Components::Camera>(
      registry.view<CTNM::Components::Camera>()
          .front()); // First object with camera component is camera

  GPU_Types::Camera gpu_cam;
  gpu_cam.pos = cam.pos;
  gpu_cam.dir = cam.fpos - cam.pos;
  gpu_cam.dir = approx_eq(magnitude(gpu_cam.dir), 0) ? vec_f3{0.0f, 0.0f, 0.0f}
                                                     : normalize(gpu_cam.dir);
  std::memcpy(m_buff_cam->contents(), &gpu_cam, sizeof(gpu_cam));

  /* Cycle to compute encoder */
  m_ce_comp.smart_release();
  m_ce_comp = m_cmd_buff->computeCommandEncoder()->retain();
  m_ce_comp->setComputePipelineState(m_ps_rt.get());
  if (m_ift.get())
    m_ce_comp->setIntersectionFunctionTable(m_ift.get(), 3);
  if (m_tlas.get())
    m_ce_comp->setAccelerationStructure(m_tlas.get(), 0);

  /* Link buffers for passing data to GPU */
  const uint32_t has_scene = m_tlas.get() ? 1u : 0u;
  std::memcpy(m_buff_scene->contents(), &has_scene, sizeof(has_scene));
  m_ce_comp->setBuffer(m_buff_cam.get(), 0, 1);
  m_ce_comp->setBuffer(m_buff_scene.get(), 0, 2);
  m_ce_comp->setTexture(m_tex_rt.get(), 0);

  /* Dispatch GPU threads for raytracing pipeline */
  const NS::UInteger tg_width = m_ps_rt->threadExecutionWidth();
  const NS::UInteger tg_height = std::max<NS::UInteger>(
      1, m_ps_rt->maxTotalThreadsPerThreadgroup() / tg_width);
  const MTL::Size grid = MTL::Size(m_tex_rt->width(), m_tex_rt->height(), 1);
  const MTL::Size tg =
      MTL::Size(tg_width, std::min<NS::UInteger>(tg_height, 8), 1);
  m_ce_comp->dispatchThreads(grid, tg);

  m_ce_comp->endEncoding();
  m_ce_comp.set_mark(true);

  /* Update screen texture to match raytraced scene texture */
  MTL_Ptr<MTL::RenderPassDescriptor> present_rp_desc =
      MTL::RenderPassDescriptor::alloc()->init();
  present_rp_desc->colorAttachments()->object(0)->setTexture(
      m_drawable->texture());
  present_rp_desc->colorAttachments()->object(0)->setLoadAction(
      MTL::LoadActionDontCare);
  present_rp_desc->colorAttachments()->object(0)->setStoreAction(
      MTL::StoreActionStore);

  m_ce_rndr.smart_release();
  m_ce_rndr = m_cmd_buff->renderCommandEncoder(present_rp_desc.get())->retain();
  m_ce_rndr->setRenderPipelineState(m_ps_present.get());
  m_ce_rndr->setFragmentTexture(m_tex_rt.get(), 0);
  m_ce_rndr->drawPrimitives(MTL::PrimitiveTypeTriangle, NS::UInteger(0),
                            NS::UInteger(3));
  m_ce_rndr->endEncoding();
  m_ce_rndr.set_mark(true);

  m_cmd_buff->presentDrawable(m_drawable.get());
  m_cmd_buff->commit();
  m_cmd_buff.set_mark(true);

#ifdef DEBUG
  m_cmd_buff->waitUntilCompleted();
#endif

  return Return_Code::Normal;
}

void GPU_Interface::create_tlas(
    const std::unordered_map<entt::entity, std::unique_ptr<Render_Packet>>
        &render_packets) {
  if (!m_ce_as.get())
    throw std::runtime_error("AS command encoder is not available");

  /* Create instance descriptors buffer */
  const size_t instance_count = render_packets.size();
  MTL_Ptr<MTL::Buffer> instances_buff = m_device->newBuffer(
      instance_count * sizeof(MTL::AccelerationStructureInstanceDescriptor),
      MTL::ResourceStorageModeShared);

  MTL::AccelerationStructureInstanceDescriptor *instances =
      reinterpret_cast<MTL::AccelerationStructureInstanceDescriptor *>(
          instances_buff->contents());

  std::vector<MTL::AccelerationStructure *> blas_handles;
  blas_handles.reserve(instance_count);

  size_t idx = 0;
  for (const auto &[_, packet] : render_packets) {
    MTL::AccelerationStructureInstanceDescriptor &asi_desc = instances[idx];
    blas_handles.emplace_back(packet->get_as().get());
    asi_desc.accelerationStructureIndex = idx++;
    asi_desc.transformationMatrix = packet->get_transformations();
    asi_desc.options = MTL::AccelerationStructureInstanceOptionOpaque;
    asi_desc.mask = 0xFF;
    asi_desc.intersectionFunctionTableOffset = IFN_IDX::Sphere;
  }

  /* Create TLAS */
  MTL_Ptr<MTL::InstanceAccelerationStructureDescriptor> tlas_desc =
      MTL::InstanceAccelerationStructureDescriptor::alloc()->init();
  tlas_desc->setInstanceDescriptorBuffer(instances_buff.get());
  tlas_desc->setInstanceDescriptorStride(
      sizeof(MTL::AccelerationStructureInstanceDescriptor));
  tlas_desc->setInstanceCount(idx);
  tlas_desc->setUsage(MTL::AccelerationStructureUsageNone);
  if (!blas_handles.empty()) {
    NS::Array *blas_array =
        NS::Array::array(reinterpret_cast<NS::Object **>(blas_handles.data()),
                         blas_handles.size());
    tlas_desc->setInstancedAccelerationStructures(blas_array);
  }

  MTL::AccelerationStructureSizes sizes =
      m_device->accelerationStructureSizes(tlas_desc.get());
  MTL_Ptr<MTL::Buffer> scratch_buff = m_device->newBuffer(
      sizes.buildScratchBufferSize, MTL::ResourceStorageModePrivate);

  m_tlas.smart_release();
  m_tlas = m_device->newAccelerationStructure(sizes.accelerationStructureSize);
  m_ce_as->buildAccelerationStructure(m_tlas.get(), tlas_desc.get(),
                                      scratch_buff.get(), 0);
}

void GPU_Interface::poll_events() const { glfwPollEvents(); }

bool GPU_Interface::should_close() const {
  return glfwWindowShouldClose(m_window);
}

} // namespace CTNM::RHI

#endif
