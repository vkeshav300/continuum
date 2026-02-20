//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLComputePass.hpp
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
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"

namespace MTL
{
class ComputePassDescriptor;
class ComputePassSampleBufferAttachmentDescriptor;
class ComputePassSampleBufferAttachmentDescriptorArray;
class CounterSampleBuffer;

class ComputePassSampleBufferAttachmentDescriptor : public NS::Copying<ComputePassSampleBufferAttachmentDescriptor>
{
public:
    static ComputePassSampleBufferAttachmentDescriptor* alloc();

    NS::UInteger                                        endOfEncoderSampleIndex() const;

    ComputePassSampleBufferAttachmentDescriptor*        init();

    CounterSampleBuffer*                                sampleBuffer() const;

    void                                                setEndOfEncoderSampleIndex(NS::UInteger endOfEncoderSampleIndex);

    void                                                setSampleBuffer(const MTL::CounterSampleBuffer* sampleBuffer);

    void                                                setStartOfEncoderSampleIndex(NS::UInteger startOfEncoderSampleIndex);
    NS::UInteger                                        startOfEncoderSampleIndex() const;
};
class ComputePassSampleBufferAttachmentDescriptorArray : public NS::Referencing<ComputePassSampleBufferAttachmentDescriptorArray>
{
public:
    static ComputePassSampleBufferAttachmentDescriptorArray* alloc();

    ComputePassSampleBufferAttachmentDescriptorArray*        init();

    ComputePassSampleBufferAttachmentDescriptor*             object(NS::UInteger attachmentIndex);
    void                                                     setObject(const MTL::ComputePassSampleBufferAttachmentDescriptor* attachment, NS::UInteger attachmentIndex);
};
class ComputePassDescriptor : public NS::Copying<ComputePassDescriptor>
{
public:
    static ComputePassDescriptor*                     alloc();

    static ComputePassDescriptor*                     computePassDescriptor();

    DispatchType                                      dispatchType() const;

    ComputePassDescriptor*                            init();

    ComputePassSampleBufferAttachmentDescriptorArray* sampleBufferAttachments() const;

    void                                              setDispatchType(MTL::DispatchType dispatchType);
};

}
/**
 * @brief Allocates a new ComputePassSampleBufferAttachmentDescriptor.
 *
 * @return ComputePassSampleBufferAttachmentDescriptor* Pointer to a newly allocated descriptor instance.
 */
_MTL_INLINE MTL::ComputePassSampleBufferAttachmentDescriptor* MTL::ComputePassSampleBufferAttachmentDescriptor::alloc()
{
    return NS::Object::alloc<MTL::ComputePassSampleBufferAttachmentDescriptor>(_MTL_PRIVATE_CLS(MTLComputePassSampleBufferAttachmentDescriptor));
}

/**
 * @brief Retrieves the end-of-encoder sample index for this attachment.
 *
 * @return NS::UInteger The sample index at which the encoder stops sampling for this attachment.
 */
_MTL_INLINE NS::UInteger MTL::ComputePassSampleBufferAttachmentDescriptor::endOfEncoderSampleIndex() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(endOfEncoderSampleIndex));
}

/**
 * @brief Initializes a ComputePassSampleBufferAttachmentDescriptor instance.
 *
 * @return ComputePassSampleBufferAttachmentDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::ComputePassSampleBufferAttachmentDescriptor* MTL::ComputePassSampleBufferAttachmentDescriptor::init()
{
    return NS::Object::init<MTL::ComputePassSampleBufferAttachmentDescriptor>();
}

/**
 * @brief Retrieves the counter sample buffer associated with this compute-pass attachment.
 *
 * @return MTL::CounterSampleBuffer* The associated CounterSampleBuffer, or `nullptr` if no sample buffer is set.
 */
_MTL_INLINE MTL::CounterSampleBuffer* MTL::ComputePassSampleBufferAttachmentDescriptor::sampleBuffer() const
{
    return Object::sendMessage<MTL::CounterSampleBuffer*>(this, _MTL_PRIVATE_SEL(sampleBuffer));
}

/**
 * @brief Sets the end-of-encoder sample index for this attachment.
 *
 * @param endOfEncoderSampleIndex The sample index to record at the end of the encoder.
 */
_MTL_INLINE void MTL::ComputePassSampleBufferAttachmentDescriptor::setEndOfEncoderSampleIndex(NS::UInteger endOfEncoderSampleIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setEndOfEncoderSampleIndex_), endOfEncoderSampleIndex);
}

/**
 * @brief Associates a CounterSampleBuffer with this compute-pass sample-buffer attachment.
 *
 * @param sampleBuffer The `MTL::CounterSampleBuffer` to attach to this descriptor, or `nullptr` to clear the association.
 */
_MTL_INLINE void MTL::ComputePassSampleBufferAttachmentDescriptor::setSampleBuffer(const MTL::CounterSampleBuffer* sampleBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSampleBuffer_), sampleBuffer);
}

/**
 * @brief Set the start sample index used for this attachment when the encoder begins.
 *
 * @param startOfEncoderSampleIndex The sample index (zero-based) at which the encoder's samples start for this attachment.
 */
_MTL_INLINE void MTL::ComputePassSampleBufferAttachmentDescriptor::setStartOfEncoderSampleIndex(NS::UInteger startOfEncoderSampleIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStartOfEncoderSampleIndex_), startOfEncoderSampleIndex);
}

/**
 * @brief Retrieves the start-of-encoder sample index for this sample buffer attachment.
 *
 * @return NS::UInteger The start-of-encoder sample index for the attachment.
 */
_MTL_INLINE NS::UInteger MTL::ComputePassSampleBufferAttachmentDescriptor::startOfEncoderSampleIndex() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(startOfEncoderSampleIndex));
}

/**
 * @brief Allocates a new ComputePassSampleBufferAttachmentDescriptorArray instance.
 *
 * The returned object is allocated but not initialized; call `init()` before using.
 *
 * @return ComputePassSampleBufferAttachmentDescriptorArray* Pointer to the newly allocated descriptor array.
 */
_MTL_INLINE MTL::ComputePassSampleBufferAttachmentDescriptorArray* MTL::ComputePassSampleBufferAttachmentDescriptorArray::alloc()
{
    return NS::Object::alloc<MTL::ComputePassSampleBufferAttachmentDescriptorArray>(_MTL_PRIVATE_CLS(MTLComputePassSampleBufferAttachmentDescriptorArray));
}

/**
 * @brief Initializes a newly allocated ComputePassSampleBufferAttachmentDescriptorArray.
 *
 * @return ComputePassSampleBufferAttachmentDescriptorArray* An initialized instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::ComputePassSampleBufferAttachmentDescriptorArray* MTL::ComputePassSampleBufferAttachmentDescriptorArray::init()
{
    return NS::Object::init<MTL::ComputePassSampleBufferAttachmentDescriptorArray>();
}

/**
 * @brief Retrieve the compute pass sample buffer attachment descriptor at an index.
 *
 * @param attachmentIndex Index of the attachment to retrieve.
 * @return MTL::ComputePassSampleBufferAttachmentDescriptor* Pointer to the descriptor at the specified index, or `nullptr` if no descriptor is set.
 */
_MTL_INLINE MTL::ComputePassSampleBufferAttachmentDescriptor* MTL::ComputePassSampleBufferAttachmentDescriptorArray::object(NS::UInteger attachmentIndex)
{
    return Object::sendMessage<MTL::ComputePassSampleBufferAttachmentDescriptor*>(this, _MTL_PRIVATE_SEL(objectAtIndexedSubscript_), attachmentIndex);
}

/**
 * @brief Set the compute pass sample buffer attachment descriptor at a given index.
 *
 * Places the provided attachment descriptor into this attachment descriptor array at the specified index.
 *
 * @param attachment The attachment descriptor to set.
 * @param attachmentIndex The index in the array where the attachment will be stored.
 */
_MTL_INLINE void MTL::ComputePassSampleBufferAttachmentDescriptorArray::setObject(const MTL::ComputePassSampleBufferAttachmentDescriptor* attachment, NS::UInteger attachmentIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObject_atIndexedSubscript_), attachment, attachmentIndex);
}

/**
 * @brief Allocates a new ComputePassDescriptor instance.
 *
 * @return ComputePassDescriptor* Pointer to the allocated, uninitialized ComputePassDescriptor.
 */
_MTL_INLINE MTL::ComputePassDescriptor* MTL::ComputePassDescriptor::alloc()
{
    return NS::Object::alloc<MTL::ComputePassDescriptor>(_MTL_PRIVATE_CLS(MTLComputePassDescriptor));
}

/**
 * @brief Creates a default compute pass descriptor.
 *
 * @return MTL::ComputePassDescriptor* A newly created ComputePassDescriptor instance configured with default settings.
 */
_MTL_INLINE MTL::ComputePassDescriptor* MTL::ComputePassDescriptor::computePassDescriptor()
{
    return Object::sendMessage<MTL::ComputePassDescriptor*>(_MTL_PRIVATE_CLS(MTLComputePassDescriptor), _MTL_PRIVATE_SEL(computePassDescriptor));
}

/**
 * @brief Gets the compute pass dispatch configuration.
 *
 * @return MTL::DispatchType The dispatch type that determines how work is scheduled for this compute pass.
 */
_MTL_INLINE MTL::DispatchType MTL::ComputePassDescriptor::dispatchType() const
{
    return Object::sendMessage<MTL::DispatchType>(this, _MTL_PRIVATE_SEL(dispatchType));
}

/**
 * @brief Initialize the compute pass descriptor.
 *
 * Performs object initialization and returns the initialized descriptor instance.
 *
 * @return Pointer to the initialized ComputePassDescriptor, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::ComputePassDescriptor* MTL::ComputePassDescriptor::init()
{
    return NS::Object::init<MTL::ComputePassDescriptor>();
}

/**
 * @brief Returns the array of sample buffer attachment descriptors for this compute pass.
 *
 * The returned object describes the per-index sample buffer attachments used by the compute pass.
 *
 * @return ComputePassSampleBufferAttachmentDescriptorArray* Array of sample buffer attachment descriptors associated with this compute pass.
 */
_MTL_INLINE MTL::ComputePassSampleBufferAttachmentDescriptorArray* MTL::ComputePassDescriptor::sampleBufferAttachments() const
{
    return Object::sendMessage<MTL::ComputePassSampleBufferAttachmentDescriptorArray*>(this, _MTL_PRIVATE_SEL(sampleBufferAttachments));
}

/**
 * @brief Sets the compute pass dispatch configuration.
 *
 * @param dispatchType The dispatch type that configures how the compute pass is dispatched (e.g., serial, concurrent, or indirect).
 */
_MTL_INLINE void MTL::ComputePassDescriptor::setDispatchType(MTL::DispatchType dispatchType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDispatchType_), dispatchType);
}