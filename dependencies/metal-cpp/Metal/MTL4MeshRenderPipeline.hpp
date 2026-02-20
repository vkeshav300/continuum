//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4MeshRenderPipeline.hpp
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
#include "MTL4RenderPipeline.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLTypes.hpp"

namespace MTL4
{
class FunctionDescriptor;
class MeshRenderPipelineDescriptor;
class RenderPipelineColorAttachmentDescriptorArray;
class StaticLinkingDescriptor;

class MeshRenderPipelineDescriptor : public NS::Copying<MeshRenderPipelineDescriptor, PipelineDescriptor>
{
public:
    static MeshRenderPipelineDescriptor*          alloc();

    AlphaToCoverageState                          alphaToCoverageState() const;

    AlphaToOneState                               alphaToOneState() const;

    LogicalToPhysicalColorAttachmentMappingState  colorAttachmentMappingState() const;

    RenderPipelineColorAttachmentDescriptorArray* colorAttachments() const;

    FunctionDescriptor*                           fragmentFunctionDescriptor() const;

    StaticLinkingDescriptor*                      fragmentStaticLinkingDescriptor() const;

    MeshRenderPipelineDescriptor*                 init();

    bool                                          isRasterizationEnabled() const;

    NS::UInteger                                  maxTotalThreadgroupsPerMeshGrid() const;

    NS::UInteger                                  maxTotalThreadsPerMeshThreadgroup() const;

    NS::UInteger                                  maxTotalThreadsPerObjectThreadgroup() const;

    NS::UInteger                                  maxVertexAmplificationCount() const;

    FunctionDescriptor*                           meshFunctionDescriptor() const;

    StaticLinkingDescriptor*                      meshStaticLinkingDescriptor() const;

    bool                                          meshThreadgroupSizeIsMultipleOfThreadExecutionWidth() const;

    FunctionDescriptor*                           objectFunctionDescriptor() const;

    StaticLinkingDescriptor*                      objectStaticLinkingDescriptor() const;

    bool                                          objectThreadgroupSizeIsMultipleOfThreadExecutionWidth() const;

    NS::UInteger                                  payloadMemoryLength() const;

    NS::UInteger                                  rasterSampleCount() const;

    [[deprecated("please use isRasterizationEnabled instead")]]
    bool                              rasterizationEnabled() const;

    MTL::Size                         requiredThreadsPerMeshThreadgroup() const;

    MTL::Size                         requiredThreadsPerObjectThreadgroup() const;

    void                              reset();

    void                              setAlphaToCoverageState(MTL4::AlphaToCoverageState alphaToCoverageState);

    void                              setAlphaToOneState(MTL4::AlphaToOneState alphaToOneState);

    void                              setColorAttachmentMappingState(MTL4::LogicalToPhysicalColorAttachmentMappingState colorAttachmentMappingState);

    void                              setFragmentFunctionDescriptor(const MTL4::FunctionDescriptor* fragmentFunctionDescriptor);

    void                              setFragmentStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* fragmentStaticLinkingDescriptor);

    void                              setMaxTotalThreadgroupsPerMeshGrid(NS::UInteger maxTotalThreadgroupsPerMeshGrid);

    void                              setMaxTotalThreadsPerMeshThreadgroup(NS::UInteger maxTotalThreadsPerMeshThreadgroup);

    void                              setMaxTotalThreadsPerObjectThreadgroup(NS::UInteger maxTotalThreadsPerObjectThreadgroup);

    void                              setMaxVertexAmplificationCount(NS::UInteger maxVertexAmplificationCount);

    void                              setMeshFunctionDescriptor(const MTL4::FunctionDescriptor* meshFunctionDescriptor);

    void                              setMeshStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* meshStaticLinkingDescriptor);

    void                              setMeshThreadgroupSizeIsMultipleOfThreadExecutionWidth(bool meshThreadgroupSizeIsMultipleOfThreadExecutionWidth);

    void                              setObjectFunctionDescriptor(const MTL4::FunctionDescriptor* objectFunctionDescriptor);

    void                              setObjectStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* objectStaticLinkingDescriptor);

    void                              setObjectThreadgroupSizeIsMultipleOfThreadExecutionWidth(bool objectThreadgroupSizeIsMultipleOfThreadExecutionWidth);

    void                              setPayloadMemoryLength(NS::UInteger payloadMemoryLength);

    void                              setRasterSampleCount(NS::UInteger rasterSampleCount);

    void                              setRasterizationEnabled(bool rasterizationEnabled);

    void                              setRequiredThreadsPerMeshThreadgroup(MTL::Size requiredThreadsPerMeshThreadgroup);

    void                              setRequiredThreadsPerObjectThreadgroup(MTL::Size requiredThreadsPerObjectThreadgroup);

    void                              setSupportFragmentBinaryLinking(bool supportFragmentBinaryLinking);

    void                              setSupportIndirectCommandBuffers(MTL4::IndirectCommandBufferSupportState supportIndirectCommandBuffers);

    void                              setSupportMeshBinaryLinking(bool supportMeshBinaryLinking);

    void                              setSupportObjectBinaryLinking(bool supportObjectBinaryLinking);

    bool                              supportFragmentBinaryLinking() const;

    IndirectCommandBufferSupportState supportIndirectCommandBuffers() const;

    bool                              supportMeshBinaryLinking() const;

    bool                              supportObjectBinaryLinking() const;
};

}
/**
 * @brief Allocate a new MeshRenderPipelineDescriptor instance.
 *
 * @return MTL4::MeshRenderPipelineDescriptor* A newly allocated, uninitialized descriptor instance.
 */
_MTL_INLINE MTL4::MeshRenderPipelineDescriptor* MTL4::MeshRenderPipelineDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::MeshRenderPipelineDescriptor>(_MTL_PRIVATE_CLS(MTL4MeshRenderPipelineDescriptor));
}

/**
 * @brief Gets the alpha-to-coverage state used by this mesh render pipeline descriptor.
 *
 * @return MTL4::AlphaToCoverageState The current alpha-to-coverage state.
 */
_MTL_INLINE MTL4::AlphaToCoverageState MTL4::MeshRenderPipelineDescriptor::alphaToCoverageState() const
{
    return Object::sendMessage<MTL4::AlphaToCoverageState>(this, _MTL_PRIVATE_SEL(alphaToCoverageState));
}

/**
 * @brief Gets the alpha-to-one blending state for this mesh render pipeline descriptor.
 *
 * @return MTL4::AlphaToOneState The alpha-to-one blending state.
 */
_MTL_INLINE MTL4::AlphaToOneState MTL4::MeshRenderPipelineDescriptor::alphaToOneState() const
{
    return Object::sendMessage<MTL4::AlphaToOneState>(this, _MTL_PRIVATE_SEL(alphaToOneState));
}

/**
 * @brief Retrieves the logical-to-physical color attachment mapping state for the descriptor.
 *
 * @return MTL4::LogicalToPhysicalColorAttachmentMappingState The mapping state currently configured on this descriptor.
 */
_MTL_INLINE MTL4::LogicalToPhysicalColorAttachmentMappingState MTL4::MeshRenderPipelineDescriptor::colorAttachmentMappingState() const
{
    return Object::sendMessage<MTL4::LogicalToPhysicalColorAttachmentMappingState>(this, _MTL_PRIVATE_SEL(colorAttachmentMappingState));
}

/**
 * @brief Accesses the color attachment descriptor array for this mesh render pipeline.
 *
 * @return MTL4::RenderPipelineColorAttachmentDescriptorArray* Pointer to the array of per-color-attachment descriptors.
 */
_MTL_INLINE MTL4::RenderPipelineColorAttachmentDescriptorArray* MTL4::MeshRenderPipelineDescriptor::colorAttachments() const
{
    return Object::sendMessage<MTL4::RenderPipelineColorAttachmentDescriptorArray*>(this, _MTL_PRIVATE_SEL(colorAttachments));
}

/**
 * @brief Retrieves the function descriptor used by the pipeline's fragment stage.
 *
 * @return MTL4::FunctionDescriptor* Pointer to the fragment function descriptor, or `nullptr` if no fragment function descriptor is set.
 */
_MTL_INLINE MTL4::FunctionDescriptor* MTL4::MeshRenderPipelineDescriptor::fragmentFunctionDescriptor() const
{
    return Object::sendMessage<MTL4::FunctionDescriptor*>(this, _MTL_PRIVATE_SEL(fragmentFunctionDescriptor));
}

/**
 * @brief Retrieves the static linking descriptor used by the fragment stage.
 *
 * @return MTL4::StaticLinkingDescriptor* Pointer to the fragment static linking descriptor, or `nullptr` if no fragment static linking descriptor is set.
 */
_MTL_INLINE MTL4::StaticLinkingDescriptor* MTL4::MeshRenderPipelineDescriptor::fragmentStaticLinkingDescriptor() const
{
    return Object::sendMessage<MTL4::StaticLinkingDescriptor*>(this, _MTL_PRIVATE_SEL(fragmentStaticLinkingDescriptor));
}

/**
 * @brief Initialize the mesh render pipeline descriptor and prepare it for use.
 *
 * @return MTL4::MeshRenderPipelineDescriptor* Pointer to the initialized descriptor instance.
 */
_MTL_INLINE MTL4::MeshRenderPipelineDescriptor* MTL4::MeshRenderPipelineDescriptor::init()
{
    return NS::Object::init<MTL4::MeshRenderPipelineDescriptor>();
}

/**
 * @brief Indicates whether rasterization is enabled for the mesh render pipeline.
 *
 * @return `true` if rasterization is enabled for the pipeline, `false` otherwise.
 */
_MTL_INLINE bool MTL4::MeshRenderPipelineDescriptor::isRasterizationEnabled() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isRasterizationEnabled));
}

/**
 * @brief Retrieves the maximum number of threadgroups allowed in a mesh grid.
 *
 * @return NS::UInteger The maximum total threadgroups permitted per mesh grid.
 */
_MTL_INLINE NS::UInteger MTL4::MeshRenderPipelineDescriptor::maxTotalThreadgroupsPerMeshGrid() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxTotalThreadgroupsPerMeshGrid));
}

/**
 * @brief Retrieves the maximum total number of threads allowed in a mesh threadgroup.
 *
 * @return NS::UInteger The maximum total threads permitted in a mesh threadgroup.
 */
_MTL_INLINE NS::UInteger MTL4::MeshRenderPipelineDescriptor::maxTotalThreadsPerMeshThreadgroup() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxTotalThreadsPerMeshThreadgroup));
}

/**
 * @brief Maximum total threads allowed in a single object threadgroup.
 *
 * @return NS::UInteger The maximum number of threads permitted per object threadgroup.
 */
_MTL_INLINE NS::UInteger MTL4::MeshRenderPipelineDescriptor::maxTotalThreadsPerObjectThreadgroup() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxTotalThreadsPerObjectThreadgroup));
}

/**
 * @brief Gets the maximum vertex amplification count for the mesh render pipeline.
 *
 * @return NS::UInteger The maximum number of vertex amplifications supported by this pipeline.
 */
_MTL_INLINE NS::UInteger MTL4::MeshRenderPipelineDescriptor::maxVertexAmplificationCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxVertexAmplificationCount));
}

/**
 * @brief Retrieves the mesh function descriptor associated with this pipeline descriptor.
 *
 * @return MTL4::FunctionDescriptor* The mesh function descriptor, or `nullptr` if no mesh function is set.
 */
_MTL_INLINE MTL4::FunctionDescriptor* MTL4::MeshRenderPipelineDescriptor::meshFunctionDescriptor() const
{
    return Object::sendMessage<MTL4::FunctionDescriptor*>(this, _MTL_PRIVATE_SEL(meshFunctionDescriptor));
}

/**
 * @brief Accesses the mesh-stage static linking descriptor.
 *
 * @return MTL4::StaticLinkingDescriptor* Pointer to the mesh-stage static linking descriptor, or `nullptr` if none is configured.
 */
_MTL_INLINE MTL4::StaticLinkingDescriptor* MTL4::MeshRenderPipelineDescriptor::meshStaticLinkingDescriptor() const
{
    return Object::sendMessage<MTL4::StaticLinkingDescriptor*>(this, _MTL_PRIVATE_SEL(meshStaticLinkingDescriptor));
}

/**
 * @brief Indicates whether the mesh threadgroup size must be a multiple of the thread execution width.
 *
 * @return `true` if the mesh threadgroup size is required to be a multiple of the thread execution width, `false` otherwise.
 */
_MTL_INLINE bool MTL4::MeshRenderPipelineDescriptor::meshThreadgroupSizeIsMultipleOfThreadExecutionWidth() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(meshThreadgroupSizeIsMultipleOfThreadExecutionWidth));
}

/**
 * @brief Gets the function descriptor used for the pipeline's object (per-object) stage.
 *
 * @return MTL4::FunctionDescriptor* Pointer to the object-stage FunctionDescriptor, or `nullptr` if no object function descriptor has been set.
 */
_MTL_INLINE MTL4::FunctionDescriptor* MTL4::MeshRenderPipelineDescriptor::objectFunctionDescriptor() const
{
    return Object::sendMessage<MTL4::FunctionDescriptor*>(this, _MTL_PRIVATE_SEL(objectFunctionDescriptor));
}

/**
 * @brief Provides the static linking descriptor for the object stage.
 *
 * @return MTL4::StaticLinkingDescriptor* Pointer to the object-stage static linking descriptor, or `nullptr` if none is set.
 */
_MTL_INLINE MTL4::StaticLinkingDescriptor* MTL4::MeshRenderPipelineDescriptor::objectStaticLinkingDescriptor() const
{
    return Object::sendMessage<MTL4::StaticLinkingDescriptor*>(this, _MTL_PRIVATE_SEL(objectStaticLinkingDescriptor));
}

/**
 * @brief Indicates whether object threadgroup sizes must be a multiple of the GPU thread execution width.
 *
 * @return `true` if object threadgroup sizes are required to be a multiple of the thread execution width, `false` otherwise.
 */
_MTL_INLINE bool MTL4::MeshRenderPipelineDescriptor::objectThreadgroupSizeIsMultipleOfThreadExecutionWidth() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(objectThreadgroupSizeIsMultipleOfThreadExecutionWidth));
}

/**
 * @brief Get the payload memory length available to mesh and object functions, in bytes.
 *
 * @return NS::UInteger The size of the payload memory, in bytes.
 */
_MTL_INLINE NS::UInteger MTL4::MeshRenderPipelineDescriptor::payloadMemoryLength() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(payloadMemoryLength));
}

/**
 * @brief Gets the number of raster samples used for rasterization.
 *
 * @return NS::UInteger Number of samples per pixel used when rasterizing fragments.
 */
_MTL_INLINE NS::UInteger MTL4::MeshRenderPipelineDescriptor::rasterSampleCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(rasterSampleCount));
}

/**
 * @brief Indicates whether rasterization is enabled for the pipeline.
 *
 * @return `true` if rasterization is enabled, `false` otherwise.
 */
_MTL_INLINE bool MTL4::MeshRenderPipelineDescriptor::rasterizationEnabled() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isRasterizationEnabled));
}

/**
 * @brief Required threadgroup size for mesh threads.
 *
 * @return MTL::Size The required number of threads per mesh threadgroup.
 */
_MTL_INLINE MTL::Size MTL4::MeshRenderPipelineDescriptor::requiredThreadsPerMeshThreadgroup() const
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(requiredThreadsPerMeshThreadgroup));
}

/**
 * Provides the required threadgroup size for object threadgroups.
 *
 * @return MTL::Size The required number of threads per object threadgroup (width, height, depth).
 */
_MTL_INLINE MTL::Size MTL4::MeshRenderPipelineDescriptor::requiredThreadsPerObjectThreadgroup() const
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(requiredThreadsPerObjectThreadgroup));
}

/**
 * @brief Restore the descriptor to its default configuration.
 *
 * Clears any custom settings applied to this MeshRenderPipelineDescriptor so it
 * matches a freshly initialized descriptor.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

/**
 * @brief Sets the alpha-to-coverage state for this mesh render pipeline descriptor.
 *
 * @param alphaToCoverageState The AlphaToCoverageState value that controls how alpha-to-coverage is applied during rasterization.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setAlphaToCoverageState(MTL4::AlphaToCoverageState alphaToCoverageState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAlphaToCoverageState_), alphaToCoverageState);
}

/**
 * @brief Sets the alpha-to-one blending state for the mesh render pipeline.
 *
 * Configures whether fragment alpha values are forced to one during blending according
 * to the specified AlphaToOneState.
 *
 * @param alphaToOneState The alpha-to-one state to apply.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setAlphaToOneState(MTL4::AlphaToOneState alphaToOneState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAlphaToOneState_), alphaToOneState);
}

/**
 * @brief Sets how logical color attachments are mapped to physical color attachments for this pipeline descriptor.
 *
 * @param colorAttachmentMappingState The mapping state that specifies the logical-to-physical color attachment mapping behavior.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setColorAttachmentMappingState(MTL4::LogicalToPhysicalColorAttachmentMappingState colorAttachmentMappingState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setColorAttachmentMappingState_), colorAttachmentMappingState);
}

/**
 * @brief Sets the function descriptor used for the fragment (pixel) stage of the pipeline.
 *
 * @param fragmentFunctionDescriptor The FunctionDescriptor that configures the fragment stage.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setFragmentFunctionDescriptor(const MTL4::FunctionDescriptor* fragmentFunctionDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFragmentFunctionDescriptor_), fragmentFunctionDescriptor);
}

/**
 * @brief Set the static linking descriptor used for the fragment stage.
 *
 * @param fragmentStaticLinkingDescriptor Descriptor that configures static binary linking for the fragment function; may be `nullptr` to clear the descriptor.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setFragmentStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* fragmentStaticLinkingDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFragmentStaticLinkingDescriptor_), fragmentStaticLinkingDescriptor);
}

/**
 * @brief Sets the maximum total threadgroups allowed for a mesh grid.
 *
 * @param maxTotalThreadgroupsPerMeshGrid Maximum number of threadgroups that a single mesh grid may contain.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setMaxTotalThreadgroupsPerMeshGrid(NS::UInteger maxTotalThreadgroupsPerMeshGrid)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxTotalThreadgroupsPerMeshGrid_), maxTotalThreadgroupsPerMeshGrid);
}

/**
 * @brief Set the maximum number of threads allowed in a mesh threadgroup.
 *
 * @param maxTotalThreadsPerMeshThreadgroup Maximum total threads permitted for a mesh threadgroup.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setMaxTotalThreadsPerMeshThreadgroup(NS::UInteger maxTotalThreadsPerMeshThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxTotalThreadsPerMeshThreadgroup_), maxTotalThreadsPerMeshThreadgroup);
}

/**
 * @brief Sets the maximum total threads allowed per object threadgroup.
 *
 * @param maxTotalThreadsPerObjectThreadgroup Maximum number of threads permitted in a single object threadgroup.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setMaxTotalThreadsPerObjectThreadgroup(NS::UInteger maxTotalThreadsPerObjectThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxTotalThreadsPerObjectThreadgroup_), maxTotalThreadsPerObjectThreadgroup);
}

/**
 * @brief Sets the maximum vertex amplification count used by the mesh render pipeline.
 *
 * @param maxVertexAmplificationCount Maximum number of vertex amplifications applied per input vertex.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setMaxVertexAmplificationCount(NS::UInteger maxVertexAmplificationCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxVertexAmplificationCount_), maxVertexAmplificationCount);
}

/**
 * @brief Sets the mesh function descriptor used by the mesh render pipeline.
 *
 * @param meshFunctionDescriptor Descriptor describing the mesh stage function to use; pass `nullptr` to clear the mesh function.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setMeshFunctionDescriptor(const MTL4::FunctionDescriptor* meshFunctionDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMeshFunctionDescriptor_), meshFunctionDescriptor);
}

/**
 * @brief Sets the static linking descriptor used for mesh-stage binary linking.
 *
 * @param meshStaticLinkingDescriptor Descriptor that configures static linking for the mesh function; may be nullptr to clear the descriptor.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setMeshStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* meshStaticLinkingDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMeshStaticLinkingDescriptor_), meshStaticLinkingDescriptor);
}

/**
 * @brief Configure whether mesh threadgroup sizes must be multiples of the GPU thread execution width.
 *
 * When enabled, mesh threadgroup dimensions are considered required to be a multiple of the device's thread
 * execution width; when disabled, no such requirement is imposed.
 *
 * @param meshThreadgroupSizeIsMultipleOfThreadExecutionWidth `true` to require mesh threadgroup sizes be multiples of the thread execution width, `false` otherwise.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setMeshThreadgroupSizeIsMultipleOfThreadExecutionWidth(bool meshThreadgroupSizeIsMultipleOfThreadExecutionWidth)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMeshThreadgroupSizeIsMultipleOfThreadExecutionWidth_), meshThreadgroupSizeIsMultipleOfThreadExecutionWidth);
}

/**
 * @brief Sets the function descriptor used for the pipeline's object stage.
 *
 * @param objectFunctionDescriptor Descriptor to assign to the object (object-stage) function.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setObjectFunctionDescriptor(const MTL4::FunctionDescriptor* objectFunctionDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObjectFunctionDescriptor_), objectFunctionDescriptor);
}

/**
 * @brief Assigns the static linking descriptor that configures object-stage static linking.
 *
 * @param objectStaticLinkingDescriptor Descriptor used to configure static linking for the object function; nullptr clears the descriptor.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setObjectStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* objectStaticLinkingDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObjectStaticLinkingDescriptor_), objectStaticLinkingDescriptor);
}

/**
 * @brief Configures whether an object threadgroup's size must be a multiple of the device thread execution width.
 *
 * @param objectThreadgroupSizeIsMultipleOfThreadExecutionWidth `true` to require object threadgroup sizes be multiples of the thread execution width, `false` otherwise.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setObjectThreadgroupSizeIsMultipleOfThreadExecutionWidth(bool objectThreadgroupSizeIsMultipleOfThreadExecutionWidth)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObjectThreadgroupSizeIsMultipleOfThreadExecutionWidth_), objectThreadgroupSizeIsMultipleOfThreadExecutionWidth);
}

/ **
 * @brief Set the size of the per-invocation payload memory.
 *
 * Sets the payload memory length, in bytes, that will be available to mesh and object functions when the pipeline is executed.
 *
 * @param payloadMemoryLength Size of the payload memory in bytes.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setPayloadMemoryLength(NS::UInteger payloadMemoryLength)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPayloadMemoryLength_), payloadMemoryLength);
}

/**
 * @brief Sets the number of samples per pixel used for rasterization.
 *
 * @param rasterSampleCount Number of raster samples (samples per pixel) to use when rasterization is enabled.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setRasterSampleCount(NS::UInteger rasterSampleCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRasterSampleCount_), rasterSampleCount);
}

/**
 * @brief Enables or disables rasterization for the mesh render pipeline.
 *
 * @param rasterizationEnabled `true` to enable rasterization, `false` to disable it.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setRasterizationEnabled(bool rasterizationEnabled)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRasterizationEnabled_), rasterizationEnabled);
}

/**
 * @brief Sets the required number of threads per mesh threadgroup.
 *
 * @param requiredThreadsPerMeshThreadgroup Size specifying the required thread dimensions for each mesh threadgroup.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setRequiredThreadsPerMeshThreadgroup(MTL::Size requiredThreadsPerMeshThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRequiredThreadsPerMeshThreadgroup_), requiredThreadsPerMeshThreadgroup);
}

/**
 * @brief Configure the required number of threads for each object threadgroup.
 *
 * @param requiredThreadsPerObjectThreadgroup The threadgroup size required for object shaders, specified as an MTL::Size (width, height, depth).
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setRequiredThreadsPerObjectThreadgroup(MTL::Size requiredThreadsPerObjectThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRequiredThreadsPerObjectThreadgroup_), requiredThreadsPerObjectThreadgroup);
}

/**
 * @brief Sets whether the pipeline descriptor supports fragment binary linking.
 *
 * @param supportFragmentBinaryLinking If `true`, fragment binary linking is enabled; if `false`, it is disabled.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setSupportFragmentBinaryLinking(bool supportFragmentBinaryLinking)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportFragmentBinaryLinking_), supportFragmentBinaryLinking);
}

/**
 * @brief Sets the level of indirect command buffer support for the mesh render pipeline.
 *
 * @param supportIndirectCommandBuffers One of the MTL4::IndirectCommandBufferSupportState values specifying how this pipeline should support indirect command buffers.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setSupportIndirectCommandBuffers(MTL4::IndirectCommandBufferSupportState supportIndirectCommandBuffers)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportIndirectCommandBuffers_), supportIndirectCommandBuffers);
}

/**
 * @brief Sets whether the pipeline supports mesh binary linking.
 *
 * @param supportMeshBinaryLinking `true` to enable mesh binary linking support, `false` to disable it.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setSupportMeshBinaryLinking(bool supportMeshBinaryLinking)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportMeshBinaryLinking_), supportMeshBinaryLinking);
}

/**
 * @brief Enable or disable support for object binary linking on this pipeline descriptor.
 *
 * @param supportObjectBinaryLinking `true` to enable object binary linking support, `false` to disable it.
 */
_MTL_INLINE void MTL4::MeshRenderPipelineDescriptor::setSupportObjectBinaryLinking(bool supportObjectBinaryLinking)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportObjectBinaryLinking_), supportObjectBinaryLinking);
}

/**
 * @brief Indicates whether fragment binary linking is supported by this pipeline descriptor.
 *
 * @return true if fragment binary linking is supported, false otherwise.
 */
_MTL_INLINE bool MTL4::MeshRenderPipelineDescriptor::supportFragmentBinaryLinking() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportFragmentBinaryLinking));
}

/**
 * @brief Retrieves the pipeline's indirect command buffer support state.
 *
 * @return The IndirectCommandBufferSupportState describing the level of indirect command buffer support for this mesh render pipeline descriptor.
 */
_MTL_INLINE MTL4::IndirectCommandBufferSupportState MTL4::MeshRenderPipelineDescriptor::supportIndirectCommandBuffers() const
{
    return Object::sendMessage<MTL4::IndirectCommandBufferSupportState>(this, _MTL_PRIVATE_SEL(supportIndirectCommandBuffers));
}

/**
 * @brief Indicates whether mesh-stage binary linking is supported by the descriptor.
 *
 * @return `true` if mesh binary linking is supported, `false` otherwise.
 */
_MTL_INLINE bool MTL4::MeshRenderPipelineDescriptor::supportMeshBinaryLinking() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportMeshBinaryLinking));
}

/**
 * @brief Indicates whether the descriptor supports object binary linking.
 *
 * @return `true` if object binary linking is supported, `false` otherwise.
 */
_MTL_INLINE bool MTL4::MeshRenderPipelineDescriptor::supportObjectBinaryLinking() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportObjectBinaryLinking));
}