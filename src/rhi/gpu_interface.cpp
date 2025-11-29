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
#include <string>
#include <unordered_map>

#include <GLFW/glfw3.h>
#include <entt/entt.hpp>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <simd/simd.h>

namespace CTNM::RHI {

/**
 * @brief Construct a macOS Metal renderer and create its GLFW window and layer.
 *
 * Initializes the system Metal device and CAMetalLayer, configures GLFW for
 * Cocoa, creates a window sized to the given dimensions, registers GLFW error
 * and framebuffer-size callbacks, sets the Metal layer's device, pixel format,
 * and drawable size, and obtains the corresponding NSWindow bridge.
 *
 * @param width Initial window framebuffer width in pixels.
 * @param height Initial window framebuffer height in pixels.
 *
 * @throws std::runtime_error If GLFW fails to initialize or the window cannot
 * be created.
 */
GPU_Interface::GPU_Interface(const uint16_t &width, const uint16_t &height)
    : m_device(MTL::CreateSystemDefaultDevice()),
      m_layer(CA::MetalLayer::layer()) {
  /* Window */
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_COCOA);
  glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_TRUE);

  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  m_window = glfwCreateWindow(width, height, "Continuum", nullptr, nullptr);

  if (!m_window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create window");
  }

  glfwSetWindowUserPointer(m_window, this);
  glfwSetErrorCallback(glfw_error_callback);
  glfwSetFramebufferSizeCallback(
      m_window,
      glfw_framebuffer_size_callback); // Executed upon window resizing

  int fb_width, fb_height;
  glfwGetFramebufferSize(m_window, &fb_width, &fb_height);
  m_layer->setDevice(m_device.get());
  m_layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
  m_layer->setDrawableSize(CGSizeMake(fb_width, fb_height));

  m_ns_window = Bridges::get_ns_window(m_window, m_layer.get());

  /* Load metal shaders */
  m_lib = m_device->newDefaultLibrary();
  if (!m_lib.get())
    throw std::runtime_error("Failed to load default library");

  m_cam_buff = m_device->newBuffer(sizeof(GPU_Types::Camera),
                                   MTL::ResourceStorageModeShared);
  m_img_out_buff = m_device->newBuffer(width * height * sizeof(vector_float4),
                                       MTL::ResourceStorageModeShared);

  m_cmd_queue = m_device->newCommandQueue();
}

/**
 * @brief Cleans up renderer resources and shuts down the platform/graphics
 * subsystems.
 *
 * Destroys the GLFW window if one exists, terminates the GLFW library, and
 * releases owned Metal objects
 */
GPU_Interface::~GPU_Interface() {
  if (m_window) {
    glfwDestroyWindow(m_window);
    m_window = nullptr;
    m_ns_window = nullptr;
  }

  glfwTerminate();
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
  // m_comp_cmd_enc->setComputePipelineState(m_rt_ps);
  m_comp_cmd_enc->setAccelerationStructure(
      render_packets.begin()->second->get_as().get(), 0);
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

void GPU_Interface::poll_events() const { glfwPollEvents(); }

bool GPU_Interface::should_close() const {
  return glfwWindowShouldClose(m_window);
}

} // namespace CTNM::RHI

#endif
