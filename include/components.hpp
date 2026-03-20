#pragma once

#include "math_utils.hpp"

#include <cstdint>
#include <vector>

namespace CTNM::Components {

struct Camera {
  Math::vec_f3 p = {-5.0f, 0.0f, 0.0f}; // Position
  Math::vec_f3 fp = {0.0f, 0.0f, 0.0f}; // Focused position
  float fov = 120.0f;
};

struct Transform {
  Math::vec_f3 p = {0.0f, 0.0f, 0.0f};       // Position
  Math::vec_f3 s = {1.0f, 1.0f, 1.0f};       // Scale
  Math::vec_f4 r = {0.0f, 0.0f, 0.0f, 0.0f}; // Rotation
};

struct Physics {
  Math::vec_f3 v = {0.0f, 0.0f, 0.0f}; // Velocity
};

struct Vertex {
  Math::vec_f3 p = {0.0f, 0.0f, 0.0f}; // Position
};

struct Mesh {
  std::vector<Vertex> verticies = {};
  std::vector<uint32_t> indicies = {};
  uint64_t revision = 0;
};

struct Surface {
  Math::vec_f3 color;
};

} // namespace CTNM::Components
