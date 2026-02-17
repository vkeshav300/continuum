#pragma once

/* Numeric manipulation */
bool approx_eq(const float a, const float b);

#ifdef __APPLE__

#include <simd/simd.h>

using vec_f3 = vector_float3;
using vec_f4 = vector_float4;

#endif

/* Vector manipulation */
float magnitude(const vec_f3 &vec);
float magnitude(const vec_f4 &vec);

vec_f3 normalize(const vec_f3 &vec);
vec_f4 normalize(const vec_f4 &vec);
