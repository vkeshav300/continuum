#pragma once

#include "window.hpp"

#ifdef __APPLE__

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

class Renderer {
private:
  MTL::Device *m_device;
  MTL::Library *m_library;
  MTL::CommandQueue *m_cmd_queue;
  MTL::CommandBuffer *m_cmd_buffer;

  Window *m_window;

public:
  Renderer();
  ~Renderer();

  void stage();
  void render();
};

} // namespace CTNM::RHI

#endif

