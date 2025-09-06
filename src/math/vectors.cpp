#include "math/vectors.hpp"

vec_f2 operator+(const vec_f2 &a, const vec_f2 &b) {
  return vec_f2{a.x + b.x, a.y + b.y};
}

vec_f2 operator-(const vec_f2 &a, const vec_f2 &b) {
  return vec_f2{a.x - b.x, a.y - b.y};
}

vec_f3 operator+(const vec_f3 &a, const vec_f3 &b) {
  return vec_f3{a.x + b.x, a.y + b.y, a.z + b.z};
}

vec_f3 operator-(const vec_f3 &a, const vec_f3 &b) {
  return vec_f3{a.x - b.x, a.y - b.y, a.z - b.z};
}

vec_f4 operator+(const vec_f4 &a, const vec_f4 &b) {
  return vec_f4{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

vec_f4 operator-(const vec_f4 &a, const vec_f4 &b) {
  return vec_f4{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}
