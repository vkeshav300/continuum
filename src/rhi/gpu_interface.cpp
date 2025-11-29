#include "rhi/gpu_interface.hpp"
#include "math_utils.hpp"
#include "rhi/bridges.hpp"
#include "rhi/gpu_context.hpp"
#include "rhi/gpu_types.hpp"
#include "rhi/mtl_ptr.hpp"
#include "rhi/render_packet.hpp"

#include <cstdint>
#include <cstring>
#include <memory>
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
    : m_device(MTL::CreateSystemDefaultDevice()),
      m_layer(CA::MetalLayer::layer()) {
  glfw_create_window(width, height);
  mtl_load();
  mtl_create_buffs();
  mtl_create_pipelines();
}

void GPU_Interface::glfw_error_callback(const int code,
                                        const char *description) {
  throw std::runtime_error("[Error]\t(GLFW " + std::to_string(code) + ") " +
                           std::string(description));
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

    m_img_out_buff.smart_release();
    m_img_out_buff = m_device->newBuffer(width * height * sizeof(vector_float4),
                                         MTL::ResourceStorageModeShared);
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
  m_layer->setDrawableSize(CGSizeMake(m_fb_width, m_fb_height));

  m_ns_window = Bridges::get_ns_window(m_window, m_layer.get());
}

void GPU_Interface::mtl_load() {
  m_lib = m_device->newDefaultLibrary();
  if (!m_lib.get())
    throw std::runtime_error("Failed to load default library");

  m_cmd_queue = m_device->newCommandQueue();
}

void GPU_Interface::mtl_create_buffs() {
  m_cam_buff = m_device->newBuffer(sizeof(GPU_Types::Camera),
                                   MTL::ResourceStorageModeShared);
  m_img_out_buff =
      m_device->newBuffer(m_fb_width * m_fb_height * sizeof(vector_float4),
                          MTL::ResourceStorageModeShared);
}

void GPU_Interface::mtl_create_pipelines() {
  m_raytracing_fn = m_lib->newFunction(NS::String::string(
      "k_raytracer", NS::StringEncoding::UTF8StringEncoding));
  if (!m_raytracing_fn.get())
    throw std::runtime_error("Failed to find k_raytracer in default library");

  NS::Error *error = nullptr;
  m_raytracing_ps =
      m_device->newComputePipelineState(m_raytracing_fn.get(), &error);
  if (!m_raytracing_ps.get())
    throw std::runtime_error(
        "Failed to create raytracing compute pipeline state");

  m_sphere_if = m_lib->newFunction(NS::String::string(
      "sphere_intersection", NS::StringEncoding::UTF8StringEncoding));
  if (!m_sphere_if.get())
    throw std::runtime_error(
        "Failed to find sphere_intersection function in default library");

  m_sphere_if_handle = m_raytracing_ps->functionHandle(m_sphere_if.get());
  if (!m_sphere_if_handle.get())
    throw std::runtime_error(
        "Failed to create function handle for sphere_intersection");

  MTL_Ptr<MTL::IntersectionFunctionTableDescriptor> ift_desc =
      MTL::IntersectionFunctionTableDescriptor::alloc()->init();
  ift_desc->setFunctionCount(1);

  m_ift = m_raytracing_ps->newIntersectionFunctionTable(ift_desc.get());
  if (!m_ift.get())
    throw std::runtime_error("Failed to create intersection function table");

  m_ift->setFunction(m_sphere_if_handle.get(), 0);
}

GPU_Interface::~GPU_Interface() {
  if (m_window) {
    glfwDestroyWindow(m_window);
    m_window = nullptr;
    m_ns_window = nullptr;
  }

  glfwTerminate();
}

void GPU_Interface::cycle_gpu_context() {
  m_as_cmd_enc.smart_release();
  m_cmd_buff.smart_release();

  m_cmd_buff.set_mark(false);
  m_as_cmd_enc.set_mark(false);
  m_cmd_buff = m_cmd_queue->commandBuffer();
  m_as_cmd_enc = m_cmd_buff->accelerationStructureCommandEncoder();
}

GPU_Context GPU_Interface::get_gpu_context() const {
  return {m_device.get(), m_as_cmd_enc.get()};
}

void GPU_Interface::next_drawable() {
  m_drawable.smart_release();
  m_drawable = m_layer->nextDrawable();
}

uint8_t GPU_Interface::render(
    const std::unordered_map<entt::entity, std::unique_ptr<Render_Packet>>
        &render_packets,
    const entt::registry &registry) {
  next_drawable();
  if (!m_drawable.get())
    return Return_Code::Skip;

  if (!m_as_cmd_enc.get() || !m_cmd_buff.get())
    cycle_gpu_context();

  if (!render_packets.empty())
    create_tlas(render_packets);
  else
    m_tlas.smart_release();

  m_as_cmd_enc->endEncoding();
  m_as_cmd_enc.set_mark(true);

  /* Gather camera data */
  const CTNM::Components::Camera &cam = registry.get<CTNM::Components::Camera>(
      registry.view<CTNM::Components::Camera>()
          .front()); // First object with camera component is camera

  GPU_Types::Camera gpu_cam;
  gpu_cam.pos = cam.pos;
  gpu_cam.dir = cam.fpos - cam.pos;
  gpu_cam.dir = approx_eq(magnitude(gpu_cam.dir), 0) ? vec_f3{0.0f, 0.0f, 0.0f}
                                                     : normalize(gpu_cam.dir);
  std::memcpy(m_cam_buff->contents(), &gpu_cam, sizeof(gpu_cam));

  /* Cycle to compute encoder */
  m_comp_cmd_enc.smart_release();
  m_comp_cmd_enc = m_cmd_buff->computeCommandEncoder();
  m_comp_cmd_enc->setComputePipelineState(m_raytracing_ps.get());
  if (m_ift.get())
    m_comp_cmd_enc->setIntersectionFunctionTable(m_ift.get(), 0);
  if (m_tlas.get())
    m_comp_cmd_enc->setAccelerationStructure(m_tlas.get(), 0);
  m_comp_cmd_enc->setBuffer(m_cam_buff.get(), 0, 1);
  m_comp_cmd_enc->setBuffer(m_img_out_buff.get(), 0, 2);
  // m_comp_cmd_enc->dispatchThreads(...) figure this out to run raytracer

  m_comp_cmd_enc->endEncoding();
  m_comp_cmd_enc.set_mark(true);

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
  if (!m_as_cmd_enc.get())
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
    asi_desc.intersectionFunctionTableOffset = 0;
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
    MTL_Ptr<NS::Array> blas_array =
        NS::Array::array(reinterpret_cast<NS::Object **>(blas_handles.data()),
                         blas_handles.size());
    tlas_desc->setInstancedAccelerationStructures(blas_array.get());
  }

  MTL::AccelerationStructureSizes sizes =
      m_device->accelerationStructureSizes(tlas_desc.get());
  MTL_Ptr<MTL::Buffer> scratch_buff = m_device->newBuffer(
      sizes.buildScratchBufferSize, MTL::ResourceStorageModePrivate);

  m_tlas.smart_release();
  m_tlas = m_device->newAccelerationStructure(sizes.accelerationStructureSize);
  m_as_cmd_enc->buildAccelerationStructure(m_tlas.get(), tlas_desc.get(),
                                           scratch_buff.get(), 0);
}

void GPU_Interface::poll_events() const { glfwPollEvents(); }

bool GPU_Interface::should_close() const {
  return glfwWindowShouldClose(m_window);
}

} // namespace CTNM::RHI

#endif
