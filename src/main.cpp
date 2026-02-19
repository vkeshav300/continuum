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
  registry.emplace<CTNM::Components::AABB>(en1);
  registry.emplace<CTNM::Components::Physics>(en1, vec_f3{0.5f, 0.5f, 0.5f});
  registry.emplace<CTNM::Components::Surface>(en1);

  entt::entity en2 = registry.create();
  registry.emplace<CTNM::Components::Transform>(en2, vec_f3{3.0f, -0.5f, 0.0f});
  registry.emplace<CTNM::Components::AABB>(en2);
  registry.emplace<CTNM::Components::Physics>(en2, vec_f3{0.0f, -0.5f, 0.0f});
  registry.emplace<CTNM::Components::Surface>(en2, vec_f3{255.0f, 0.0f, 0.0f});

  entt::entity en3 = registry.create();
  registry.emplace<CTNM::Components::Transform>(en3, vec_f3{3.0f, -0.5f, 0.0f});
  registry.emplace<CTNM::Components::AABB>(en3);
  registry.emplace<CTNM::Components::Surface>(en3,
                                              vec_f3{155.0f, 0.0f, 155.0f});

  entt::entity cam = registry.create();
  registry.emplace<CTNM::Components::Camera>(cam);
  registry.get<CTNM::Components::Camera>(cam).fov = 45.0f;

  std::shared_ptr<CTNM::Stager> stager = std::make_shared<CTNM::Stager>();
  registry.on_destroy<CTNM::Components::AABB>()
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
  registry.on_destroy<CTNM::Components::AABB>()
      .disconnect<&CTNM::Stager::callback_bbox_destroyed>(*stager);

  return 0;
}
