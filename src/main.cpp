#include "rhi/gpu_context.hpp"
#include "rhi/gpu_interface.hpp"
#include "stager.hpp"
#include "window.hpp"

#include <chrono>
#include <memory>
#include <thread>

int main(int argc, char *argv[]) {
  entt::registry reg;
  std::shared_ptr<CTNM::Window> win(
      std::make_shared<CTNM::Window>(CTNM::FB_Size{800, 600}));
  CTNM::RHI::GPU_Interface interface(win);
  CTNM::Stager stager;
  const auto target_frame_time = std::chrono::milliseconds(16); // ~60 FPS

  auto sink_on_aabb_destroy = reg.on_destroy<CTNM::Components::AABB>();
  auto &bec_on_cpu_completed = interface.on_cpu_completed();
  auto &bec_on_gpu_completed = interface.on_gpu_completed();
  sink_on_aabb_destroy.connect<&CTNM::Stager::decommission_packet>(stager);
  bec_on_cpu_completed.connect<&CTNM::Stager::attach_decommissioned_packets>(
      stager);
  bec_on_gpu_completed.connect<&CTNM::Stager::clear_decommissioned_packets>(
      stager);

  while (!win->should_close()) {
    const auto frame_start = std::chrono::steady_clock::now();
    interface.cycle_frame();

    CTNM::RHI::GPU_Context gpu_context = interface.get_gpu_context();
    if (gpu_context.skip_frame) {
      const auto elapsed = std::chrono::steady_clock::now() - frame_start;
      if (elapsed < target_frame_time)
        std::this_thread::sleep_for(target_frame_time - elapsed);

      continue;
    }

    stager.stage(interface.get_gpu_context(), reg);
    interface.render(stager.get_render_packets(), stager.get_mutex());

    win->poll_events();
    const auto elapsed = std::chrono::steady_clock::now() - frame_start;
    if (elapsed < target_frame_time)
      std::this_thread::sleep_for(target_frame_time - elapsed);
  }

  stager.wait_until_idle();

  sink_on_aabb_destroy.disconnect();
  bec_on_cpu_completed.clear();
  bec_on_gpu_completed.clear();

  return 0;
}
