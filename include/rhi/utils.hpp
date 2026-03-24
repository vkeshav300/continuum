#pragma once

#include "../math_utils.hpp"
#include "gpu_types.hpp"
#include "mtl_ptr.hpp"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

namespace CTNM::RHI::Utils {

inline GPU_Types::vec_pf3 pack(const Math::vec_f3 &vec) {
  return GPU_Types::vec_pf3{vec.x, vec.y, vec.z};
}

inline GPU_Types::Range make_range(const size_t start) {
  return GPU_Types::Range{
      static_cast<uint32_t>(start),
      static_cast<uint32_t>(start + 1)}; // Assume length = 1
}

inline GPU_Types::Range make_range(const size_t start, const size_t end) {
  return GPU_Types::Range{static_cast<uint32_t>(start),
                          static_cast<uint32_t>(end - start)};
}

template <typename T>
inline void dynamic_resize(
    MTL::Device *device, MTL_Unique<MTL::Buffer> &buffer, size_t count,
    const NS::UInteger resource_storage_mode = MTL::ResourceStorageModeShared) {
  if (count == 0)
    count = 1;

  const size_t size = count * sizeof(T);
  if (!buffer.exists() || buffer->length() < size)
    buffer = device->newBuffer(size, resource_storage_mode);
}

}; // namespace CTNM::RHI::Utils
