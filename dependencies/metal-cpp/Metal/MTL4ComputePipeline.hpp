//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4ComputePipeline.hpp
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
class ComputePipelineDescriptor;
class FunctionDescriptor;
class StaticLinkingDescriptor;

class ComputePipelineDescriptor : public NS::Copying<ComputePipelineDescriptor, PipelineDescriptor>
{
public:
    static ComputePipelineDescriptor* alloc();

    FunctionDescriptor*               computeFunctionDescriptor() const;

    ComputePipelineDescriptor*        init();

    NS::UInteger                      maxTotalThreadsPerThreadgroup() const;

    MTL::Size                         requiredThreadsPerThreadgroup() const;

    void                              reset();

    void                              setComputeFunctionDescriptor(const MTL4::FunctionDescriptor* computeFunctionDescriptor);

    void                              setMaxTotalThreadsPerThreadgroup(NS::UInteger maxTotalThreadsPerThreadgroup);

    void                              setRequiredThreadsPerThreadgroup(MTL::Size requiredThreadsPerThreadgroup);

    void                              setStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* staticLinkingDescriptor);

    void                              setSupportBinaryLinking(bool supportBinaryLinking);

    void                              setSupportIndirectCommandBuffers(MTL4::IndirectCommandBufferSupportState supportIndirectCommandBuffers);

    void                              setThreadGroupSizeIsMultipleOfThreadExecutionWidth(bool threadGroupSizeIsMultipleOfThreadExecutionWidth);

    StaticLinkingDescriptor*          staticLinkingDescriptor() const;

    bool                              supportBinaryLinking() const;

    IndirectCommandBufferSupportState supportIndirectCommandBuffers() const;

    bool                              threadGroupSizeIsMultipleOfThreadExecutionWidth() const;
};

}
/**
 * @brief Allocate a new ComputePipelineDescriptor instance.
 *
 * @return MTL4::ComputePipelineDescriptor* A newly allocated, uninitialized ComputePipelineDescriptor object.
 */
_MTL_INLINE MTL4::ComputePipelineDescriptor* MTL4::ComputePipelineDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::ComputePipelineDescriptor>(_MTL_PRIVATE_CLS(MTL4ComputePipelineDescriptor));
}

/**
 * @brief Retrieves the function descriptor used by this compute pipeline descriptor.
 *
 * @return MTL4::FunctionDescriptor* The associated FunctionDescriptor pointer, or `nullptr` if no compute function descriptor is set.
 */
_MTL_INLINE MTL4::FunctionDescriptor* MTL4::ComputePipelineDescriptor::computeFunctionDescriptor() const
{
    return Object::sendMessage<MTL4::FunctionDescriptor*>(this, _MTL_PRIVATE_SEL(computeFunctionDescriptor));
}

/**
 * @brief Initializes the compute pipeline descriptor.
 *
 * Performs object initialization and returns the initialized instance.
 *
 * @return ComputePipelineDescriptor* Pointer to the initialized descriptor, or `nullptr` on failure.
 */
_MTL_INLINE MTL4::ComputePipelineDescriptor* MTL4::ComputePipelineDescriptor::init()
{
    return NS::Object::init<MTL4::ComputePipelineDescriptor>();
}

/**
 * @brief Retrieves the maximum total number of threads allowed in a threadgroup.
 *
 * @return NS::UInteger The maximum total threads per threadgroup.
 */
_MTL_INLINE NS::UInteger MTL4::ComputePipelineDescriptor::maxTotalThreadsPerThreadgroup() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxTotalThreadsPerThreadgroup));
}

/**
 * @brief Retrieve the required threadgroup size for the compute pipeline.
 *
 * @return MTL::Size The required number of threads per threadgroup.
 */
_MTL_INLINE MTL::Size MTL4::ComputePipelineDescriptor::requiredThreadsPerThreadgroup() const
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(requiredThreadsPerThreadgroup));
}

/**
 * @brief Resets the compute pipeline descriptor to its default state.
 *
 * Restores all configurable properties on this descriptor back to their initial defaults.
 */
_MTL_INLINE void MTL4::ComputePipelineDescriptor::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

/**
 * @brief Sets the function descriptor used to configure the compute pipeline.
 *
 * @param computeFunctionDescriptor Pointer to the FunctionDescriptor that specifies the compute function for the pipeline.
 */
_MTL_INLINE void MTL4::ComputePipelineDescriptor::setComputeFunctionDescriptor(const MTL4::FunctionDescriptor* computeFunctionDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setComputeFunctionDescriptor_), computeFunctionDescriptor);
}

/**
 * @brief Sets the maximum total number of threads allowed per threadgroup.
 *
 * @param maxTotalThreadsPerThreadgroup Maximum total threads allowed in a single threadgroup.
 */
_MTL_INLINE void MTL4::ComputePipelineDescriptor::setMaxTotalThreadsPerThreadgroup(NS::UInteger maxTotalThreadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxTotalThreadsPerThreadgroup_), maxTotalThreadsPerThreadgroup);
}

/**
 * @brief Sets the required threadgroup size for the compute pipeline.
 *
 * Configures the exact number of threads (per dimension) that must be used for each threadgroup when this pipeline is executed.
 *
 * @param requiredThreadsPerThreadgroup The required threadgroup size as an MTL::Size (width, height, depth).
 */
_MTL_INLINE void MTL4::ComputePipelineDescriptor::setRequiredThreadsPerThreadgroup(MTL::Size requiredThreadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRequiredThreadsPerThreadgroup_), requiredThreadsPerThreadgroup);
}

/**
 * @brief Sets the static linking descriptor used by the compute pipeline.
 *
 * @param staticLinkingDescriptor Descriptor that configures static linking behavior for the pipeline; pass `nullptr` to clear the descriptor.
 */
_MTL_INLINE void MTL4::ComputePipelineDescriptor::setStaticLinkingDescriptor(const MTL4::StaticLinkingDescriptor* staticLinkingDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStaticLinkingDescriptor_), staticLinkingDescriptor);
}

/**
 * @brief Set whether the compute pipeline supports binary linking.
 *
 * @param supportBinaryLinking `true` to enable binary linking support for the pipeline, `false` to disable it.
 */
_MTL_INLINE void MTL4::ComputePipelineDescriptor::setSupportBinaryLinking(bool supportBinaryLinking)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportBinaryLinking_), supportBinaryLinking);
}

/**
 * @brief Configure the indirect command buffer support state for this compute pipeline descriptor.
 *
 * @param supportIndirectCommandBuffers The desired IndirectCommandBufferSupportState to apply to the descriptor.
 */
_MTL_INLINE void MTL4::ComputePipelineDescriptor::setSupportIndirectCommandBuffers(MTL4::IndirectCommandBufferSupportState supportIndirectCommandBuffers)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportIndirectCommandBuffers_), supportIndirectCommandBuffers);
}

/**
 * @brief Sets whether the threadgroup size is required to be a multiple of the device's thread execution width.
 *
 * @param threadGroupSizeIsMultipleOfThreadExecutionWidth `true` to require the threadgroup size to be a multiple of the thread execution width; `false` to allow other sizes.
 */
_MTL_INLINE void MTL4::ComputePipelineDescriptor::setThreadGroupSizeIsMultipleOfThreadExecutionWidth(bool threadGroupSizeIsMultipleOfThreadExecutionWidth)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setThreadGroupSizeIsMultipleOfThreadExecutionWidth_), threadGroupSizeIsMultipleOfThreadExecutionWidth);
}

/**
 * @brief Retrieves the static linking descriptor associated with this compute pipeline descriptor.
 *
 * @return MTL4::StaticLinkingDescriptor* The associated StaticLinkingDescriptor, or `nullptr` if no descriptor is set.
 */
_MTL_INLINE MTL4::StaticLinkingDescriptor* MTL4::ComputePipelineDescriptor::staticLinkingDescriptor() const
{
    return Object::sendMessage<MTL4::StaticLinkingDescriptor*>(this, _MTL_PRIVATE_SEL(staticLinkingDescriptor));
}

/**
 * @brief Indicates whether the compute pipeline supports binary linking.
 *
 * @return `true` if binary linking is supported, `false` otherwise.
 */
_MTL_INLINE bool MTL4::ComputePipelineDescriptor::supportBinaryLinking() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportBinaryLinking));
}

/**
 * @brief Query the indirect command buffer support state for this compute pipeline descriptor.
 *
 * @return MTL4::IndirectCommandBufferSupportState The indirect command buffer support state for the descriptor.
 */
_MTL_INLINE MTL4::IndirectCommandBufferSupportState MTL4::ComputePipelineDescriptor::supportIndirectCommandBuffers() const
{
    return Object::sendMessage<MTL4::IndirectCommandBufferSupportState>(this, _MTL_PRIVATE_SEL(supportIndirectCommandBuffers));
}

/**
 * @brief Indicates whether the threadgroup size must be a multiple of the thread execution width.
 *
 * @return `true` if the threadgroup size is required to be a multiple of the thread execution width, `false` otherwise.
 */
_MTL_INLINE bool MTL4::ComputePipelineDescriptor::threadGroupSizeIsMultipleOfThreadExecutionWidth() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(threadGroupSizeIsMultipleOfThreadExecutionWidth));
}