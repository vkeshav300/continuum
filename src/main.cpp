/*
 * TEMPORARY MAIN FILE
 */
#include "components.hpp"
#include "math_utils.hpp"
#include "rhi/gpu_interface.hpp"
#include "stager.hpp"

#include <iostream>

#include <entt/entt.hpp>

int main(int argc, char *argv[]) {
  std::cout << "Continuum v0.0.0\n";

  entt::registry registry;
  entt::entity entity = registry.create();
  registry.emplace<CTNM::Components::Transform>(
      entity, vec_f3{0.0f, 0.0f, 0.0f}, vec_f3{1.0f, 1.0f, 1.0f},
      vec_f4{0.0f, 0.0f, 0.0f, 0.0f});
  registry.emplace<CTNM::Components::Sphere_AABB>(entity, 1.0f);
  entt::entity camera = registry.create();
  registry.emplace<CTNM::Components::Camera>(entity, vec_f3{-5.0f, 0.0f, 0.0f},
                                             vec_f3{0.0f, 0.0f, 0.0f});

  CTNM::Stager stager;
  registry.on_destroy<CTNM::Components::Sphere_AABB>()
      .connect<&CTNM::Stager::callback_bbox_destroyed>(stager);

  CTNM::RHI::GPU_Interface interface(800, 600);

  while (!interface.should_close()) {
    interface.cycle_gpu_context();
    stager.stage(registry, interface.get_gpu_context());

    if (interface.render(stager.get_render_packets(), registry) ==
        CTNM::RHI::Return_Code::Skip)
      continue;

    interface.poll_events();
  }

  /* Prevent calling callback which might not exist */
  registry.on_destroy<CTNM::Components::Sphere_AABB>()
      .disconnect<&CTNM::Stager::callback_bbox_destroyed>(stager);

  return 0;
}
