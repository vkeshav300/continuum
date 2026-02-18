/*
 * TEMPORARY MAIN FILE
 */
#include "components.hpp"
#include "math_utils.hpp"
#include "rhi/gpu_interface.hpp"
#include "stager.hpp"

#include <entt/entt.hpp>
#include <memory>

int main(int argc, char *argv[]) {
  CTNM::RHI::GPU_Interface interface(800, 600);

  entt::registry registry;

  entt::entity en1 = registry.create();
  registry.emplace<CTNM::Components::Transform>(en1);
  registry.emplace<CTNM::Components::Sphere_AABB>(en1);
  registry.get<CTNM::Components::Transform>(en1).v = vec_f3{0.5f, 0.5f, 0.5f};

  entt::entity en2 = registry.create();
  registry.emplace<CTNM::Components::Transform>(en2);
  registry.emplace<CTNM::Components::Sphere_AABB>(en2);
  registry.get<CTNM::Components::Transform>(en2).p = vec_f3{3.0f, -0.5f, 0.0f};
  registry.get<CTNM::Components::Transform>(en2).v = vec_f3{0.0f, -0.5f, 0.0f};

  entt::entity cam = registry.create();
  registry.emplace<CTNM::Components::Camera>(cam);
  registry.get<CTNM::Components::Camera>(cam).fov = 45.0f;

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

  /* Prevent double freeing */
  registry.on_destroy<CTNM::Components::Sphere_AABB>()
      .disconnect<&CTNM::Stager::callback_bbox_destroyed>(*stager);

  return 0;
}
