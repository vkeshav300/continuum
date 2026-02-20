//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLAccelerationStructureCommandEncoder.hpp
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
#include "MTLAccelerationStructure.hpp"
#include "MTLCommandEncoder.hpp"
#include "MTLDataType.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"

namespace MTL
{
class AccelerationStructure;
class AccelerationStructureDescriptor;
class AccelerationStructurePassDescriptor;
class AccelerationStructurePassSampleBufferAttachmentDescriptor;
class AccelerationStructurePassSampleBufferAttachmentDescriptorArray;
class Buffer;
class CounterSampleBuffer;
class Fence;
class Heap;
class Resource;

class AccelerationStructureCommandEncoder : public NS::Referencing<AccelerationStructureCommandEncoder, CommandEncoder>
{
public:
    void buildAccelerationStructure(const MTL::AccelerationStructure* accelerationStructure, const MTL::AccelerationStructureDescriptor* descriptor, const MTL::Buffer* scratchBuffer, NS::UInteger scratchBufferOffset);

    void copyAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL::AccelerationStructure* destinationAccelerationStructure);

    void copyAndCompactAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL::AccelerationStructure* destinationAccelerationStructure);

    void refitAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL::AccelerationStructureDescriptor* descriptor, const MTL::AccelerationStructure* destinationAccelerationStructure, const MTL::Buffer* scratchBuffer, NS::UInteger scratchBufferOffset);
    void refitAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL::AccelerationStructureDescriptor* descriptor, const MTL::AccelerationStructure* destinationAccelerationStructure, const MTL::Buffer* scratchBuffer, NS::UInteger scratchBufferOffset, MTL::AccelerationStructureRefitOptions options);

    void sampleCountersInBuffer(const MTL::CounterSampleBuffer* sampleBuffer, NS::UInteger sampleIndex, bool barrier);

    void updateFence(const MTL::Fence* fence);

    void useHeap(const MTL::Heap* heap);
    void useHeaps(const MTL::Heap* const heaps[], NS::UInteger count);

    void useResource(const MTL::Resource* resource, MTL::ResourceUsage usage);
    void useResources(const MTL::Resource* const resources[], NS::UInteger count, MTL::ResourceUsage usage);

    void waitForFence(const MTL::Fence* fence);

    void writeCompactedAccelerationStructureSize(const MTL::AccelerationStructure* accelerationStructure, const MTL::Buffer* buffer, NS::UInteger offset);
    void writeCompactedAccelerationStructureSize(const MTL::AccelerationStructure* accelerationStructure, const MTL::Buffer* buffer, NS::UInteger offset, MTL::DataType sizeDataType);
};
class AccelerationStructurePassSampleBufferAttachmentDescriptor : public NS::Copying<AccelerationStructurePassSampleBufferAttachmentDescriptor>
{
public:
    static AccelerationStructurePassSampleBufferAttachmentDescriptor* alloc();

    NS::UInteger                                                      endOfEncoderSampleIndex() const;

    AccelerationStructurePassSampleBufferAttachmentDescriptor*        init();

    CounterSampleBuffer*                                              sampleBuffer() const;

    void                                                              setEndOfEncoderSampleIndex(NS::UInteger endOfEncoderSampleIndex);

    void                                                              setSampleBuffer(const MTL::CounterSampleBuffer* sampleBuffer);

    void                                                              setStartOfEncoderSampleIndex(NS::UInteger startOfEncoderSampleIndex);
    NS::UInteger                                                      startOfEncoderSampleIndex() const;
};
class AccelerationStructurePassSampleBufferAttachmentDescriptorArray : public NS::Referencing<AccelerationStructurePassSampleBufferAttachmentDescriptorArray>
{
public:
    static AccelerationStructurePassSampleBufferAttachmentDescriptorArray* alloc();

    AccelerationStructurePassSampleBufferAttachmentDescriptorArray*        init();

    AccelerationStructurePassSampleBufferAttachmentDescriptor*             object(NS::UInteger attachmentIndex);
    void                                                                   setObject(const MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor* attachment, NS::UInteger attachmentIndex);
};
class AccelerationStructurePassDescriptor : public NS::Copying<AccelerationStructurePassDescriptor>
{
public:
    static AccelerationStructurePassDescriptor*                     accelerationStructurePassDescriptor();

    static AccelerationStructurePassDescriptor*                     alloc();

    AccelerationStructurePassDescriptor*                            init();

    AccelerationStructurePassSampleBufferAttachmentDescriptorArray* sampleBufferAttachments() const;
};

}
/**
 * @brief Encodes a command to build an acceleration structure using the provided descriptor and scratch storage.
 *
 * Encodes a build operation that constructs or updates the contents of the given acceleration structure
 * according to the provided descriptor, using the specified scratch buffer region for temporary workspace.
 *
 * @param accelerationStructure The acceleration structure to build or update.
 * @param descriptor The descriptor that describes the acceleration structure geometry and build parameters.
 * @param scratchBuffer A buffer used for temporary scratch/storage during the build.
 * @param scratchBufferOffset Byte offset into `scratchBuffer` where scratch storage begins.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::buildAccelerationStructure(const MTL::AccelerationStructure* accelerationStructure, const MTL::AccelerationStructureDescriptor* descriptor, const MTL::Buffer* scratchBuffer, NS::UInteger scratchBufferOffset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(buildAccelerationStructure_descriptor_scratchBuffer_scratchBufferOffset_), accelerationStructure, descriptor, scratchBuffer, scratchBufferOffset);
}

/**
 * @brief Encodes a command to copy an acceleration structure into another.
 *
 * Encodes a GPU command that copies the contents of the source acceleration structure
 * into the destination acceleration structure.
 *
 * @param sourceAccelerationStructure Source acceleration structure to copy from.
 * @param destinationAccelerationStructure Destination acceleration structure to copy into.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::copyAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL::AccelerationStructure* destinationAccelerationStructure)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyAccelerationStructure_toAccelerationStructure_), sourceAccelerationStructure, destinationAccelerationStructure);
}

/**
 * @brief Encodes a command to copy and compact an acceleration structure into another.
 *
 * This records an operation that copies the GPU representation of the source acceleration
 * structure into the destination and compacts it to reduce memory usage.
 *
 * @param sourceAccelerationStructure The acceleration structure to copy from.
 * @param destinationAccelerationStructure The acceleration structure to copy the compacted result into.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::copyAndCompactAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL::AccelerationStructure* destinationAccelerationStructure)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyAndCompactAccelerationStructure_toAccelerationStructure_), sourceAccelerationStructure, destinationAccelerationStructure);
}

/**
 * @brief Encodes a command to refit an existing acceleration structure into a destination structure.
 *
 * Encodes a refit operation that updates the destination acceleration structure based on the
 * provided descriptor and the contents of the source acceleration structure, using the
 * specified scratch buffer for temporary storage.
 *
 * @param sourceAccelerationStructure The acceleration structure providing source geometry/state.
 * @param descriptor Descriptor describing how the acceleration structure should be refit.
 * @param destinationAccelerationStructure The acceleration structure to receive the refit result.
 * @param scratchBuffer Buffer used for temporary scratch storage during refit.
 * @param scratchBufferOffset Byte offset into `scratchBuffer` where scratch memory begins.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::refitAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL::AccelerationStructureDescriptor* descriptor, const MTL::AccelerationStructure* destinationAccelerationStructure, const MTL::Buffer* scratchBuffer, NS::UInteger scratchBufferOffset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(refitAccelerationStructure_descriptor_destination_scratchBuffer_scratchBufferOffset_), sourceAccelerationStructure, descriptor, destinationAccelerationStructure, scratchBuffer, scratchBufferOffset);
}

/**
 * @brief Encodes a command to refit an acceleration structure into a destination acceleration structure.
 *
 * Updates the destination acceleration structure to reflect changes described by `descriptor`, using `scratchBuffer`
 * at `scratchBufferOffset` for temporary storage and applying the specified `options`.
 *
 * @param sourceAccelerationStructure The original acceleration structure to refit.
 * @param descriptor Descriptor describing how the source should be refitted.
 * @param destinationAccelerationStructure The acceleration structure that will be updated with the refit result.
 * @param scratchBuffer Buffer used for scratch/temporary storage during the refit operation.
 * @param scratchBufferOffset Byte offset into `scratchBuffer` where scratch space begins.
 * @param options Options that modify refitting behavior.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::refitAccelerationStructure(const MTL::AccelerationStructure* sourceAccelerationStructure, const MTL::AccelerationStructureDescriptor* descriptor, const MTL::AccelerationStructure* destinationAccelerationStructure, const MTL::Buffer* scratchBuffer, NS::UInteger scratchBufferOffset, MTL::AccelerationStructureRefitOptions options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(refitAccelerationStructure_descriptor_destination_scratchBuffer_scratchBufferOffset_options_), sourceAccelerationStructure, descriptor, destinationAccelerationStructure, scratchBuffer, scratchBufferOffset, options);
}

/**
 * @brief Encodes a command to record GPU counter samples into a counter sample buffer.
 *
 * @param sampleBuffer The CounterSampleBuffer that receives the sample data.
 * @param sampleIndex The index within the sample buffer where the sample will be written.
 * @param barrier If `true`, insert a synchronization barrier so the sample reflects completed GPU work; if `false`, no barrier is inserted.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::sampleCountersInBuffer(const MTL::CounterSampleBuffer* sampleBuffer, NS::UInteger sampleIndex, bool barrier)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(sampleCountersInBuffer_atSampleIndex_withBarrier_), sampleBuffer, sampleIndex, barrier);
}

/**
 * @brief Encode a command that records the encoder's current progress into a fence.
 *
 * Records an update to the provided fence so it reflects the encoder's execution progress
 * at the point this command is encoded.
 *
 * @param fence The fence to update with the encoder's current progress.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::updateFence(const MTL::Fence* fence)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(updateFence_), fence);
}

/**
 * @brief Declares that the encoder will allocate or bind resources from the specified heap for subsequent commands.
 *
 * @param heap Heap whose memory is preferred for resources used by later encoded acceleration-structure commands.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::useHeap(const MTL::Heap* heap)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(useHeap_), heap);
}

/**
 * @brief Make the encoder use the specified memory heaps for resource usage.
 *
 * Marks the provided array of heaps as in-use by this command encoder so resources backed by those
 * heaps are considered for synchronization and residency for the duration of the encoded commands.
 *
 * @param heaps Array of pointers to heaps to be used by the encoder.
 * @param count Number of entries in `heaps`.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::useHeaps(const MTL::Heap* const heaps[], NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(useHeaps_count_), heaps, count);
}

/**
 * @brief Declare that this encoder will use a specific resource with the given usage flags.
 *
 * Marks the provided resource for use by subsequent commands encoded by this AccelerationStructureCommandEncoder,
 * specifying the intended access pattern so the driver can manage hazards and resource residency.
 *
 * @param resource The resource to be used by the encoder.
 * @param usage Bitmask describing how the encoder will access the resource (for example read, write, or read-write).
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::useResource(const MTL::Resource* resource, MTL::ResourceUsage usage)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(useResource_usage_), resource, usage);
}

/**
 * @brief Declare usage of multiple GPU resources for subsequent encoding commands.
 *
 * Informs the encoder that the provided array of resources will be accessed with the specified usage
 * for the duration of this encoder's recorded commands.
 *
 * @param resources Array of resource pointers to mark for usage.
 * @param count Number of resources in `resources`.
 * @param usage The access pattern (read, write, or read-write) to apply to each resource.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::useResources(const MTL::Resource* const resources[], NS::UInteger count, MTL::ResourceUsage usage)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(useResources_count_usage_), resources, count, usage);
}

/**
 * @brief Encodes a command that waits for a synchronization fence before proceeding.
 *
 * @param fence The fence to wait for; the GPU will not execute subsequent commands recorded by this encoder until the fence is reached/signaled.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::waitForFence(const MTL::Fence* fence)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(waitForFence_), fence);
}

/**
 * @brief Encodes a command to write the size required to store a compacted acceleration structure into a buffer.
 *
 * @param accelerationStructure The acceleration structure whose compacted size will be written.
 * @param buffer The destination buffer to receive the size.
 * @param offset Byte offset in `buffer` where the size value will be written.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::writeCompactedAccelerationStructureSize(const MTL::AccelerationStructure* accelerationStructure, const MTL::Buffer* buffer, NS::UInteger offset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(writeCompactedAccelerationStructureSize_toBuffer_offset_), accelerationStructure, buffer, offset);
}

/**
 * @brief Writes the size of a compacted acceleration structure into a buffer.
 *
 * Encodes a command to write the compacted byte size of the specified acceleration structure into the given buffer at the provided byte offset using the specified data type for the size value.
 *
 * @param accelerationStructure The acceleration structure whose compacted size will be written.
 * @param buffer The destination buffer where the size will be stored.
 * @param offset Byte offset within `buffer` where the size value will be written.
 * @param sizeDataType The data type used to encode the size value in `buffer`.
 */
_MTL_INLINE void MTL::AccelerationStructureCommandEncoder::writeCompactedAccelerationStructureSize(const MTL::AccelerationStructure* accelerationStructure, const MTL::Buffer* buffer, NS::UInteger offset, MTL::DataType sizeDataType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(writeCompactedAccelerationStructureSize_toBuffer_offset_sizeDataType_), accelerationStructure, buffer, offset, sizeDataType);
}

/**
 * @brief Allocate a new AccelerationStructurePassSampleBufferAttachmentDescriptor.
 *
 * @return MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor* A newly allocated descriptor object; the caller should invoke init() (or use an allocator that initializes) before using the instance.
 */
_MTL_INLINE MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor* MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor::alloc()
{
    return NS::Object::alloc<MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor>(_MTL_PRIVATE_CLS(MTLAccelerationStructurePassSampleBufferAttachmentDescriptor));
}

/**
 * @brief Retrieves the configured end-of-encoder sample index for this attachment.
 *
 * @return NS::UInteger The sample index that will be written (or has been configured to be written) at the end of the encoder.
 */
_MTL_INLINE NS::UInteger MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor::endOfEncoderSampleIndex() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(endOfEncoderSampleIndex));
}

/**
 * @brief Initializes a newly allocated acceleration structure pass sample buffer attachment descriptor.
 *
 * Performs object initialization and returns the initialized descriptor instance.
 *
 * @return MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor* MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor::init()
{
    return NS::Object::init<MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor>();
}

/**
 * @brief Retrieve the counter sample buffer associated with this attachment descriptor.
 *
 * @return MTL::CounterSampleBuffer* The CounterSampleBuffer attached to this descriptor, or `nullptr` if no buffer is set.
 */
_MTL_INLINE MTL::CounterSampleBuffer* MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor::sampleBuffer() const
{
    return Object::sendMessage<MTL::CounterSampleBuffer*>(this, _MTL_PRIVATE_SEL(sampleBuffer));
}

/**
 * @brief Sets the end-of-encoder sample index for this attachment.
 *
 * Specifies the index in the associated CounterSampleBuffer where the encoder will record the end-of-encoder sample for this attachment.
 *
 * @param endOfEncoderSampleIndex Sample index to use for the end-of-encoder marker.
 */
_MTL_INLINE void MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor::setEndOfEncoderSampleIndex(NS::UInteger endOfEncoderSampleIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setEndOfEncoderSampleIndex_), endOfEncoderSampleIndex);
}

/**
 * @brief Set the counter sample buffer for this pass sample buffer attachment.
 *
 * Associates the provided CounterSampleBuffer with the attachment; passing `nullptr` detaches any currently set buffer.
 *
 * @param sampleBuffer The CounterSampleBuffer to attach, or `nullptr` to clear the attachment.
 */
_MTL_INLINE void MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor::setSampleBuffer(const MTL::CounterSampleBuffer* sampleBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSampleBuffer_), sampleBuffer);
}

/**
 * @brief Set the sample index at which the encoder will record the start-of-encoder counter sample.
 *
 * @param startOfEncoderSampleIndex Sample buffer index used to mark the start of the encoder's sampling region.
 */
_MTL_INLINE void MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor::setStartOfEncoderSampleIndex(NS::UInteger startOfEncoderSampleIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStartOfEncoderSampleIndex_), startOfEncoderSampleIndex);
}

/**
 * @brief Retrieve the start-of-encoder sample index for this attachment.
 *
 * @return NS::UInteger The sample index at which sampling begins at the start of the encoder.
 */
_MTL_INLINE NS::UInteger MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor::startOfEncoderSampleIndex() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(startOfEncoderSampleIndex));
}

/**
 * @brief Allocate a new AccelerationStructurePassSampleBufferAttachmentDescriptorArray instance.
 *
 * The returned object is allocated but not initialized; call init() before use.
 *
 * @return AccelerationStructurePassSampleBufferAttachmentDescriptorArray* Pointer to the newly allocated instance.
 */
_MTL_INLINE MTL::AccelerationStructurePassSampleBufferAttachmentDescriptorArray* MTL::AccelerationStructurePassSampleBufferAttachmentDescriptorArray::alloc()
{
    return NS::Object::alloc<MTL::AccelerationStructurePassSampleBufferAttachmentDescriptorArray>(_MTL_PRIVATE_CLS(MTLAccelerationStructurePassSampleBufferAttachmentDescriptorArray));
}

/**
 * @brief Initialize a newly allocated AccelerationStructurePassSampleBufferAttachmentDescriptorArray.
 *
 * @return An initialized AccelerationStructurePassSampleBufferAttachmentDescriptorArray instance.
 */
_MTL_INLINE MTL::AccelerationStructurePassSampleBufferAttachmentDescriptorArray* MTL::AccelerationStructurePassSampleBufferAttachmentDescriptorArray::init()
{
    return NS::Object::init<MTL::AccelerationStructurePassSampleBufferAttachmentDescriptorArray>();
}

/**
 * @brief Retrieve the sample-buffer attachment descriptor at the specified index.
 *
 * @param attachmentIndex Index of the attachment to retrieve.
 * @return MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor* Pointer to the attachment descriptor at the given index, or `nullptr` if none is present.
 */
_MTL_INLINE MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor* MTL::AccelerationStructurePassSampleBufferAttachmentDescriptorArray::object(NS::UInteger attachmentIndex)
{
    return Object::sendMessage<MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor*>(this, _MTL_PRIVATE_SEL(objectAtIndexedSubscript_), attachmentIndex);
}

/**
 * @brief Sets the sample buffer attachment descriptor at the specified index.
 *
 * Replaces the descriptor stored at `attachmentIndex` with `attachment`.
 *
 * @param attachment Attachment descriptor to store.
 * @param attachmentIndex Index at which to set the descriptor.
 */
_MTL_INLINE void MTL::AccelerationStructurePassSampleBufferAttachmentDescriptorArray::setObject(const MTL::AccelerationStructurePassSampleBufferAttachmentDescriptor* attachment, NS::UInteger attachmentIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObject_atIndexedSubscript_), attachment, attachmentIndex);
}

/**
 * @brief Creates a new acceleration structure pass descriptor.
 *
 * @return MTL::AccelerationStructurePassDescriptor* A new pass descriptor for configuring acceleration-structure passes.
 */
_MTL_INLINE MTL::AccelerationStructurePassDescriptor* MTL::AccelerationStructurePassDescriptor::accelerationStructurePassDescriptor()
{
    return Object::sendMessage<MTL::AccelerationStructurePassDescriptor*>(_MTL_PRIVATE_CLS(MTLAccelerationStructurePassDescriptor), _MTL_PRIVATE_SEL(accelerationStructurePassDescriptor));
}

/**
 * @brief Allocates a new AccelerationStructurePassDescriptor instance.
 *
 * Allocates raw object memory for a pass descriptor; the returned object is uninitialized and must be initialized with init() before use.
 *
 * @return MTL::AccelerationStructurePassDescriptor* Pointer to the allocated descriptor.
 */
_MTL_INLINE MTL::AccelerationStructurePassDescriptor* MTL::AccelerationStructurePassDescriptor::alloc()
{
    return NS::Object::alloc<MTL::AccelerationStructurePassDescriptor>(_MTL_PRIVATE_CLS(MTLAccelerationStructurePassDescriptor));
}

/**
 * @brief Initializes an AccelerationStructurePassDescriptor instance.
 *
 * @return MTL::AccelerationStructurePassDescriptor* The initialized descriptor (`this`).
 */
_MTL_INLINE MTL::AccelerationStructurePassDescriptor* MTL::AccelerationStructurePassDescriptor::init()
{
    return NS::Object::init<MTL::AccelerationStructurePassDescriptor>();
}

/**
 * @brief Accesses the array of sample-buffer attachments configured for this acceleration structure pass.
 *
 * @return AccelerationStructurePassSampleBufferAttachmentDescriptorArray* Pointer to the array of sample buffer attachment descriptors for this pass.
 */
_MTL_INLINE MTL::AccelerationStructurePassSampleBufferAttachmentDescriptorArray* MTL::AccelerationStructurePassDescriptor::sampleBufferAttachments() const
{
    return Object::sendMessage<MTL::AccelerationStructurePassSampleBufferAttachmentDescriptorArray*>(this, _MTL_PRIVATE_SEL(sampleBufferAttachments));
}