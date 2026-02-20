//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLBlitPass.hpp
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
class BlitPassDescriptor;
class BlitPassSampleBufferAttachmentDescriptor;
class BlitPassSampleBufferAttachmentDescriptorArray;
class CounterSampleBuffer;

class BlitPassSampleBufferAttachmentDescriptor : public NS::Copying<BlitPassSampleBufferAttachmentDescriptor>
{
public:
    static BlitPassSampleBufferAttachmentDescriptor* alloc();

    NS::UInteger                                     endOfEncoderSampleIndex() const;

    BlitPassSampleBufferAttachmentDescriptor*        init();

    CounterSampleBuffer*                             sampleBuffer() const;

    void                                             setEndOfEncoderSampleIndex(NS::UInteger endOfEncoderSampleIndex);

    void                                             setSampleBuffer(const MTL::CounterSampleBuffer* sampleBuffer);

    void                                             setStartOfEncoderSampleIndex(NS::UInteger startOfEncoderSampleIndex);
    NS::UInteger                                     startOfEncoderSampleIndex() const;
};
class BlitPassSampleBufferAttachmentDescriptorArray : public NS::Referencing<BlitPassSampleBufferAttachmentDescriptorArray>
{
public:
    static BlitPassSampleBufferAttachmentDescriptorArray* alloc();

    BlitPassSampleBufferAttachmentDescriptorArray*        init();

    BlitPassSampleBufferAttachmentDescriptor*             object(NS::UInteger attachmentIndex);
    void                                                  setObject(const MTL::BlitPassSampleBufferAttachmentDescriptor* attachment, NS::UInteger attachmentIndex);
};
class BlitPassDescriptor : public NS::Copying<BlitPassDescriptor>
{
public:
    static BlitPassDescriptor*                     alloc();

    static BlitPassDescriptor*                     blitPassDescriptor();

    BlitPassDescriptor*                            init();

    BlitPassSampleBufferAttachmentDescriptorArray* sampleBufferAttachments() const;
};

}
/**
 * @brief Allocate a new BlitPassSampleBufferAttachmentDescriptor instance.
 *
 * @return MTL::BlitPassSampleBufferAttachmentDescriptor* A newly allocated descriptor instance.
 */
_MTL_INLINE MTL::BlitPassSampleBufferAttachmentDescriptor* MTL::BlitPassSampleBufferAttachmentDescriptor::alloc()
{
    return NS::Object::alloc<MTL::BlitPassSampleBufferAttachmentDescriptor>(_MTL_PRIVATE_CLS(MTLBlitPassSampleBufferAttachmentDescriptor));
}

/**
 * @brief Retrieve the sample index that marks the end of the encoder's sample range.
 *
 * @return NS::UInteger The end-of-encoder sample index.
 */
_MTL_INLINE NS::UInteger MTL::BlitPassSampleBufferAttachmentDescriptor::endOfEncoderSampleIndex() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(endOfEncoderSampleIndex));
}

/**
 * @brief Initializes the descriptor instance.
 *
 * Performs object initialization and returns the initialized descriptor.
 *
 * @return MTL::BlitPassSampleBufferAttachmentDescriptor* Pointer to the initialized descriptor instance.
 */
_MTL_INLINE MTL::BlitPassSampleBufferAttachmentDescriptor* MTL::BlitPassSampleBufferAttachmentDescriptor::init()
{
    return NS::Object::init<MTL::BlitPassSampleBufferAttachmentDescriptor>();
}

/**
 * @brief Retrieves the CounterSampleBuffer currently associated with this attachment descriptor.
 *
 * @return MTL::CounterSampleBuffer* The associated CounterSampleBuffer pointer, or `nullptr` if none is set.
 */
_MTL_INLINE MTL::CounterSampleBuffer* MTL::BlitPassSampleBufferAttachmentDescriptor::sampleBuffer() const
{
    return Object::sendMessage<MTL::CounterSampleBuffer*>(this, _MTL_PRIVATE_SEL(sampleBuffer));
}

/**
 * @brief Set the sample index that will be recorded at the end of the encoder for this attachment.
 *
 * @param endOfEncoderSampleIndex Index of the sample to record when the encoder ends.
 */
_MTL_INLINE void MTL::BlitPassSampleBufferAttachmentDescriptor::setEndOfEncoderSampleIndex(NS::UInteger endOfEncoderSampleIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setEndOfEncoderSampleIndex_), endOfEncoderSampleIndex);
}

/**
 * @brief Sets the CounterSampleBuffer for this attachment descriptor.
 *
 * @param sampleBuffer Pointer to the CounterSampleBuffer to associate with the attachment.
 */
_MTL_INLINE void MTL::BlitPassSampleBufferAttachmentDescriptor::setSampleBuffer(const MTL::CounterSampleBuffer* sampleBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSampleBuffer_), sampleBuffer);
}

/**
 * @brief Sets the start sample index to record for this attachment when the encoder begins.
 *
 * @param startOfEncoderSampleIndex Index within the associated CounterSampleBuffer at which sampling should start when the blit encoder begins.
 */
_MTL_INLINE void MTL::BlitPassSampleBufferAttachmentDescriptor::setStartOfEncoderSampleIndex(NS::UInteger startOfEncoderSampleIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStartOfEncoderSampleIndex_), startOfEncoderSampleIndex);
}

/**
 * @brief Retrieves the sample index where the encoder begins sampling.
 *
 * @return NS::UInteger The start-of-encoder sample index. */
_MTL_INLINE NS::UInteger MTL::BlitPassSampleBufferAttachmentDescriptor::startOfEncoderSampleIndex() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(startOfEncoderSampleIndex));
}

/**
 * @brief Allocate a new BlitPassSampleBufferAttachmentDescriptorArray.
 *
 * @return MTL::BlitPassSampleBufferAttachmentDescriptorArray* Pointer to a newly allocated descriptor array instance.
 */
_MTL_INLINE MTL::BlitPassSampleBufferAttachmentDescriptorArray* MTL::BlitPassSampleBufferAttachmentDescriptorArray::alloc()
{
    return NS::Object::alloc<MTL::BlitPassSampleBufferAttachmentDescriptorArray>(_MTL_PRIVATE_CLS(MTLBlitPassSampleBufferAttachmentDescriptorArray));
}

/**
 * @brief Initializes a BlitPassSampleBufferAttachmentDescriptorArray instance.
 *
 * @return MTL::BlitPassSampleBufferAttachmentDescriptorArray* Pointer to the initialized descriptor array.
 */
_MTL_INLINE MTL::BlitPassSampleBufferAttachmentDescriptorArray* MTL::BlitPassSampleBufferAttachmentDescriptorArray::init()
{
    return NS::Object::init<MTL::BlitPassSampleBufferAttachmentDescriptorArray>();
}

/**
 * @brief Retrieve the attachment descriptor at the specified index.
 *
 * @param attachmentIndex Zero-based index of the attachment within the array.
 * @return MTL::BlitPassSampleBufferAttachmentDescriptor* The attachment descriptor at the given index.
 */
_MTL_INLINE MTL::BlitPassSampleBufferAttachmentDescriptor* MTL::BlitPassSampleBufferAttachmentDescriptorArray::object(NS::UInteger attachmentIndex)
{
    return Object::sendMessage<MTL::BlitPassSampleBufferAttachmentDescriptor*>(this, _MTL_PRIVATE_SEL(objectAtIndexedSubscript_), attachmentIndex);
}

/**
 * @brief Sets the attachment descriptor at a specific index in the array.
 *
 * Replaces the entry at the given index with the provided BlitPassSampleBufferAttachmentDescriptor.
 *
 * @param attachment Descriptor to store at the index.
 * @param attachmentIndex Index at which to set the descriptor.
 */
_MTL_INLINE void MTL::BlitPassSampleBufferAttachmentDescriptorArray::setObject(const MTL::BlitPassSampleBufferAttachmentDescriptor* attachment, NS::UInteger attachmentIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObject_atIndexedSubscript_), attachment, attachmentIndex);
}

/**
 * @brief Allocates and returns a new BlitPassDescriptor instance.
 *
 * @return MTL::BlitPassDescriptor* Pointer to the newly allocated descriptor.
 */
_MTL_INLINE MTL::BlitPassDescriptor* MTL::BlitPassDescriptor::alloc()
{
    return NS::Object::alloc<MTL::BlitPassDescriptor>(_MTL_PRIVATE_CLS(MTLBlitPassDescriptor));
}

/**
 * @brief Creates a blit pass descriptor.
 *
 * @return MTL::BlitPassDescriptor* A descriptor suitable for configuring and creating a blit pass.
 */
_MTL_INLINE MTL::BlitPassDescriptor* MTL::BlitPassDescriptor::blitPassDescriptor()
{
    return Object::sendMessage<MTL::BlitPassDescriptor*>(_MTL_PRIVATE_CLS(MTLBlitPassDescriptor), _MTL_PRIVATE_SEL(blitPassDescriptor));
}

/**
 * @brief Initialize the BlitPassDescriptor instance.
 *
 * @return BlitPassDescriptor* The initialized descriptor instance, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::BlitPassDescriptor* MTL::BlitPassDescriptor::init()
{
    return NS::Object::init<MTL::BlitPassDescriptor>();
}

/**
 * @brief Accesses the sample buffer attachment descriptor array for this blit pass descriptor.
 *
 * @return MTL::BlitPassSampleBufferAttachmentDescriptorArray* The array of sample buffer attachment descriptors associated with this descriptor.
 */
_MTL_INLINE MTL::BlitPassSampleBufferAttachmentDescriptorArray* MTL::BlitPassDescriptor::sampleBufferAttachments() const
{
    return Object::sendMessage<MTL::BlitPassSampleBufferAttachmentDescriptorArray*>(this, _MTL_PRIVATE_SEL(sampleBufferAttachments));
}