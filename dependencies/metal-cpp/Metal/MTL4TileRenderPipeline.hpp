//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4TileRenderPipeline.hpp
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
#include "MTL4PipelineState.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLTypes.hpp"

namespace MTL4
{
class FunctionDescriptor;
class StaticLinkingDescriptor;
class TileRenderPipelineDescriptor;
}

namespace MTL
{
class TileRenderPipelineColorAttachmentDescriptorArray;
}

namespace MTL4
{
class TileRenderPipelineDescriptor : public NS::Copying<TileRenderPipelineDescriptor, PipelineDescriptor>
{
public:
    static TileRenderPipelineDescriptor*                   alloc();

    MTL::TileRenderPipelineColorAttachmentDescriptorArray* colorAttachments() const;

    TileRenderPipelineDescriptor*                          init();

    NS::UInteger                                           maxTotalThreadsPerThreadgroup() const;

    NS::UInteger                                           rasterSampleCount() const;

    MTL::Size                                              requiredThreadsPerThreadgroup() const;

    void                                                   reset();

    void                                                   setMaxTotalThreadsPerThreadgroup(NS::UInteger maxTotalThreadsPerThreadgroup);

    void                                                   setRasterSampleCount(NS::UInteger rasterSampleCount);

    void                                                   setRequiredThreadsPerThreadgroup(MTL::Size requiredThreadsPerThreadgroup);

    void                                                   setStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* staticLinkingDescriptor);

    void                                                   setSupportBinaryLinking(bool supportBinaryLinking);

    void                                                   setThreadgroupSizeMatchesTileSize(bool threadgroupSizeMatchesTileSize);

    void                                                   setTileFunctionDescriptor(const MTL4::FunctionDescriptor* tileFunctionDescriptor);

    StaticLinkingDescriptor*                               staticLinkingDescriptor() const;

    bool                                                   supportBinaryLinking() const;

    bool                                                   threadgroupSizeMatchesTileSize() const;

    FunctionDescriptor*                                    tileFunctionDescriptor() const;
};

}
/**
 * @brief Allocate a new TileRenderPipelineDescriptor instance.
 *
 * @return MTL4::TileRenderPipelineDescriptor* A newly allocated TileRenderPipelineDescriptor.
 */
_MTL_INLINE MTL4::TileRenderPipelineDescriptor* MTL4::TileRenderPipelineDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::TileRenderPipelineDescriptor>(_MTL_PRIVATE_CLS(MTL4TileRenderPipelineDescriptor));
}

/**
 * @brief Accesses the array of color attachment descriptors for this tile render pipeline descriptor.
 *
 * @return MTL::TileRenderPipelineColorAttachmentDescriptorArray* Pointer to the color attachment descriptor array. 
 */
_MTL_INLINE MTL::TileRenderPipelineColorAttachmentDescriptorArray* MTL4::TileRenderPipelineDescriptor::colorAttachments() const
{
    return Object::sendMessage<MTL::TileRenderPipelineColorAttachmentDescriptorArray*>(this, _MTL_PRIVATE_SEL(colorAttachments));
}

/**
 * @brief Initializes the TileRenderPipelineDescriptor instance.
 *
 * @return MTL4::TileRenderPipelineDescriptor* Pointer to the receiver initialized as a TileRenderPipelineDescriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL4::TileRenderPipelineDescriptor* MTL4::TileRenderPipelineDescriptor::init()
{
    return NS::Object::init<MTL4::TileRenderPipelineDescriptor>();
}

/**
 * @brief Gets the maximum total threads per threadgroup.
 *
 * @return Maximum number of threads that may be scheduled in a single threadgroup.
 */
_MTL_INLINE NS::UInteger MTL4::TileRenderPipelineDescriptor::maxTotalThreadsPerThreadgroup() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxTotalThreadsPerThreadgroup));
}

/**
 * @brief Gets the raster sample count used when rasterizing tiles.
 *
 * @return The number of raster samples per pixel for the pipeline descriptor.
 */
_MTL_INLINE NS::UInteger MTL4::TileRenderPipelineDescriptor::rasterSampleCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(rasterSampleCount));
}

/**
 * @brief Gets the required threadgroup dimensions for this tile render pipeline descriptor.
 *
 * @return MTL::Size The required number of threads per threadgroup as an MTL::Size struct.
 */
_MTL_INLINE MTL::Size MTL4::TileRenderPipelineDescriptor::requiredThreadsPerThreadgroup() const
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(requiredThreadsPerThreadgroup));
}

/**
 * @brief Resets the descriptor to its default state.
 *
 * Restores all configurable properties of the tile render pipeline descriptor to their default values.
 */
_MTL_INLINE void MTL4::TileRenderPipelineDescriptor::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

/**
 * @brief Sets the maximum total number of threads for a threadgroup.
 *
 * @param maxTotalThreadsPerThreadgroup Maximum total threads allowed in a single threadgroup.
 */
_MTL_INLINE void MTL4::TileRenderPipelineDescriptor::setMaxTotalThreadsPerThreadgroup(NS::UInteger maxTotalThreadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxTotalThreadsPerThreadgroup_), maxTotalThreadsPerThreadgroup);
}

/**
 * @brief Set the number of rasterization samples used by the pipeline.
 *
 * Specifies the number of samples per pixel that rasterization will use for this tile render pipeline descriptor.
 *
 * @param rasterSampleCount Number of samples per pixel to use for rasterization.
 */
_MTL_INLINE void MTL4::TileRenderPipelineDescriptor::setRasterSampleCount(NS::UInteger rasterSampleCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRasterSampleCount_), rasterSampleCount);
}

/**
 * @brief Sets the required threads-per-threadgroup size for the tile render pipeline.
 *
 * @param requiredThreadsPerThreadgroup Size specifying the required threadgroup dimensions (width, height, depth).
 */
_MTL_INLINE void MTL4::TileRenderPipelineDescriptor::setRequiredThreadsPerThreadgroup(MTL::Size requiredThreadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRequiredThreadsPerThreadgroup_), requiredThreadsPerThreadgroup);
}

/**
 * @brief Assigns the static linking descriptor for this tile render pipeline descriptor.
 *
 * @param staticLinkingDescriptor Descriptor to associate with the pipeline.
 */
_MTL_INLINE void MTL4::TileRenderPipelineDescriptor::setStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* staticLinkingDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStaticLinkingDescriptor_), staticLinkingDescriptor);
}

/**
 * @brief Enable or disable binary linking support for this tile render pipeline descriptor.
 *
 * @param supportBinaryLinking `true` to enable binary linking support, `false` to disable it.
 */
_MTL_INLINE void MTL4::TileRenderPipelineDescriptor::setSupportBinaryLinking(bool supportBinaryLinking)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportBinaryLinking_), supportBinaryLinking);
}

/**
 * @brief Configures whether the threadgroup size matches the tile size for this pipeline descriptor.
 *
 * When `true`, the threadgroup size will match the tile size; when `false`, the threadgroup size is not constrained to the tile size.
 *
 * @param threadgroupSizeMatchesTileSize `true` to make threadgroup size match tile size, `false` otherwise.
 */
_MTL_INLINE void MTL4::TileRenderPipelineDescriptor::setThreadgroupSizeMatchesTileSize(bool threadgroupSizeMatchesTileSize)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setThreadgroupSizeMatchesTileSize_), threadgroupSizeMatchesTileSize);
}

/**
 * @brief Sets the tile-stage function descriptor for this pipeline descriptor.
 *
 * @param tileFunctionDescriptor Descriptor describing the tile function to use for the pipeline; may be nullptr to clear the tile function.
 */
_MTL_INLINE void MTL4::TileRenderPipelineDescriptor::setTileFunctionDescriptor(const MTL4::FunctionDescriptor* tileFunctionDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTileFunctionDescriptor_), tileFunctionDescriptor);
}

/**
 * @brief Retrieve the static linking descriptor associated with the tile render pipeline.
 *
 * @return MTL4::StaticLinkingDescriptor* Pointer to the static linking descriptor, or `nullptr` if no descriptor is set.
 */
_MTL_INLINE MTL4::StaticLinkingDescriptor* MTL4::TileRenderPipelineDescriptor::staticLinkingDescriptor() const
{
    return Object::sendMessage<MTL4::StaticLinkingDescriptor*>(this, _MTL_PRIVATE_SEL(staticLinkingDescriptor));
}

/**
 * @brief Indicates whether binary linking is supported by this descriptor.
 *
 * @return `true` if binary linking is supported, `false` otherwise.
 */
_MTL_INLINE bool MTL4::TileRenderPipelineDescriptor::supportBinaryLinking() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportBinaryLinking));
}

/**
 * @brief Indicates whether the pipeline's threadgroup size equals the tile size.
 *
 * @return `true` if the threadgroup size matches the tile size, `false` otherwise.
 */
_MTL_INLINE bool MTL4::TileRenderPipelineDescriptor::threadgroupSizeMatchesTileSize() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(threadgroupSizeMatchesTileSize));
}

/**
 * @brief Retrieves the tile function descriptor associated with this tile render pipeline.
 *
 * @return MTL4::FunctionDescriptor* Pointer to the tile function descriptor, or `nullptr` if no tile function descriptor is set.
 */
_MTL_INLINE MTL4::FunctionDescriptor* MTL4::TileRenderPipelineDescriptor::tileFunctionDescriptor() const
{
    return Object::sendMessage<MTL4::FunctionDescriptor*>(this, _MTL_PRIVATE_SEL(tileFunctionDescriptor));
}