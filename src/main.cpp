/*
 * TEMPORARY MAIN FILE
 */
#include "components.h"
#include "rhi/renderer.hpp"
#include "vectors.h"

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
      entity, vec_f3{-1.0f, -1.0f, -1.0f}, vec_f3{1.0f, 1.0f, 1.0f});

  CTNM::RHI::Renderer renderer = CTNM::RHI::Renderer(800, 700);
  renderer.stage(registry);
  renderer.render_to_preview(registry);

  return 0;
}
