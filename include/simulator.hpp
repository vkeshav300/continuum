#pragma once

#include <chrono>

#include <entt/entt.hpp>

namespace CTNM {

class Simulator {
public:
  Simulator() = default;
  ~Simulator() = default;

  void update(entt::registry &reg);

private:
  bool first_update = true;
  std::chrono::time_point<std::chrono::steady_clock> m_tp_last;
};

}; // namespace CTNM
