/*
 * TEMPORARY MAIN FILE
 */
#include "dtypes/components.h"
#include "dtypes/vectors.h"
#include "rhi/gpu_interface.hpp"
#include "stager.hpp"

#include <iostream>

#include <entt/entt.hpp>

/**
 * @brief Program entry point that initializes a minimal scene and runs a single
 * preview render.
 *
 * Creates an EnTT registry with one entity (a Transform and a Bounding_Box),
 * constructs an RHI renderer with a fixed viewport size, stages the registry
 * state for rendering, and produces a preview render before exiting.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return int `0` on successful execution.
 */
int main(int argc, char *argv[]) {
  std::cout << "Continuum v0.0.0\n";

  entt::registry registry;
  entt::entity entity = registry.create();
  registry.emplace<CTNM::Components::Transform>(entity,
                                                vec_f3{0.0f, 0.0f, 0.0f});
  registry.emplace<CTNM::Components::Bounding_Box>(
      entity, 1.0f, CTNM::Components::Bounding_Box_Style::Sphere);

  CTNM::Stager stager;
  registry.on_destroy<CTNM::Components::Bounding_Box>()
      .connect<&CTNM::Stager::callback_bbox_destroyed>(stager);

  CTNM::RHI::GPU_Interface interface(800, 600);

  while (!interface.should_close()) {
    stager.stage(registry, interface.get_gpu_context());

    if (interface.render(stager.get_render_packets()) ==
        CTNM::RHI::Return_Code::Skip)
      continue;

    interface.poll_events();
  }

  /* Prevent calling callback which might not exist */
  registry.on_destroy<CTNM::Components::Bounding_Box>()
      .disconnect<&CTNM::Stager::callback_bbox_destroyed>(stager);

  return 0;
}
