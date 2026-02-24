#include "rhi/gpu_context.hpp"
#include "rhi/gpu_interface.hpp"
#include "stager.hpp"
#include "window.hpp"

#include <chrono>
#include <memory>

int main(int argc, char *argv[]) {
  entt::registry reg;
  std::shared_ptr<CTNM::Window> win(std::make_shared<CTNM::Window>(
      CTNM::FB_Size{800, 600}, std::chrono::milliseconds(16))); // 16ms ~ 60fps
  CTNM::RHI::GPU_Interface interface(win);
  CTNM::Stager stager;

  auto sink_on_aabb_destroy = reg.on_destroy<CTNM::Components::AABB>();
  auto &ev_on_cpu_completed = interface.on_cpu_completed();
  auto &ev_on_gpu_completed = interface.on_gpu_completed();
  sink_on_aabb_destroy.connect<&CTNM::Stager::decommission_packet>(stager);
  ev_on_cpu_completed.connect<&CTNM::Stager::attach_decommissioned_packets>(
      stager);
  ev_on_gpu_completed.connect<&CTNM::Stager::clear_decommissioned_packets>(
      stager);

  while (!win->should_close()) {
    win->start_frame();
    interface.cycle_frame();

    CTNM::RHI::GPU_Context gpu_context = interface.get_gpu_context();
    if (gpu_context.skip_frame) {
      win->end_frame();
      continue;
    }

    stager.stage(interface.get_gpu_context(), reg);
    interface.render(stager.get_render_packets(), stager.get_mutex());

    win->end_frame();
  }

  stager.wait_until_idle();

  sink_on_aabb_destroy.disconnect();
  ev_on_cpu_completed.clear();
  ev_on_gpu_completed.clear();

  return 0;
}
