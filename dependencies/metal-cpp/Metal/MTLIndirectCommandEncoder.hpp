//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLIndirectCommandEncoder.hpp
//
// Copyright 2020-2025 Apple Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

#include "../Foundation/Foundation.hpp"
#include "MTLArgument.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLRenderCommandEncoder.hpp"
#include "MTLTypes.hpp"

namespace MTL
{
class Buffer;
class ComputePipelineState;
class RenderPipelineState;

class IndirectRenderCommand : public NS::Referencing<IndirectRenderCommand>
{
public:
    void clearBarrier();

    void drawIndexedPatches(NS::UInteger numberOfPatchControlPoints, NS::UInteger patchStart, NS::UInteger patchCount, const MTL::Buffer* patchIndexBuffer, NS::UInteger patchIndexBufferOffset, const MTL::Buffer* controlPointIndexBuffer, NS::UInteger controlPointIndexBufferOffset, NS::UInteger instanceCount, NS::UInteger baseInstance, const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger instanceStride);

    void drawIndexedPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger indexCount, MTL::IndexType indexType, const MTL::Buffer* indexBuffer, NS::UInteger indexBufferOffset, NS::UInteger instanceCount, NS::Integer baseVertex, NS::UInteger baseInstance);

    void drawMeshThreadgroups(MTL::Size threadgroupsPerGrid, MTL::Size threadsPerObjectThreadgroup, MTL::Size threadsPerMeshThreadgroup);

    void drawMeshThreads(MTL::Size threadsPerGrid, MTL::Size threadsPerObjectThreadgroup, MTL::Size threadsPerMeshThreadgroup);

    void drawPatches(NS::UInteger numberOfPatchControlPoints, NS::UInteger patchStart, NS::UInteger patchCount, const MTL::Buffer* patchIndexBuffer, NS::UInteger patchIndexBufferOffset, NS::UInteger instanceCount, NS::UInteger baseInstance, const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger instanceStride);

    void drawPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger vertexStart, NS::UInteger vertexCount, NS::UInteger instanceCount, NS::UInteger baseInstance);

    void reset();

    void setBarrier();

    void setCullMode(MTL::CullMode cullMode);

    void setDepthBias(float depthBias, float slopeScale, float clamp);

    void setDepthClipMode(MTL::DepthClipMode depthClipMode);

    void setDepthStencilState(const MTL::DepthStencilState* depthStencilState);

    void setFragmentBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index);

    void setFrontFacingWinding(MTL::Winding frontFacingWindning);

    void setMeshBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index);

    void setObjectBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index);

    void setObjectThreadgroupMemoryLength(NS::UInteger length, NS::UInteger index);

    void setRenderPipelineState(const MTL::RenderPipelineState* pipelineState);

    void setTriangleFillMode(MTL::TriangleFillMode fillMode);

    void setVertexBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index);
    void setVertexBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger stride, NS::UInteger index);
};
class IndirectComputeCommand : public NS::Referencing<IndirectComputeCommand>
{
public:
    void clearBarrier();

    void concurrentDispatchThreadgroups(MTL::Size threadgroupsPerGrid, MTL::Size threadsPerThreadgroup);

    void concurrentDispatchThreads(MTL::Size threadsPerGrid, MTL::Size threadsPerThreadgroup);

    void reset();

    void setBarrier();

    void setComputePipelineState(const MTL::ComputePipelineState* pipelineState);

    void setImageblockWidth(NS::UInteger width, NS::UInteger height);

    void setKernelBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index);
    void setKernelBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger stride, NS::UInteger index);

    void setStageInRegion(MTL::Region region);

    void setThreadgroupMemoryLength(NS::UInteger length, NS::UInteger index);
};

}
/**
 * @brief Clears any barrier state on the indirect render command.
 *
 * This removes a previously set barrier so subsequent indirect commands encode without that barrier.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::clearBarrier()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(clearBarrier));
}

/**
 * @brief Configures an indirect indexed tessellated patch draw using provided patch and control-point index buffers.
 *
 * Configures this indirect render command to draw indexed patches with tessellation by specifying index buffers,
 * ranges, instance parameters, and the tessellation factor buffer with its offset and per-instance stride.
 *
 * @param numberOfPatchControlPoints Number of control points per patch.
 * @param patchStart Start index of the first patch to draw.
 * @param patchCount Number of patches to draw.
 * @param patchIndexBuffer Buffer containing patch indices.
 * @param patchIndexBufferOffset Byte offset into `patchIndexBuffer` where patch indices begin.
 * @param controlPointIndexBuffer Buffer containing control-point indices.
 * @param controlPointIndexBufferOffset Byte offset into `controlPointIndexBuffer` where control-point indices begin.
 * @param instanceCount Number of instances to draw.
 * @param baseInstance Base instance value added to each instance's ID.
 * @param buffer Tessellation factor buffer (per-patch or per-instance factors).
 * @param offset Byte offset into `buffer` where tessellation factors begin.
 * @param instanceStride Stride, in bytes, between tessellation factor data for consecutive instances.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::drawIndexedPatches(NS::UInteger numberOfPatchControlPoints, NS::UInteger patchStart, NS::UInteger patchCount, const MTL::Buffer* patchIndexBuffer, NS::UInteger patchIndexBufferOffset, const MTL::Buffer* controlPointIndexBuffer, NS::UInteger controlPointIndexBufferOffset, NS::UInteger instanceCount, NS::UInteger baseInstance, const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger instanceStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawIndexedPatches_patchStart_patchCount_patchIndexBuffer_patchIndexBufferOffset_controlPointIndexBuffer_controlPointIndexBufferOffset_instanceCount_baseInstance_tessellationFactorBuffer_tessellationFactorBufferOffset_tessellationFactorBufferInstanceStride_), numberOfPatchControlPoints, patchStart, patchCount, patchIndexBuffer, patchIndexBufferOffset, controlPointIndexBuffer, controlPointIndexBufferOffset, instanceCount, baseInstance, buffer, offset, instanceStride);
}

/**
 * @brief Configure the indirect render command to draw indexed primitives.
 *
 * Sets up an indexed draw using the provided primitive type, index buffer and
 * instance/vertex offsets; the command is executed later by an encoder that
 * consumes this indirect command.
 *
 * @param primitiveType The primitive topology to render (e.g., triangle, line).
 * @param indexCount The number of indices to read from the index buffer.
 * @param indexType The type/size of each index in the index buffer.
 * @param indexBuffer Buffer containing index data.
 * @param indexBufferOffset Byte offset in `indexBuffer` where index data begins.
 * @param instanceCount The number of instances to draw.
 * @param baseVertex Signed offset added to each index when fetching vertex data.
 * @param baseInstance The first instance ID for the draw.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::drawIndexedPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger indexCount, MTL::IndexType indexType, const MTL::Buffer* indexBuffer, NS::UInteger indexBufferOffset, NS::UInteger instanceCount, NS::Integer baseVertex, NS::UInteger baseInstance)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawIndexedPrimitives_indexCount_indexType_indexBuffer_indexBufferOffset_instanceCount_baseVertex_baseInstance_), primitiveType, indexCount, indexType, indexBuffer, indexBufferOffset, instanceCount, baseVertex, baseInstance);
}

/**
 * @brief Configures an indirect mesh dispatch using grid and threadgroup sizing.
 *
 * Sets up this indirect render command to dispatch mesh work with the specified number of
 * threadgroups and the per-object and per-mesh threadgroup sizes.
 *
 * @param threadgroupsPerGrid Number of threadgroups across the grid.
 * @param threadsPerObjectThreadgroup Number of threads in each object threadgroup.
 * @param threadsPerMeshThreadgroup Number of threads in each mesh threadgroup.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::drawMeshThreadgroups(MTL::Size threadgroupsPerGrid, MTL::Size threadsPerObjectThreadgroup, MTL::Size threadsPerMeshThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawMeshThreadgroups_threadsPerObjectThreadgroup_threadsPerMeshThreadgroup_), threadgroupsPerGrid, threadsPerObjectThreadgroup, threadsPerMeshThreadgroup);
}

/**
 * @brief Configure an indirect mesh-thread dispatch with explicit grid and threadgroup sizes.
 *
 * Sets up this indirect render command to draw using mesh threads, specifying the total
 * threads per dispatch and the threadgroup sizes for object and mesh threadgroups.
 *
 * @param threadsPerGrid Total number of threads to dispatch across the grid.
 * @param threadsPerObjectThreadgroup Number of threads in each object threadgroup.
 * @param threadsPerMeshThreadgroup Number of threads in each mesh threadgroup.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::drawMeshThreads(MTL::Size threadsPerGrid, MTL::Size threadsPerObjectThreadgroup, MTL::Size threadsPerMeshThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawMeshThreads_threadsPerObjectThreadgroup_threadsPerMeshThreadgroup_), threadsPerGrid, threadsPerObjectThreadgroup, threadsPerMeshThreadgroup);
}

/**
 * @brief Configures an indirect non-indexed patch draw with tessellation and instance parameters.
 *
 * Configures this indirect render command to draw a sequence of patches using the provided
 * patch-control-point count, patch index buffer, and per-instance buffer/stride information.
 *
 * @param numberOfPatchControlPoints Number of control points per patch.
 * @param patchStart Index of the first patch to draw.
 * @param patchCount Number of patches to draw.
 * @param patchIndexBuffer Buffer containing patch indices; may be nullptr if not used.
 * @param patchIndexBufferOffset Byte offset into `patchIndexBuffer` where indices begin.
 * @param instanceCount Number of instances to draw for each patch.
 * @param baseInstance Base instance value added to each generated instance ID.
 * @param buffer Buffer supplying per-instance or tessellation-factor data.
 * @param offset Byte offset into `buffer` where the per-instance/tessellation data begins.
 * @param instanceStride Byte stride between successive per-instance entries in `buffer`.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::drawPatches(NS::UInteger numberOfPatchControlPoints, NS::UInteger patchStart, NS::UInteger patchCount, const MTL::Buffer* patchIndexBuffer, NS::UInteger patchIndexBufferOffset, NS::UInteger instanceCount, NS::UInteger baseInstance, const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger instanceStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawPatches_patchStart_patchCount_patchIndexBuffer_patchIndexBufferOffset_instanceCount_baseInstance_tessellationFactorBuffer_tessellationFactorBufferOffset_tessellationFactorBufferInstanceStride_), numberOfPatchControlPoints, patchStart, patchCount, patchIndexBuffer, patchIndexBufferOffset, instanceCount, baseInstance, buffer, offset, instanceStride);
}

/**
 * @brief Configures an indirect non-indexed primitives draw with a vertex range and instance parameters.
 *
 * @param primitiveType The primitive topology to render (e.g., point, line, triangle).
 * @param vertexStart The first vertex index to draw from the bound vertex buffers.
 * @param vertexCount The number of vertices to draw.
 * @param instanceCount The number of instances to draw.
 * @param baseInstance A value added to each instance's instance ID when fetching per-instance data.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::drawPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger vertexStart, NS::UInteger vertexCount, NS::UInteger instanceCount, NS::UInteger baseInstance)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawPrimitives_vertexStart_vertexCount_instanceCount_baseInstance_), primitiveType, vertexStart, vertexCount, instanceCount, baseInstance);
}

/**
 * @brief Reset the indirect render command to its initial state.
 *
 * Restores the command's configuration to a clean baseline so subsequent
 * state changes and draw invocations start from a known default.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

/**
 * @brief Inserts a barrier into this indirect render command to enforce ordering and synchronize resource access for subsequent commands.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setBarrier()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBarrier));
}

/**
 * @brief Sets the triangle culling mode for this indirect render command.
 *
 * Configures which triangle faces are culled during rasterization when the command is executed.
 *
 * @param cullMode The culling mode to apply (e.g., none, front, back).
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setCullMode(MTL::CullMode cullMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCullMode_), cullMode);
}

/**
 * @brief Configure depth bias parameters for this indirect render command.
 *
 * Sets the constant depth bias, the slope-scaled bias factor, and the maximum
 * allowed bias that will be applied during rasterization for subsequent draws.
 *
 * @param depthBias Constant value added to depth.
 * @param slopeScale Value multiplied by the maximum depth slope to compute a slope-dependent bias.
 * @param clamp Maximum absolute value that the computed depth bias may take.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setDepthBias(float depthBias, float slopeScale, float clamp)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthBias_slopeScale_clamp_), depthBias, slopeScale, clamp);
}

/**
 * @brief Sets the depth clipping mode used when this indirect render command is executed.
 *
 * @param depthClipMode The depth clipping mode to apply (controls whether fragments outside the near/far depth range are clipped).
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setDepthClipMode(MTL::DepthClipMode depthClipMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthClipMode_), depthClipMode);
}

/**
 * @brief Assigns the depth and stencil state to use when this indirect render command executes.
 *
 * @param depthStencilState Depth-stencil state object that will be applied for depth and stencil testing during the command; pass `nullptr` to clear any previously set state.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setDepthStencilState(const MTL::DepthStencilState* depthStencilState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthStencilState_), depthStencilState);
}

/**
 * @brief Sets the fragment buffer to use when this indirect render command is executed.
 *
 * Binds a buffer for fragment-stage access with the given byte offset at the specified argument index.
 *
 * @param buffer The buffer to bind for the fragment stage.
 * @param offset Byte offset into `buffer` where the bound data begins.
 * @param index Argument index at which to bind the buffer.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setFragmentBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFragmentBuffer_offset_atIndex_), buffer, offset, index);
}

/**
 * @brief Sets the winding order used to determine front-facing triangles for this indirect render command.
 *
 * @param frontFacingWindning The winding order to treat as front-facing.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setFrontFacingWinding(MTL::Winding frontFacingWindning)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFrontFacingWinding_), frontFacingWindning);
}

/**
 * @brief Binds a mesh buffer to this indirect render command at the specified binding index and byte offset.
 *
 * @param buffer The mesh buffer to bind; may be nullptr to unbind.
 * @param offset Byte offset into the buffer where the bound data begins.
 * @param index Binding index for the mesh buffer slot.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setMeshBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMeshBuffer_offset_atIndex_), buffer, offset, index);
}

/**
 * @brief Binds an object buffer to the indirect render command at a specified index.
 *
 * @param buffer Pointer to the buffer to bind as the object buffer.
 * @param offset Byte offset within the buffer where the bound region begins.
 * @param index Object buffer binding index used by the command.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setObjectBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObjectBuffer_offset_atIndex_), buffer, offset, index);
}

/**
 * @brief Set the per-object threadgroup memory allocation for an object binding.
 *
 * Configures the amount of threadgroup (shared) memory, in bytes, reserved for the object at the given index when this indirect render command executes.
 *
 * @param length Size in bytes of threadgroup memory to allocate for the object.
 * @param index Binding index of the object whose threadgroup memory length is being set.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setObjectThreadgroupMemoryLength(NS::UInteger length, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObjectThreadgroupMemoryLength_atIndex_), length, index);
}

/**
 * @brief Assigns the render pipeline state to be used when this indirect render command is executed.
 *
 * @param pipelineState Pointer to the RenderPipelineState to bind for the command.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setRenderPipelineState(const MTL::RenderPipelineState* pipelineState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRenderPipelineState_), pipelineState);
}

/**
 * @brief Sets the triangle rasterization fill mode for this indirect render command.
 *
 * @param fillMode The triangle fill mode to use (controls whether triangles are filled or drawn as lines).
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setTriangleFillMode(MTL::TriangleFillMode fillMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTriangleFillMode_), fillMode);
}

/**
 * @brief Binds a vertex buffer to the command at a specific vertex buffer slot.
 *
 * Binds the provided buffer to the given vertex buffer index for this indirect render command, applying the supplied byte offset.
 *
 * @param buffer Pointer to the vertex buffer to bind.
 * @param offset Byte offset into `buffer` where vertex data begins.
 * @param index Vertex buffer slot index to bind the buffer to.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setVertexBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexBuffer_offset_atIndex_), buffer, offset, index);
}

/**
 * @brief Binds a vertex buffer to this indirect render command with a specified byte offset and per-vertex stride.
 *
 * @param buffer Pointer to the vertex buffer to bind.
 * @param offset Byte offset into the buffer where vertex data begins.
 * @param stride Byte stride between consecutive vertices.
 * @param index Vertex buffer slot index to bind the buffer to.
 */
_MTL_INLINE void MTL::IndirectRenderCommand::setVertexBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger stride, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexBuffer_offset_attributeStride_atIndex_), buffer, offset, stride, index);
}

/**
 * @brief Clears any previously set barrier on this indirect compute command.
 *
 * Calling this removes a barrier so subsequent commands encoded by this indirect
 * command are not ordered by that barrier.
 */
_MTL_INLINE void MTL::IndirectComputeCommand::clearBarrier()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(clearBarrier));
}

/**
 * @brief Configures this indirect compute command to perform a concurrent dispatch of threadgroups.
 *
 * Sets the threadgroup grid size and the per-threadgroup thread counts to use when this command is executed.
 *
 * @param threadgroupsPerGrid Number of threadgroups to dispatch in each dimension.
 * @param threadsPerThreadgroup Number of threads per threadgroup in each dimension.
 */
_MTL_INLINE void MTL::IndirectComputeCommand::concurrentDispatchThreadgroups(MTL::Size threadgroupsPerGrid, MTL::Size threadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(concurrentDispatchThreadgroups_threadsPerThreadgroup_), threadgroupsPerGrid, threadsPerThreadgroup);
}

/**
 * @brief Configures an indirect concurrent thread dispatch with the given grid and threadgroup sizes.
 *
 * @param threadsPerGrid The total number of threads to execute across the dispatch grid.
 * @param threadsPerThreadgroup The number of threads contained in each threadgroup.
 */
_MTL_INLINE void MTL::IndirectComputeCommand::concurrentDispatchThreads(MTL::Size threadsPerGrid, MTL::Size threadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(concurrentDispatchThreads_threadsPerThreadgroup_), threadsPerGrid, threadsPerThreadgroup);
}

/**
 * @brief Reset the indirect compute command to its initial, unconfigured state.
 *
 * After calling this, previously recorded dispatch settings, bound buffers, and
 * per-command state are cleared so the command can be reconfigured from a clean baseline.
 */
_MTL_INLINE void MTL::IndirectComputeCommand::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

/**
 * @brief Inserts a synchronization barrier for this indirect compute command.
 *
 * Ensures prior memory and execution effects are observed before subsequent indirect commands are executed.
 */
_MTL_INLINE void MTL::IndirectComputeCommand::setBarrier()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBarrier));
}

/**
 * @brief Sets the compute pipeline state for this indirect compute command.
 *
 * @param pipelineState The compute pipeline state to bind to the command.
 */
_MTL_INLINE void MTL::IndirectComputeCommand::setComputePipelineState(const MTL::ComputePipelineState* pipelineState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setComputePipelineState_), pipelineState);
}

/**
 * @brief Configure the imageblock dimensions used by this indirect compute command.
 *
 * @param width Width of the imageblock in pixels.
 * @param height Height of the imageblock in pixels.
 */
_MTL_INLINE void MTL::IndirectComputeCommand::setImageblockWidth(NS::UInteger width, NS::UInteger height)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setImageblockWidth_height_), width, height);
}

/**
 * @brief Bind a buffer to the compute kernel argument slot for this indirect command.
 *
 * Binds `buffer` to the kernel argument at `index`, using `offset` bytes from the buffer start.
 *
 * @param buffer Pointer to the buffer to bind.
 * @param offset Byte offset within `buffer` where the binding begins.
 * @param index Argument slot index in the kernel's binding table.
 */
_MTL_INLINE void MTL::IndirectComputeCommand::setKernelBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setKernelBuffer_offset_atIndex_), buffer, offset, index);
}

/**
 * @brief Sets the kernel buffer, byte offset, and attribute stride for the specified argument index on this indirect compute command.
 *
 * @param buffer The buffer to bind to the kernel argument.
 * @param offset Byte offset into the buffer where data begins.
 * @param stride Byte distance between consecutive attributes/elements in the buffer.
 * @param index Argument index at which to set the buffer.
 */
_MTL_INLINE void MTL::IndirectComputeCommand::setKernelBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger stride, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setKernelBuffer_offset_attributeStride_atIndex_), buffer, offset, stride, index);
}

/**
 * @brief Sets the region used for stage-in data.
 *
 * @param region The region that defines the area used for stage-in data during the compute dispatch.
 */
_MTL_INLINE void MTL::IndirectComputeCommand::setStageInRegion(MTL::Region region)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStageInRegion_), region);
}

/**
 * @brief Sets the length, in bytes, of threadgroup-local memory for a specific index.
 *
 * @param length Size in bytes to allocate for the threadgroup memory at the given index.
 * @param index The threadgroup memory index to set.
 */
_MTL_INLINE void MTL::IndirectComputeCommand::setThreadgroupMemoryLength(NS::UInteger length, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setThreadgroupMemoryLength_atIndex_), length, index);
}