//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4Archive.hpp
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

namespace MTL
{
class ComputePipelineState;
class RenderPipelineState;
}

namespace MTL4
{
class BinaryFunction;
class BinaryFunctionDescriptor;
class ComputePipelineDescriptor;
class PipelineDescriptor;
class PipelineStageDynamicLinkingDescriptor;
class RenderPipelineDynamicLinkingDescriptor;

class Archive : public NS::Referencing<Archive>
{
public:
    NS::String*                label() const;

    BinaryFunction*            newBinaryFunction(const MTL4::BinaryFunctionDescriptor* descriptor, NS::Error** error);

    MTL::ComputePipelineState* newComputePipelineState(const MTL4::ComputePipelineDescriptor* descriptor, NS::Error** error);
    MTL::ComputePipelineState* newComputePipelineState(const MTL4::ComputePipelineDescriptor* descriptor, const MTL4::PipelineStageDynamicLinkingDescriptor* dynamicLinkingDescriptor, NS::Error** error);

    MTL::RenderPipelineState*  newRenderPipelineState(const MTL4::PipelineDescriptor* descriptor, NS::Error** error);
    MTL::RenderPipelineState*  newRenderPipelineState(const MTL4::PipelineDescriptor* descriptor, const MTL4::RenderPipelineDynamicLinkingDescriptor* dynamicLinkingDescriptor, NS::Error** error);

    void                       setLabel(const NS::String* label);
};

}
/**
 * @brief Retrieve the archive's label.
 *
 * @return NS::String* The archive's label string, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL4::Archive::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Creates a BinaryFunction configured by the provided descriptor.
 *
 * @param descriptor Descriptor that specifies the binary function's properties.
 * @param error If non-null and creation fails, set to an NS::Error describing the failure; pass nullptr to ignore errors.
 * @return MTL4::BinaryFunction* Pointer to the created BinaryFunction, or nullptr if creation failed.
 */
_MTL_INLINE MTL4::BinaryFunction* MTL4::Archive::newBinaryFunction(const MTL4::BinaryFunctionDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<MTL4::BinaryFunction*>(this, _MTL_PRIVATE_SEL(newBinaryFunctionWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Creates a compute pipeline state from the provided descriptor.
 *
 * @param descriptor Descriptor that specifies the compute pipeline configuration to create.
 * @param error If non-null and creation fails, an error object is written to this pointer describing the failure.
 * @return MTL::ComputePipelineState* Pointer to the created compute pipeline state, or `nullptr` if creation failed.
 */
_MTL_INLINE MTL::ComputePipelineState* MTL4::Archive::newComputePipelineState(const MTL4::ComputePipelineDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<MTL::ComputePipelineState*>(this, _MTL_PRIVATE_SEL(newComputePipelineStateWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Create a compute pipeline state using a pipeline descriptor and dynamic linking options.
 *
 * @param descriptor Descriptor that specifies the compute pipeline to create.
 * @param dynamicLinkingDescriptor Descriptor that configures per-stage dynamic linking; may be `nullptr` if not used.
 * @param error If non-null, receives an `NS::Error*` describing failure details when creation fails.
 * @return MTL::ComputePipelineState* Created compute pipeline state object on success, `nullptr` on failure.
 */
_MTL_INLINE MTL::ComputePipelineState* MTL4::Archive::newComputePipelineState(const MTL4::ComputePipelineDescriptor* descriptor, const MTL4::PipelineStageDynamicLinkingDescriptor* dynamicLinkingDescriptor, NS::Error** error)
{
    return Object::sendMessage<MTL::ComputePipelineState*>(this, _MTL_PRIVATE_SEL(newComputePipelineStateWithDescriptor_dynamicLinkingDescriptor_error_), descriptor, dynamicLinkingDescriptor, error);
}

/**
 * @brief Creates a render pipeline state from the provided pipeline descriptor.
 *
 * @param descriptor Descriptor that describes the render pipeline to create.
 * @param error Pointer to an NS::Error* that will be set on failure; may be nullptr.
 * @return MTL::RenderPipelineState* The newly created render pipeline state, or `nullptr` if creation failed.
 */
_MTL_INLINE MTL::RenderPipelineState* MTL4::Archive::newRenderPipelineState(const MTL4::PipelineDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<MTL::RenderPipelineState*>(this, _MTL_PRIVATE_SEL(newRenderPipelineStateWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Creates a render pipeline state from a pipeline descriptor and optional dynamic linking descriptor.
 *
 * Constructs a new MTL::RenderPipelineState configured by the given pipeline descriptor and
 * the render-pipeline-specific dynamic linking descriptor. If pipeline creation fails, no
 * pipeline is returned and an NSError may be provided.
 *
 * @param descriptor Pipeline descriptor that defines the render pipeline configuration.
 * @param dynamicLinkingDescriptor Descriptor that configures dynamic linking for pipeline stages; may be nullptr.
 * @param error Pointer to an NS::Error* that will be set on failure; may be nullptr.
 * @return MTL::RenderPipelineState* The created render pipeline state, or `nullptr` if creation failed.
 */
_MTL_INLINE MTL::RenderPipelineState* MTL4::Archive::newRenderPipelineState(const MTL4::PipelineDescriptor* descriptor, const MTL4::RenderPipelineDynamicLinkingDescriptor* dynamicLinkingDescriptor, NS::Error** error)
{
    return Object::sendMessage<MTL::RenderPipelineState*>(this, _MTL_PRIVATE_SEL(newRenderPipelineStateWithDescriptor_dynamicLinkingDescriptor_error_), descriptor, dynamicLinkingDescriptor, error);
}

/**
 * @brief Assigns a human-readable label to the archive.
 *
 * @param label The label string to set on the archive.
 */
_MTL_INLINE void MTL4::Archive::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}