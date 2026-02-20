//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLCommandQueue.hpp
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
class CommandBuffer;
class CommandBufferDescriptor;
class CommandQueueDescriptor;
class Device;
class LogState;
class ResidencySet;

class CommandQueue : public NS::Referencing<CommandQueue>
{
public:
    void           addResidencySet(const MTL::ResidencySet* residencySet);
    void           addResidencySets(const MTL::ResidencySet* const residencySets[], NS::UInteger count);

    CommandBuffer* commandBuffer();
    CommandBuffer* commandBuffer(const MTL::CommandBufferDescriptor* descriptor);
    CommandBuffer* commandBufferWithUnretainedReferences();

    Device*        device() const;

    void           insertDebugCaptureBoundary();

    NS::String*    label() const;

    void           removeResidencySet(const MTL::ResidencySet* residencySet);
    void           removeResidencySets(const MTL::ResidencySet* const residencySets[], NS::UInteger count);

    void           setLabel(const NS::String* label);
};
class CommandQueueDescriptor : public NS::Copying<CommandQueueDescriptor>
{
public:
    static CommandQueueDescriptor* alloc();

    CommandQueueDescriptor*        init();

    LogState*                      logState() const;

    NS::UInteger                   maxCommandBufferCount() const;

    void                           setLogState(const MTL::LogState* logState);

    void                           setMaxCommandBufferCount(NS::UInteger maxCommandBufferCount);
};

}
/**
 * @brief Adds a residency set to the command queue.
 *
 * The residency set is registered with the queue so the resources it contains
 * are considered for residency management for work submitted to this queue.
 *
 * @param residencySet Pointer to the ResidencySet to add.
 */
_MTL_INLINE void MTL::CommandQueue::addResidencySet(const MTL::ResidencySet* residencySet)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(addResidencySet_), residencySet);
}

/**
 * @brief Adds multiple residency sets to the command queue.
 *
 * Adds the provided array of residency sets to the queue's residency tracking so the
 * resources referenced by those sets remain resident for commands submitted on this queue.
 *
 * @param residencySets Pointer to an array of ResidencySet pointers to add.
 * @param count Number of residency sets in the array.
 */
_MTL_INLINE void MTL::CommandQueue::addResidencySets(const MTL::ResidencySet* const residencySets[], NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(addResidencySets_count_), residencySets, count);
}

/**
 * @brief Creates a command buffer associated with this command queue.
 *
 * @return MTL::CommandBuffer* Pointer to a CommandBuffer associated with this command queue.
 */
_MTL_INLINE MTL::CommandBuffer* MTL::CommandQueue::commandBuffer()
{
    return Object::sendMessage<MTL::CommandBuffer*>(this, _MTL_PRIVATE_SEL(commandBuffer));
}

/**
 * @brief Creates a command buffer configured by the given descriptor.
 *
 * @param descriptor Descriptor that configures the returned command buffer; if `nullptr`, default configuration is used.
 * @return MTL::CommandBuffer* A command buffer configured according to `descriptor`.
 */
_MTL_INLINE MTL::CommandBuffer* MTL::CommandQueue::commandBuffer(const MTL::CommandBufferDescriptor* descriptor)
{
    return Object::sendMessage<MTL::CommandBuffer*>(this, _MTL_PRIVATE_SEL(commandBufferWithDescriptor_), descriptor);
}

/**
 * @brief Creates a command buffer that holds unretained object references.
 *
 * The returned command buffer will reference resources without retaining them; callers must ensure those
 * resources remain valid for the lifetime of the command buffer.
 *
 * @return MTL::CommandBuffer* A new command buffer configured to use unretained references.
 */
_MTL_INLINE MTL::CommandBuffer* MTL::CommandQueue::commandBufferWithUnretainedReferences()
{
    return Object::sendMessage<MTL::CommandBuffer*>(this, _MTL_PRIVATE_SEL(commandBufferWithUnretainedReferences));
}

/**
 * @brief Retrieve the device associated with this command queue.
 *
 * @return Pointer to the associated MTL::Device, or `nullptr` if no device is available.
 */
_MTL_INLINE MTL::Device* MTL::CommandQueue::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Inserts a debug capture boundary into the command queue's command stream.
 *
 * Marks a point in the queue where GPU capture/profiling tools can delimit command recording.
 */
_MTL_INLINE void MTL::CommandQueue::insertDebugCaptureBoundary()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(insertDebugCaptureBoundary));
}

/**
 * @brief Label assigned to the command queue.
 *
 * @return NS::String* The label string, or nullptr if no label is set.
 */
_MTL_INLINE NS::String* MTL::CommandQueue::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Removes the specified residency set from the command queue.
 *
 * @param residencySet Residency set to remove from the queue's residency tracking.
 */
_MTL_INLINE void MTL::CommandQueue::removeResidencySet(const MTL::ResidencySet* residencySet)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(removeResidencySet_), residencySet);
}

/**
 * @brief Removes multiple residency sets from the command queue.
 *
 * Removes each residency set in the provided array so the queue no longer holds residency references for them.
 *
 * @param residencySets Pointer to an array of `ResidencySet` pointers to remove.
 * @param count Number of residency sets in `residencySets`.
 */
_MTL_INLINE void MTL::CommandQueue::removeResidencySets(const MTL::ResidencySet* const residencySets[], NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(removeResidencySets_count_), residencySets, count);
}

/**
 * @brief Set the human-readable label for the command queue.
 *
 * Assigns a label used for identification and debugging purposes.
 *
 * @param label The string to assign as the queue's label. Passing `nullptr` clears the label.
 */
_MTL_INLINE void MTL::CommandQueue::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Allocates a new CommandQueueDescriptor instance.
 *
 * @return MTL::CommandQueueDescriptor* A newly allocated, uninitialized CommandQueueDescriptor.
 * The caller should call `init()` on the returned object before use.
 */
_MTL_INLINE MTL::CommandQueueDescriptor* MTL::CommandQueueDescriptor::alloc()
{
    return NS::Object::alloc<MTL::CommandQueueDescriptor>(_MTL_PRIVATE_CLS(MTLCommandQueueDescriptor));
}

/**
 * @brief Initializes the CommandQueueDescriptor instance.
 *
 * @return MTL::CommandQueueDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::CommandQueueDescriptor* MTL::CommandQueueDescriptor::init()
{
    return NS::Object::init<MTL::CommandQueueDescriptor>();
}

/**
 * @brief Returns the log state associated with this command queue descriptor.
 *
 * @return MTL::LogState* Pointer to the descriptor's LogState, or `nullptr` if no log state is set.
 */
_MTL_INLINE MTL::LogState* MTL::CommandQueueDescriptor::logState() const
{
    return Object::sendMessage<MTL::LogState*>(this, _MTL_PRIVATE_SEL(logState));
}

/**
 * @brief Retrieves the maximum number of command buffers that may be created from the queue described by this descriptor.
 *
 * @return NS::UInteger The maximum command buffer count configured on this descriptor.
 */
_MTL_INLINE NS::UInteger MTL::CommandQueueDescriptor::maxCommandBufferCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxCommandBufferCount));
}

/**
 * @brief Sets the LogState used by the command queue descriptor.
 *
 * @param logState Pointer to the LogState to assign to the descriptor. May be nullptr to clear the descriptor's log state.
 */
_MTL_INLINE void MTL::CommandQueueDescriptor::setLogState(const MTL::LogState* logState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLogState_), logState);
}

/**
 * @brief Sets the maximum number of command buffers the descriptor allows.
 *
 * @param maxCommandBufferCount Maximum number of in-flight command buffers permitted by the descriptor.
 */
_MTL_INLINE void MTL::CommandQueueDescriptor::setMaxCommandBufferCount(NS::UInteger maxCommandBufferCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxCommandBufferCount_), maxCommandBufferCount);
}