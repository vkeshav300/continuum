#include "rhi/gpu_interface.hpp"
#include "window.hpp"

#include <chrono>
#include <memory>
#include <thread>

int main(int argc, char *argv[]) {
  std::shared_ptr<CTNM::Window> win(
      std::make_shared<CTNM::Window>(CTNM::FB_Size{800, 600}));
  CTNM::RHI::GPU_Interface interface(win);
  const auto target_frame_time = std::chrono::milliseconds(16); // ~60 FPS

  while (!win->should_close()) {
    const auto frame_start = std::chrono::steady_clock::now();
    const uint8_t result = interface.render();

    win->poll_events();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    const auto frame_elapsed = std::chrono::steady_clock::now() - frame_start;
    if (frame_elapsed < target_frame_time)
      std::this_thread::sleep_for(target_frame_time - frame_elapsed);
  }

  return 0;
}
