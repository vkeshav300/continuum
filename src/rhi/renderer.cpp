#include "rhi/renderer.hpp"
#include "rhi/window.hpp"

#include <stdexcept>

#ifdef __APPLE__

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

namespace CTNM::RHI {

/**
 * @brief Construct a renderer and initialize its Metal device and window.
 *
 * Initializes the renderer by creating the system's default Metal device and
 * creating an internal Window sized 800×700 backed by that device.
 */
Renderer::Renderer()
    : m_device(MTL::CreateSystemDefaultDevice()),
      m_window(new Window(m_device, 800, 700)) {}

/**
 * @brief Release renderer-owned resources and destroy the window.
 *
 * Releases the Metal command queue, library, and device, then deletes the owned Window and sets its pointer to nullptr.
 */
Renderer::~Renderer() {
  delete m_window;
  m_window = nullptr;

  m_cmd_queue->release();
  m_library->release();
  m_device->release();
}

/**
 * @brief Loads the default Metal shader library and creates a command queue.
 *
 * Acquires the device's default Metal library and stores it in m_library, then
 * creates a command queue and stores it in m_cmd_queue. If the library cannot
 * be obtained, m_library will remain null and no exception is thrown.
 */
void Renderer::stage() {
  m_library = m_device->newDefaultLibrary();

  /* Loads shaders (no shaders currently present)
  if (!m_library)
    throw std::runtime_error("Failed to load library");
    */

  m_cmd_queue = m_device->newCommandQueue();
}

/**
 * @brief Runs the renderer's main loop until the associated window closes.
 *
 * Presents available Metal drawables each frame, commits their command buffers,
 * waits for completion in debug builds, and polls window events. Frames that
 * have no available drawable are skipped.
 */
void Renderer::render() {
  while (!m_window->should_close()) {
    NS::AutoreleasePool *pool =
        NS::AutoreleasePool::alloc()
            ->init(); // Automatically releases objc pointers within scope

    m_window->next_drawable(); // Cycle to next drawable frame
    if (!m_window->drawable()) {
      pool->release();
      continue;
    }

    m_cmd_buffer = m_cmd_queue->commandBuffer();

    // render stuff

    m_cmd_buffer->presentDrawable(m_window->get_metal_drawable());
    // end render command encoder encoding
    m_cmd_buffer->commit();

#ifdef DEBUG
    m_cmd_buffer->waitUntilCompleted();
#endif

    pool->release();
    m_window->poll_events();
  }
}

} // namespace CTNM::RHI

#endif