#include "rhi/renderer.hpp"
#include "rhi/window.hpp"

#include <stdexcept>

#ifdef __APPLE__

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

namespace CTNM::RHI {

Renderer::Renderer()
    : m_device(MTL::CreateSystemDefaultDevice()),
      m_window(new Window(m_device, 800, 700)) {}

Renderer::~Renderer() {
  delete m_window;
  m_window = nullptr;

  m_cmd_queue->release();
  m_library->release();
  m_device->release();
}

void Renderer::stage() {
  m_library = m_device->newDefaultLibrary();

  /* Loads shaders (no shaders currently present)
  if (!m_library)
    throw std::runtime_error("Failed to load library");
    */

  m_cmd_queue = m_device->newCommandQueue();
}

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
