#include "rhi/gpu_interface.hpp"
#include "window.hpp"

#include <chrono>
#include <memory>
#include <thread>

int main(int argc, char *argv[]) {
  std::shared_ptr<CTNM::Window> win(
      std::make_shared<CTNM::Window>(CTNM::FB_Size{800, 600}));
  CTNM::RHI::GPU_Interface interface(win);

  while (!win->should_close()) {
    win->poll_events();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  return 0;
}
