#pragma once

/* Numeric manipulation */
bool approx_eq(const float a, const float b);

#include <simd/simd.h>

using vec_f3 = vector_float3;
using vec_f4 = vector_float4;

using color = vector_float3;

/* Vector manipulation */
float magnitude(const vec_f3 &vec);
float magnitude(const vec_f4 &vec);

vec_f3 normalize(const vec_f3 &vec);
vec_f4 normalize(const vec_f4 &vec);
