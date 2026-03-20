#ifndef __APPLE__

#include <exception>

int main(int argc, char *argv[]) {
  throw std::runtime_error("Application requires Apple system to run.");
}

#else

#include "rhi/gpu_context.hpp"
#include "rhi/gpu_interface.hpp"
#include "simulator.hpp"
#include "stager.hpp"
#include "window.hpp"

#include <chrono>
#include <memory>

inline CTNM::Components::Mesh generate_cube_mesh(const float h = 0.5f) {
  CTNM::Components::Mesh mesh{.verticies =
                                  {
                                      {{-h, -h, +h}}, {{+h, -h, +h}},
                                      {{+h, +h, +h}}, {{-h, +h, +h}}, // front
                                      {{+h, -h, -h}}, {{-h, -h, -h}},
                                      {{-h, +h, -h}}, {{+h, +h, -h}}, // back
                                      {{-h, -h, -h}}, {{-h, -h, +h}},
                                      {{-h, +h, +h}}, {{-h, +h, -h}}, // left
                                      {{+h, -h, +h}}, {{+h, -h, -h}},
                                      {{+h, +h, -h}}, {{+h, +h, +h}}, // right
                                      {{-h, +h, +h}}, {{+h, +h, +h}},
                                      {{+h, +h, -h}}, {{-h, +h, -h}}, // top
                                      {{-h, -h, -h}}, {{+h, -h, -h}},
                                      {{+h, -h, +h}}, {{-h, -h, +h}}, // bottom
                                  },
                              .indicies = {
                                  0,  1,  2,  0,  2,  3,  // front
                                  4,  5,  6,  4,  6,  7,  // back
                                  8,  9,  10, 8,  10, 11, // left
                                  12, 13, 14, 12, 14, 15, // right
                                  16, 17, 18, 16, 18, 19, // top
                                  20, 21, 22, 20, 22, 23  // bottom
                              }};
  return mesh;
}

int main(int argc, char *argv[]) {
  entt::registry reg;
  std::shared_ptr<CTNM::Window> win(std::make_shared<CTNM::Window>(
      CTNM::FB_Size{800, 600}, std::chrono::milliseconds(16))); // 16ms ~ 60fps
  CTNM::RHI::GPU_Interface interface(win);
  CTNM::Stager stager;
  CTNM::Simulator sim;

  const float h = 0.5f;
  entt::entity en1 = reg.create();
  reg.emplace<CTNM::Components::Transform>(
      en1, CTNM::Math::vec_f3{0.0f, 0.0f, 0.0f},
      CTNM::Math::vec_f3{1.0f, 1.0f, 1.0f},
      CTNM::Math::vec_f4{25.0f, 25.0f, 25.0f, 1.0f});
  reg.emplace<CTNM::Components::Physics>(en1,
                                         CTNM::Math::vec_f3{0.0f, -1.5f, 0.0f});
  reg.emplace<CTNM::Components::Mesh>(en1, generate_cube_mesh());
  reg.emplace<CTNM::Components::Surface>(
      en1, CTNM::Math::vec_f3{0.0f, 255.0f, 0.0f});

  entt::entity en2 = reg.create();
  reg.emplace<CTNM::Components::Transform>(
      en2, CTNM::Math::vec_f3{-2.0f, -2.0f, -2.0f});
  reg.emplace<CTNM::Components::Mesh>(en2, generate_cube_mesh());
  reg.emplace<CTNM::Components::Surface>(
      en2, CTNM::Math::vec_f3{0.0f, 0.0f, 255.0f});

  entt::entity cam = reg.create();
  reg.emplace<CTNM::Components::Camera>(cam);

  auto sink_on_mesh_destroy = reg.on_destroy<CTNM::Components::Mesh>();
  auto &ev_on_cpu_completed = interface.on_cpu_completed();
  auto &ev_on_gpu_completed = interface.on_gpu_completed();
  sink_on_mesh_destroy.connect<&CTNM::Stager::decommission_packet>(stager);
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

    sim.update(reg);
    stager.stage(gpu_context, reg);
    interface.render(stager.get_render_packets(), stager.get_mutex(),
                     stager.get_revision(), reg);

    win->end_frame();
  }

  stager.wait_until_idle();

  sink_on_mesh_destroy.disconnect();
  ev_on_cpu_completed.clear();
  ev_on_gpu_completed.clear();

  return 0;
}

#endif
