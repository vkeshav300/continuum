#pragma once

namespace CTNM::RHI::GPU_Types {

#ifdef __METAL_VERSION__

struct Present_Vertex_Out {
  float4 p [[position]];
  float2 uv;
};

#endif

} // namespace CTNM::RHI::GPU_Types
