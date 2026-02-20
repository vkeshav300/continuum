//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4CommandQueue.hpp
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
#include "MTL4CommitFeedback.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLResourceStateCommandEncoder.hpp"
#include "MTLTypes.hpp"
#include <cstdint>
#include <dispatch/dispatch.h>

namespace MTL
{
class Buffer;
class Device;
class Drawable;
class Event;
class Heap;
class ResidencySet;
class Texture;
}

namespace MTL4
{
class CommandBuffer;
class CommandQueueDescriptor;
class CommitOptions;
struct CopySparseBufferMappingOperation;
struct CopySparseTextureMappingOperation;
struct UpdateSparseBufferMappingOperation;
struct UpdateSparseTextureMappingOperation;
/**
 * @brief Error codes produced by command queue operations.
 *
 * Represents specific failure conditions that can occur when using a command queue.
 */

/**
 * @brief Parameters for updating a region of a sparse texture's mapping.
 *
 * @param mode Mapping mode that describes how the mapping is applied.
 * @param textureRegion Region of the texture to update.
 * @param textureLevel Mipmap level of the texture to update.
 * @param textureSlice Slice (array layer) of the texture to update.
 * @param heapOffset Byte offset into the heap where the mapping begins.
 */

/**
 * @brief Parameters for copying sparse texture mapping data between textures.
 *
 * @param sourceRegion Region within the source texture to copy.
 * @param sourceLevel Mipmap level in the source texture.
 * @param sourceSlice Slice (array layer) in the source texture.
 * @param destinationOrigin Origin within the destination texture where the region will be placed.
 * @param destinationLevel Mipmap level in the destination texture.
 * @param destinationSlice Slice (array layer) in the destination texture.
 */

/**
 * @brief Parameters for updating a region of a sparse buffer's mapping.
 *
 * @param mode Mapping mode that describes how the mapping is applied.
 * @param bufferRange Byte range within the buffer to update.
 * @param heapOffset Byte offset into the heap where the mapping begins.
 */

/**
 * @brief Parameters for copying sparse buffer mapping data between buffers.
 *
 * @param sourceRange Byte range within the source buffer to copy.
 * @param destinationOffset Byte offset within the destination buffer where the data will be placed.
 */

/**
 * @brief Options for committing command buffers that can carry commit-time feedback handlers.
 *
 * Use to attach handlers that will be invoked with commit feedback.
 *
 * @param block A block-style feedback handler to register.
 */

/**
 * @brief Options for committing command buffers that can carry commit-time feedback handlers.
 *
 * @param function A callable feedback handler to register; the function will be wrapped and invoked like a block handler.
 */

/**
 * @brief Allocate a new CommitOptions instance.
 *
 * @return CommitOptions* Newly allocated CommitOptions instance.
 */

/**
 * @brief Initialize a CommitOptions instance.
 *
 * @return CommitOptions* Initialized CommitOptions instance.
 */

/**
 * @brief Descriptor configuring properties for a command queue.
 *
 * Holds metadata such as a label and a feedback dispatch queue for the command queue.
 */

/**
 * @brief Allocate a new CommandQueueDescriptor instance.
 *
 * @return CommandQueueDescriptor* Newly allocated descriptor.
 */

/**
 * @brief The dispatch queue used to deliver feedback for the command queue.
 *
 * @return dispatch_queue_t The feedback dispatch queue, or nullptr if none is set.
 */

/**
 * @brief Initialize a CommandQueueDescriptor instance.
 *
 * @return CommandQueueDescriptor* Initialized descriptor instance.
 */

/**
 * @brief Human-readable label for the command queue.
 *
 * @return NS::String* The label string, or nullptr if none is set.
 */

/**
 * @brief Set the dispatch queue used to deliver feedback for the command queue.
 *
 * @param feedbackQueue Dispatch queue to receive feedback callbacks.
 */

/**
 * @brief Set the human-readable label for the command queue.
 *
 * @param label The label string to set.
 */

/**
 * @brief Represents a Metal command queue and exposes operations for submission, residency and sparse mappings.
 *
 * Provides methods to manage residency sets, commit command buffers (with optional commit-time options), perform sparse resource copy/update mappings, signal and wait on synchronization primitives, and query associated device/label.
 */

/**
 * @brief Add a residency set to the command queue.
 *
 * @param residencySet Residency set to add.
 */

/**
 * @brief Add multiple residency sets to the command queue.
 *
 * @param residencySets Array of residency set pointers to add.
 * @param count Number of residency sets in the array.
 */

/**
 * @brief Commit an array of command buffers to the queue for execution.
 *
 * @param commandBuffers Array of command buffer pointers to commit.
 * @param count Number of command buffers in the array.
 */

/**
 * @brief Commit an array of command buffers to the queue with commit-time options.
 *
 * @param commandBuffers Array of command buffer pointers to commit.
 * @param count Number of command buffers in the array.
 * @param options Commit options that may include feedback handlers.
 */

/**
 * @brief Copy sparse buffer mapping entries from one buffer to another.
 *
 * @param sourceBuffer Source buffer containing mapping entries.
 * @param destinationBuffer Destination buffer to receive mapping entries.
 * @param operations Array of copy operations describing ranges and offsets.
 * @param count Number of operations in the array.
 */

/**
 * @brief Copy sparse texture mapping entries from one texture to another.
 *
 * @param sourceTexture Source texture containing mapping entries.
 * @param destinationTexture Destination texture to receive mapping entries.
 * @param operations Array of copy operations describing regions and destinations.
 * @param count Number of operations in the array.
 */

/**
 * @brief The device that owns this command queue.
 *
 * @return MTL::Device* The associated device.
 */

/**
 * @brief Human-readable label for the command queue.
 *
 * @return NS::String* The label string, or nullptr if none is set.
 */

/**
 * @brief Remove a residency set from the command queue.
 *
 * @param residencySet Residency set to remove.
 */

/**
 * @brief Remove multiple residency sets from the command queue.
 *
 * @param residencySets Array of residency set pointers to remove.
 * @param count Number of residency sets in the array.
 */

/**
 * @brief Signal a drawable on the queue, typically used to indicate presentation or readiness.
 *
 * @param drawable Drawable to signal.
 */

/**
 * @brief Signal an event with a 64-bit value on the queue.
 *
 * @param event Event to signal.
 * @param value Value to signal with the event.
 */

/**
 * @brief Update sparse buffer mappings using entries that reference a heap.
 *
 * @param buffer Buffer whose mappings are being updated.
 * @param heap Heap providing physical memory for the mappings.
 * @param operations Array of update operations describing ranges and heap offsets.
 * @param count Number of operations in the array.
 */

/**
 * @brief Update sparse texture mappings using entries that reference a heap.
 *
 * @param texture Texture whose mappings are being updated.
 * @param heap Heap providing physical memory for the mappings.
 * @param operations Array of update operations describing regions, levels, slices, and heap offsets.
 * @param count Number of operations in the array.
 */

/**
 * @brief Wait on an event until it reaches the specified value before proceeding.
 *
 * @param event Event to wait on.
 * @param value Value to wait for.
 */

/**
 * @brief Wait until the specified drawable is available/ready before proceeding.
 *
 * @param drawable Drawable to wait for.
 */
_MTL_ENUM(NS::Integer, CommandQueueError) {
    CommandQueueErrorNone = 0,
    CommandQueueErrorTimeout = 1,
    CommandQueueErrorNotPermitted = 2,
    CommandQueueErrorOutOfMemory = 3,
    CommandQueueErrorDeviceRemoved = 4,
    CommandQueueErrorAccessRevoked = 5,
    CommandQueueErrorInternal = 6,
};

struct UpdateSparseTextureMappingOperation
{
    MTL::SparseTextureMappingMode mode;
    MTL::Region                   textureRegion;
    NS::UInteger                  textureLevel;
    NS::UInteger                  textureSlice;
    NS::UInteger                  heapOffset;
} _MTL_PACKED;

struct CopySparseTextureMappingOperation
{
    MTL::Region  sourceRegion;
    NS::UInteger sourceLevel;
    NS::UInteger sourceSlice;
    MTL::Origin  destinationOrigin;
    NS::UInteger destinationLevel;
    NS::UInteger destinationSlice;
} _MTL_PACKED;

struct UpdateSparseBufferMappingOperation
{
    MTL::SparseTextureMappingMode mode;
    NS::Range                     bufferRange;
    NS::UInteger                  heapOffset;
} _MTL_PACKED;

struct CopySparseBufferMappingOperation
{
    NS::Range    sourceRange;
    NS::UInteger destinationOffset;
} _MTL_PACKED;

class CommitOptions : public NS::Referencing<CommitOptions>
{
public:
    void                  addFeedbackHandler(const MTL4::CommitFeedbackHandler block);
    void                  addFeedbackHandler(const MTL4::CommitFeedbackHandlerFunction& function);

    static CommitOptions* alloc();

    CommitOptions*        init();
};
class CommandQueueDescriptor : public NS::Copying<CommandQueueDescriptor>
{
public:
    static CommandQueueDescriptor* alloc();

    dispatch_queue_t               feedbackQueue() const;

    CommandQueueDescriptor*        init();

    NS::String*                    label() const;

    void                           setFeedbackQueue(const dispatch_queue_t feedbackQueue);

    void                           setLabel(const NS::String* label);
};
class CommandQueue : public NS::Referencing<CommandQueue>
{
public:
    void         addResidencySet(const MTL::ResidencySet* residencySet);
    void         addResidencySets(const MTL::ResidencySet* const residencySets[], NS::UInteger count);

    void         commit(const MTL4::CommandBuffer* const commandBuffers[], NS::UInteger count);
    void         commit(const MTL4::CommandBuffer* const commandBuffers[], NS::UInteger count, const MTL4::CommitOptions* options);

    void         copyBufferMappingsFromBuffer(const MTL::Buffer* sourceBuffer, const MTL::Buffer* destinationBuffer, const MTL4::CopySparseBufferMappingOperation* operations, NS::UInteger count);

    void         copyTextureMappingsFromTexture(const MTL::Texture* sourceTexture, const MTL::Texture* destinationTexture, const MTL4::CopySparseTextureMappingOperation* operations, NS::UInteger count);

    MTL::Device* device() const;

    NS::String*  label() const;

    void         removeResidencySet(const MTL::ResidencySet* residencySet);
    void         removeResidencySets(const MTL::ResidencySet* const residencySets[], NS::UInteger count);

    void         signalDrawable(const MTL::Drawable* drawable);

    void         signalEvent(const MTL::Event* event, uint64_t value);

    void         updateBufferMappings(const MTL::Buffer* buffer, const MTL::Heap* heap, const MTL4::UpdateSparseBufferMappingOperation* operations, NS::UInteger count);

    void         updateTextureMappings(const MTL::Texture* texture, const MTL::Heap* heap, const MTL4::UpdateSparseTextureMappingOperation* operations, NS::UInteger count);

    void         wait(const MTL::Event* event, uint64_t value);
    void         wait(const MTL::Drawable* drawable);
};

}

/**
 * @brief Registers a feedback handler to be invoked for commit-time notifications.
 *
 * @param block A callback invoked with commit feedback when the associated command buffers are committed.
 */
_MTL_INLINE void MTL4::CommitOptions::addFeedbackHandler(const MTL4::CommitFeedbackHandler block)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(addFeedbackHandler_), block);
}

/**
 * @brief Registers a commit-time feedback handler.
 *
 * Adds the provided callable as a feedback handler that will be invoked with a pointer
 * to a CommitFeedback when commit feedback is produced.
 *
 * @param function Callable that will be called with a `MTL4::CommitFeedback*` argument.
 */
_MTL_INLINE void MTL4::CommitOptions::addFeedbackHandler(const MTL4::CommitFeedbackHandlerFunction& function)
{
    __block MTL4::CommitFeedbackHandlerFunction blockFunction = function;
    addFeedbackHandler(^(MTL4::CommitFeedback* pFeedback) { blockFunction(pFeedback); });
}

/**
 * @brief Allocates a new CommitOptions instance.
 *
 * Allocates memory for a CommitOptions object; the returned object is uninitialized and must be initialized by calling init() before use.
 *
 * @return MTL4::CommitOptions* Pointer to the newly allocated CommitOptions instance.
 */
_MTL_INLINE MTL4::CommitOptions* MTL4::CommitOptions::alloc()
{
    return NS::Object::alloc<MTL4::CommitOptions>(_MTL_PRIVATE_CLS(MTL4CommitOptions));
}

/**
 * @brief Initialize a newly allocated CommitOptions instance.
 *
 * Initializes the object and returns the initialized instance.
 *
 * @return MTL4::CommitOptions* The initialized CommitOptions object, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL4::CommitOptions* MTL4::CommitOptions::init()
{
    return NS::Object::init<MTL4::CommitOptions>();
}

/**
 * @brief Allocate a new CommandQueueDescriptor instance.
 *
 * @return MTL4::CommandQueueDescriptor* A newly allocated, uninitialized CommandQueueDescriptor object; call `init()` before use.
 */
_MTL_INLINE MTL4::CommandQueueDescriptor* MTL4::CommandQueueDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::CommandQueueDescriptor>(_MTL_PRIVATE_CLS(MTL4CommandQueueDescriptor));
}

/**
 * @brief Get the dispatch queue used for commit feedback.
 *
 * @return dispatch_queue_t The dispatch queue on which commit feedback handlers will be invoked, or `nullptr` if no feedback queue is configured.
 */
_MTL_INLINE dispatch_queue_t MTL4::CommandQueueDescriptor::feedbackQueue() const
{
    return Object::sendMessage<dispatch_queue_t>(this, _MTL_PRIVATE_SEL(feedbackQueue));
}

/**
 * @brief Initialize a newly allocated CommandQueueDescriptor to its default state.
 *
 * @return MTL4::CommandQueueDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL4::CommandQueueDescriptor* MTL4::CommandQueueDescriptor::init()
{
    return NS::Object::init<MTL4::CommandQueueDescriptor>();
}

/**
 * @brief Retrieves the human-readable label for this command queue descriptor.
 *
 * @return NS::String* The label string for the command queue descriptor, or `nullptr` if no label has been set.
 */
_MTL_INLINE NS::String* MTL4::CommandQueueDescriptor::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Set the dispatch queue used to deliver commit feedback handlers for this descriptor.
 *
 * @param feedbackQueue The dispatch queue that will be used to invoke commit feedback handlers.
 */
_MTL_INLINE void MTL4::CommandQueueDescriptor::setFeedbackQueue(const dispatch_queue_t feedbackQueue)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFeedbackQueue_), feedbackQueue);
}

/**
 * @brief Sets the human-readable label for the command queue descriptor.
 *
 * @param label The label string to associate with this descriptor.
 */
_MTL_INLINE void MTL4::CommandQueueDescriptor::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Adds a residency set to the command queue.
 *
 * Adds the given residency set so the queue considers the set's resources resident
 * for commands submitted to this queue.
 *
 * @param residencySet Residency set whose resources should be made resident for this queue.
 */
_MTL_INLINE void MTL4::CommandQueue::addResidencySet(const MTL::ResidencySet* residencySet)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(addResidencySet_), residencySet);
}

/**
 * @brief Adds the given residency sets to this command queue.
 *
 * @param residencySets Array of pointers to residency sets to add.
 * @param count Number of residency sets in the `residencySets` array.
 */
_MTL_INLINE void MTL4::CommandQueue::addResidencySets(const MTL::ResidencySet* const residencySets[], NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(addResidencySets_count_), residencySets, count);
}

/**
 * @brief Commits multiple command buffers to this command queue for execution.
 *
 * Commits the command buffers contained in the provided array in order.
 *
 * @param commandBuffers Pointer to an array of command buffer pointers to commit.
 * @param count Number of command buffers in the array.
 */
_MTL_INLINE void MTL4::CommandQueue::commit(const MTL4::CommandBuffer* const commandBuffers[], NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(commit_count_), commandBuffers, count);
}

/**
 * @brief Commits a sequence of command buffers to the command queue using the provided commit options.
 *
 * Commits the given array of command buffers in order to the queue; if `options` is non-null, those
 * commit-time options (such as feedback handlers) are applied to the commit operation.
 *
 * @param commandBuffers Pointer to an array of command buffer pointers to commit.
 * @param count Number of command buffers in `commandBuffers`.
 * @param options Commit options to apply to this commit; may be `nullptr` to use default behavior.
 */
_MTL_INLINE void MTL4::CommandQueue::commit(const MTL4::CommandBuffer* const commandBuffers[], NS::UInteger count, const MTL4::CommitOptions* options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(commit_count_options_), commandBuffers, count, options);
}

/**
 * Copies sparse buffer mappings from a source buffer into a destination buffer.
 *
 * @param sourceBuffer Source buffer whose sparse mappings will be read.
 * @param destinationBuffer Destination buffer whose mappings will be updated.
 * @param operations Pointer to an array of `CopySparseBufferMappingOperation` describing each mapping copy.
 * @param count Number of mapping operations in `operations`.
 */
_MTL_INLINE void MTL4::CommandQueue::copyBufferMappingsFromBuffer(const MTL::Buffer* sourceBuffer, const MTL::Buffer* destinationBuffer, const MTL4::CopySparseBufferMappingOperation* operations, NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyBufferMappingsFromBuffer_toBuffer_operations_count_), sourceBuffer, destinationBuffer, operations, count);
}

/**
 * @brief Copies sparse texture mapping entries from one texture to another.
 *
 * Applies the provided array of sparse texture mapping copy operations, copying mappings from the source texture into the destination texture.
 *
 * @param sourceTexture Source texture whose sparse mappings will be copied.
 * @param destinationTexture Destination texture that will receive the copied mappings.
 * @param operations Pointer to an array of `MTL4::CopySparseTextureMappingOperation` describing regions and levels to copy.
 * @param count Number of operations in the `operations` array.
 */
_MTL_INLINE void MTL4::CommandQueue::copyTextureMappingsFromTexture(const MTL::Texture* sourceTexture, const MTL::Texture* destinationTexture, const MTL4::CopySparseTextureMappingOperation* operations, NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyTextureMappingsFromTexture_toTexture_operations_count_), sourceTexture, destinationTexture, operations, count);
}

/**
 * @brief Retrieve the device associated with this command queue.
 *
 * @return MTL::Device* The device associated with the command queue.
 */
_MTL_INLINE MTL::Device* MTL4::CommandQueue::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Retrieve the label assigned to the command queue.
 *
 * @return NS::String* The command queue's label string, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL4::CommandQueue::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Remove a residency set from the command queue.
 *
 * @param residencySet The residency set to remove from the queue.
 */
_MTL_INLINE void MTL4::CommandQueue::removeResidencySet(const MTL::ResidencySet* residencySet)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(removeResidencySet_), residencySet);
}

/**
 * @brief Remove residency sets from the command queue.
 *
 * Removes the specified residency sets from this command queue so the queue
 * no longer holds residency references for those sets.
 *
 * @param residencySets Array of residency set pointers to remove.
 * @param count Number of residency sets in the `residencySets` array.
 */
_MTL_INLINE void MTL4::CommandQueue::removeResidencySets(const MTL::ResidencySet* const residencySets[], NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(removeResidencySets_count_), residencySets, count);
}

/**
 * @brief Signal the given drawable on the command queue.
 *
 * Notify the command queue that the specified drawable has been signaled,
 * allowing the queue to proceed with operations that depend on that drawable.
 *
 * @param drawable The drawable to signal.
 */
_MTL_INLINE void MTL4::CommandQueue::signalDrawable(const MTL::Drawable* drawable)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(signalDrawable_), drawable);
}

/**
 * @brief Signals the given synchronization event on this command queue with a 64-bit value.
 *
 * @param event The event to signal.
 * @param value The 64-bit value to deliver with the signal.
 */
_MTL_INLINE void MTL4::CommandQueue::signalEvent(const MTL::Event* event, uint64_t value)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(signalEvent_value_), event, value);
}

/**
 * @brief Update sparse mappings for a buffer by applying a sequence of mapping operations.
 *
 * Applies `count` UpdateSparseBufferMappingOperation entries from `operations` to `buffer`,
 * associating mapped ranges with `heap` as the backing storage.
 *
 * @param buffer Target buffer whose sparse mappings will be modified.
 * @param heap Heap used as the backing storage for the mapped ranges.
 * @param operations Pointer to an array of UpdateSparseBufferMappingOperation describing each mapping update.
 * @param count Number of operations in the `operations` array.
 */
_MTL_INLINE void MTL4::CommandQueue::updateBufferMappings(const MTL::Buffer* buffer, const MTL::Heap* heap, const MTL4::UpdateSparseBufferMappingOperation* operations, NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(updateBufferMappings_heap_operations_count_), buffer, heap, operations, count);
}

/**
 * @brief Update sparse texture mappings by binding regions of a texture to offsets in a heap.
 *
 * Applies each mapping described in the `operations` array to `texture`, associating the specified
 * texture regions and levels/slices with heap offsets.
 *
 * @param texture Target texture whose sparse mappings will be updated.
 * @param heap Heap providing memory to satisfy the texture mappings.
 * @param operations Pointer to an array of UpdateSparseTextureMappingOperation structs describing each mapping.
 * @param count Number of entries in the `operations` array.
 */
_MTL_INLINE void MTL4::CommandQueue::updateTextureMappings(const MTL::Texture* texture, const MTL::Heap* heap, const MTL4::UpdateSparseTextureMappingOperation* operations, NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(updateTextureMappings_heap_operations_count_), texture, heap, operations, count);
}

/**
 * @brief Waits for an event to reach a specified signal value before proceeding.
 *
 * @param event The event to wait on.
 * @param value The signal value to wait for; the command queue will wait until the event's value is at least `value`.
 */
_MTL_INLINE void MTL4::CommandQueue::wait(const MTL::Event* event, uint64_t value)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(waitForEvent_value_), event, value);
}

/**
 * @brief Blocks the command queue until the specified drawable is reached.
 *
 * Waits on the command queue for the provided drawable to be signaled/presented, preventing further queue progress until that drawable is ready.
 *
 * @param drawable The drawable to wait for.
 */
_MTL_INLINE void MTL4::CommandQueue::wait(const MTL::Drawable* drawable)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(waitForDrawable_), drawable);
}