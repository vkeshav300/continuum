#pragma once

#include "math_utils.hpp"

#include <cstdint>
#include <vector>

namespace CTNM::Components {

struct Transform {
  vec_f3 p = {0.0f, 0.0f, 0.0f};       // Position
  vec_f3 s = {1.0f, 1.0f, 1.0f};       // Scale
  vec_f4 r = {0.0f, 0.0f, 0.0f, 0.0f}; // Rotation
};

struct Physics {
  vec_f3 v = {0.0f, 0.0f, 0.0f}; // Velocity
};

struct Vertex {
  vec_f3 pos = {0.0f, 0.0f, 0.0f};
};

struct Mesh {
  std::vector<Vertex> verticies = {};
  std::vector<uint32_t> indicies = {};
  uint64_t revision = 0;
};

struct Camera {
  vec_f3 p = {-5.0f, 0.0f, 0.0f}; // Position
  vec_f3 fp = {0.0f, 0.0f, 0.0f}; // Focused position
  float fov = 120.0f;
};

} // namespace CTNM::Components
