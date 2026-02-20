//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4RenderPass.hpp
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
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLRenderPass.hpp"

namespace MTL4
{
class RenderPassDescriptor;
}

namespace MTL
{
class Buffer;
class RasterizationRateMap;
class RenderPassColorAttachmentDescriptorArray;
class RenderPassDepthAttachmentDescriptor;
class RenderPassStencilAttachmentDescriptor;
struct SamplePosition;
}

namespace MTL4
{
class RenderPassDescriptor : public NS::Copying<RenderPassDescriptor>
{
public:
    static RenderPassDescriptor*                   alloc();

    MTL::RenderPassColorAttachmentDescriptorArray* colorAttachments() const;

    NS::UInteger                                   defaultRasterSampleCount() const;

    MTL::RenderPassDepthAttachmentDescriptor*      depthAttachment() const;

    NS::UInteger                                   getSamplePositions(MTL::SamplePosition* positions, NS::UInteger count);

    NS::UInteger                                   imageblockSampleLength() const;

    RenderPassDescriptor*                          init();

    MTL::RasterizationRateMap*                     rasterizationRateMap() const;

    NS::UInteger                                   renderTargetArrayLength() const;

    NS::UInteger                                   renderTargetHeight() const;

    NS::UInteger                                   renderTargetWidth() const;

    void                                           setDefaultRasterSampleCount(NS::UInteger defaultRasterSampleCount);

    void                                           setDepthAttachment(const MTL::RenderPassDepthAttachmentDescriptor* depthAttachment);

    void                                           setImageblockSampleLength(NS::UInteger imageblockSampleLength);

    void                                           setRasterizationRateMap(const MTL::RasterizationRateMap* rasterizationRateMap);

    void                                           setRenderTargetArrayLength(NS::UInteger renderTargetArrayLength);

    void                                           setRenderTargetHeight(NS::UInteger renderTargetHeight);

    void                                           setRenderTargetWidth(NS::UInteger renderTargetWidth);

    void                                           setSamplePositions(const MTL::SamplePosition* positions, NS::UInteger count);

    void                                           setStencilAttachment(const MTL::RenderPassStencilAttachmentDescriptor* stencilAttachment);

    void                                           setSupportColorAttachmentMapping(bool supportColorAttachmentMapping);

    void                                           setThreadgroupMemoryLength(NS::UInteger threadgroupMemoryLength);

    void                                           setTileHeight(NS::UInteger tileHeight);

    void                                           setTileWidth(NS::UInteger tileWidth);

    void                                           setVisibilityResultBuffer(const MTL::Buffer* visibilityResultBuffer);

    void                                           setVisibilityResultType(MTL::VisibilityResultType visibilityResultType);

    MTL::RenderPassStencilAttachmentDescriptor*    stencilAttachment() const;

    bool                                           supportColorAttachmentMapping() const;

    NS::UInteger                                   threadgroupMemoryLength() const;

    NS::UInteger                                   tileHeight() const;

    NS::UInteger                                   tileWidth() const;

    MTL::Buffer*                                   visibilityResultBuffer() const;

    MTL::VisibilityResultType                      visibilityResultType() const;
};

}
/**
 * @brief Allocates a new RenderPassDescriptor instance.
 *
 * @return MTL4::RenderPassDescriptor* Pointer to a newly allocated RenderPassDescriptor. The object is allocated but not initialized; call init() before use.
 */
_MTL_INLINE MTL4::RenderPassDescriptor* MTL4::RenderPassDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::RenderPassDescriptor>(_MTL_PRIVATE_CLS(MTL4RenderPassDescriptor));
}

/**
 * @brief Accesses the array of color attachment descriptors for the render pass.
 *
 * Provides the RenderPassColorAttachmentDescriptorArray describing each color
 * attachment configured on this render pass descriptor.
 *
 * @return MTL::RenderPassColorAttachmentDescriptorArray* Pointer to the color
 * attachment descriptor array.
 */
_MTL_INLINE MTL::RenderPassColorAttachmentDescriptorArray* MTL4::RenderPassDescriptor::colorAttachments() const
{
    return Object::sendMessage<MTL::RenderPassColorAttachmentDescriptorArray*>(this, _MTL_PRIVATE_SEL(colorAttachments));
}

/**
 * @brief Retrieve the default raster sample count used for rasterization.
 *
 * @return NS::UInteger The default number of raster samples. 
 */
_MTL_INLINE NS::UInteger MTL4::RenderPassDescriptor::defaultRasterSampleCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(defaultRasterSampleCount));
}

/**
 * @brief Retrieve the depth attachment descriptor for the render pass.
 *
 * @return MTL::RenderPassDepthAttachmentDescriptor* Pointer to the depth attachment descriptor, or nullptr if no depth attachment is configured.
 */
_MTL_INLINE MTL::RenderPassDepthAttachmentDescriptor* MTL4::RenderPassDescriptor::depthAttachment() const
{
    return Object::sendMessage<MTL::RenderPassDepthAttachmentDescriptor*>(this, _MTL_PRIVATE_SEL(depthAttachment));
}

/**
 * @brief Retrieve sample positions for the render pass into a provided buffer.
 *
 * @param positions Pointer to an array of `MTL::SamplePosition` to receive positions; may be null if only the count is needed.
 * @param count Maximum number of sample positions to write into `positions`.
 * @return NS::UInteger Number of sample positions written into `positions`.
 */
_MTL_INLINE NS::UInteger MTL4::RenderPassDescriptor::getSamplePositions(MTL::SamplePosition* positions, NS::UInteger count)
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(getSamplePositions_count_), positions, count);
}

/**
 * @brief Retrieve the image block sample length for the render pass.
 *
 * @return NS::UInteger The image block sample length.
 */
_MTL_INLINE NS::UInteger MTL4::RenderPassDescriptor::imageblockSampleLength() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(imageblockSampleLength));
}

/**
 * @brief Initializes a newly allocated RenderPassDescriptor instance.
 *
 * Performs class-specific initialization after allocation.
 *
 * @return RenderPassDescriptor* A pointer to the initialized RenderPassDescriptor instance, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL4::RenderPassDescriptor* MTL4::RenderPassDescriptor::init()
{
    return NS::Object::init<MTL4::RenderPassDescriptor>();
}

/**
 * Retrieve the rasterization rate map for this render pass descriptor.
 *
 * @return MTL::RasterizationRateMap* The rasterization rate map associated with the descriptor, or `nullptr` if none is set.
 */
_MTL_INLINE MTL::RasterizationRateMap* MTL4::RenderPassDescriptor::rasterizationRateMap() const
{
    return Object::sendMessage<MTL::RasterizationRateMap*>(this, _MTL_PRIVATE_SEL(rasterizationRateMap));
}

/**
 * @brief Retrieves the render target array length.
 *
 * @return NS::UInteger The number of layers in the render target array.
 */
_MTL_INLINE NS::UInteger MTL4::RenderPassDescriptor::renderTargetArrayLength() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(renderTargetArrayLength));
}

/**
 * @brief Retrieves the render target height for this render pass descriptor.
 *
 * @return NS::UInteger The render target height in pixels.
 */
_MTL_INLINE NS::UInteger MTL4::RenderPassDescriptor::renderTargetHeight() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(renderTargetHeight));
}

/**
 * @brief Gets the configured render target width for this render pass.
 *
 * @return NS::UInteger The render target width in pixels.
 */
_MTL_INLINE NS::UInteger MTL4::RenderPassDescriptor::renderTargetWidth() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(renderTargetWidth));
}

/**
 * @brief Sets the default raster sample count for this render pass descriptor.
 *
 * @param defaultRasterSampleCount The sample count to use for rasterization when an attachment or render target does not specify a different sample count.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setDefaultRasterSampleCount(NS::UInteger defaultRasterSampleCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDefaultRasterSampleCount_), defaultRasterSampleCount);
}

/**
 * @brief Sets the depth attachment descriptor for this render pass.
 *
 * @param depthAttachment Pointer to the RenderPassDepthAttachmentDescriptor to assign to the render pass.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setDepthAttachment(const MTL::RenderPassDepthAttachmentDescriptor* depthAttachment)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthAttachment_), depthAttachment);
}

/**
 * @brief Set the image block sample length used for the render pass.
 *
 * @param imageblockSampleLength Number of samples per image block; controls sampling granularity for imageblock-based operations in the render pass.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setImageblockSampleLength(NS::UInteger imageblockSampleLength)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setImageblockSampleLength_), imageblockSampleLength);
}

/**
 * @brief Set the rasterization rate map for this render pass.
 *
 * Associates the given rasterization rate map with the render pass descriptor so it will be used
 * when rasterizing work submitted with this descriptor.
 *
 * @param rasterizationRateMap Rasterization rate map to apply to the render pass.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setRasterizationRateMap(const MTL::RasterizationRateMap* rasterizationRateMap)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRasterizationRateMap_), rasterizationRateMap);
}

/**
 * @brief Sets the number of layers in the render target array for the render pass.
 *
 * @param renderTargetArrayLength The length of the render target array (number of layers).
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setRenderTargetArrayLength(NS::UInteger renderTargetArrayLength)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRenderTargetArrayLength_), renderTargetArrayLength);
}

/**
 * @brief Sets the render target height used by this render pass descriptor.
 *
 * @param renderTargetHeight Height, in pixels, to assign to the render targets for the render pass.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setRenderTargetHeight(NS::UInteger renderTargetHeight)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRenderTargetHeight_), renderTargetHeight);
}

/**
 * @brief Sets the width of the render target for this render pass descriptor.
 *
 * @param renderTargetWidth Width of the render target in pixels.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setRenderTargetWidth(NS::UInteger renderTargetWidth)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRenderTargetWidth_), renderTargetWidth);
}

/**
 * @brief Sets the sample positions used by the render pass from an array.
 *
 * Sets the sample positions for the render pass descriptor using the provided array of
 * MTL::SamplePosition structures.
 *
 * @param positions Pointer to the first element of an array of sample positions.
 * @param count Number of sample positions in `positions` to apply.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setSamplePositions(const MTL::SamplePosition* positions, NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSamplePositions_count_), positions, count);
}

/**
 * @brief Set the stencil attachment descriptor for this render pass.
 *
 * Replaces the current stencil attachment with the provided descriptor. Passing `nullptr`
 * clears any existing stencil attachment.
 *
 * @param stencilAttachment Descriptor for the stencil attachment, or `nullptr` to clear it.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setStencilAttachment(const MTL::RenderPassStencilAttachmentDescriptor* stencilAttachment)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStencilAttachment_), stencilAttachment);
}

/**
 * @brief Enables or disables support for color attachment mapping on the render pass.
 *
 * @param supportColorAttachmentMapping If `true`, enable color attachment mapping; if `false`, disable it.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setSupportColorAttachmentMapping(bool supportColorAttachmentMapping)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportColorAttachmentMapping_), supportColorAttachmentMapping);
}

/**
 * @brief Sets the amount of threadgroup memory available to the render pass.
 *
 * @param threadgroupMemoryLength Length of threadgroup memory in bytes.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setThreadgroupMemoryLength(NS::UInteger threadgroupMemoryLength)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setThreadgroupMemoryLength_), threadgroupMemoryLength);
}

/**
 * @brief Set the tile height used by the render pass.
 *
 * @param tileHeight Height in pixels of each tile for tile-based rendering.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setTileHeight(NS::UInteger tileHeight)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTileHeight_), tileHeight);
}

/**
 * @brief Sets the tile width used for tile-based rendering in the render pass descriptor.
 *
 * @param tileWidth Width of a tile in pixels.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setTileWidth(NS::UInteger tileWidth)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTileWidth_), tileWidth);
}

/**
 * @brief Sets the buffer used to store visibility results for the render pass.
 *
 * @param visibilityResultBuffer Buffer that will receive visibility (occlusion) results, or `nullptr` to disable writing visibility results.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setVisibilityResultBuffer(const MTL::Buffer* visibilityResultBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVisibilityResultBuffer_), visibilityResultBuffer);
}

/**
 * @brief Set the visibility result type used by this render pass.
 *
 * Determines how visibility (occlusion) results are recorded for the render pass.
 *
 * @param visibilityResultType The visibility result type to use for this render pass.
 */
_MTL_INLINE void MTL4::RenderPassDescriptor::setVisibilityResultType(MTL::VisibilityResultType visibilityResultType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVisibilityResultType_), visibilityResultType);
}

/**
 * @brief Retrieves the stencil attachment descriptor for the render pass.
 *
 * @return MTL::RenderPassStencilAttachmentDescriptor* Pointer to the stencil attachment descriptor, or `nullptr` if no stencil attachment is set.
 */
_MTL_INLINE MTL::RenderPassStencilAttachmentDescriptor* MTL4::RenderPassDescriptor::stencilAttachment() const
{
    return Object::sendMessage<MTL::RenderPassStencilAttachmentDescriptor*>(this, _MTL_PRIVATE_SEL(stencilAttachment));
}

/**
 * @brief Indicates whether color attachment mapping is supported by this render pass.
 *
 * @return `true` if color attachment mapping is supported, `false` otherwise.
 */
_MTL_INLINE bool MTL4::RenderPassDescriptor::supportColorAttachmentMapping() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportColorAttachmentMapping));
}

/**
 * @brief Retrieves the threadgroup memory length used by the render pass.
 *
 * @return NS::UInteger The threadgroup memory length, in bytes.
 */
_MTL_INLINE NS::UInteger MTL4::RenderPassDescriptor::threadgroupMemoryLength() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(threadgroupMemoryLength));
}

/**
 * @brief Retrieve the render pass tile height.
 *
 * @return NS::UInteger The tile height, in pixels.
 */
_MTL_INLINE NS::UInteger MTL4::RenderPassDescriptor::tileHeight() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(tileHeight));
}

/**
 * @brief Retrieves the tile width used by the render pass.
 *
 * @return NS::UInteger The tile width in pixels.
 */
_MTL_INLINE NS::UInteger MTL4::RenderPassDescriptor::tileWidth() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(tileWidth));
}

/**
 * @brief Buffer used to store visibility (occlusion) results for the render pass.
 *
 * @return MTL::Buffer* Pointer to the visibility result buffer, or `nullptr` if no buffer is set.
 */
_MTL_INLINE MTL::Buffer* MTL4::RenderPassDescriptor::visibilityResultBuffer() const
{
    return Object::sendMessage<MTL::Buffer*>(this, _MTL_PRIVATE_SEL(visibilityResultBuffer));
}

/**
 * @brief Get the visibility result type configured for this render pass.
 *
 * @return MTL::VisibilityResultType The visibility result type for the render pass.
 */
_MTL_INLINE MTL::VisibilityResultType MTL4::RenderPassDescriptor::visibilityResultType() const
{
    return Object::sendMessage<MTL::VisibilityResultType>(this, _MTL_PRIVATE_SEL(visibilityResultType));
}