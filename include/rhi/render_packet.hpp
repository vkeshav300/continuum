#pragma once

#include "../components.hpp"

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

static inline MTL::PackedFloat4x3
get_mtl_transform(const CTNM::Components::Transform &transform);

class Render_Packet {
public:
  Render_Packet(const Components::Transform &transform);
  ~Render_Packet() = default;

  void update(const Components::Transform &transform);

private:
  MTL::PackedFloat4x3 m_transform;
};

} // namespace CTNM::RHI
