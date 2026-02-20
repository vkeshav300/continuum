//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4RenderPipeline.hpp
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
#include "MTLPixelFormat.hpp"
#include "MTLPrivate.hpp"
#include "MTLRenderPipeline.hpp"

namespace MTL4
{
class FunctionDescriptor;
class RenderPipelineBinaryFunctionsDescriptor;
class RenderPipelineColorAttachmentDescriptor;
class RenderPipelineColorAttachmentDescriptorArray;
class RenderPipelineDescriptor;
class StaticLinkingDescriptor;
}

namespace MTL
{
class VertexDescriptor;
}

namespace MTL4
{
/**
 * @brief Mapping state for translating logical color attachment indices to physical attachments.
 *
 * Defines how logical color attachment indices are interpreted when configuring a render pipeline.
 */

/**
 * @brief Describes the blending and pixel-related configuration for a single color attachment.
 *
 * Provides properties to query and set blend operations, blend factors for RGB and alpha,
 * the overall blending state, pixel format, and the color write mask. Includes lifecycle
 * helpers to allocate, initialize, and reset the descriptor to its default state.
 */

/**
 * @brief Array container for multiple RenderPipelineColorAttachmentDescriptor objects.
 *
 * Acts as an indexed collection of color attachment descriptors, allowing retrieval and
 * assignment by attachment index, and provides allocation/initialization and reset helpers.
 */

/**
 * @brief Describes additional binary function lists for pipeline shader stages.
 *
 * Holds optional NS::Array lists of additional binary functions for fragment, mesh, object,
 * tile, and vertex stages. Supports allocation, initialization, setting and retrieving each
 * stage's list, and resetting to default state.
 */

/**
 * @brief Encapsulates render pipeline configuration and related descriptors.
 *
 * Represents the full render pipeline descriptor including rasterization and sampling states,
 * alpha-to-coverage/one behavior, logical-to-physical color attachment mapping, color attachment
 * descriptors, function descriptors and static linking descriptors for vertex/fragment stages,
 * input primitive topology, vertex amplification, and feature support flags (binary linking,
 * indirect command buffers). Provides allocation/initialization, getters and setters for all
 * configurable properties, and a reset helper to restore defaults.
 */
_MTL_ENUM(NS::Integer, LogicalToPhysicalColorAttachmentMappingState) {
    LogicalToPhysicalColorAttachmentMappingStateIdentity = 0,
    LogicalToPhysicalColorAttachmentMappingStateInherited = 1,
};

class RenderPipelineColorAttachmentDescriptor : public NS::Copying<RenderPipelineColorAttachmentDescriptor>
{
public:
    static RenderPipelineColorAttachmentDescriptor* alloc();

    MTL::BlendOperation                             alphaBlendOperation() const;

    BlendState                                      blendingState() const;

    MTL::BlendFactor                                destinationAlphaBlendFactor() const;

    MTL::BlendFactor                                destinationRGBBlendFactor() const;

    RenderPipelineColorAttachmentDescriptor*        init();

    MTL::PixelFormat                                pixelFormat() const;

    void                                            reset();

    MTL::BlendOperation                             rgbBlendOperation() const;

    void                                            setAlphaBlendOperation(MTL::BlendOperation alphaBlendOperation);

    void                                            setBlendingState(MTL4::BlendState blendingState);

    void                                            setDestinationAlphaBlendFactor(MTL::BlendFactor destinationAlphaBlendFactor);

    void                                            setDestinationRGBBlendFactor(MTL::BlendFactor destinationRGBBlendFactor);

    void                                            setPixelFormat(MTL::PixelFormat pixelFormat);

    void                                            setRgbBlendOperation(MTL::BlendOperation rgbBlendOperation);

    void                                            setSourceAlphaBlendFactor(MTL::BlendFactor sourceAlphaBlendFactor);

    void                                            setSourceRGBBlendFactor(MTL::BlendFactor sourceRGBBlendFactor);

    void                                            setWriteMask(MTL::ColorWriteMask writeMask);

    MTL::BlendFactor                                sourceAlphaBlendFactor() const;

    MTL::BlendFactor                                sourceRGBBlendFactor() const;

    MTL::ColorWriteMask                             writeMask() const;
};

class RenderPipelineColorAttachmentDescriptorArray : public NS::Copying<RenderPipelineColorAttachmentDescriptorArray>
{
public:
    static RenderPipelineColorAttachmentDescriptorArray* alloc();

    RenderPipelineColorAttachmentDescriptorArray*        init();

    RenderPipelineColorAttachmentDescriptor*             object(NS::UInteger attachmentIndex);

    void                                                 reset();

    void                                                 setObject(const MTL4::RenderPipelineColorAttachmentDescriptor* attachment, NS::UInteger attachmentIndex);
};

class RenderPipelineBinaryFunctionsDescriptor : public NS::Copying<RenderPipelineBinaryFunctionsDescriptor>
{
public:
    static RenderPipelineBinaryFunctionsDescriptor* alloc();

    NS::Array*                                      fragmentAdditionalBinaryFunctions() const;

    RenderPipelineBinaryFunctionsDescriptor*        init();

    NS::Array*                                      meshAdditionalBinaryFunctions() const;

    NS::Array*                                      objectAdditionalBinaryFunctions() const;

    void                                            reset();

    void                                            setFragmentAdditionalBinaryFunctions(const NS::Array* fragmentAdditionalBinaryFunctions);

    void                                            setMeshAdditionalBinaryFunctions(const NS::Array* meshAdditionalBinaryFunctions);

    void                                            setObjectAdditionalBinaryFunctions(const NS::Array* objectAdditionalBinaryFunctions);

    void                                            setTileAdditionalBinaryFunctions(const NS::Array* tileAdditionalBinaryFunctions);

    void                                            setVertexAdditionalBinaryFunctions(const NS::Array* vertexAdditionalBinaryFunctions);

    NS::Array*                                      tileAdditionalBinaryFunctions() const;

    NS::Array*                                      vertexAdditionalBinaryFunctions() const;
};

class RenderPipelineDescriptor : public NS::Copying<RenderPipelineDescriptor, PipelineDescriptor>
{
public:
    static RenderPipelineDescriptor*              alloc();

    AlphaToCoverageState                          alphaToCoverageState() const;

    AlphaToOneState                               alphaToOneState() const;

    LogicalToPhysicalColorAttachmentMappingState  colorAttachmentMappingState() const;

    RenderPipelineColorAttachmentDescriptorArray* colorAttachments() const;

    FunctionDescriptor*                           fragmentFunctionDescriptor() const;

    StaticLinkingDescriptor*                      fragmentStaticLinkingDescriptor() const;

    RenderPipelineDescriptor*                     init();

    MTL::PrimitiveTopologyClass                   inputPrimitiveTopology() const;

    bool                                          isRasterizationEnabled() const;

    NS::UInteger                                  maxVertexAmplificationCount() const;

    NS::UInteger                                  rasterSampleCount() const;

    [[deprecated("please use isRasterizationEnabled instead")]]
    bool                              rasterizationEnabled() const;

    void                              reset();

    void                              setAlphaToCoverageState(MTL4::AlphaToCoverageState alphaToCoverageState);

    void                              setAlphaToOneState(MTL4::AlphaToOneState alphaToOneState);

    void                              setColorAttachmentMappingState(MTL4::LogicalToPhysicalColorAttachmentMappingState colorAttachmentMappingState);

    void                              setFragmentFunctionDescriptor(const MTL4::FunctionDescriptor* fragmentFunctionDescriptor);

    void                              setFragmentStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* fragmentStaticLinkingDescriptor);

    void                              setInputPrimitiveTopology(MTL::PrimitiveTopologyClass inputPrimitiveTopology);

    void                              setMaxVertexAmplificationCount(NS::UInteger maxVertexAmplificationCount);

    void                              setRasterSampleCount(NS::UInteger rasterSampleCount);

    void                              setRasterizationEnabled(bool rasterizationEnabled);

    void                              setSupportFragmentBinaryLinking(bool supportFragmentBinaryLinking);

    void                              setSupportIndirectCommandBuffers(MTL4::IndirectCommandBufferSupportState supportIndirectCommandBuffers);

    void                              setSupportVertexBinaryLinking(bool supportVertexBinaryLinking);

    void                              setVertexDescriptor(const MTL::VertexDescriptor* vertexDescriptor);

    void                              setVertexFunctionDescriptor(const MTL4::FunctionDescriptor* vertexFunctionDescriptor);

    void                              setVertexStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* vertexStaticLinkingDescriptor);

    bool                              supportFragmentBinaryLinking() const;

    IndirectCommandBufferSupportState supportIndirectCommandBuffers() const;

    bool                              supportVertexBinaryLinking() const;

    MTL::VertexDescriptor*            vertexDescriptor() const;

    FunctionDescriptor*               vertexFunctionDescriptor() const;

    StaticLinkingDescriptor*          vertexStaticLinkingDescriptor() const;
};

}
/**
 * @brief Allocates a new RenderPipelineColorAttachmentDescriptor instance.
 *
 * @return Pointer to a newly allocated MTL4::RenderPipelineColorAttachmentDescriptor.
 */
_MTL_INLINE MTL4::RenderPipelineColorAttachmentDescriptor* MTL4::RenderPipelineColorAttachmentDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::RenderPipelineColorAttachmentDescriptor>(_MTL_PRIVATE_CLS(MTL4RenderPipelineColorAttachmentDescriptor));
}

/**
 * @brief Retrieves the alpha blend operation for this color attachment.
 *
 * @return MTL::BlendOperation The alpha blend operation applied to the attachment.
 */
_MTL_INLINE MTL::BlendOperation MTL4::RenderPipelineColorAttachmentDescriptor::alphaBlendOperation() const
{
    return Object::sendMessage<MTL::BlendOperation>(this, _MTL_PRIVATE_SEL(alphaBlendOperation));
}

/**
 * @brief Retrieves the blending state for this color attachment.
 *
 * @return MTL4::BlendState The blending state currently configured for the attachment.
 */
_MTL_INLINE MTL4::BlendState MTL4::RenderPipelineColorAttachmentDescriptor::blendingState() const
{
    return Object::sendMessage<MTL4::BlendState>(this, _MTL_PRIVATE_SEL(blendingState));
}

/**
 * @brief Blend factor used for the destination alpha channel during blending.
 *
 * @return MTL::BlendFactor The destination alpha blend factor.
 */
_MTL_INLINE MTL::BlendFactor MTL4::RenderPipelineColorAttachmentDescriptor::destinationAlphaBlendFactor() const
{
    return Object::sendMessage<MTL::BlendFactor>(this, _MTL_PRIVATE_SEL(destinationAlphaBlendFactor));
}

/**
 * @brief Retrieves the destination RGB blend factor used when composing source and destination RGB components.
 *
 * @return MTL::BlendFactor The blend factor applied to destination RGB components.
 */
_MTL_INLINE MTL::BlendFactor MTL4::RenderPipelineColorAttachmentDescriptor::destinationRGBBlendFactor() const
{
    return Object::sendMessage<MTL::BlendFactor>(this, _MTL_PRIVATE_SEL(destinationRGBBlendFactor));
}

/**
 * @brief Initializes a newly allocated RenderPipelineColorAttachmentDescriptor instance.
 *
 * @return MTL4::RenderPipelineColorAttachmentDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL4::RenderPipelineColorAttachmentDescriptor* MTL4::RenderPipelineColorAttachmentDescriptor::init()
{
    return NS::Object::init<MTL4::RenderPipelineColorAttachmentDescriptor>();
}

/**
 * @brief Pixel format used by this color attachment.
 *
 * @return MTL::PixelFormat The pixel format of the attachment.
 */
_MTL_INLINE MTL::PixelFormat MTL4::RenderPipelineColorAttachmentDescriptor::pixelFormat() const
{
    return Object::sendMessage<MTL::PixelFormat>(this, _MTL_PRIVATE_SEL(pixelFormat));
}

/**
 * @brief Reset the color attachment descriptor to its default state.
 *
 * Restores all attachment properties (blend operations, blend factors,
 * pixel format, write mask, and blending state) to their default values.
 */
_MTL_INLINE void MTL4::RenderPipelineColorAttachmentDescriptor::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

/**
 * @brief Gets the RGB blend operation for this color attachment.
 *
 * @return MTL::BlendOperation The blend operation applied to RGB channels for the attachment.
 */
_MTL_INLINE MTL::BlendOperation MTL4::RenderPipelineColorAttachmentDescriptor::rgbBlendOperation() const
{
    return Object::sendMessage<MTL::BlendOperation>(this, _MTL_PRIVATE_SEL(rgbBlendOperation));
}

/**
 * @brief Sets the alpha blend operation for this color attachment descriptor.
 *
 * @param alphaBlendOperation The blend operation to apply to the alpha channel.
 */
_MTL_INLINE void MTL4::RenderPipelineColorAttachmentDescriptor::setAlphaBlendOperation(MTL::BlendOperation alphaBlendOperation)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAlphaBlendOperation_), alphaBlendOperation);
}

/**
 * @brief Sets the overall blending state for the color attachment.
 *
 * @param blendingState Blending state to apply to the color attachment.
 */
_MTL_INLINE void MTL4::RenderPipelineColorAttachmentDescriptor::setBlendingState(MTL4::BlendState blendingState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBlendingState_), blendingState);
}

/**
 * @brief Set the destination alpha blend factor for this color attachment.
 *
 * @param destinationAlphaBlendFactor Blend factor applied to the destination alpha channel during blending.
 */
_MTL_INLINE void MTL4::RenderPipelineColorAttachmentDescriptor::setDestinationAlphaBlendFactor(MTL::BlendFactor destinationAlphaBlendFactor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDestinationAlphaBlendFactor_), destinationAlphaBlendFactor);
}

/**
 * @brief Set the destination RGB blend factor for this color attachment.
 *
 * @param destinationRGBBlendFactor The blend factor to apply to the destination RGB components when blending.
 */
_MTL_INLINE void MTL4::RenderPipelineColorAttachmentDescriptor::setDestinationRGBBlendFactor(MTL::BlendFactor destinationRGBBlendFactor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDestinationRGBBlendFactor_), destinationRGBBlendFactor);
}

/**
 * @brief Sets the pixel format used by this color attachment.
 *
 * @param pixelFormat The pixel format to assign to the attachment.
 */
_MTL_INLINE void MTL4::RenderPipelineColorAttachmentDescriptor::setPixelFormat(MTL::PixelFormat pixelFormat)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPixelFormat_), pixelFormat);
}

/**
 * @brief Set the RGB blend operation for this color attachment descriptor.
 *
 * @param rgbBlendOperation The blend operation to apply to the RGB channels.
 */
_MTL_INLINE void MTL4::RenderPipelineColorAttachmentDescriptor::setRgbBlendOperation(MTL::BlendOperation rgbBlendOperation)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRgbBlendOperation_), rgbBlendOperation);
}

/**
 * @brief Sets the blend factor used for the source alpha channel of this color attachment.
 *
 * @param sourceAlphaBlendFactor The `MTL::BlendFactor` to apply to the source alpha when blending.
 */
_MTL_INLINE void MTL4::RenderPipelineColorAttachmentDescriptor::setSourceAlphaBlendFactor(MTL::BlendFactor sourceAlphaBlendFactor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSourceAlphaBlendFactor_), sourceAlphaBlendFactor);
}

/**
 * @brief Set the blend factor applied to the source RGB channels for this color attachment.
 *
 * @param sourceRGBBlendFactor Blend factor used for the source RGB components when performing color blending.
 */
_MTL_INLINE void MTL4::RenderPipelineColorAttachmentDescriptor::setSourceRGBBlendFactor(MTL::BlendFactor sourceRGBBlendFactor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSourceRGBBlendFactor_), sourceRGBBlendFactor);
}

/**
 * @brief Sets which color components are written to the render target for this attachment.
 *
 * @param writeMask Bitmask specifying the color channels (red, green, blue, alpha) that will be written.
 */
_MTL_INLINE void MTL4::RenderPipelineColorAttachmentDescriptor::setWriteMask(MTL::ColorWriteMask writeMask)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setWriteMask_), writeMask);
}

/**
 * @brief Retrieves the blend factor used for the source alpha component of this color attachment.
 *
 * @return MTL::BlendFactor The blend factor applied to the source alpha channel for this attachment.
 */
_MTL_INLINE MTL::BlendFactor MTL4::RenderPipelineColorAttachmentDescriptor::sourceAlphaBlendFactor() const
{
    return Object::sendMessage<MTL::BlendFactor>(this, _MTL_PRIVATE_SEL(sourceAlphaBlendFactor));
}

/**
 * @brief Gets the source RGB blend factor for this color attachment.
 *
 * @return MTL::BlendFactor The blend factor applied to the source RGB channels when performing color blending for this attachment.
 */
_MTL_INLINE MTL::BlendFactor MTL4::RenderPipelineColorAttachmentDescriptor::sourceRGBBlendFactor() const
{
    return Object::sendMessage<MTL::BlendFactor>(this, _MTL_PRIVATE_SEL(sourceRGBBlendFactor));
}

/**
 * @brief Color write mask for this color attachment.
 *
 * @return MTL::ColorWriteMask Bitmask specifying which color components (red, green, blue, alpha) will be written for the attachment.
 */
_MTL_INLINE MTL::ColorWriteMask MTL4::RenderPipelineColorAttachmentDescriptor::writeMask() const
{
    return Object::sendMessage<MTL::ColorWriteMask>(this, _MTL_PRIVATE_SEL(writeMask));
}

/**
 * @brief Allocate a new RenderPipelineColorAttachmentDescriptorArray instance.
 *
 * @return RenderPipelineColorAttachmentDescriptorArray* A newly allocated,
 * uninitialized instance of RenderPipelineColorAttachmentDescriptorArray.
 */
_MTL_INLINE MTL4::RenderPipelineColorAttachmentDescriptorArray* MTL4::RenderPipelineColorAttachmentDescriptorArray::alloc()
{
    return NS::Object::alloc<MTL4::RenderPipelineColorAttachmentDescriptorArray>(_MTL_PRIVATE_CLS(MTL4RenderPipelineColorAttachmentDescriptorArray));
}

/**
 * @brief Initializes a newly allocated RenderPipelineColorAttachmentDescriptorArray instance.
 *
 * @return RenderPipelineColorAttachmentDescriptorArray* Pointer to the initialized instance, or `nullptr` on failure.
 */
_MTL_INLINE MTL4::RenderPipelineColorAttachmentDescriptorArray* MTL4::RenderPipelineColorAttachmentDescriptorArray::init()
{
    return NS::Object::init<MTL4::RenderPipelineColorAttachmentDescriptorArray>();
}

/**
 * @brief Accesses the color attachment descriptor at the specified index.
 *
 * @param attachmentIndex Index of the color attachment to retrieve.
 * @return MTL4::RenderPipelineColorAttachmentDescriptor* Pointer to the descriptor for the given attachment index.
 */
_MTL_INLINE MTL4::RenderPipelineColorAttachmentDescriptor* MTL4::RenderPipelineColorAttachmentDescriptorArray::object(NS::UInteger attachmentIndex)
{
    return Object::sendMessage<MTL4::RenderPipelineColorAttachmentDescriptor*>(this, _MTL_PRIVATE_SEL(objectAtIndexedSubscript_), attachmentIndex);
}

/**
 * @brief Reset the color attachment descriptor array to its default state.
 *
 * Restores the array and its contained RenderPipelineColorAttachmentDescriptor
 * objects to their default configuration.
 */
_MTL_INLINE void MTL4::RenderPipelineColorAttachmentDescriptorArray::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

/**
 * @brief Sets the color attachment descriptor at the specified index.
 *
 * Replaces the descriptor stored at attachmentIndex with attachment.
 *
 * @param attachment Descriptor to place into the array.
 * @param attachmentIndex Index at which to set the descriptor.
 */
_MTL_INLINE void MTL4::RenderPipelineColorAttachmentDescriptorArray::setObject(const MTL4::RenderPipelineColorAttachmentDescriptor* attachment, NS::UInteger attachmentIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObject_atIndexedSubscript_), attachment, attachmentIndex);
}

/**
 * @brief Allocate a new RenderPipelineBinaryFunctionsDescriptor instance.
 *
 * @return MTL4::RenderPipelineBinaryFunctionsDescriptor* Pointer to a newly allocated RenderPipelineBinaryFunctionsDescriptor.
 */
_MTL_INLINE MTL4::RenderPipelineBinaryFunctionsDescriptor* MTL4::RenderPipelineBinaryFunctionsDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::RenderPipelineBinaryFunctionsDescriptor>(_MTL_PRIVATE_CLS(MTL4RenderPipelineBinaryFunctionsDescriptor));
}

/**
 * @brief Accesses the additional binary functions assigned to the fragment stage.
 *
 * @return NS::Array* Array of fragment-stage additional binary functions, or `nullptr` if none are set.
 */
_MTL_INLINE NS::Array* MTL4::RenderPipelineBinaryFunctionsDescriptor::fragmentAdditionalBinaryFunctions() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(fragmentAdditionalBinaryFunctions));
}

/**
 * @brief Initialize a newly allocated RenderPipelineBinaryFunctionsDescriptor instance.
 *
 * @return MTL4::RenderPipelineBinaryFunctionsDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL4::RenderPipelineBinaryFunctionsDescriptor* MTL4::RenderPipelineBinaryFunctionsDescriptor::init()
{
    return NS::Object::init<MTL4::RenderPipelineBinaryFunctionsDescriptor>();
}

/**
 * @brief Retrieve the array of additional binary functions for the mesh shader stage.
 *
 * @return NS::Array* Array of additional binary functions for the mesh stage.
 */
_MTL_INLINE NS::Array* MTL4::RenderPipelineBinaryFunctionsDescriptor::meshAdditionalBinaryFunctions() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(meshAdditionalBinaryFunctions));
}

/**
 * @brief Retrieves the additional binary functions configured for the object shader stage.
 *
 * @return NS::Array* Array of additional binary function descriptors for the object stage.
 */
_MTL_INLINE NS::Array* MTL4::RenderPipelineBinaryFunctionsDescriptor::objectAdditionalBinaryFunctions() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(objectAdditionalBinaryFunctions));
}

/**
 * @brief Reset the descriptor to its default state.
 *
 * Restores all per-stage additional binary function lists and any other
 * modified properties to their defaults.
 */
_MTL_INLINE void MTL4::RenderPipelineBinaryFunctionsDescriptor::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

/**
 * @brief Set the array of additional binary functions for the fragment shader stage.
 *
 * Replaces the current list of fragment-stage additional binary functions with the provided array.
 *
 * @param fragmentAdditionalBinaryFunctions Array of binary function descriptors to use for the fragment stage.
 */
_MTL_INLINE void MTL4::RenderPipelineBinaryFunctionsDescriptor::setFragmentAdditionalBinaryFunctions(const NS::Array* fragmentAdditionalBinaryFunctions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFragmentAdditionalBinaryFunctions_), fragmentAdditionalBinaryFunctions);
}

/**
 * @brief Set the additional binary functions used by the mesh shader stage.
 *
 * @param meshAdditionalBinaryFunctions An NS::Array containing the mesh-stage additional binary functions to associate with this descriptor.
 */
_MTL_INLINE void MTL4::RenderPipelineBinaryFunctionsDescriptor::setMeshAdditionalBinaryFunctions(const NS::Array* meshAdditionalBinaryFunctions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMeshAdditionalBinaryFunctions_), meshAdditionalBinaryFunctions);
}

/**
 * @brief Sets the additional binary functions for the object shader stage.
 *
 * @param objectAdditionalBinaryFunctions Array of additional binary functions to associate with the object stage.
 */
_MTL_INLINE void MTL4::RenderPipelineBinaryFunctionsDescriptor::setObjectAdditionalBinaryFunctions(const NS::Array* objectAdditionalBinaryFunctions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObjectAdditionalBinaryFunctions_), objectAdditionalBinaryFunctions);
}

/**
 * @brief Sets the additional compiled binary functions to be used by the tile shading stage.
 *
 * @param tileAdditionalBinaryFunctions An NSArray of function objects describing additional tile-stage binary functions; passing `nullptr` clears the list.
 */
_MTL_INLINE void MTL4::RenderPipelineBinaryFunctionsDescriptor::setTileAdditionalBinaryFunctions(const NS::Array* tileAdditionalBinaryFunctions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTileAdditionalBinaryFunctions_), tileAdditionalBinaryFunctions);
}

/**
 * @brief Specifies additional precompiled binary functions for the vertex shader stage.
 *
 * @param vertexAdditionalBinaryFunctions An NS::Array containing function descriptors for vertex-stage additional binary functions; each element is expected to be a `MTL4::FunctionDescriptor` or equivalent descriptor object.
 */
_MTL_INLINE void MTL4::RenderPipelineBinaryFunctionsDescriptor::setVertexAdditionalBinaryFunctions(const NS::Array* vertexAdditionalBinaryFunctions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexAdditionalBinaryFunctions_), vertexAdditionalBinaryFunctions);
}

/**
 * @brief Retrieve the additional binary functions configured for the tile shader stage.
 *
 * @return NS::Array* An array containing additional binary function descriptors for the tile stage
 * (each element is a `FunctionDescriptor*`), or `nullptr` if no additional tile functions are set.
 */
_MTL_INLINE NS::Array* MTL4::RenderPipelineBinaryFunctionsDescriptor::tileAdditionalBinaryFunctions() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(tileAdditionalBinaryFunctions));
}

/**
 * @brief Accesses the additional binary functions associated with the vertex stage.
 *
 * @return NS::Array* Array containing additional binary function descriptors for the vertex shader stage.
 */
_MTL_INLINE NS::Array* MTL4::RenderPipelineBinaryFunctionsDescriptor::vertexAdditionalBinaryFunctions() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(vertexAdditionalBinaryFunctions));
}

/**
 * @brief Allocate a new RenderPipelineDescriptor.
 *
 * @return MTL4::RenderPipelineDescriptor* Newly allocated RenderPipelineDescriptor instance; not initialized — call init() before use.
 */
_MTL_INLINE MTL4::RenderPipelineDescriptor* MTL4::RenderPipelineDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::RenderPipelineDescriptor>(_MTL_PRIVATE_CLS(MTL4RenderPipelineDescriptor));
}

/**
 * @brief Retrieves the alpha-to-coverage state for this render pipeline descriptor.
 *
 * @return MTL4::AlphaToCoverageState The current alpha-to-coverage state.
 */
_MTL_INLINE MTL4::AlphaToCoverageState MTL4::RenderPipelineDescriptor::alphaToCoverageState() const
{
    return Object::sendMessage<MTL4::AlphaToCoverageState>(this, _MTL_PRIVATE_SEL(alphaToCoverageState));
}

/**
 * @brief Retrieves the alpha-to-one state for this render pipeline descriptor.
 *
 * @return MTL4::AlphaToOneState The current alpha-to-one state.
 */
_MTL_INLINE MTL4::AlphaToOneState MTL4::RenderPipelineDescriptor::alphaToOneState() const
{
    return Object::sendMessage<MTL4::AlphaToOneState>(this, _MTL_PRIVATE_SEL(alphaToOneState));
}

/**
 * @brief Query the logical-to-physical color attachment mapping state for this render pipeline.
 *
 * @return MTL4::LogicalToPhysicalColorAttachmentMappingState The mapping state: `Identity` if logical and physical attachments are the same, `Inherited` if the mapping is inherited.
 */
_MTL_INLINE MTL4::LogicalToPhysicalColorAttachmentMappingState MTL4::RenderPipelineDescriptor::colorAttachmentMappingState() const
{
    return Object::sendMessage<MTL4::LogicalToPhysicalColorAttachmentMappingState>(this, _MTL_PRIVATE_SEL(colorAttachmentMappingState));
}

/**
 * @brief Accesses the array of color attachment descriptors for this render pipeline descriptor.
 *
 * @return MTL4::RenderPipelineColorAttachmentDescriptorArray* Pointer to the descriptor array containing per-attachment RenderPipelineColorAttachmentDescriptor objects.
 */
_MTL_INLINE MTL4::RenderPipelineColorAttachmentDescriptorArray* MTL4::RenderPipelineDescriptor::colorAttachments() const
{
    return Object::sendMessage<MTL4::RenderPipelineColorAttachmentDescriptorArray*>(this, _MTL_PRIVATE_SEL(colorAttachments));
}

/**
 * @brief Retrieves the fragment-stage function descriptor for this render pipeline.
 *
 * The returned descriptor represents the fragment function configured for the pipeline, or `nullptr` if no fragment function descriptor is set.
 *
 * @return MTL4::FunctionDescriptor* Pointer to the fragment function descriptor, or `nullptr`.
 */
_MTL_INLINE MTL4::FunctionDescriptor* MTL4::RenderPipelineDescriptor::fragmentFunctionDescriptor() const
{
    return Object::sendMessage<MTL4::FunctionDescriptor*>(this, _MTL_PRIVATE_SEL(fragmentFunctionDescriptor));
}

/**
 * @brief Accesses the fragment-stage static linking descriptor for the render pipeline.
 *
 * @return MTL4::StaticLinkingDescriptor* The fragment-stage static linking descriptor, or `nullptr` if no fragment static linking descriptor is set.
 */
_MTL_INLINE MTL4::StaticLinkingDescriptor* MTL4::RenderPipelineDescriptor::fragmentStaticLinkingDescriptor() const
{
    return Object::sendMessage<MTL4::StaticLinkingDescriptor*>(this, _MTL_PRIVATE_SEL(fragmentStaticLinkingDescriptor));
}

/**
 * @brief Initializes a newly allocated RenderPipelineDescriptor instance.
 *
 * @return MTL4::RenderPipelineDescriptor* Pointer to the initialized RenderPipelineDescriptor.
 */
_MTL_INLINE MTL4::RenderPipelineDescriptor* MTL4::RenderPipelineDescriptor::init()
{
    return NS::Object::init<MTL4::RenderPipelineDescriptor>();
}

/**
 * @brief Retrieves the input primitive topology for this render pipeline descriptor.
 *
 * @return MTL::PrimitiveTopologyClass The topology class that defines how vertex primitives are assembled.
 */
_MTL_INLINE MTL::PrimitiveTopologyClass MTL4::RenderPipelineDescriptor::inputPrimitiveTopology() const
{
    return Object::sendMessage<MTL::PrimitiveTopologyClass>(this, _MTL_PRIVATE_SEL(inputPrimitiveTopology));
}

/**
 * @brief Indicates whether rasterization is enabled for this render pipeline descriptor.
 *
 * @return `true` if rasterization is enabled, `false` otherwise.
 */
_MTL_INLINE bool MTL4::RenderPipelineDescriptor::isRasterizationEnabled() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isRasterizationEnabled));
}

/**
 * @brief Retrieves the maximum vertex amplification count configured for this render pipeline.
 *
 * @return NS::UInteger Maximum number of times a single vertex invocation may be amplified by the pipeline.
 */
_MTL_INLINE NS::UInteger MTL4::RenderPipelineDescriptor::maxVertexAmplificationCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxVertexAmplificationCount));
}

/**
 * @brief The number of rasterization samples used by this render pipeline.
 *
 * @return NS::UInteger The number of samples per pixel used when rasterizing.
 */
_MTL_INLINE NS::UInteger MTL4::RenderPipelineDescriptor::rasterSampleCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(rasterSampleCount));
}

/**
 * @brief Indicates whether rasterization is enabled for the render pipeline.
 *
 * @return `true` if rasterization is enabled, `false` otherwise.
 */
_MTL_INLINE bool MTL4::RenderPipelineDescriptor::rasterizationEnabled() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isRasterizationEnabled));
}

/**
 * @brief Reset the render pipeline descriptor to its default state.
 *
 * Restores all configurable properties of this descriptor (including nested
 * color attachment, binary function, and static linking descriptors) to their
 * default values.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

/**
 * @brief Set the alpha-to-coverage state used by the render pipeline descriptor.
 *
 * @param alphaToCoverageState The AlphaToCoverageState to apply to this descriptor.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setAlphaToCoverageState(MTL4::AlphaToCoverageState alphaToCoverageState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAlphaToCoverageState_), alphaToCoverageState);
}

/**
 * @brief Sets the alpha-to-one state for the render pipeline.
 *
 * Controls whether fragment alpha values are treated as one during blending operations.
 *
 * @param alphaToOneState The AlphaToOneState value to apply to the pipeline.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setAlphaToOneState(MTL4::AlphaToOneState alphaToOneState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAlphaToOneState_), alphaToOneState);
}

/**
 * @brief Set the logical-to-physical color attachment mapping state for the render pipeline.
 *
 * @param colorAttachmentMappingState Specifies how logical color attachment indices are mapped to physical attachments.
 *        Use `MTL4::LogicalToPhysicalColorAttachmentMappingState::Identity` to map logical indices directly to the same physical indices,
 *        or `MTL4::LogicalToPhysicalColorAttachmentMappingState::Inherited` to inherit the mapping from an enclosing state.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setColorAttachmentMappingState(MTL4::LogicalToPhysicalColorAttachmentMappingState colorAttachmentMappingState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setColorAttachmentMappingState_), colorAttachmentMappingState);
}

/**
 * @brief Assigns the fragment-stage function descriptor for this render pipeline.
 *
 * @param fragmentFunctionDescriptor Pointer to a MTL4::FunctionDescriptor that specifies the fragment function to use for the pipeline; may be nullptr to clear the fragment function.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setFragmentFunctionDescriptor(const MTL4::FunctionDescriptor* fragmentFunctionDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFragmentFunctionDescriptor_), fragmentFunctionDescriptor);
}

/**
 * @brief Sets the static linking descriptor for the fragment stage of the render pipeline.
 *
 * @param fragmentStaticLinkingDescriptor Descriptor that configures static binary linking for fragment-stage functions; pass `nullptr` to clear it.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setFragmentStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* fragmentStaticLinkingDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFragmentStaticLinkingDescriptor_), fragmentStaticLinkingDescriptor);
}

/**
 * @brief Sets the primitive topology class used to interpret vertex input for the pipeline.
 *
 * @param inputPrimitiveTopology The primitive topology class that defines how vertex/index data are assembled into primitives (e.g., points, lines, triangles).
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setInputPrimitiveTopology(MTL::PrimitiveTopologyClass inputPrimitiveTopology)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInputPrimitiveTopology_), inputPrimitiveTopology);
}

/**
 * @brief Set the maximum number of vertex amplification instances the pipeline may use.
 *
 * @param maxVertexAmplificationCount Maximum vertex amplification count (number of vertex shader invocations per input vertex).
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setMaxVertexAmplificationCount(NS::UInteger maxVertexAmplificationCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxVertexAmplificationCount_), maxVertexAmplificationCount);
}

/**
 * @brief Sets the number of raster samples used per pixel during rasterization.
 *
 * @param rasterSampleCount Number of samples per pixel to use for rasterization.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setRasterSampleCount(NS::UInteger rasterSampleCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRasterSampleCount_), rasterSampleCount);
}

/**
 * @brief Sets whether rasterization is enabled for the render pipeline.
 *
 * @param rasterizationEnabled `true` to enable rasterization, `false` to disable it.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setRasterizationEnabled(bool rasterizationEnabled)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRasterizationEnabled_), rasterizationEnabled);
}

/**
 * @brief Enable or disable fragment-stage binary linking for the render pipeline.
 *
 * @param supportFragmentBinaryLinking True to enable fragment binary linking, false to disable it.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setSupportFragmentBinaryLinking(bool supportFragmentBinaryLinking)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportFragmentBinaryLinking_), supportFragmentBinaryLinking);
}

/**
 * @brief Sets the indirect command buffer support state for the render pipeline.
 *
 * @param supportIndirectCommandBuffers The IndirectCommandBufferSupportState value to apply to this descriptor.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setSupportIndirectCommandBuffers(MTL4::IndirectCommandBufferSupportState supportIndirectCommandBuffers)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportIndirectCommandBuffers_), supportIndirectCommandBuffers);
}

/**
 * @brief Enable or disable vertex binary linking support on the render pipeline descriptor.
 *
 * @param supportVertexBinaryLinking `true` to enable vertex binary linking support, `false` to disable it.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setSupportVertexBinaryLinking(bool supportVertexBinaryLinking)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportVertexBinaryLinking_), supportVertexBinaryLinking);
}

/**
 * @brief Set the vertex layout and attribute configuration used by the pipeline.
 *
 * @param vertexDescriptor The `MTL::VertexDescriptor` describing vertex buffer layouts and attribute formats to apply to this render pipeline descriptor.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setVertexDescriptor(const MTL::VertexDescriptor* vertexDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexDescriptor_), vertexDescriptor);
}

/**
 * @brief Sets the vertex-stage function descriptor used by the render pipeline.
 *
 * @param vertexFunctionDescriptor Descriptor describing the vertex function to attach to the pipeline; pass `nullptr` to clear any existing vertex function descriptor.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setVertexFunctionDescriptor(const MTL4::FunctionDescriptor* vertexFunctionDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexFunctionDescriptor_), vertexFunctionDescriptor);
}

/**
 * @brief Assigns the static linking descriptor for the pipeline's vertex stage.
 *
 * @param vertexStaticLinkingDescriptor Descriptor to use for vertex-stage static linking; may be `nullptr` to unset.
 */
_MTL_INLINE void MTL4::RenderPipelineDescriptor::setVertexStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* vertexStaticLinkingDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexStaticLinkingDescriptor_), vertexStaticLinkingDescriptor);
}

/**
 * @brief Reports whether fragment binary linking is supported.
 *
 * @return `true` if fragment binary linking is supported, `false` otherwise.
 */
_MTL_INLINE bool MTL4::RenderPipelineDescriptor::supportFragmentBinaryLinking() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportFragmentBinaryLinking));
}

/**
 * @brief Queries the render pipeline's support level for indirect command buffers.
 *
 * @return MTL4::IndirectCommandBufferSupportState The pipeline's indirect command buffer support state.
 */
_MTL_INLINE MTL4::IndirectCommandBufferSupportState MTL4::RenderPipelineDescriptor::supportIndirectCommandBuffers() const
{
    return Object::sendMessage<MTL4::IndirectCommandBufferSupportState>(this, _MTL_PRIVATE_SEL(supportIndirectCommandBuffers));
}

/**
 * @brief Indicates whether vertex binary linking is supported.
 *
 * @return `true` if vertex binary linking is supported, `false` otherwise.
 */
_MTL_INLINE bool MTL4::RenderPipelineDescriptor::supportVertexBinaryLinking() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportVertexBinaryLinking));
}

/**
 * @brief Retrieves the vertex descriptor associated with the render pipeline.
 *
 * @return MTL::VertexDescriptor* Pointer to the vertex descriptor used by the pipeline, or `nullptr` if none is set.
 */
_MTL_INLINE MTL::VertexDescriptor* MTL4::RenderPipelineDescriptor::vertexDescriptor() const
{
    return Object::sendMessage<MTL::VertexDescriptor*>(this, _MTL_PRIVATE_SEL(vertexDescriptor));
}

/**
 * @brief Get the vertex function descriptor associated with the render pipeline.
 *
 * @return MTL4::FunctionDescriptor* The vertex function descriptor, or `nullptr` if none is set.
 */
_MTL_INLINE MTL4::FunctionDescriptor* MTL4::RenderPipelineDescriptor::vertexFunctionDescriptor() const
{
    return Object::sendMessage<MTL4::FunctionDescriptor*>(this, _MTL_PRIVATE_SEL(vertexFunctionDescriptor));
}

/**
 * @brief Accesses the static linking descriptor for the vertex shader stage.
 *
 * @return MTL4::StaticLinkingDescriptor* The static linking descriptor for the vertex stage, or `nullptr` if no descriptor is set.
 */
_MTL_INLINE MTL4::StaticLinkingDescriptor* MTL4::RenderPipelineDescriptor::vertexStaticLinkingDescriptor() const
{
    return Object::sendMessage<MTL4::StaticLinkingDescriptor*>(this, _MTL_PRIVATE_SEL(vertexStaticLinkingDescriptor));
}