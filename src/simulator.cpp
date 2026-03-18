#include "simulator.hpp"
#include "components.hpp"

#include <entt/entt.hpp>

namespace CTNM {

void Simulator::update(entt::registry &reg) {
  if (first_update) {
    m_tp_last = std::chrono::steady_clock::now();
    first_update = false;
    return;
  }

  const auto now = std::chrono::steady_clock::now();
  const std::chrono::duration<float> _dt = now - m_tp_last;
  const float dt = _dt.count();
  m_tp_last = now;

  const auto &physics_entities =
      reg.view<Components::Transform, Components::Physics>();
  for (const auto e : physics_entities) {
    auto &&[transform, physics] =
        reg.get<Components::Transform, Components::Physics>(e);
    transform.p += physics.v * dt;
  }
}

} // namespace CTNM
