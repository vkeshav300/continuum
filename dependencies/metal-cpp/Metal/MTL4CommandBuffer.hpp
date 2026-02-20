//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4CommandBuffer.hpp
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
#include "MTL4RenderCommandEncoder.hpp"
#include "MTLAccelerationStructureTypes.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"

namespace MTL4
{
class CommandAllocator;
class CommandBufferOptions;
class ComputeCommandEncoder;
class CounterHeap;
class MachineLearningCommandEncoder;
class RenderCommandEncoder;
class RenderPassDescriptor;
}

namespace MTL
{
class Device;
class Fence;
class LogState;
class ResidencySet;
}

namespace MTL4
{
class CommandBufferOptions : public NS::Copying<CommandBufferOptions>
{
public:
    static CommandBufferOptions* alloc();

    CommandBufferOptions*        init();

    MTL::LogState*               logState() const;
    void                         setLogState(const MTL::LogState* logState);
};
class CommandBuffer : public NS::Referencing<CommandBuffer>
{
public:
    void                           beginCommandBuffer(const MTL4::CommandAllocator* allocator);
    void                           beginCommandBuffer(const MTL4::CommandAllocator* allocator, const MTL4::CommandBufferOptions* options);

    ComputeCommandEncoder*         computeCommandEncoder();

    MTL::Device*                   device() const;

    void                           endCommandBuffer();

    NS::String*                    label() const;

    MachineLearningCommandEncoder* machineLearningCommandEncoder();

    void                           popDebugGroup();

    void                           pushDebugGroup(const NS::String* string);

    RenderCommandEncoder*          renderCommandEncoder(const MTL4::RenderPassDescriptor* descriptor);
    RenderCommandEncoder*          renderCommandEncoder(const MTL4::RenderPassDescriptor* descriptor, MTL4::RenderEncoderOptions options);

    void                           resolveCounterHeap(const MTL4::CounterHeap* counterHeap, NS::Range range, const MTL4::BufferRange bufferRange, const MTL::Fence* fenceToWait, const MTL::Fence* fenceToUpdate);

    void                           setLabel(const NS::String* label);

    void                           useResidencySet(const MTL::ResidencySet* residencySet);
    void                           useResidencySets(const MTL::ResidencySet* const residencySets[], NS::UInteger count);

    void                           writeTimestampIntoHeap(const MTL4::CounterHeap* counterHeap, NS::UInteger index);
};

}
/**
 * @brief Allocate a new CommandBufferOptions instance.
 *
 * @return MTL4::CommandBufferOptions* An allocated, uninitialized CommandBufferOptions instance; call `init()` before use.
 */
_MTL_INLINE MTL4::CommandBufferOptions* MTL4::CommandBufferOptions::alloc()
{
    return NS::Object::alloc<MTL4::CommandBufferOptions>(_MTL_PRIVATE_CLS(MTL4CommandBufferOptions));
}

/**
 * @brief Initializes the CommandBufferOptions instance.
 *
 * @return MTL4::CommandBufferOptions* The initialized object, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL4::CommandBufferOptions* MTL4::CommandBufferOptions::init()
{
    return NS::Object::init<MTL4::CommandBufferOptions>();
}

/**
 * @brief Retrieves the log state associated with this CommandBufferOptions.
 *
 * @return MTL::LogState* The current log state object for the options, or `nullptr` if no log state is set.
 */
_MTL_INLINE MTL::LogState* MTL4::CommandBufferOptions::logState() const
{
    return Object::sendMessage<MTL::LogState*>(this, _MTL_PRIVATE_SEL(logState));
}

/**
 * @brief Set the log state for these command buffer options.
 *
 * Sets the LogState used by the command buffer options to control logging behavior.
 *
 * @param logState Pointer to the MTL::LogState to apply; may be `nullptr` to clear the log state.
 */
_MTL_INLINE void MTL4::CommandBufferOptions::setLogState(const MTL::LogState* logState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLogState_), logState);
}

/**
 * @brief Begins recording commands into this command buffer using the specified allocator.
 *
 * @param allocator Command allocator used to allocate resources for commands recorded into the buffer.
 */
_MTL_INLINE void MTL4::CommandBuffer::beginCommandBuffer(const MTL4::CommandAllocator* allocator)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(beginCommandBufferWithAllocator_), allocator);
}

/**
 * @brief Begins recording commands on this command buffer using the specified allocator and options.
 *
 * @param allocator Allocator that supplies memory/resources for command recording.
 * @param options Optional settings that configure how the command buffer is begun; may be null.
 */
_MTL_INLINE void MTL4::CommandBuffer::beginCommandBuffer(const MTL4::CommandAllocator* allocator, const MTL4::CommandBufferOptions* options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(beginCommandBufferWithAllocator_options_), allocator, options);
}

/**
 * @brief Creates a compute command encoder associated with this command buffer.
 *
 * @return MTL4::ComputeCommandEncoder* A compute command encoder for encoding compute commands into this command buffer.
 */
_MTL_INLINE MTL4::ComputeCommandEncoder* MTL4::CommandBuffer::computeCommandEncoder()
{
    return Object::sendMessage<MTL4::ComputeCommandEncoder*>(this, _MTL_PRIVATE_SEL(computeCommandEncoder));
}

/**
 * @brief Provide the MTL device associated with this command buffer.
 *
 * @return MTL::Device* The device that created or manages this command buffer.
 */
_MTL_INLINE MTL::Device* MTL4::CommandBuffer::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Finalizes the command buffer, ending recording of commands.
 *
 * Completes the command buffer's recording state so it can be committed or encoded further by the system.
 */
_MTL_INLINE void MTL4::CommandBuffer::endCommandBuffer()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(endCommandBuffer));
}

/**
 * @brief Retrieves the command buffer's human-readable label.
 *
 * @return NS::String* The label assigned to the command buffer, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL4::CommandBuffer::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Obtain a MachineLearningCommandEncoder for encoding machine-learning commands into this command buffer.
 *
 * @return MTL4::MachineLearningCommandEncoder* Command encoder for machine-learning work, or `nullptr` if an encoder cannot be created.
 */
_MTL_INLINE MTL4::MachineLearningCommandEncoder* MTL4::CommandBuffer::machineLearningCommandEncoder()
{
    return Object::sendMessage<MTL4::MachineLearningCommandEncoder*>(this, _MTL_PRIVATE_SEL(machineLearningCommandEncoder));
}

/**
 * @brief Removes the most recently pushed debug group from the command buffer's debug group stack.
 *
 * This ends the current debug group scope for subsequent commands recorded into the command buffer.
 */
_MTL_INLINE void MTL4::CommandBuffer::popDebugGroup()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(popDebugGroup));
}

/**
 * @brief Pushes a debug group with the given label onto the command buffer's debug stack.
 *
 * @param string Label used to identify the pushed debug group in GPU captures and debugging tools.
 */
_MTL_INLINE void MTL4::CommandBuffer::pushDebugGroup(const NS::String* string)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(pushDebugGroup_), string);
}

/**
 * @brief Creates a render command encoder configured with the provided render pass descriptor.
 *
 * @param descriptor The render pass descriptor that configures the returned encoder.
 * @return MTL4::RenderCommandEncoder* A pointer to the created render command encoder.
 */
_MTL_INLINE MTL4::RenderCommandEncoder* MTL4::CommandBuffer::renderCommandEncoder(const MTL4::RenderPassDescriptor* descriptor)
{
    return Object::sendMessage<MTL4::RenderCommandEncoder*>(this, _MTL_PRIVATE_SEL(renderCommandEncoderWithDescriptor_), descriptor);
}

/**
 * @brief Creates a render command encoder configured for the given render pass descriptor and options.
 *
 * @param descriptor The render pass descriptor that defines attachments and their load/store actions.
 * @param options Options that control encoder creation and behavior.
 * @return MTL4::RenderCommandEncoder* A new render command encoder configured for the specified descriptor and options.
 */
_MTL_INLINE MTL4::RenderCommandEncoder* MTL4::CommandBuffer::renderCommandEncoder(const MTL4::RenderPassDescriptor* descriptor, MTL4::RenderEncoderOptions options)
{
    return Object::sendMessage<MTL4::RenderCommandEncoder*>(this, _MTL_PRIVATE_SEL(renderCommandEncoderWithDescriptor_options_), descriptor, options);
}

/**
 * @brief Resolve a range of counters from a counter heap into a destination buffer range.
 *
 * Resolves counter values stored in the given counter heap over `range` into the specified
 * `bufferRange`. Optionally waits on `fenceToWait` before performing the resolve and updates
 * `fenceToUpdate` after the resolve completes.
 *
 * @param counterHeap Source counter heap containing the counters to resolve.
 * @param range Range of counters within the heap to resolve.
 * @param bufferRange Destination buffer range describing where resolved counter data is written.
 * @param fenceToWait Optional fence that the GPU must wait on before starting the resolve (may be `nullptr`).
 * @param fenceToUpdate Optional fence that will be updated/signaled when the resolve completes (may be `nullptr`).
 */
_MTL_INLINE void MTL4::CommandBuffer::resolveCounterHeap(const MTL4::CounterHeap* counterHeap, NS::Range range, const MTL4::BufferRange bufferRange, const MTL::Fence* fenceToWait, const MTL::Fence* fenceToUpdate)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(resolveCounterHeap_withRange_intoBuffer_waitFence_updateFence_), counterHeap, range, bufferRange, fenceToWait, fenceToUpdate);
}

/**
 * @brief Sets the command buffer's label.
 *
 * Assigns a user-visible label to this command buffer for identification in debugging and profiling tools.
 *
 * @param label The label string to assign to the command buffer.
 */
_MTL_INLINE void MTL4::CommandBuffer::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Registers a residency set with the command buffer.
 *
 * Associates the given residency set with this command buffer so the referenced
 * GPU resources remain resident for the command buffer's execution.
 *
 * @param residencySet Residency set whose resources should be used by this command buffer.
 */
_MTL_INLINE void MTL4::CommandBuffer::useResidencySet(const MTL::ResidencySet* residencySet)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(useResidencySet_), residencySet);
}

/**
 * @brief Registers multiple residency sets with the command buffer for upcoming execution.
 *
 * @param residencySets Array of pointers to residency sets to be used by the command buffer.
 * @param count Number of residency sets in the array.
 */
_MTL_INLINE void MTL4::CommandBuffer::useResidencySets(const MTL::ResidencySet* const residencySets[], NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(useResidencySets_count_), residencySets, count);
}

/**
 * @brief Write a GPU timestamp into the specified counter heap at the given index.
 *
 * Records the command buffer's current timestamp value into `counterHeap` at `index`.
 *
 * @param counterHeap Counter heap that will receive the timestamp.
 * @param index Index within the counter heap to write the timestamp.
 */
_MTL_INLINE void MTL4::CommandBuffer::writeTimestampIntoHeap(const MTL4::CounterHeap* counterHeap, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(writeTimestampIntoHeap_atIndex_), counterHeap, index);
}