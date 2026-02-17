/*
 * TEMPORARY MAIN FILE
 */
#include "components.hpp"
#include "math_utils.hpp"
#include "rhi/gpu_interface.hpp"
#include "stager.hpp"

#include <entt/entt.hpp>
#include <memory>

/**
 * @brief Application entry point that initializes the GPU, scene registry,
 * staging system, and runs the main render loop.
 *
 * Initializes a CTNM GPU interface (800×600), creates an EnTT registry with a
 * primary entity (Transform and Sphere_AABB) and a camera entity, constructs a
 * CTNM::Stager and connects a Sphere_AABB destruction callback, then enters the
 * render loop which advances the GPU context, stages scene data, issues render
 * calls, waits for staging to become idle, and processes events. Before exiting
 * the callback connection is disconnected to avoid dangling references.
 *
 * @param argc Number of command-line arguments (unused).
 * @param argv Command-line arguments (unused).
 * @return int 0 on successful exit.
 */
int main(int argc, char *argv[]) {
  CTNM::RHI::GPU_Interface interface(800, 600);

  entt::registry registry;
  entt::entity entity = registry.create();
  registry.emplace<CTNM::Components::Transform>(
      entity, vec_f3{1.0f, -2.0f, 5.0f}, vec_f3{1.0f, 1.0f, 1.0f},
      vec_f4{0.0f, 0.0f, 0.0f, 0.0f});
  registry.emplace<CTNM::Components::Sphere_AABB>(entity, 1.0f);
  entt::entity camera = registry.create();
  registry.emplace<CTNM::Components::Camera>(camera, vec_f3{0.0f, 0.0f, -5.0f},
                                             vec_f3{1.0f, -2.0f, 5.0f}, 75.0f);

  std::shared_ptr<CTNM::Stager> stager = std::make_shared<CTNM::Stager>();
  registry.on_destroy<CTNM::Components::Sphere_AABB>()
      .connect<&CTNM::Stager::callback_bbox_destroyed>(*stager);

  while (!interface.should_close()) {
    interface.cycle_gpu_context();
    stager->stage(registry, interface.get_gpu_context());

    if (interface.render(stager->get_render_packets(), stager->get_mutex(),
                         registry) == CTNM::RHI::Return_Code::Skip)
      continue;

    stager->wait_until_idle();

    interface.poll_events();
  }

  /* Prevent calling callback which might not exist */
  registry.on_destroy<CTNM::Components::Sphere_AABB>()
      .disconnect<&CTNM::Stager::callback_bbox_destroyed>(*stager);

  return 0;
}
