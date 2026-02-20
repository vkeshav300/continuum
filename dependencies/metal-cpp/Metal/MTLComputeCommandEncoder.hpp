//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLComputeCommandEncoder.hpp
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
#include "MTLCommandBuffer.hpp"
#include "MTLCommandEncoder.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLTypes.hpp"
#include <cstdint>

namespace MTL
{
class AccelerationStructure;
class Buffer;
class ComputePipelineState;
class CounterSampleBuffer;
class Fence;
class Heap;
class IndirectCommandBuffer;
class IntersectionFunctionTable;
class Resource;
class SamplerState;
class Texture;
class VisibleFunctionTable;

struct DispatchThreadgroupsIndirectArguments
{
    uint32_t threadgroupsPerGrid[3];
} _MTL_PACKED;

struct DispatchThreadsIndirectArguments
{
    uint32_t threadsPerGrid[3];
    uint32_t threadsPerThreadgroup[3];
} _MTL_PACKED;

struct StageInRegionIndirectArguments
{
    uint32_t stageInOrigin[3];
    uint32_t stageInSize[3];
} _MTL_PACKED;

class ComputeCommandEncoder : public NS::Referencing<ComputeCommandEncoder, CommandEncoder>
{
public:
    void         dispatchThreadgroups(MTL::Size threadgroupsPerGrid, MTL::Size threadsPerThreadgroup);
    void         dispatchThreadgroups(const MTL::Buffer* indirectBuffer, NS::UInteger indirectBufferOffset, MTL::Size threadsPerThreadgroup);

    void         dispatchThreads(MTL::Size threadsPerGrid, MTL::Size threadsPerThreadgroup);

    DispatchType dispatchType() const;

    void         executeCommandsInBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, NS::Range executionRange);
    void         executeCommandsInBuffer(const MTL::IndirectCommandBuffer* indirectCommandbuffer, const MTL::Buffer* indirectRangeBuffer, NS::UInteger indirectBufferOffset);

    void         memoryBarrier(MTL::BarrierScope scope);
    void         memoryBarrier(const MTL::Resource* const resources[], NS::UInteger count);

    void         sampleCountersInBuffer(const MTL::CounterSampleBuffer* sampleBuffer, NS::UInteger sampleIndex, bool barrier);

    void         setAccelerationStructure(const MTL::AccelerationStructure* accelerationStructure, NS::UInteger bufferIndex);

    void         setBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index);
    void         setBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger stride, NS::UInteger index);
    void         setBufferOffset(NS::UInteger offset, NS::UInteger index);
    void         setBufferOffset(NS::UInteger offset, NS::UInteger stride, NS::UInteger index);

    void         setBuffers(const MTL::Buffer* const buffers[], const NS::UInteger offsets[], NS::Range range);
    void         setBuffers(const MTL::Buffer* const buffers[], const NS::UInteger* offsets, const NS::UInteger* strides, NS::Range range);

    void         setBytes(const void* bytes, NS::UInteger length, NS::UInteger index);
    void         setBytes(const void* bytes, NS::UInteger length, NS::UInteger stride, NS::UInteger index);

    void         setComputePipelineState(const MTL::ComputePipelineState* state);

    void         setImageblockWidth(NS::UInteger width, NS::UInteger height);

    void         setIntersectionFunctionTable(const MTL::IntersectionFunctionTable* intersectionFunctionTable, NS::UInteger bufferIndex);
    void         setIntersectionFunctionTables(const MTL::IntersectionFunctionTable* const intersectionFunctionTables[], NS::Range range);

    void         setSamplerState(const MTL::SamplerState* sampler, NS::UInteger index);
    void         setSamplerState(const MTL::SamplerState* sampler, float lodMinClamp, float lodMaxClamp, NS::UInteger index);
    void         setSamplerStates(const MTL::SamplerState* const samplers[], NS::Range range);
    void         setSamplerStates(const MTL::SamplerState* const samplers[], const float lodMinClamps[], const float lodMaxClamps[], NS::Range range);

    void         setStageInRegion(MTL::Region region);
    void         setStageInRegion(const MTL::Buffer* indirectBuffer, NS::UInteger indirectBufferOffset);

    void         setTexture(const MTL::Texture* texture, NS::UInteger index);
    void         setTextures(const MTL::Texture* const textures[], NS::Range range);

    void         setThreadgroupMemoryLength(NS::UInteger length, NS::UInteger index);

    void         setVisibleFunctionTable(const MTL::VisibleFunctionTable* visibleFunctionTable, NS::UInteger bufferIndex);
    void         setVisibleFunctionTables(const MTL::VisibleFunctionTable* const visibleFunctionTables[], NS::Range range);

    void         updateFence(const MTL::Fence* fence);

    void         useHeap(const MTL::Heap* heap);
    void         useHeaps(const MTL::Heap* const heaps[], NS::UInteger count);

    void         useResource(const MTL::Resource* resource, MTL::ResourceUsage usage);
    void         useResources(const MTL::Resource* const resources[], NS::UInteger count, MTL::ResourceUsage usage);

    void         waitForFence(const MTL::Fence* fence);
};

}

/**
 * @brief Enqueues a compute dispatch with explicit grid and threadgroup dimensions.
 *
 * Schedules a compute kernel to execute with the specified number of threadgroups for the grid
 * and the specified number of threads per threadgroup. Both parameters represent 3D counts
 * (x, y, z).
 *
 * @param threadgroupsPerGrid Number of threadgroups to dispatch in each dimension.
 * @param threadsPerThreadgroup Number of threads in each threadgroup for each dimension.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::dispatchThreadgroups(MTL::Size threadgroupsPerGrid, MTL::Size threadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(dispatchThreadgroups_threadsPerThreadgroup_), threadgroupsPerGrid, threadsPerThreadgroup);
}

/**
 * @brief Enqueues a threadgroup dispatch using threadgroup counts read from an indirect buffer.
 *
 * The indirect buffer must contain a DispatchThreadgroupsIndirectArguments structure (or equivalent
 * data) at the specified byte offset; its contents are used as the threadgroups-per-grid values.
 *
 * @param indirectBuffer Buffer that supplies the dispatch arguments.
 * @param indirectBufferOffset Byte offset into `indirectBuffer` where the dispatch arguments begin.
 * @param threadsPerThreadgroup Number of threads in each threadgroup.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::dispatchThreadgroups(const MTL::Buffer* indirectBuffer, NS::UInteger indirectBufferOffset, MTL::Size threadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(dispatchThreadgroupsWithIndirectBuffer_indirectBufferOffset_threadsPerThreadgroup_), indirectBuffer, indirectBufferOffset, threadsPerThreadgroup);
}

/**
 * @brief Enqueues a compute dispatch using explicit per-grid and per-threadgroup thread counts.
 *
 * @param threadsPerGrid Total number of threads to execute across the grid, specified as an MTL::Size (width, height, depth).
 * @param threadsPerThreadgroup Number of threads in each threadgroup (workgroup), specified as an MTL::Size (width, height, depth).
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::dispatchThreads(MTL::Size threadsPerGrid, MTL::Size threadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(dispatchThreads_threadsPerThreadgroup_), threadsPerGrid, threadsPerThreadgroup);
}

/**
 * @brief Queries the compute encoder's current dispatch interpretation.
 *
 * @return MTL::DispatchType The dispatch type currently configured on this encoder.
 */
_MTL_INLINE MTL::DispatchType MTL::ComputeCommandEncoder::dispatchType() const
{
    return Object::sendMessage<MTL::DispatchType>(this, _MTL_PRIVATE_SEL(dispatchType));
}

/**
 * @brief Executes a contiguous range of commands from an indirect command buffer.
 *
 * Executes the commands encoded in indirectCommandBuffer specified by executionRange on this compute command encoder.
 *
 * @param indirectCommandBuffer The indirect command buffer containing encoded commands to execute.
 * @param executionRange The range of commands within the indirect command buffer to execute.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::executeCommandsInBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, NS::Range executionRange)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(executeCommandsInBuffer_withRange_), indirectCommandBuffer, executionRange);
}

/**
 * @brief Executes commands from an indirect command buffer using an indirect range buffer.
 *
 * Executes commands encoded in the specified `indirectCommandbuffer`, where the specific
 * command range(s) to execute are provided by `indirectRangeBuffer` at the given byte
 * `indirectBufferOffset`.
 *
 * @param indirectCommandbuffer The indirect command buffer whose commands will be executed.
 * @param indirectRangeBuffer A buffer that provides the execution range data used to select which commands from `indirectCommandbuffer` to run.
 * @param indirectBufferOffset Byte offset into `indirectRangeBuffer` where the execution range data begins.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::executeCommandsInBuffer(const MTL::IndirectCommandBuffer* indirectCommandbuffer, const MTL::Buffer* indirectRangeBuffer, NS::UInteger indirectBufferOffset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(executeCommandsInBuffer_indirectBuffer_indirectBufferOffset_), indirectCommandbuffer, indirectRangeBuffer, indirectBufferOffset);
}

/**
 * @brief Enforces a memory barrier for the given barrier scope.
 *
 * Ensures memory ordering and visibility for resources and operations covered by the specified scope.
 *
 * @param scope The BarrierScope that defines the range of resources and operations the barrier applies to.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::memoryBarrier(MTL::BarrierScope scope)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(memoryBarrierWithScope_), scope);
}

/**
 * @brief Enforces a memory barrier for a list of resources to synchronize their GPU memory accesses.
 *
 * Ensures that prior memory writes to the specified resources are made visible to subsequent GPU operations that access those resources.
 *
 * @param resources Array of resource pointers to apply the barrier to.
 * @param count Number of resources in the `resources` array.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::memoryBarrier(const MTL::Resource* const resources[], NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(memoryBarrierWithResources_count_), resources, count);
}

/**
 * @brief Samples GPU counter values into a counter sample buffer at a given index.
 *
 * Records a counter sample from the encoder's current point into the specified sample buffer.
 *
 * @param sampleBuffer Counter sample buffer to receive the sample.
 * @param sampleIndex Index within the sample buffer where the sample will be stored.
 * @param barrier If `true`, inserts a barrier to ensure prior GPU work is visible to the sampled counters.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::sampleCountersInBuffer(const MTL::CounterSampleBuffer* sampleBuffer, NS::UInteger sampleIndex, bool barrier)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(sampleCountersInBuffer_atSampleIndex_withBarrier_), sampleBuffer, sampleIndex, barrier);
}

/**
 * @brief Binds an acceleration structure to the compute encoder at the given buffer index.
 *
 * @param accelerationStructure Acceleration structure to bind.
 * @param bufferIndex Buffer slot index where the acceleration structure will be set.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setAccelerationStructure(const MTL::AccelerationStructure* accelerationStructure, NS::UInteger bufferIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAccelerationStructure_atBufferIndex_), accelerationStructure, bufferIndex);
}

/**
 * @brief Binds a buffer to the compute encoder at the specified argument index.
 *
 * Makes the provided buffer available to the compute pipeline for the given argument index, with the shader-visible region starting at the specified byte offset.
 *
 * @param buffer Pointer to the buffer to bind.
 * @param offset Byte offset within the buffer where the shader-visible region begins.
 * @param index Argument index in the compute function where the buffer will be bound.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBuffer_offset_atIndex_), buffer, offset, index);
}

/**
 * @brief Bind a buffer to the encoder at a specific index with an explicit byte offset and per-element stride.
 *
 * @param buffer The buffer to bind.
 * @param offset Byte offset into the buffer where binding begins.
 * @param stride Per-element byte stride to use when the shader reads the bound buffer.
 * @param index The resource index to which the buffer will be bound.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger stride, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBuffer_offset_attributeStride_atIndex_), buffer, offset, stride, index);
}

/**
 * @brief Set the byte offset for the buffer bound at the specified index.
 *
 * Adjusts the start offset used when the buffer bound to the given index is accessed by GPU kernels.
 *
 * @param offset Byte offset into the bound buffer.
 * @param index Buffer argument index to which the offset applies.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setBufferOffset(NS::UInteger offset, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBufferOffset_atIndex_), offset, index);
}

/**
 * @brief Set the byte offset and per-element stride for the buffer bound at the specified index.
 *
 * @param offset Byte offset into the bound buffer where accesses should begin.
 * @param stride Per-element stride in bytes for indexed access into the buffer.
 * @param index Argument table index of the previously bound buffer whose offset and stride are being set.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setBufferOffset(NS::UInteger offset, NS::UInteger stride, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBufferOffset_attributeStride_atIndex_), offset, stride, index);
}

/**
 * @brief Binds an array of buffers with per-buffer offsets to consecutive buffer indices.
 *
 * @param buffers Array of buffer pointers to bind.
 * @param offsets Array of byte offsets corresponding to each buffer.
 * @param range Range of buffer indices to set; `buffers[0]` is bound to index `range.location`, `buffers[1]` to `range.location + 1`, and so on for `range.length` entries.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setBuffers(const MTL::Buffer* const buffers[], const NS::UInteger offsets[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBuffers_offsets_withRange_), buffers, offsets, range);
}

/**
 * @brief Binds an array of buffers to consecutive buffer slots with per-buffer offsets and attribute strides.
 *
 * Binds each buffer from `buffers` into the encoder's argument table for the indices specified by `range`, using the corresponding entry in `offsets` as the byte offset into that buffer and the corresponding entry in `strides` as the per-element attribute stride.
 *
 * @param buffers Array of buffer pointers to bind; entries correspond to indices in `range`.
 * @param offsets Array of byte offsets for each buffer; entries correspond to `buffers`.
 * @param strides Array of attribute strides (in bytes) for each buffer; entries correspond to `buffers`.
 * @param range Range of consecutive argument indices to which the buffers are bound.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setBuffers(const MTL::Buffer* const buffers[], const NS::UInteger* offsets, const NS::UInteger* strides, NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBuffers_offsets_attributeStrides_withRange_), buffers, offsets, strides, range);
}

/**
 * @brief Sets raw byte data for the specified buffer index of the encoder.
 *
 * Copies `length` bytes from `bytes` into the encoder argument at `index`.
 *
 * @param bytes Pointer to the source byte data.
 * @param length Number of bytes to set.
 * @param index Argument buffer index that will receive the bytes.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setBytes(const void* bytes, NS::UInteger length, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBytes_length_atIndex_), bytes, length, index);
}

/**
 * @brief Bind raw byte data to a compute argument slot at the specified index with a per-entry stride.
 *
 * @param bytes Pointer to the raw data to bind.
 * @param length Number of bytes from `bytes` to bind.
 * @param stride Byte stride between consecutive entries when the bound data represents an array of elements.
 * @param index Argument index to bind the data to.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setBytes(const void* bytes, NS::UInteger length, NS::UInteger stride, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBytes_length_attributeStride_atIndex_), bytes, length, stride, index);
}

/**
 * @brief Sets the compute pipeline state to be used by subsequent compute commands.
 *
 * @param state The compute pipeline state to bind for dispatches and other compute operations.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setComputePipelineState(const MTL::ComputePipelineState* state)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setComputePipelineState_), state);
}

/**
 * @brief Configure the image block dimensions used by the encoder.
 *
 * Sets the width and height, in pixels, of the imageblock region that will be used for subsequent imageblock-based compute operations.
 *
 * @param width Width of the image block in pixels.
 * @param height Height of the image block in pixels.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setImageblockWidth(NS::UInteger width, NS::UInteger height)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setImageblockWidth_height_), width, height);
}

/**
 * @brief Binds an intersection function table to a shader buffer slot.
 *
 * Makes the specified intersection function table available to the compute pipeline at the given buffer index.
 *
 * @param intersectionFunctionTable The intersection function table to bind.
 * @param bufferIndex The buffer index (argument slot) where the table will be bound.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setIntersectionFunctionTable(const MTL::IntersectionFunctionTable* intersectionFunctionTable, NS::UInteger bufferIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIntersectionFunctionTable_atBufferIndex_), intersectionFunctionTable, bufferIndex);
}

/**
 * @brief Binds multiple intersection function tables into the encoder over the specified index range.
 *
 * @param intersectionFunctionTables Pointer to an array of intersection function table pointers to bind. The array must contain at least `range.length` entries.
 * @param range Index range to which the tables will be bound; the table at `intersectionFunctionTables[i]` is bound to index `range.location + i`.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setIntersectionFunctionTables(const MTL::IntersectionFunctionTable* const intersectionFunctionTables[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIntersectionFunctionTables_withBufferRange_), intersectionFunctionTables, range);
}

/**
 * @brief Binds a sampler state to the specified sampler index for subsequent shader sampling.
 *
 * @param sampler The sampler state to bind.
 * @param index The sampler slot index to set the sampler state at.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setSamplerState(const MTL::SamplerState* sampler, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSamplerState_atIndex_), sampler, index);
}

/**
 * @brief Binds a sampler state to the encoder at the specified argument index and applies LOD clamps.
 *
 * @param sampler The sampler state to bind.
 * @param lodMinClamp Minimum level-of-detail clamp; sampled LOD values below this are clamped to this value.
 * @param lodMaxClamp Maximum level-of-detail clamp; sampled LOD values above this are clamped to this value.
 * @param index The argument table index at which to set the sampler.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setSamplerState(const MTL::SamplerState* sampler, float lodMinClamp, float lodMaxClamp, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSamplerState_lodMinClamp_lodMaxClamp_atIndex_), sampler, lodMinClamp, lodMaxClamp, index);
}

/**
 * @brief Binds multiple sampler state objects to a consecutive range of resource indices for the compute encoder.
 *
 * @param samplers Pointer to an array of sampler state pointers to assign to the encoder.
 * @param range Range of argument indices to which the sampler states will be bound; the array length should be at least `range.length`.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setSamplerStates(const MTL::SamplerState* const samplers[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSamplerStates_withRange_), samplers, range);
}

/**
 * @brief Binds an array of sampler states to consecutive shader sampler slots, with per-sampler LOD clamp ranges.
 *
 * Binds `samplers` into the encoder's sampler slot range specified by `range`. For each sampler in the range,
 * `lodMinClamps[i]` and `lodMaxClamps[i]` provide the minimum and maximum level-of-detail clamp values applied to that sampler.
 *
 * @param samplers Array of sampler state pointers to bind.
 * @param lodMinClamps Array of per-sampler minimum LOD clamp values; must have at least `range.length` entries.
 * @param lodMaxClamps Array of per-sampler maximum LOD clamp values; must have at least `range.length` entries.
 * @param range Range of sampler slot indices to populate (start index and length).
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setSamplerStates(const MTL::SamplerState* const samplers[], const float lodMinClamps[], const float lodMaxClamps[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSamplerStates_lodMinClamps_lodMaxClamps_withRange_), samplers, lodMinClamps, lodMaxClamps, range);
}

/**
 * @brief Sets the stage-in region for subsequent compute dispatches.
 *
 * @param region The region (origin and size) that defines the stage-in area presented to kernels.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setStageInRegion(MTL::Region region)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStageInRegion_), region);
}

/**
 * @brief Sets the stage-in region from an indirect buffer.
 *
 * Reads stage-in region parameters from the provided buffer at the given byte offset
 * and configures the encoder's stage-in region accordingly.
 *
 * @param indirectBuffer Buffer containing a StageInRegionIndirectArguments structure.
 * @param indirectBufferOffset Byte offset into @p indirectBuffer where the arguments begin.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setStageInRegion(const MTL::Buffer* indirectBuffer, NS::UInteger indirectBufferOffset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStageInRegionWithIndirectBuffer_indirectBufferOffset_), indirectBuffer, indirectBufferOffset);
}

/**
 * @brief Binds a texture to the compute encoder at the specified argument index.
 *
 * @param texture Texture to bind to the encoder. May be `nullptr` to unbind the slot.
 * @param index Argument index at which the texture will be bound.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setTexture(const MTL::Texture* texture, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTexture_atIndex_), texture, index);
}

/**
 * @brief Binds an array of textures to consecutive texture argument slots for this compute encoder.
 *
 * @param textures Array of texture pointers to bind. Each element is bound to the corresponding argument slot defined by `range` (null entries unbind those slots).
 * @param range The range of consecutive argument indices to populate (from `range.location` to `range.location + range.length - 1`).
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setTextures(const MTL::Texture* const textures[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTextures_withRange_), textures, range);
}

/**
 * @brief Sets the size, in bytes, of the threadgroup (shared) memory for the compute function argument at the specified index.
 *
 * @param length Size in bytes to reserve for the threadgroup memory at the given index.
 * @param index Argument index identifying which threadgroup memory slot to configure.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setThreadgroupMemoryLength(NS::UInteger length, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setThreadgroupMemoryLength_atIndex_), length, index);
}

/**
 * @brief Binds a visible function table to the specified buffer binding index.
 *
 * @param visibleFunctionTable The visible function table to bind.
 * @param bufferIndex The buffer index at which to bind the table.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setVisibleFunctionTable(const MTL::VisibleFunctionTable* visibleFunctionTable, NS::UInteger bufferIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVisibleFunctionTable_atBufferIndex_), visibleFunctionTable, bufferIndex);
}

/**
 * @brief Binds multiple visible function tables to consecutive buffer indices.
 *
 * Binds the entries in `visibleFunctionTables` to the encoder's argument table slots specified by `range`; each array element is assigned to the corresponding index within `range`.
 *
 * @param visibleFunctionTables Array of pointers to VisibleFunctionTable objects whose elements will be bound into the encoder.
 * @param range Range of buffer indices that will be populated with the provided visible function tables.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::setVisibleFunctionTables(const MTL::VisibleFunctionTable* const visibleFunctionTables[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVisibleFunctionTables_withBufferRange_), visibleFunctionTables, range);
}

/**
 * @brief Updates a fence to capture the progress of work encoded by this encoder.
 *
 * @param fence Fence object that will be updated to reflect the encoder's completion state.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::updateFence(const MTL::Fence* fence)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(updateFence_), fence);
}

/**
 * @brief Marks a heap for use by this compute command encoder so resources from it are available to subsequent encoded commands.
 *
 * @param heap The heap to mark as in-use by the encoder.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::useHeap(const MTL::Heap* heap)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(useHeap_), heap);
}

/**
 * @brief Marks a set of heaps as being used by subsequent commands encoded by this compute command encoder.
 *
 * Calling this informs the encoder that the provided heaps will be accessed by GPU work encoded after this call, allowing the runtime to track and manage heap usage.
 *
 * @param heaps Array of pointers to heaps to mark as used.
 * @param count Number of entries in the `heaps` array.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::useHeaps(const MTL::Heap* const heaps[], NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(useHeaps_count_), heaps, count);
}

/**
 * @brief Declares that the encoder will use the specified resource with the given access usage.
 *
 * @param resource The resource to be used by subsequent commands.
 * @param usage The intended access pattern for the resource (for example read, write, or read-write).
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::useResource(const MTL::Resource* resource, MTL::ResourceUsage usage)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(useResource_usage_), resource, usage);
}

/**
 * @brief Declare that the encoder will use a set of resources with the specified usage.
 *
 * Informs the command encoder of intended access patterns for the provided resources so the driver
 * can track hazards and resource residency for the duration of encoding.
 *
 * @param resources Array of pointers to resources to be used.
 * @param count Number of entries in `resources`.
 * @param usage Bitfield specifying the intended usage (e.g., read, write) for all listed resources.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::useResources(const MTL::Resource* const resources[], NS::UInteger count, MTL::ResourceUsage usage)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(useResources_count_usage_), resources, count, usage);
}

/**
 * Ensures subsequent commands encoded on this encoder do not execute until the specified fence is reached.
 *
 * @param fence The fence to wait on; the encoder will defer execution of later commands until the GPU has reached this fence.
 */
_MTL_INLINE void MTL::ComputeCommandEncoder::waitForFence(const MTL::Fence* fence)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(waitForFence_), fence);
}