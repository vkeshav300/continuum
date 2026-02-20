//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLIOCommandQueue.hpp
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
class Buffer;
class IOCommandBuffer;
class IOCommandQueueDescriptor;
class IOScratchBuffer;
class IOScratchBufferAllocator;
_MTL_ENUM(NS::Integer, IOPriority) {
    IOPriorityHigh = 0,
    IOPriorityNormal = 1,
    IOPriorityLow = 2,
};

_MTL_ENUM(NS::Integer, IOCommandQueueType) {
    IOCommandQueueTypeConcurrent = 0,
    IOCommandQueueTypeSerial = 1,
};

/**
 * @brief IO-related error codes.
 *
 * Enumerates specific error conditions reported by IO operations.
 */

/**
 * @brief Error domain for IO errors.
 */

/**
 * @brief A queue for encoding and committing IO command buffers.
 */

/**
 * @brief Creates and returns a new command buffer to record IO commands.
 *
 * @returns IOCommandBuffer* A newly created command buffer owned by the caller.
 */

/**
 * @brief Creates and returns a new command buffer that does not retain object references.
 *
 * Use this when recorded commands must avoid retaining Objective-C/C++ objects.
 *
 * @returns IOCommandBuffer* A newly created command buffer owned by the caller.
 */

/**
 * @brief Inserts a barrier into the queue that ensures previously enqueued work completes before subsequent work begins.
 */

/**
 * @brief Returns the label assigned to the command queue.
 *
 * @returns NS::String* The queue's label, or nullptr if none is set.
 */

/**
 * @brief Sets a human-readable label for the command queue.
 *
 * @param label The label string to assign to the queue.
 */

/**
 * @brief A scratch buffer wrapper that exposes an underlying GPU/IO buffer.
 */

/**
 * @brief Returns the underlying buffer associated with this scratch buffer.
 *
 * @returns Buffer* The underlying Buffer, or nullptr if unavailable.
 */

/**
 * @brief Allocator for transient scratch buffers used by IO command recording.
 */

/**
 * @brief Allocates a new scratch buffer with at least the requested minimum size.
 *
 * @param minimumSize Minimum number of bytes required in the returned scratch buffer.
 * @returns IOScratchBuffer* A new scratch buffer meeting the size requirement.
 */

/**
 * @brief Descriptor for configuring an IO command queue.
 */

/**
 * @brief Allocates a new, uninitialized IOCommandQueueDescriptor.
 *
 * @returns IOCommandQueueDescriptor* An allocated descriptor instance.
 */

/**
 * @brief Initializes the descriptor to default values.
 *
 * @returns IOCommandQueueDescriptor* The initialized descriptor instance.
 */

/**
 * @brief Returns the maximum number of command buffers the queue will create.
 *
 * @returns NS::UInteger The configured maximum command buffer count.
 */

/**
 * @brief Returns the maximum number of in-flight commands allowed by the queue.
 *
 * @returns NS::UInteger The maximum commands in flight.
 */

/**
 * @brief Returns the scheduling priority assigned to the queue.
 *
 * @returns IOPriority The queue's I/O priority.
 */

/**
 * @brief Returns the allocator used for creating scratch buffers for this queue.
 *
 * @returns IOScratchBufferAllocator* The scratch buffer allocator, or nullptr if none is set.
 */

/**
 * @brief Sets the maximum number of command buffers the queue may create.
 *
 * @param maxCommandBufferCount The maximum number of command buffers.
 */

/**
 * @brief Sets the maximum number of commands that may be in flight concurrently.
 *
 * @param maxCommandsInFlight The maximum in-flight command count.
 */

/**
 * @brief Sets the scheduling priority for the queue.
 *
 * @param priority The I/O priority to assign.
 */

/**
 * @brief Sets the scratch buffer allocator to be used by the queue.
 *
 * @param scratchBufferAllocator The allocator responsible for producing scratch buffers.
 */

/**
 * @brief Sets the concurrency type for the command queue.
 *
 * @param type The command queue type (concurrent or serial).
 */

/**
 * @brief Returns the configured concurrency type for the command queue.
 *
 * @returns IOCommandQueueType The queue's concurrency type.
 */

/**
 * @brief A handle representing an open IO file or resource.
 */

/**
 * @brief Returns the human-readable label assigned to the file handle.
 *
 * @returns NS::String* The file handle's label, or nullptr if none is set.
 */

/**
 * @brief Assigns a human-readable label to the file handle.
 *
 * @param label The label string to assign to the file handle.
 */
_MTL_ENUM(NS::Integer, IOError) {
    IOErrorURLInvalid = 1,
    IOErrorInternal = 2,
};

_MTL_CONST(NS::ErrorDomain, IOErrorDomain);
class IOCommandQueue : public NS::Referencing<IOCommandQueue>
{
public:
    IOCommandBuffer* commandBuffer();
    IOCommandBuffer* commandBufferWithUnretainedReferences();

    void             enqueueBarrier();

    NS::String*      label() const;
    void             setLabel(const NS::String* label);
};
class IOScratchBuffer : public NS::Referencing<IOScratchBuffer>
{
public:
    Buffer* buffer() const;
};
class IOScratchBufferAllocator : public NS::Referencing<IOScratchBufferAllocator>
{
public:
    IOScratchBuffer* newScratchBuffer(NS::UInteger minimumSize);
};
class IOCommandQueueDescriptor : public NS::Copying<IOCommandQueueDescriptor>
{
public:
    static IOCommandQueueDescriptor* alloc();

    IOCommandQueueDescriptor*        init();

    NS::UInteger                     maxCommandBufferCount() const;

    NS::UInteger                     maxCommandsInFlight() const;

    IOPriority                       priority() const;

    IOScratchBufferAllocator*        scratchBufferAllocator() const;

    void                             setMaxCommandBufferCount(NS::UInteger maxCommandBufferCount);

    void                             setMaxCommandsInFlight(NS::UInteger maxCommandsInFlight);

    void                             setPriority(MTL::IOPriority priority);

    void                             setScratchBufferAllocator(const MTL::IOScratchBufferAllocator* scratchBufferAllocator);

    void                             setType(MTL::IOCommandQueueType type);
    IOCommandQueueType               type() const;
};
class IOFileHandle : public NS::Referencing<IOFileHandle>
{
public:
    NS::String* label() const;
    void        setLabel(const NS::String* label);
};

}
_MTL_PRIVATE_DEF_CONST(NS::ErrorDomain, IOErrorDomain);
/**
 * @brief Creates a new command buffer associated with this command queue.
 *
 * @return MTL::IOCommandBuffer* The newly created command buffer for encoding and committing IO work.
 */
_MTL_INLINE MTL::IOCommandBuffer* MTL::IOCommandQueue::commandBuffer()
{
    return Object::sendMessage<MTL::IOCommandBuffer*>(this, _MTL_PRIVATE_SEL(commandBuffer));
}

/**
 * @brief Creates a command buffer that uses unretained references.
 *
 * @return MTL::IOCommandBuffer* A command buffer configured to avoid retaining referenced objects.
 */
_MTL_INLINE MTL::IOCommandBuffer* MTL::IOCommandQueue::commandBufferWithUnretainedReferences()
{
    return Object::sendMessage<MTL::IOCommandBuffer*>(this, _MTL_PRIVATE_SEL(commandBufferWithUnretainedReferences));
}

/**
 * @brief Inserts a barrier into the command queue to ensure all previously enqueued commands complete
 * before subsequent commands begin execution.
 */
_MTL_INLINE void MTL::IOCommandQueue::enqueueBarrier()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(enqueueBarrier));
}

/**
 * @brief Returns the human-readable label assigned to the command queue.
 *
 * @return NS::String* The label string, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::IOCommandQueue::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Set the human-readable label for the command queue.
 *
 * @param label The label string to assign to this IOCommandQueue.
 */
_MTL_INLINE void MTL::IOCommandQueue::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Returns the Buffer associated with this scratch buffer.
 *
 * @return MTL::Buffer* Pointer to the associated Buffer.
 */
_MTL_INLINE MTL::Buffer* MTL::IOScratchBuffer::buffer() const
{
    return Object::sendMessage<MTL::Buffer*>(this, _MTL_PRIVATE_SEL(buffer));
}

/**
 * @brief Creates a scratch buffer with at least the requested size.
 *
 * @param minimumSize Minimum required byte size for the returned scratch buffer.
 * @return MTL::IOScratchBuffer* Scratch buffer whose capacity is greater than or equal to `minimumSize`.
 */
_MTL_INLINE MTL::IOScratchBuffer* MTL::IOScratchBufferAllocator::newScratchBuffer(NS::UInteger minimumSize)
{
    return Object::sendMessage<MTL::IOScratchBuffer*>(this, _MTL_PRIVATE_SEL(newScratchBufferWithMinimumSize_), minimumSize);
}

/**
 * @brief Allocate raw, uninitialized storage for an IOCommandQueueDescriptor.
 *
 * @return MTL::IOCommandQueueDescriptor* Pointer to the allocated, uninitialized descriptor.
 */
_MTL_INLINE MTL::IOCommandQueueDescriptor* MTL::IOCommandQueueDescriptor::alloc()
{
    return NS::Object::alloc<MTL::IOCommandQueueDescriptor>(_MTL_PRIVATE_CLS(MTLIOCommandQueueDescriptor));
}

/**
 * @brief Initializes an IOCommandQueueDescriptor instance.
 *
 * @return IOCommandQueueDescriptor* The initialized descriptor instance.
 */
_MTL_INLINE MTL::IOCommandQueueDescriptor* MTL::IOCommandQueueDescriptor::init()
{
    return NS::Object::init<MTL::IOCommandQueueDescriptor>();
}

/**
 * @brief Retrieve the maximum number of command buffers the descriptor permits.
 *
 * @return The maximum number of command buffers permitted by the descriptor.
 */
_MTL_INLINE NS::UInteger MTL::IOCommandQueueDescriptor::maxCommandBufferCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxCommandBufferCount));
}

/**
 * @brief Query the maximum number of commands allowed in flight for this descriptor.
 *
 * @return NS::UInteger The maximum number of commands that may be in flight concurrently.
 */
_MTL_INLINE NS::UInteger MTL::IOCommandQueueDescriptor::maxCommandsInFlight() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxCommandsInFlight));
}

/**
 * @brief The priority level configured for this command queue descriptor.
 *
 * @return MTL::IOPriority The descriptor's priority: `IOPriorityHigh`, `IOPriorityNormal`, or `IOPriorityLow`.
 */
_MTL_INLINE MTL::IOPriority MTL::IOCommandQueueDescriptor::priority() const
{
    return Object::sendMessage<MTL::IOPriority>(this, _MTL_PRIVATE_SEL(priority));
}

/**
 * @brief The scratch buffer allocator associated with the descriptor.
 *
 * @return MTL::IOScratchBufferAllocator* The allocator used to create scratch buffers, or `nullptr` if none is set.
 */
_MTL_INLINE MTL::IOScratchBufferAllocator* MTL::IOCommandQueueDescriptor::scratchBufferAllocator() const
{
    return Object::sendMessage<MTL::IOScratchBufferAllocator*>(this, _MTL_PRIVATE_SEL(scratchBufferAllocator));
}

/**
 * @brief Sets the maximum number of command buffers the descriptor may allocate.
 *
 * @param maxCommandBufferCount Maximum number of command buffers allowed.
 */
_MTL_INLINE void MTL::IOCommandQueueDescriptor::setMaxCommandBufferCount(NS::UInteger maxCommandBufferCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxCommandBufferCount_), maxCommandBufferCount);
}

/**
 * @brief Set the maximum number of commands that may be in flight for this queue descriptor.
 *
 * @param maxCommandsInFlight Maximum number of commands allowed to be active (in flight) concurrently.
 */
_MTL_INLINE void MTL::IOCommandQueueDescriptor::setMaxCommandsInFlight(NS::UInteger maxCommandsInFlight)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxCommandsInFlight_), maxCommandsInFlight);
}

/**
 * @brief Sets the priority level for this command queue descriptor.
 *
 * @param priority Priority to assign to the descriptor — one of `IOPriorityHigh`, `IOPriorityNormal`, or `IOPriorityLow`.
 */
_MTL_INLINE void MTL::IOCommandQueueDescriptor::setPriority(MTL::IOPriority priority)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPriority_), priority);
}

/**
 * @brief Sets the scratch buffer allocator for the command queue descriptor.
 *
 * @param scratchBufferAllocator Allocator used to provide scratch buffers for command buffers created by queues configured with this descriptor.
 */
_MTL_INLINE void MTL::IOCommandQueueDescriptor::setScratchBufferAllocator(const MTL::IOScratchBufferAllocator* scratchBufferAllocator)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setScratchBufferAllocator_), scratchBufferAllocator);
}

/**
 * @brief Sets the command queue's type.
 *
 * @param type The IOCommandQueueType to assign to the descriptor (e.g., IOCommandQueueTypeConcurrent or IOCommandQueueTypeSerial).
 */
_MTL_INLINE void MTL::IOCommandQueueDescriptor::setType(MTL::IOCommandQueueType type)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setType_), type);
}

/**
 * The command queue's type.
 *
 * @return IOCommandQueueType Value indicating whether the queue is concurrent or serial.
 */
_MTL_INLINE MTL::IOCommandQueueType MTL::IOCommandQueueDescriptor::type() const
{
    return Object::sendMessage<MTL::IOCommandQueueType>(this, _MTL_PRIVATE_SEL(type));
}

/**
 * @brief Retrieves the label associated with the file handle.
 *
 * @return NS::String* The label string for the file handle, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::IOFileHandle::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

_MTL_INLINE void MTL::IOFileHandle::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}