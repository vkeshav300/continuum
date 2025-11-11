/*
 * TEMPORARY MAIN FILE
 */
#include "components.h"
#include "rhi/renderer.hpp"
#include "vectors.h"

#include <iostream>

#include <entt/entt.hpp>

int main(int argc, char *argv[]) {
  std::cout << "Continuum v0.0.0\n";

  entt::registry registry;
  entt::entity entity = registry.create();
  registry.emplace<Transform>(entity, vec_f3{0.0f, 0.0f, 0.0f});
  registry.emplace<Sphere_Bounding_Box>(entity, vec_f3{-1.0f, -1.0f, -1.0f},
                                        vec_f3{1.0f, 1.0f, 1.0f});

  CTNM::RHI::Renderer renderer = CTNM::RHI::Renderer(800, 700);
  renderer.stage(registry);
  renderer.render_to_preview(registry);

  return 0;
}
