//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLBlitCommandEncoder.hpp
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
#include "MTLCommandEncoder.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLTypes.hpp"
#include <cstdint>

namespace MTL
{
class Buffer;
class CounterSampleBuffer;
class Fence;
class IndirectCommandBuffer;
class Resource;
class Tensor;
class TensorExtents;
class Texture;

/**
 * @brief Options that modify blit operations.
 *
 * Use as a bitmask to enable specific behaviors when copying or converting texture and buffer data.
 */

/**
 * @brief Copy a rectangular region from a source buffer into a destination texture.
 *
 * @param sourceBuffer The source buffer to read from.
 * @param sourceOffset Byte offset within the source buffer where the region begins.
 * @param sourceBytesPerRow Number of bytes between successive rows in the source buffer.
 * @param sourceBytesPerImage Number of bytes between successive image slices in the source buffer.
 * @param sourceSize Width, height and depth of the source region.
 * @param destinationTexture Destination texture to write into.
 * @param destinationSlice Destination texture slice index.
 * @param destinationLevel Destination texture mipmap level.
 * @param destinationOrigin Origin within the destination texture where the copy starts.
 */

/**
 * @brief Copy a rectangular region from a source buffer into a destination texture with options.
 *
 * @param sourceBuffer The source buffer to read from.
 * @param sourceOffset Byte offset within the source buffer where the region begins.
 * @param sourceBytesPerRow Number of bytes between successive rows in the source buffer.
 * @param sourceBytesPerImage Number of bytes between successive image slices in the source buffer.
 * @param sourceSize Width, height and depth of the source region.
 * @param destinationTexture Destination texture to write into.
 * @param destinationSlice Destination texture slice index.
 * @param destinationLevel Destination texture mipmap level.
 * @param destinationOrigin Origin within the destination texture where the copy starts.
 * @param options Bitmask of BlitOption flags that modify the copy behavior.
 */

/**
 * @brief Copy a contiguous range of bytes from one buffer to another.
 *
 * @param sourceBuffer Source buffer to copy from.
 * @param sourceOffset Byte offset in the source buffer to start copying.
 * @param destinationBuffer Destination buffer to copy into.
 * @param destinationOffset Byte offset in the destination buffer where data will be written.
 * @param size Number of bytes to copy.
 */

/**
 * @brief Copy a subregion between tensors, specified by tensor extents for origin and dimensions.
 *
 * @param sourceTensor Source tensor to copy from.
 * @param sourceOrigin Tensor extents that specify the origin within the source tensor.
 * @param sourceDimensions Dimensions of the region to copy from the source tensor.
 * @param destinationTensor Destination tensor to copy into.
 * @param destinationOrigin Tensor extents that specify the origin within the destination tensor.
 * @param destinationDimensions Dimensions of the region to place into the destination tensor.
 */

/**
 * @brief Copy a rectangular region from one texture to another.
 *
 * @param sourceTexture Source texture to read from.
 * @param sourceSlice Source texture slice index.
 * @param sourceLevel Source texture mipmap level.
 * @param sourceOrigin Origin within the source texture where the copy starts.
 * @param sourceSize Width, height and depth of the region to copy.
 * @param destinationTexture Destination texture to write into.
 * @param destinationSlice Destination texture slice index.
 * @param destinationLevel Destination texture mipmap level.
 * @param destinationOrigin Origin within the destination texture where the copy starts.
 */

/**
 * @brief Copy a rectangular region from a texture into a buffer.
 *
 * @param sourceTexture Source texture to read from.
 * @param sourceSlice Source texture slice index.
 * @param sourceLevel Source texture mipmap level.
 * @param sourceOrigin Origin within the source texture where the copy starts.
 * @param sourceSize Width, height and depth of the region to copy.
 * @param destinationBuffer Destination buffer to write into.
 * @param destinationOffset Byte offset in the destination buffer where data will be written.
 * @param destinationBytesPerRow Number of bytes between successive rows written into the buffer.
 * @param destinationBytesPerImage Number of bytes between successive image slices written into the buffer.
 */

/**
 * @brief Copy a rectangular region from a texture into a buffer with options.
 *
 * @param sourceTexture Source texture to read from.
 * @param sourceSlice Source texture slice index.
 * @param sourceLevel Source texture mipmap level.
 * @param sourceOrigin Origin within the source texture where the copy starts.
 * @param sourceSize Width, height and depth of the region to copy.
 * @param destinationBuffer Destination buffer to write into.
 * @param destinationOffset Byte offset in the destination buffer where data will be written.
 * @param destinationBytesPerRow Number of bytes between successive rows written into the buffer.
 * @param destinationBytesPerImage Number of bytes between successive image slices written into the buffer.
 * @param options Bitmask of BlitOption flags that modify the copy behavior.
 */

/**
 * @brief Copy multiple slices and mipmap levels from one texture to another.
 *
 * @param sourceTexture Source texture to read from.
 * @param sourceSlice Starting slice index in the source texture.
 * @param sourceLevel Starting mipmap level in the source texture.
 * @param destinationTexture Destination texture to write into.
 * @param destinationSlice Starting slice index in the destination texture.
 * @param destinationLevel Starting mipmap level in the destination texture.
 * @param sliceCount Number of slices to copy.
 * @param levelCount Number of mipmap levels to copy.
 */

/**
 * @brief Copy the entire contents from one texture to another.
 *
 * @param sourceTexture Source texture to read from.
 * @param destinationTexture Destination texture to write into.
 */

/**
 * @brief Copy a range of commands from one indirect command buffer into another.
 *
 * @param source Source indirect command buffer to copy from.
 * @param sourceRange Range of commands within the source buffer to copy.
 * @param destination Destination indirect command buffer to copy into.
 * @param destinationIndex Index in the destination buffer where the copied commands will be placed.
 */

/**
 * @brief Fill a range of a buffer with a constant byte value.
 *
 * @param buffer The buffer to fill.
 * @param range The byte range within the buffer to fill.
 * @param value The byte value used to fill the range.
 */

/**
 * @brief Generate mipmaps for the provided texture.
 *
 * @param texture Texture for which mipmaps will be generated.
 */

/**
 * @brief Retrieve texture access counters for a region and write them into a buffer.
 *
 * @param texture Texture whose access counters are being queried.
 * @param region Region within the texture to sample counters from.
 * @param mipLevel Mipmap level of the texture to sample.
 * @param slice Texture slice index to sample.
 * @param resetCounters If true, reset the texture's counters after sampling.
 * @param countersBuffer Destination buffer to receive counter data.
 * @param countersBufferOffset Byte offset within the destination buffer to start writing counters.
 */

/**
 * @brief Prepare a texture's contents for efficient CPU read access.
 *
 * @param texture The texture to optimize for CPU access.
 */

/**
 * @brief Prepare a specific slice and level of a texture for efficient CPU read access.
 *
 * @param texture The texture to optimize for CPU access.
 * @param slice Texture slice index to optimize.
 * @param level Mipmap level to optimize.
 */

/**
 * @brief Prepare a texture's contents for efficient GPU access.
 *
 * @param texture The texture to optimize for GPU access.
 */

/**
 * @brief Prepare a specific slice and level of a texture for efficient GPU access.
 *
 * @param texture The texture to optimize for GPU access.
 * @param slice Texture slice index to optimize.
 * @param level Mipmap level to optimize.
 */

/**
 * @brief Optimize an indirect command buffer for execution over the given range.
 *
 * @param indirectCommandBuffer The indirect command buffer to optimize.
 * @param range Range of commands within the buffer to optimize.
 */

/**
 * @brief Reset commands in an indirect command buffer over the given range.
 *
 * @param buffer The indirect command buffer to reset.
 * @param range Range of commands within the buffer to reset.
 */

/**
 * @brief Reset texture access counters for a specified region, mip level, and slice.
 *
 * @param texture Texture whose access counters will be reset.
 * @param region Region within the texture whose counters will be reset.
 * @param mipLevel Mipmap level of the texture.
 * @param slice Texture slice index.
 */

/**
 * @brief Resolve counter samples from a CounterSampleBuffer into a destination buffer.
 *
 * @param sampleBuffer Source counter sample buffer containing recorded counter samples.
 * @param range Range of samples within the sample buffer to resolve.
 * @param destinationBuffer Destination buffer to receive resolved counter values.
 * @param destinationOffset Byte offset within the destination buffer where resolved data will be written.
 */

/**
 * @brief Sample counters from a CounterSampleBuffer at a specific sample index.
 *
 * @param sampleBuffer The counter sample buffer to sample.
 * @param sampleIndex Index of the sample to capture.
 * @param barrier If true, insert a barrier to ensure counters are sampled after prior GPU work completes.
 */

/**
 * @brief Ensure a resource's CPU and GPU views are synchronized.
 *
 * @param resource The resource to synchronize.
 */

/**
 * @brief Ensure the specified slice and level of a texture are synchronized between CPU and GPU.
 *
 * @param texture The texture to synchronize.
 * @param slice Texture slice index to synchronize.
 * @param level Mipmap level to synchronize.
 */

/**
 * @brief Update (signal) a fence from the current encoder position.
 *
 * @param fence The fence to update.
 */

/**
 * @brief Wait on a fence, blocking subsequent GPU work until the fence is reached.
 *
 * @param fence The fence to wait for.
 */
_MTL_OPTIONS(NS::UInteger, BlitOption) {
    BlitOptionNone = 0,
    BlitOptionDepthFromDepthStencil = 1,
    BlitOptionStencilFromDepthStencil = 1 << 1,
    BlitOptionRowLinearPVRTC = 1 << 2,
};

class BlitCommandEncoder : public NS::Referencing<BlitCommandEncoder, CommandEncoder>
{
public:
    void copyFromBuffer(const MTL::Buffer* sourceBuffer, NS::UInteger sourceOffset, NS::UInteger sourceBytesPerRow, NS::UInteger sourceBytesPerImage, MTL::Size sourceSize, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, MTL::Origin destinationOrigin);
    void copyFromBuffer(const MTL::Buffer* sourceBuffer, NS::UInteger sourceOffset, NS::UInteger sourceBytesPerRow, NS::UInteger sourceBytesPerImage, MTL::Size sourceSize, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, MTL::Origin destinationOrigin, MTL::BlitOption options);
    void copyFromBuffer(const MTL::Buffer* sourceBuffer, NS::UInteger sourceOffset, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset, NS::UInteger size);

    void copyFromTensor(const MTL::Tensor* sourceTensor, const MTL::TensorExtents* sourceOrigin, const MTL::TensorExtents* sourceDimensions, const MTL::Tensor* destinationTensor, const MTL::TensorExtents* destinationOrigin, const MTL::TensorExtents* destinationDimensions);

    void copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, MTL::Origin destinationOrigin);
    void copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset, NS::UInteger destinationBytesPerRow, NS::UInteger destinationBytesPerImage);
    void copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset, NS::UInteger destinationBytesPerRow, NS::UInteger destinationBytesPerImage, MTL::BlitOption options);
    void copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, NS::UInteger sliceCount, NS::UInteger levelCount);
    void copyFromTexture(const MTL::Texture* sourceTexture, const MTL::Texture* destinationTexture);

    void copyIndirectCommandBuffer(const MTL::IndirectCommandBuffer* source, NS::Range sourceRange, const MTL::IndirectCommandBuffer* destination, NS::UInteger destinationIndex);

    void fillBuffer(const MTL::Buffer* buffer, NS::Range range, uint8_t value);

    void generateMipmaps(const MTL::Texture* texture);

    void getTextureAccessCounters(const MTL::Texture* texture, MTL::Region region, NS::UInteger mipLevel, NS::UInteger slice, bool resetCounters, const MTL::Buffer* countersBuffer, NS::UInteger countersBufferOffset);

    void optimizeContentsForCPUAccess(const MTL::Texture* texture);
    void optimizeContentsForCPUAccess(const MTL::Texture* texture, NS::UInteger slice, NS::UInteger level);

    void optimizeContentsForGPUAccess(const MTL::Texture* texture);
    void optimizeContentsForGPUAccess(const MTL::Texture* texture, NS::UInteger slice, NS::UInteger level);

    void optimizeIndirectCommandBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, NS::Range range);

    void resetCommandsInBuffer(const MTL::IndirectCommandBuffer* buffer, NS::Range range);

    void resetTextureAccessCounters(const MTL::Texture* texture, MTL::Region region, NS::UInteger mipLevel, NS::UInteger slice);

    void resolveCounters(const MTL::CounterSampleBuffer* sampleBuffer, NS::Range range, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset);

    void sampleCountersInBuffer(const MTL::CounterSampleBuffer* sampleBuffer, NS::UInteger sampleIndex, bool barrier);

    void synchronizeResource(const MTL::Resource* resource);

    void synchronizeTexture(const MTL::Texture* texture, NS::UInteger slice, NS::UInteger level);

    void updateFence(const MTL::Fence* fence);

    void waitForFence(const MTL::Fence* fence);
};

}
/**
 * @brief Copies a rectangular region of texel data from a linear source buffer into a destination texture.
 *
 * Copies sourceSize texels starting at sourceOffset within sourceBuffer into destinationTexture at
 * the specified destinationOrigin, destinationSlice and destinationLevel. The buffer layout is
 * described by sourceBytesPerRow (bytes per row) and sourceBytesPerImage (bytes per image/depth slice).
 *
 * @param sourceBuffer Source buffer containing tightly or strided image data.
 * @param sourceOffset Byte offset within sourceBuffer where the copy begins.
 * @param sourceBytesPerRow Number of bytes between consecutive rows in the source image data.
 * @param sourceBytesPerImage Number of bytes between consecutive image slices (depth or array slices) in the source.
 * @param sourceSize Size (width, height, depth) of the region to copy, in texels.
 * @param destinationTexture Destination texture to receive the copied texel data.
 * @param destinationSlice Array slice or 3D slice index within destinationTexture.
 * @param destinationLevel Mipmap level within destinationTexture.
 * @param destinationOrigin Origin (x, y, z) in destinationTexture, in texel coordinates, where the copy is placed.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::copyFromBuffer(const MTL::Buffer* sourceBuffer, NS::UInteger sourceOffset, NS::UInteger sourceBytesPerRow, NS::UInteger sourceBytesPerImage, MTL::Size sourceSize, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, MTL::Origin destinationOrigin)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromBuffer_sourceOffset_sourceBytesPerRow_sourceBytesPerImage_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_), sourceBuffer, sourceOffset, sourceBytesPerRow, sourceBytesPerImage, sourceSize, destinationTexture, destinationSlice, destinationLevel, destinationOrigin);
}

/**
 * @brief Copies a rectangular region from a source buffer into a destination texture.
 *
 * Copies a block of memory described by sourceOffset, sourceBytesPerRow, sourceBytesPerImage and sourceSize into the specified slice, mipmap level, and origin of destinationTexture, applying the given blit options.
 *
 * @param sourceBuffer The buffer containing the source data.
 * @param sourceOffset Byte offset in sourceBuffer where the source region begins.
 * @param sourceBytesPerRow Number of bytes between the start of consecutive rows in the source region.
 * @param sourceBytesPerImage Number of bytes between the start of consecutive image slices in the source region.
 * @param sourceSize The width, height and depth of the source region to copy.
 * @param destinationTexture The texture to receive the copied data.
 * @param destinationSlice The slice (array layer) of destinationTexture to write into.
 * @param destinationLevel The mipmap level of destinationTexture to write into.
 * @param destinationOrigin The origin within the destination texture where the copy begins.
 * @param options Blit options that modify copy behavior (see MTL::BlitOption).
 */
_MTL_INLINE void MTL::BlitCommandEncoder::copyFromBuffer(const MTL::Buffer* sourceBuffer, NS::UInteger sourceOffset, NS::UInteger sourceBytesPerRow, NS::UInteger sourceBytesPerImage, MTL::Size sourceSize, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, MTL::Origin destinationOrigin, MTL::BlitOption options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromBuffer_sourceOffset_sourceBytesPerRow_sourceBytesPerImage_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_options_), sourceBuffer, sourceOffset, sourceBytesPerRow, sourceBytesPerImage, sourceSize, destinationTexture, destinationSlice, destinationLevel, destinationOrigin, options);
}

/**
 * @brief Copies a contiguous range of bytes from one buffer to another.
 *
 * Copies `size` bytes starting at `sourceOffset` in `sourceBuffer` to `destinationBuffer` beginning at `destinationOffset`.
 *
 * @param sourceBuffer Source buffer to copy from.
 * @param sourceOffset Byte offset in `sourceBuffer` where the copy begins.
 * @param destinationBuffer Destination buffer to copy to.
 * @param destinationOffset Byte offset in `destinationBuffer` where the data is written.
 * @param size Number of bytes to copy.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::copyFromBuffer(const MTL::Buffer* sourceBuffer, NS::UInteger sourceOffset, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset, NS::UInteger size)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromBuffer_sourceOffset_toBuffer_destinationOffset_size_), sourceBuffer, sourceOffset, destinationBuffer, destinationOffset, size);
}

/**
 * @brief Copies a rectangular region from one tensor into another.
 *
 * Copies the region of sourceTensor defined by sourceOrigin and sourceDimensions
 * into destinationTensor at destinationOrigin using destinationDimensions to
 * describe the destination extents.
 *
 * @param sourceTensor The tensor to copy data from.
 * @param sourceOrigin The origin within the source tensor where the copy begins.
 * @param sourceDimensions The extents within the source tensor to copy.
 * @param destinationTensor The tensor to copy data into.
 * @param destinationOrigin The origin within the destination tensor where data is written.
 * @param destinationDimensions The extents within the destination tensor for the copied region.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::copyFromTensor(const MTL::Tensor* sourceTensor, const MTL::TensorExtents* sourceOrigin, const MTL::TensorExtents* sourceDimensions, const MTL::Tensor* destinationTensor, const MTL::TensorExtents* destinationOrigin, const MTL::TensorExtents* destinationDimensions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromTensor_sourceOrigin_sourceDimensions_toTensor_destinationOrigin_destinationDimensions_), sourceTensor, sourceOrigin, sourceDimensions, destinationTensor, destinationOrigin, destinationDimensions);
}

/**
 * @brief Copies a rectangular 3D region from a source texture into a destination texture.
 *
 * Copies the region defined by `sourceOrigin` and `sourceSize` from `sourceTexture` at the
 * specified slice and mipmap level into `destinationTexture` at the specified slice,
 * mipmap level, and origin.
 *
 * @param sourceTexture Source texture to copy from.
 * @param sourceSlice Slice index in the source texture.
 * @param sourceLevel Mipmap level in the source texture.
 * @param sourceOrigin Origin within the source texture where the copy begins.
 * @param sourceSize Size of the region to copy from the source texture.
 * @param destinationTexture Destination texture to copy into.
 * @param destinationSlice Slice index in the destination texture.
 * @param destinationLevel Mipmap level in the destination texture.
 * @param destinationOrigin Origin within the destination texture where the copy is placed.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, MTL::Origin destinationOrigin)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_), sourceTexture, sourceSlice, sourceLevel, sourceOrigin, sourceSize, destinationTexture, destinationSlice, destinationLevel, destinationOrigin);
}

/**
 * @brief Copies a rectangular region from a texture into a linear buffer.
 *
 * Copies the specified region (slice, mip level, origin, and size) of `sourceTexture`
 * into `destinationBuffer` using the provided linear layout parameters.
 *
 * @param sourceTexture Source texture to read from.
 * @param sourceSlice Array slice index in the source texture.
 * @param sourceLevel Mip-map level in the source texture.
 * @param sourceOrigin Origin (x, y, z) within the source texture where the copy begins.
 * @param sourceSize Size (width, height, depth) of the region to copy.
 * @param destinationBuffer Destination buffer to write the texture data into.
 * @param destinationOffset Byte offset into `destinationBuffer` where the copy starts.
 * @param destinationBytesPerRow Number of bytes between the start of consecutive rows in the destination layout.
 * @param destinationBytesPerImage Number of bytes between the start of consecutive image slices in the destination layout.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset, NS::UInteger destinationBytesPerRow, NS::UInteger destinationBytesPerImage)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toBuffer_destinationOffset_destinationBytesPerRow_destinationBytesPerImage_), sourceTexture, sourceSlice, sourceLevel, sourceOrigin, sourceSize, destinationBuffer, destinationOffset, destinationBytesPerRow, destinationBytesPerImage);
}

/**
 * @brief Copies a rectangular region from a source texture into a destination buffer using the specified layout and blit options.
 *
 * @param sourceTexture Pointer to the source texture to read from.
 * @param sourceSlice Index of the slice or layer in the source texture.
 * @param sourceLevel Mipmap level in the source texture.
 * @param sourceOrigin Origin within the source texture describing the x, y, z offset of the region to copy.
 * @param sourceSize Size of the region to copy from the source texture.
 * @param destinationBuffer Pointer to the destination buffer to write texel data into.
 * @param destinationOffset Byte offset within the destination buffer where the first texel will be written.
 * @param destinationBytesPerRow Number of bytes between the start of consecutive rows in the destination buffer.
 * @param destinationBytesPerImage Number of bytes between the start of consecutive images (slices) in the destination buffer; use 0 for tightly packed 2D data when not applicable.
 * @param options Bitmask of MTL::BlitOption flags that modify copy behavior (for example, depth/stencil handling).
 */
_MTL_INLINE void MTL::BlitCommandEncoder::copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset, NS::UInteger destinationBytesPerRow, NS::UInteger destinationBytesPerImage, MTL::BlitOption options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toBuffer_destinationOffset_destinationBytesPerRow_destinationBytesPerImage_options_), sourceTexture, sourceSlice, sourceLevel, sourceOrigin, sourceSize, destinationBuffer, destinationOffset, destinationBytesPerRow, destinationBytesPerImage, options);
}

/**
 * @brief Copies a rectangular block of texture slices and mipmap levels from one texture to another.
 *
 * Copies sliceCount consecutive array slices starting at sourceSlice and levelCount consecutive mipmap
 * levels starting at sourceLevel from sourceTexture into destinationTexture beginning at destinationSlice
 * and destinationLevel. The source and destination textures must be compatible for the copy.
 *
 * @param sourceTexture Source texture to copy from.
 * @param sourceSlice First array slice index in the source texture.
 * @param sourceLevel First mipmap level in the source texture.
 * @param destinationTexture Destination texture to copy into.
 * @param destinationSlice First array slice index in the destination texture.
 * @param destinationLevel First mipmap level in the destination texture.
 * @param sliceCount Number of consecutive array slices to copy.
 * @param levelCount Number of consecutive mipmap levels to copy.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::copyFromTexture(const MTL::Texture* sourceTexture, NS::UInteger sourceSlice, NS::UInteger sourceLevel, const MTL::Texture* destinationTexture, NS::UInteger destinationSlice, NS::UInteger destinationLevel, NS::UInteger sliceCount, NS::UInteger levelCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromTexture_sourceSlice_sourceLevel_toTexture_destinationSlice_destinationLevel_sliceCount_levelCount_), sourceTexture, sourceSlice, sourceLevel, destinationTexture, destinationSlice, destinationLevel, sliceCount, levelCount);
}

/**
 * @brief Copies the full contents of a source texture into a destination texture.
 *
 * The destination texture's contents are replaced with the source texture's contents.
 *
 * @param sourceTexture Source texture to copy from.
 * @param destinationTexture Destination texture to copy into.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::copyFromTexture(const MTL::Texture* sourceTexture, const MTL::Texture* destinationTexture)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyFromTexture_toTexture_), sourceTexture, destinationTexture);
}

/**
 * @brief Copies a range of commands from one indirect command buffer into another at the specified destination index.
 *
 * @param source The source IndirectCommandBuffer to copy commands from.
 * @param sourceRange The range of commands within the source buffer to copy.
 * @param destination The destination IndirectCommandBuffer to receive the copied commands.
 * @param destinationIndex The index in the destination buffer at which the first copied command will be placed.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::copyIndirectCommandBuffer(const MTL::IndirectCommandBuffer* source, NS::Range sourceRange, const MTL::IndirectCommandBuffer* destination, NS::UInteger destinationIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyIndirectCommandBuffer_sourceRange_destination_destinationIndex_), source, sourceRange, destination, destinationIndex);
}

/**
 * @brief Fills a region of a buffer with a byte value.
 *
 * Writes `value` into every byte within `range` of `buffer`.
 *
 * @param buffer The destination buffer to fill.
 * @param range The byte range within the buffer to fill.
 * @param value The byte value to write into the specified range.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::fillBuffer(const MTL::Buffer* buffer, NS::Range range, uint8_t value)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(fillBuffer_range_value_), buffer, range, value);
}

/**
 * @brief Generates the mipmap chain for the provided texture from its highest-resolution level.
 *
 * @param texture The texture whose mipmap levels will be produced from its base (level 0) image.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::generateMipmaps(const MTL::Texture* texture)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(generateMipmapsForTexture_), texture);
}

/**
 * @brief Retrieves texture access counters for a specified region, mip level, and slice into a buffer.
 *
 * Writes the access counter data for `texture` covering `region` at `mipLevel` and `slice` into `countersBuffer`
 * starting at `countersBufferOffset`.
 *
 * @param texture Target texture whose access counters will be read.
 * @param region Region of the texture to sample counters from.
 * @param mipLevel Mipmap level within the texture.
 * @param slice Array slice (or layer) within the texture.
 * @param resetCounters If `true`, resets the texture's access counters after they are written to the buffer.
 * @param countersBuffer Destination buffer that will receive the counter data.
 * @param countersBufferOffset Byte offset into `countersBuffer` where the counter data will be written.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::getTextureAccessCounters(const MTL::Texture* texture, MTL::Region region, NS::UInteger mipLevel, NS::UInteger slice, bool resetCounters, const MTL::Buffer* countersBuffer, NS::UInteger countersBufferOffset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(getTextureAccessCounters_region_mipLevel_slice_resetCounters_countersBuffer_countersBufferOffset_), texture, region, mipLevel, slice, resetCounters, countersBuffer, countersBufferOffset);
}

/**
 * @brief Prepare a texture's contents for efficient CPU access.
 *
 * Enqueues work to optimize the specified texture so its contents can be accessed efficiently by the CPU.
 *
 * @param texture The texture whose contents should be optimized for CPU access.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::optimizeContentsForCPUAccess(const MTL::Texture* texture)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(optimizeContentsForCPUAccess_), texture);
}

/**
 * @brief Prepare the contents of a texture for efficient CPU access.
 *
 * Ensures the specified slice and mipmap level of `texture` are optimized so the CPU can read or write them with reduced cost or stalls.
 *
 * @param texture The texture whose contents will be optimized.
 * @param slice The slice index (array slice or depth slice) to optimize.
 * @param level The mipmap level to optimize.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::optimizeContentsForCPUAccess(const MTL::Texture* texture, NS::UInteger slice, NS::UInteger level)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(optimizeContentsForCPUAccess_slice_level_), texture, slice, level);
}

/**
 * @brief Prepare a texture's contents for efficient GPU access.
 *
 * Ensures the provided texture's contents are arranged or prepared so the GPU can access them with improved performance.
 *
 * @param texture The texture whose contents will be optimized for GPU access.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::optimizeContentsForGPUAccess(const MTL::Texture* texture)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(optimizeContentsForGPUAccess_), texture);
}

/**
 * @brief Optimize the contents of a texture for GPU access.
 *
 * Ensures the specified slice and mipmap level of `texture` are prepared for efficient GPU reads and writes.
 *
 * @param texture The texture whose contents will be optimized.
 * @param slice The slice index within the texture array or 3D texture to optimize.
 * @param level The mipmap level to optimize.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::optimizeContentsForGPUAccess(const MTL::Texture* texture, NS::UInteger slice, NS::UInteger level)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(optimizeContentsForGPUAccess_slice_level_), texture, slice, level);
}

/**
 * @brief Optimize the contents of an indirect command buffer for execution.
 *
 * Optimize internal data/formatting of the specified indirect command buffer for GPU execution over the given range of commands.
 *
 * @param indirectCommandBuffer The indirect command buffer to optimize.
 * @param range The range of commands within the buffer to optimize (location and length).
 */
_MTL_INLINE void MTL::BlitCommandEncoder::optimizeIndirectCommandBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(optimizeIndirectCommandBuffer_withRange_), indirectCommandBuffer, range);
}

/**
 * @brief Resets commands in an indirect command buffer for a specified range.
 *
 * Marks the command entries within the given range of the indirect command buffer as reset,
 * making those slots available for recording new commands.
 *
 * @param buffer The indirect command buffer whose commands will be reset.
 * @param range The range (start index and count) of command entries to reset.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::resetCommandsInBuffer(const MTL::IndirectCommandBuffer* buffer, NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(resetCommandsInBuffer_withRange_), buffer, range);
}

/**
 * @brief Reset texture access counters for a specific region, mip level, and slice.
 *
 * Resets the GPU-maintained access counters for the given texture region so subsequent
 * access tracking starts from zero for that region at the specified mip level and slice.
 *
 * @param texture The texture whose access counters will be reset.
 * @param region The region within the texture to reset (in texel coordinates and size).
 * @param mipLevel The mipmap level within the texture to target.
 * @param slice The array slice or 3D texture slice to target.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::resetTextureAccessCounters(const MTL::Texture* texture, MTL::Region region, NS::UInteger mipLevel, NS::UInteger slice)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(resetTextureAccessCounters_region_mipLevel_slice_), texture, region, mipLevel, slice);
}

/**
 * @brief Resolves GPU counter samples into a destination buffer.
 *
 * Copies the counter sample data specified by `range` from `sampleBuffer` into `destinationBuffer` beginning at `destinationOffset` bytes.
 *
 * @param sampleBuffer The source CounterSampleBuffer containing the samples to resolve.
 * @param range The NS::Range of samples to resolve (start index and length).
 * @param destinationBuffer The destination Buffer that receives the resolved counter data.
 * @param destinationOffset Byte offset within `destinationBuffer` where the resolved data will be written.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::resolveCounters(const MTL::CounterSampleBuffer* sampleBuffer, NS::Range range, const MTL::Buffer* destinationBuffer, NS::UInteger destinationOffset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(resolveCounters_inRange_destinationBuffer_destinationOffset_), sampleBuffer, range, destinationBuffer, destinationOffset);
}

/**
 * @brief Encode a counter sample read from a CounterSampleBuffer.
 *
 * Samples the counter at the given index from the provided CounterSampleBuffer and encodes that sample read into this blit command stream.
 *
 * @param sampleBuffer Counter sample buffer to read from.
 * @param sampleIndex Index of the sample within `sampleBuffer` to sample.
 * @param barrier If `true`, insert a GPU barrier to ensure prior work is complete before sampling.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::sampleCountersInBuffer(const MTL::CounterSampleBuffer* sampleBuffer, NS::UInteger sampleIndex, bool barrier)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(sampleCountersInBuffer_atSampleIndex_withBarrier_), sampleBuffer, sampleIndex, barrier);
}

/**
 * @brief Synchronizes CPU and GPU views of the specified resource.
 *
 * Ensures that the resource's contents are made coherent so that CPU access observes
 * GPU-produced data and subsequent GPU work sees CPU-visible updates.
 *
 * @param resource The resource to synchronize.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::synchronizeResource(const MTL::Resource* resource)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(synchronizeResource_), resource);
}

/**
 * @brief Synchronizes the contents of a texture slice and mipmap level between CPU and GPU.
 *
 * Ensures the specified slice and mipmap level of `texture` are synchronized so subsequent
 * CPU or GPU operations observe the latest contents.
 *
 * @param texture The texture whose contents will be synchronized.
 * @param slice The slice index within the texture to synchronize.
 * @param level The mipmap level within the texture to synchronize.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::synchronizeTexture(const MTL::Texture* texture, NS::UInteger slice, NS::UInteger level)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(synchronizeTexture_slice_level_), texture, slice, level);
}

/**
 * @brief Record an update to the specified fence at the current point in the command stream.
 *
 * Records a fence update so the fence becomes signaled after all work encoded by this encoder
 * prior to this call has completed on the GPU.
 *
 * @param fence The fence to update (will be signaled when preceding GPU work finishes).
 */
_MTL_INLINE void MTL::BlitCommandEncoder::updateFence(const MTL::Fence* fence)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(updateFence_), fence);
}

/**
 * @brief Instructs the blit command encoder to stall execution until the given fence is reached.
 *
 * This encodes a dependency so subsequent blit commands do not execute until `fence` has been updated by a prior encoder.
 *
 * @param fence The fence to wait on; the encoder will not proceed until this fence is signaled/updated.
 */
_MTL_INLINE void MTL::BlitCommandEncoder::waitForFence(const MTL::Fence* fence)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(waitForFence_), fence);
}