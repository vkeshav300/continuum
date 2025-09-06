#pragma once

struct vec_f2 {
  float x;
  float y;
};

vec_f2 operator+(const vec_f2 &a, const vec_f2 &b);
vec_f2 operator-(const vec_f2 &a, const vec_f2 &b);

struct vec_f3 {
  float x;
  float y;
  float z;
};

vec_f3 operator+(const vec_f3 &a, const vec_f3 &b);
vec_f3 operator-(const vec_f3 &a, const vec_f3 &b);

struct vec_f4 {
  float x;
  float y;
  float z;
  float w;
};

vec_f4 operator+(const vec_f4 &a, const vec_f4 &b);
vec_f4 operator-(const vec_f4 &a, const vec_f4 &b);
