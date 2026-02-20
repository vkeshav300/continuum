//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4ComputeCommandEncoder.hpp
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
#include "MTL4CommandEncoder.hpp"
#include "MTL4Counters.hpp"
#include "MTLAccelerationStructure.hpp"
#include "MTLAccelerationStructureTypes.hpp"
#include "MTLBlitCommandEncoder.hpp"
#include "MTLCommandEncoder.hpp"
#include "MTLDefines.hpp"
#include "MTLGPUAddress.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLTypes.hpp"
#include <cstdint>

namespace MTL4
{
class AccelerationStructureDescriptor;
class ArgumentTable;
class CounterHeap;
}

namespace MTL
{
class AccelerationStructure;
class Buffer;
class ComputePipelineState;
class IndirectCommandBuffer;
class Tensor;
class TensorExtents;
class Texture;
}

namespace MTL4
{
class ComputeCommandEncoder : public NS::Referencing<ComputeCommandEncoder, CommandEncoder>
{
public:
    void        buildAccelerationStructure(const MTL::AccelerationStructure* accelerationStructure, const MTL4::AccelerationStructureDescriptor* descriptor, const MTL4::BufferRange scratchBuffer);

    void        copyAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL::AccelerationStructure* destinationAccelerationStructure);

    void        copyAndCompactAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL::AccelerationStructure* destinationAccelerationStructure);

    void        copyFromBuffer(const MTL::Buffer* sourceBuffer, NS::UInteger sourceOffset, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset, NS::UInteger size);
    void        copyFromBuffer(const MTL::Buffer* sourceBuffer, NS::UInteger sourceOffset, NS::UInteger sourceBytesPerRow, NS::UInteger sourceBytesPerImage, MTL::Size sourceSize, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, MTL::Origin destinationOrigin);
    void        copyFromBuffer(const MTL::Buffer* sourceBuffer, NS::UInteger sourceOffset, NS::UInteger sourceBytesPerRow, NS::UInteger sourceBytesPerImage, MTL::Size sourceSize, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, MTL::Origin destinationOrigin, MTL::BlitOption options);

    void        copyFromTensor(const MTL::Tensor* sourceTensor, const MTL::TensorExtents* sourceOrigin, const MTL::TensorExtents* sourceDimensions, const MTL::Tensor* destinationTensor, const MTL::TensorExtents* destinationOrigin, const MTL::TensorExtents* destinationDimensions);

    void        copyFromTexture(const MTL::Texture* sourceTexture, const MTL::Texture* destinationTexture);
    void        copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, NS::UInteger sliceCount, NS::UInteger levelCount);
    void        copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, MTL::Origin destinationOrigin);
    void        copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset, NS::UInteger destinationBytesPerRow, NS::UInteger destinationBytesPerImage);
    void        copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset, NS::UInteger destinationBytesPerRow, NS::UInteger destinationBytesPerImage, MTL::BlitOption options);

    void        copyIndirectCommandBuffer(const MTL::IndirectCommandBuffer* source, NS::Range sourceRange, const MTL::IndirectCommandBuffer* destination, NS::UInteger destinationIndex);

    void        dispatchThreadgroups(MTL::Size threadgroupsPerGrid, MTL::Size threadsPerThreadgroup);
    void        dispatchThreadgroups(MTL::GPUAddress indirectBuffer, MTL::Size threadsPerThreadgroup);

    void        dispatchThreads(MTL::Size threadsPerGrid, MTL::Size threadsPerThreadgroup);
    void        dispatchThreads(MTL::GPUAddress indirectBuffer);

    void        executeCommandsInBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, NS::Range executionRange);
    void        executeCommandsInBuffer(const MTL::IndirectCommandBuffer* indirectCommandbuffer, MTL::GPUAddress indirectRangeBuffer);

    void        fillBuffer(const MTL::Buffer* buffer, NS::Range range, uint8_t value);

    void        generateMipmaps(const MTL::Texture* texture);

    void        optimizeContentsForCPUAccess(const MTL::Texture* texture);
    void        optimizeContentsForCPUAccess(const MTL::Texture* texture, NS::UInteger slice, NS::UInteger level);

    void        optimizeContentsForGPUAccess(const MTL::Texture* texture);
    void        optimizeContentsForGPUAccess(const MTL::Texture* texture, NS::UInteger slice, NS::UInteger level);

    void        optimizeIndirectCommandBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, NS::Range range);

    void        refitAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL4::AccelerationStructureDescriptor* descriptor, const MTL::AccelerationStructure* destinationAccelerationStructure, const MTL4::BufferRange scratchBuffer);
    void        refitAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL4::AccelerationStructureDescriptor* descriptor, const MTL::AccelerationStructure* destinationAccelerationStructure, const MTL4::BufferRange scratchBuffer, MTL::AccelerationStructureRefitOptions options);

    void        resetCommandsInBuffer(const MTL::IndirectCommandBuffer* buffer, NS::Range range);

    void        setArgumentTable(const MTL4::ArgumentTable* argumentTable);

    void        setComputePipelineState(const MTL::ComputePipelineState* state);

    void        setImageblockWidth(NS::UInteger width, NS::UInteger height);

    void        setThreadgroupMemoryLength(NS::UInteger length, NS::UInteger index);

    MTL::Stages stages();

    void        writeCompactedAccelerationStructureSize(const MTL::AccelerationStructure* accelerationStructure, const MTL4::BufferRange buffer);

    void        writeTimestamp(MTL4::TimestampGranularity granularity, const MTL4::CounterHeap* counterHeap, NS::UInteger index);
};

}
/**
 * @brief Builds the given acceleration structure using the provided descriptor and scratch space.
 *
 * Builds or updates the contents of `accelerationStructure` according to `descriptor`, using
 * `scratchBuffer` as temporary storage during the build operation.
 *
 * @param accelerationStructure Destination acceleration structure to be built or updated.
 * @param descriptor Descriptor that defines the acceleration-structure geometry and build parameters.
 * @param scratchBuffer BufferRange specifying the temporary buffer region used for the build.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::buildAccelerationStructure(const MTL::AccelerationStructure* accelerationStructure, const MTL4::AccelerationStructureDescriptor* descriptor, const MTL4::BufferRange scratchBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(buildAccelerationStructure_descriptor_scratchBuffer_), accelerationStructure, descriptor, scratchBuffer);
}

/**
 * @brief Copies the contents of one acceleration structure into another.
 *
 * Copies GPU-side acceleration structure data from sourceAccelerationStructure into destinationAccelerationStructure,
 * replacing the destination's contents.
 *
 * @param sourceAccelerationStructure Source acceleration structure to copy from.
 * @param destinationAccelerationStructure Destination acceleration structure to overwrite with the source contents.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::copyAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL::AccelerationStructure* destinationAccelerationStructure)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyAccelerationStructure_toAccelerationStructure_), sourceAccelerationStructure, destinationAccelerationStructure);
}

/**
 * @brief Copies and compacts an existing acceleration structure into another acceleration structure.
 *
 * Copies the contents of `sourceAccelerationStructure` into `destinationAccelerationStructure`
 * while producing a compacted representation in the destination.
 *
 * @param sourceAccelerationStructure The source acceleration structure to copy and compact.
 * @param destinationAccelerationStructure The destination acceleration structure that receives the compacted data.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::copyAndCompactAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL::AccelerationStructure* destinationAccelerationStructure)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyAndCompactAccelerationStructure_toAccelerationStructure_), sourceAccelerationStructure, destinationAccelerationStructure);
}

/**
 * @brief Copies a contiguous region of bytes from one buffer to another.
 *
 * Copies exactly `size` bytes starting at `sourceOffset` in `sourceBuffer` to
 * `destinationBuffer` starting at `destinationOffset`.
 *
 * @param sourceBuffer Source buffer to copy from.
 * @param sourceOffset Byte offset within `sourceBuffer` where copying begins.
 * @param destinationBuffer Destination buffer to copy into.
 * @param destinationOffset Byte offset within `destinationBuffer` where data is written.
 * @param size Number of bytes to copy.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::copyFromBuffer(const MTL::Buffer* sourceBuffer, NS::UInteger sourceOffset, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset, NS::UInteger size)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromBuffer_sourceOffset_toBuffer_destinationOffset_size_), sourceBuffer, sourceOffset, destinationBuffer, destinationOffset, size);
}

/**
 * @brief Copies a rectangular region of pixel data from a linear source buffer into a destination texture.
 *
 * Copies a block defined by `sourceSize` from `sourceBuffer` (using the provided byte strides and offsets)
 * into `destinationTexture` at the specified slice, mip level, and origin.
 *
 * @param sourceBuffer Source buffer containing the pixel data.
 * @param sourceOffset Byte offset within `sourceBuffer` where the region begins.
 * @param sourceBytesPerRow Number of bytes between the start of consecutive rows in the source buffer.
 * @param sourceBytesPerImage Number of bytes between the start of consecutive image slices in the source buffer.
 * @param sourceSize 3D size (width, height, depth) of the region to copy from the source buffer.
 * @param destinationTexture Destination texture to receive the copied region.
 * @param destinationSlice Destination array slice (or slice index for 3D textures) within the texture.
 * @param destinationLevel Destination mipmap level within the texture.
 * @param destinationOrigin Origin (x, y, z) in the destination texture at which to place the copied region.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::copyFromBuffer(const MTL::Buffer* sourceBuffer, NS::UInteger sourceOffset, NS::UInteger sourceBytesPerRow, NS::UInteger sourceBytesPerImage, MTL::Size sourceSize, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, MTL::Origin destinationOrigin)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromBuffer_sourceOffset_sourceBytesPerRow_sourceBytesPerImage_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_), sourceBuffer, sourceOffset, sourceBytesPerRow, sourceBytesPerImage, sourceSize, destinationTexture, destinationSlice, destinationLevel, destinationOrigin);
}

/**
 * @brief Copies a rectangular region of texel data from a buffer into a texture using explicit row/image strides and placement parameters.
 *
 * Copies a region defined by `sourceSize` from `sourceBuffer` (starting at `sourceOffset`) into `destinationTexture` at the given slice, mipmap level, and origin. `sourceBytesPerRow` and `sourceBytesPerImage` specify the buffer layout for rows and image slices. `options` controls additional blit behavior.
 *
 * @param sourceBuffer The source linear buffer containing texel data.
 * @param sourceOffset Byte offset into `sourceBuffer` where the copied region begins.
 * @param sourceBytesPerRow Number of bytes between successive rows in the buffer.
 * @param sourceBytesPerImage Number of bytes between successive image slices in the buffer (for 3D or array textures).
 * @param sourceSize The width, height, and depth of the region to copy (in texels).
 * @param destinationTexture The destination texture to receive the copied region.
 * @param destinationSlice Destination slice (array layer) within the texture.
 * @param destinationLevel Destination mipmap level within the texture.
 * @param destinationOrigin Origin within the destination mipmap level where the copy is placed.
 * @param options Blit options that modify copy behavior (e.g., synchronization or aliasing considerations).
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::copyFromBuffer(const MTL::Buffer* sourceBuffer, NS::UInteger sourceOffset, NS::UInteger sourceBytesPerRow, NS::UInteger sourceBytesPerImage, MTL::Size sourceSize, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, MTL::Origin destinationOrigin, MTL::BlitOption options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromBuffer_sourceOffset_sourceBytesPerRow_sourceBytesPerImage_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_options_), sourceBuffer, sourceOffset, sourceBytesPerRow, sourceBytesPerImage, sourceSize, destinationTexture, destinationSlice, destinationLevel, destinationOrigin, options);
}

/**
 * @brief Copies a sub-region of tensor data from a source tensor into a destination tensor.
 *
 * Copies the region defined by `sourceOrigin` and `sourceDimensions` from `sourceTensor`
 * into the region defined by `destinationOrigin` and `destinationDimensions` in `destinationTensor`.
 *
 * @param sourceTensor Source tensor to copy from.
 * @param sourceOrigin Starting coordinates within the source tensor for the copy.
 * @param sourceDimensions Extents (size) of the region to copy from the source tensor.
 * @param destinationTensor Destination tensor to copy into.
 * @param destinationOrigin Starting coordinates within the destination tensor where data will be written.
 * @param destinationDimensions Extents (size) of the region to write into the destination tensor.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::copyFromTensor(const MTL::Tensor* sourceTensor, const MTL::TensorExtents* sourceOrigin, const MTL::TensorExtents* sourceDimensions, const MTL::Tensor* destinationTensor, const MTL::TensorExtents* destinationOrigin, const MTL::TensorExtents* destinationDimensions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromTensor_sourceOrigin_sourceDimensions_toTensor_destinationOrigin_destinationDimensions_), sourceTensor, sourceOrigin, sourceDimensions, destinationTensor, destinationOrigin, destinationDimensions);
}

/**
 * @brief Copies the contents of one texture into another.
 *
 * Copies all mipmap levels and array slices from the source texture into the destination texture.
 *
 * @param sourceTexture The texture to copy data from.
 * @param destinationTexture The texture to copy data into.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::copyFromTexture(const MTL::Texture* sourceTexture, const MTL::Texture* destinationTexture)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromTexture_toTexture_), sourceTexture, destinationTexture);
}

/**
 * @brief Copies a rectangular subset of mipmap levels and array slices from one texture to another.
 *
 * Copies `sliceCount` consecutive array slices starting at `sourceSlice` and `levelCount` consecutive mipmap
 * levels starting at `sourceLevel` from `sourceTexture` into `destinationTexture` at `destinationSlice`
 * and `destinationLevel`, respectively.
 *
 * @param sourceTexture Source texture to copy from.
 * @param sourceSlice First array slice in the source texture to copy.
 * @param sourceLevel First mipmap level in the source texture to copy.
 * @param destinationTexture Destination texture to copy into.
 * @param destinationSlice First array slice in the destination texture to receive the copy.
 * @param destinationLevel First mipmap level in the destination texture to receive the copy.
 * @param sliceCount Number of consecutive array slices to copy.
 * @param levelCount Number of consecutive mipmap levels to copy.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, NS::UInteger sliceCount, NS::UInteger levelCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromTexture_sourceSlice_sourceLevel_toTexture_destinationSlice_destinationLevel_sliceCount_levelCount_), sourceTexture, sourceSlice, sourceLevel, destinationTexture, destinationSlice, destinationLevel, sliceCount, levelCount);
}

/**
 * @brief Copies a rectangular region from one texture to another.
 *
 * Copies the region of sourceTexture defined by sourceSlice, sourceLevel,
 * sourceOrigin, and sourceSize into destinationTexture at the location
 * specified by destinationSlice, destinationLevel, and destinationOrigin.
 * Coordinates and sizes are specified in texels.
 *
 * @param sourceTexture Source texture.
 * @param sourceSlice Source slice (array slice or texture slice index).
 * @param sourceLevel Source mipmap level.
 * @param sourceOrigin Origin of the source region in texel coordinates.
 * @param sourceSize Size of the source region in texels.
 * @param destinationTexture Destination texture.
 * @param destinationSlice Destination slice (array slice or texture slice index).
 * @param destinationLevel Destination mipmap level.
 * @param destinationOrigin Origin in the destination texture where the source region will be placed, in texel coordinates.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, MTL::Origin destinationOrigin)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_), sourceTexture, sourceSlice, sourceLevel, sourceOrigin, sourceSize, destinationTexture, destinationSlice, destinationLevel, destinationOrigin);
}

/**
 * @brief Copies a rectangular region from a texture into a linear buffer.
 *
 * Copies the texel region defined by `sourceOrigin` and `sourceSize` from `sourceTexture`
 * (at `sourceSlice` and `sourceLevel`) into `destinationBuffer` laid out with the given
 * row and image strides.
 *
 * @param sourceTexture Source texture to copy from.
 * @param sourceSlice Array slice index within the source texture.
 * @param sourceLevel Mipmap level within the source texture.
 * @param sourceOrigin Origin (x,y,z) of the region within the source texture.
 * @param sourceSize Size (width,height,depth) of the region to copy.
 * @param destinationBuffer Destination buffer to receive the copied texel data.
 * @param destinationOffset Byte offset in `destinationBuffer` where the copy begins.
 * @param destinationBytesPerRow Number of bytes between consecutive rows in the destination layout.
 * @param destinationBytesPerImage Number of bytes between consecutive images (slices) in the destination layout.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset, NS::UInteger destinationBytesPerRow, NS::UInteger destinationBytesPerImage)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toBuffer_destinationOffset_destinationBytesPerRow_destinationBytesPerImage_), sourceTexture, sourceSlice, sourceLevel, sourceOrigin, sourceSize, destinationBuffer, destinationOffset, destinationBytesPerRow, destinationBytesPerImage);
}

/**
 * @brief Copies a rectangular region from a texture into a linear buffer with specified layout and options.
 *
 * @param sourceTexture The texture to copy from.
 * @param sourceSlice The array slice or depth slice within the source texture.
 * @param sourceLevel The mipmap level within the source texture.
 * @param sourceOrigin The origin (x, y, z) within the source texture where the copy begins.
 * @param sourceSize The size (width, height, depth) of the region to copy.
 * @param destinationBuffer The buffer to copy the texture data into.
 * @param destinationOffset Byte offset in the destination buffer where the first texel is written.
 * @param destinationBytesPerRow The byte stride between successive rows in the destination buffer.
 * @param destinationBytesPerImage The byte stride between successive image slices (depth or array slices) in the destination buffer.
 * @param options Blit options that modify copy behavior (e.g., synchronization or compression-related hints).
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset, NS::UInteger destinationBytesPerRow, NS::UInteger destinationBytesPerImage, MTL::BlitOption options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toBuffer_destinationOffset_destinationBytesPerRow_destinationBytesPerImage_options_), sourceTexture, sourceSlice, sourceLevel, sourceOrigin, sourceSize, destinationBuffer, destinationOffset, destinationBytesPerRow, destinationBytesPerImage, options);
}

/**
 * @brief Copies a range of commands from one indirect command buffer into another at a specified destination index.
 *
 * Copies the commands identified by `sourceRange` from `source` into `destination`, writing the first copied command at `destinationIndex` and preserving command order.
 *
 * @param source Source indirect command buffer to copy from.
 * @param sourceRange Range of command indices in the source buffer to copy.
 * @param destination Destination indirect command buffer to copy into.
 * @param destinationIndex Element index in the destination buffer where the first copied command will be written.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::copyIndirectCommandBuffer(const MTL::IndirectCommandBuffer* source, NS::Range sourceRange, const MTL::IndirectCommandBuffer* destination, NS::UInteger destinationIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyIndirectCommandBuffer_sourceRange_destination_destinationIndex_), source, sourceRange, destination, destinationIndex);
}

/**
 * @brief Dispatches a compute workload using explicit threadgroup and grid sizes.
 *
 * Dispatches compute work where the compute grid is defined by `threadgroupsPerGrid`
 * and each threadgroup contains `threadsPerThreadgroup` threads.
 *
 * @param threadgroupsPerGrid Number of threadgroups to execute across the grid (x, y, z).
 * @param threadsPerThreadgroup Size of each threadgroup in threads (x, y, z).
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::dispatchThreadgroups(MTL::Size threadgroupsPerGrid, MTL::Size threadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(dispatchThreadgroups_threadsPerThreadgroup_), threadgroupsPerGrid, threadsPerThreadgroup);
}

/**
 * @brief Enqueues a compute dispatch whose threadgroup counts are sourced from an indirect GPU buffer while using the provided threads-per-threadgroup dimensions.
 *
 * @param indirectBuffer GPU address of the indirect buffer containing dispatch threadgroup counts.
 * @param threadsPerThreadgroup Number of threads in each threadgroup (x, y, z).
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::dispatchThreadgroups(MTL::GPUAddress indirectBuffer, MTL::Size threadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(dispatchThreadgroupsWithIndirectBuffer_threadsPerThreadgroup_), indirectBuffer, threadsPerThreadgroup);
}

/**
 * @brief Enqueues a compute dispatch with an explicit grid size and threadgroup size.
 *
 * @param threadsPerGrid Total number of threads to dispatch across the grid (width, height, depth).
 * @param threadsPerThreadgroup Number of threads in each threadgroup (width, height, depth).
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::dispatchThreads(MTL::Size threadsPerGrid, MTL::Size threadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(dispatchThreads_threadsPerThreadgroup_), threadsPerGrid, threadsPerThreadgroup);
}

/**
 * @brief Dispatches a compute thread execution using an indirect buffer referenced by GPU address.
 *
 * @param indirectBuffer GPU virtual address of the indirect buffer that encodes the thread-grid configuration for the dispatch.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::dispatchThreads(MTL::GPUAddress indirectBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(dispatchThreadsWithIndirectBuffer_), indirectBuffer);
}

/**
 * @brief Executes a contiguous range of commands from an indirect command buffer.
 *
 * @param indirectCommandBuffer The indirect command buffer that contains the commands to execute.
 * @param executionRange The range (start index and length) of commands within the indirect command buffer to execute.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::executeCommandsInBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, NS::Range executionRange)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(executeCommandsInBuffer_withRange_), indirectCommandBuffer, executionRange);
}

/**
 * @brief Executes commands from an indirect command buffer using an indirect range buffer.
 *
 * Executes the commands encoded in indirectCommandbuffer as specified by the ranges stored
 * in the buffer referenced by indirectRangeBuffer.
 *
 * @param indirectCommandbuffer The indirect command buffer whose commands will be executed.
 * @param indirectRangeBuffer GPU address of a buffer that contains the execution ranges which
 *        specify which commands within indirectCommandbuffer to run.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::executeCommandsInBuffer(const MTL::IndirectCommandBuffer* indirectCommandbuffer, MTL::GPUAddress indirectRangeBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(executeCommandsInBuffer_indirectBuffer_), indirectCommandbuffer, indirectRangeBuffer);
}

/**
 * @brief Fills a contiguous range of a buffer with a byte value.
 *
 * @param buffer The buffer whose contents will be written.
 * @param range The byte range within the buffer to fill.
 * @param value The byte value to write into each byte of the specified range.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::fillBuffer(const MTL::Buffer* buffer, NS::Range range, uint8_t value)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(fillBuffer_range_value_), buffer, range, value);
}

/**
 * @brief Generate all mipmap levels for the specified texture.
 *
 * Ensures the texture's mipmap chain is populated from its base level so that lower-resolution
 * mip levels are available for sampling or other GPU operations.
 *
 * @param texture The texture whose mipmaps will be generated.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::generateMipmaps(const MTL::Texture* texture)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(generateMipmapsForTexture_), texture);
}

/**
 * @brief Prepares the contents of the specified texture for efficient CPU access.
 *
 * Ensures the texture's contents are arranged and synchronized so the CPU can read or write them efficiently.
 *
 * @param texture The texture whose contents should be prepared for CPU access.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::optimizeContentsForCPUAccess(const MTL::Texture* texture)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(optimizeContentsForCPUAccess_), texture);
}

/**
 * @brief Prepare a specific slice and mipmap level of a texture for efficient CPU access.
 *
 * Ensures the texture contents for the given slice and mipmap level are made accessible/optimized for reads and writes from the CPU.
 *
 * @param texture The texture whose contents will be prepared.
 * @param slice The slice (array layer) of the texture to optimize.
 * @param level The mipmap level of the texture to optimize.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::optimizeContentsForCPUAccess(const MTL::Texture* texture, NS::UInteger slice, NS::UInteger level)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(optimizeContentsForCPUAccess_slice_level_), texture, slice, level);
}

/**
 * @brief Prepare a texture's contents for efficient GPU access.
 *
 * Ensures the texture data is arranged or migrated so subsequent GPU operations can access it efficiently.
 *
 * @param texture The texture whose contents should be optimized for GPU access.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::optimizeContentsForGPUAccess(const MTL::Texture* texture)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(optimizeContentsForGPUAccess_), texture);
}

/**
 * @brief Prepares the specified slice and mipmap level of a texture for efficient GPU access.
 *
 * Ensures the texture contents for the given slice and mipmap level are optimized for GPU usage,
 * potentially performing whatever re-layouts or transfers are required by the implementation.
 *
 * @param texture Texture whose contents should be optimized.
 * @param slice Index of the texture slice to optimize.
 * @param level Mipmap level of the texture to optimize.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::optimizeContentsForGPUAccess(const MTL::Texture* texture, NS::UInteger slice, NS::UInteger level)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(optimizeContentsForGPUAccess_slice_level_), texture, slice, level);
}

/**
 * @brief Optimize an indirect command buffer over a specified range for GPU execution.
 *
 * @param indirectCommandBuffer The indirect command buffer to optimize.
 * @param range The range of commands within the buffer to optimize (starting index and length).
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::optimizeIndirectCommandBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(optimizeIndirectCommandBuffer_withRange_), indirectCommandBuffer, range);
}

/**
 * @brief Refits an existing acceleration structure to match a new descriptor and writes the result into a destination acceleration structure.
 *
 * Recomputes the layout/contents of the source acceleration structure according to the provided descriptor and stores the refitted structure in the destination, using the supplied scratch buffer for temporary storage.
 *
 * @param sourceAccelerationStructure The source acceleration structure to be refitted.
 * @param descriptor Descriptor describing the desired layout and parameters for the refit.
 * @param destinationAccelerationStructure The destination acceleration structure that will receive the refitted data.
 * @param scratchBuffer A BufferRange specifying the scratch memory to use for the refit operation.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::refitAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL4::AccelerationStructureDescriptor* descriptor, const MTL::AccelerationStructure* destinationAccelerationStructure, const MTL4::BufferRange scratchBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(refitAccelerationStructure_descriptor_destination_scratchBuffer_), sourceAccelerationStructure, descriptor, destinationAccelerationStructure, scratchBuffer);
}

/**
 * @brief Refits an existing acceleration structure into a destination structure using a new descriptor.
 *
 * Updates the destination acceleration structure by refitting data from the source according to the provided descriptor.
 *
 * @param sourceAccelerationStructure The acceleration structure providing source geometry/data to be refit.
 * @param descriptor Descriptor that describes the desired layout/parameters for the refitted acceleration structure.
 * @param destinationAccelerationStructure The acceleration structure to receive the refitted result.
 * @param scratchBuffer Buffer range used for temporary/scratch workspace during the refit operation.
 * @param options Options that modify the refit operation's behavior.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::refitAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL4::AccelerationStructureDescriptor* descriptor, const MTL::AccelerationStructure* destinationAccelerationStructure, const MTL4::BufferRange scratchBuffer, MTL::AccelerationStructureRefitOptions options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(refitAccelerationStructure_descriptor_destination_scratchBuffer_options_), sourceAccelerationStructure, descriptor, destinationAccelerationStructure, scratchBuffer, options);
}

/**
 * @brief Resets a range of commands in an indirect command buffer to their default (unencoded) state.
 *
 * Clears encoded commands in the specified range of the indirect command buffer so those command slots can be re-recorded.
 *
 * @param buffer Indirect command buffer whose commands will be reset.
 * @param range Range of command indices to reset within the buffer.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::resetCommandsInBuffer(const MTL::IndirectCommandBuffer* buffer, NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(resetCommandsInBuffer_withRange_), buffer, range);
}

/**
 * @brief Assigns an argument table to the encoder for subsequent compute commands.
 *
 * @param argumentTable The argument table whose resource bindings and layout will be applied by the encoder.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::setArgumentTable(const MTL4::ArgumentTable* argumentTable)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setArgumentTable_), argumentTable);
}

/**
 * @brief Sets the compute pipeline state used for subsequent dispatches.
 *
 * @param state Compute pipeline state object to use for subsequent dispatches.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::setComputePipelineState(const MTL::ComputePipelineState* state)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setComputePipelineState_), state);
}

/**
 * @brief Set the image block dimensions used by subsequent compute operations.
 *
 * @param width Width of the image block in pixels.
 * @param height Height of the image block in pixels.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::setImageblockWidth(NS::UInteger width, NS::UInteger height)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setImageblockWidth_height_), width, height);
}

/**
 * @brief Set the size, in bytes, of the threadgroup (shared) memory at a given index.
 *
 * Configures how many bytes of threadgroup-local memory are allocated for the specified
 * threadgroup memory slot used by the currently bound compute pipeline.
 *
 * @param length Number of bytes to allocate for the threadgroup memory slot.
 * @param index  Index of the threadgroup memory slot to configure.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::setThreadgroupMemoryLength(NS::UInteger length, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setThreadgroupMemoryLength_atIndex_), length, index);
}

/**
 * @brief Query the shader stages associated with this compute command encoder.
 *
 * @return MTL::Stages A bitmask of shader stages associated with this encoder.
 */
_MTL_INLINE MTL::Stages MTL4::ComputeCommandEncoder::stages()
{
    return Object::sendMessage<MTL::Stages>(this, _MTL_PRIVATE_SEL(stages));
}

/**
 * @brief Writes the compacted size of an acceleration structure into a buffer range.
 *
 * Writes the number of bytes required to store the acceleration structure after compaction
 * into the provided buffer range.
 *
 * @param accelerationStructure Acceleration structure whose compacted size will be written.
 * @param buffer Destination buffer range where the compacted size (in bytes) will be stored.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::writeCompactedAccelerationStructureSize(const MTL::AccelerationStructure* accelerationStructure, const MTL4::BufferRange buffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(writeCompactedAccelerationStructureSize_toBuffer_), accelerationStructure, buffer);
}

/**
 * @brief Writes a timestamp into the specified counter heap at the given index using the provided granularity.
 *
 * @param granularity Timestamp granularity controlling precision.
 * @param counterHeap Destination counter heap that will receive the timestamp.
 * @param index Index within the counter heap where the timestamp is written.
 */
_MTL_INLINE void MTL4::ComputeCommandEncoder::writeTimestamp(MTL4::TimestampGranularity granularity, const MTL4::CounterHeap* counterHeap, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(writeTimestampWithGranularity_intoHeap_atIndex_), granularity, counterHeap, index);
}