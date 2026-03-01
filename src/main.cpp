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

  entt::entity en1 = reg.create();
  reg.emplace<CTNM::Components::Transform>(en1);
  reg.emplace<CTNM::Components::AABB>(en1);
  reg.emplace<CTNM::Components::Physics>(en1, vec_f3{0.5f, 0.5f, 0.5f});
  reg.emplace<CTNM::Components::Surface>(en1);

  entt::entity en2 = reg.create();
  reg.emplace<CTNM::Components::Transform>(en2, vec_f3{3.0f, -0.5f, 0.0f});
  reg.emplace<CTNM::Components::AABB>(en2);
  reg.emplace<CTNM::Components::Physics>(en2, vec_f3{0.0f, -0.5f, 0.0f});
  reg.emplace<CTNM::Components::Surface>(en2, vec_f3{255.0f, 0.0f, 0.0f});

  entt::entity en3 = reg.create();
  reg.emplace<CTNM::Components::Transform>(en3, vec_f3{3.0f, -0.5f, 0.0f});
  reg.emplace<CTNM::Components::AABB>(en3);
  reg.emplace<CTNM::Components::Surface>(en3, vec_f3{155.0f, 0.0f, 155.0f});

  entt::entity cam = reg.create();
  reg.emplace<CTNM::Components::Camera>(cam);
  reg.get<CTNM::Components::Camera>(cam).fov = 45.0f;

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

    stager.stage(gpu_context, reg);
    interface.render(stager.get_render_packets(), stager.get_mutex(),
                     stager.get_revision());

    win->end_frame();
  }

  stager.wait_until_idle();

  sink_on_aabb_destroy.disconnect();
  ev_on_cpu_completed.clear();
  ev_on_gpu_completed.clear();

  return 0;
}
