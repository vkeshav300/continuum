//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLCommandBuffer.hpp
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
#include <CoreFoundation/CoreFoundation.h>
#include <cstdint>

#include <functional>

namespace MTL
{
class AccelerationStructureCommandEncoder;
class AccelerationStructurePassDescriptor;
class BlitCommandEncoder;
class BlitPassDescriptor;
class CommandBuffer;
class CommandBufferDescriptor;
class CommandQueue;
class ComputeCommandEncoder;
class ComputePassDescriptor;
class Device;
class Drawable;
class Event;
class LogContainer;
class LogState;
class ParallelRenderCommandEncoder;
class RenderCommandEncoder;
class RenderPassDescriptor;
class ResidencySet;
class ResourceStateCommandEncoder;
class ResourceStatePassDescriptor;
_MTL_ENUM(NS::UInteger, CommandBufferStatus) {
    CommandBufferStatusNotEnqueued = 0,
    CommandBufferStatusEnqueued = 1,
    CommandBufferStatusCommitted = 2,
    CommandBufferStatusScheduled = 3,
    CommandBufferStatusCompleted = 4,
    CommandBufferStatusError = 5,
};

_MTL_ENUM(NS::UInteger, CommandBufferError) {
    CommandBufferErrorNone = 0,
    CommandBufferErrorInternal = 1,
    CommandBufferErrorTimeout = 2,
    CommandBufferErrorPageFault = 3,
    CommandBufferErrorBlacklisted = 4,
    CommandBufferErrorAccessRevoked = 4,
    CommandBufferErrorNotPermitted = 7,
    CommandBufferErrorOutOfMemory = 8,
    CommandBufferErrorInvalidResource = 9,
    CommandBufferErrorMemoryless = 10,
    CommandBufferErrorDeviceRemoved = 11,
    CommandBufferErrorStackOverflow = 12,
};

_MTL_ENUM(NS::Integer, CommandEncoderErrorState) {
    CommandEncoderErrorStateUnknown = 0,
    CommandEncoderErrorStateCompleted = 1,
    CommandEncoderErrorStateAffected = 2,
    CommandEncoderErrorStatePending = 3,
    CommandEncoderErrorStateFaulted = 4,
};

_MTL_ENUM(NS::UInteger, DispatchType) {
    DispatchTypeSerial = 0,
    DispatchTypeConcurrent = 1,
};

/**
 * @brief Options controlling which command buffer errors are reported.
 *
 * @note Values can be combined as bitflags.
 */

/**
 * @brief Type alias for a completion/scheduled block handler receiving a CommandBuffer.
 */

/**
 * @brief Type alias for a completion/scheduled std::function receiving a CommandBuffer.
 */

/**
 * @brief Allocate a new CommandBufferDescriptor.
 *
 * @return CommandBufferDescriptor* Newly allocated descriptor (uninitialized).
 */

/**
 * @brief The configured error reporting options for this descriptor.
 *
 * @return CommandBufferErrorOption Current error reporting flags.
 */

/**
 * @brief Initialize a newly allocated CommandBufferDescriptor.
 *
 * @return CommandBufferDescriptor* Initialized descriptor instance.
 */

/**
 * @brief The LogState associated with this descriptor, if any.
 *
 * @return LogState* Pointer to the associated LogState, or nullptr if none.
 */

/**
 * @brief Whether the descriptor requests retained (strong) references for resources.
 *
 * @return bool `true` if retained references are enabled, `false` otherwise.
 */

/**
 * @brief Set which error reporting options this descriptor should use.
 *
 * @param errorOptions Error reporting flags to apply.
 */

/**
 * @brief Assign a LogState to the descriptor.
 *
 * @param logState Pointer to the LogState to associate; may be nullptr to clear.
 */

/**
 * @brief Enable or disable retained (strong) references for resources created with this descriptor.
 *
 * @param retainedReferences `true` to enable retained references, `false` to disable.
 */

/**
 * @brief Retrieve debug signposts recorded for this encoder info.
 *
 * @return NS::Array* Array of debug signpost entries, or nullptr if none.
 */

/**
 * @brief The encoder's reported error state.
 *
 * @return CommandEncoderErrorState Current error state of the encoder.
 */

/**
 * @brief Optional human-readable label for this encoder info.
 *
 * @return NS::String* Label string, or nullptr if not set.
 */

/**
 * @brief GPU end time recorded for this command buffer.
 *
 * @return CFTimeInterval Timestamp when GPU work for this buffer finished.
 */

/**
 * @brief GPU start time recorded for this command buffer.
 *
 * @return CFTimeInterval Timestamp when GPU work for this buffer began.
 */

/**
 * @brief Create an acceleration-structure command encoder for this command buffer.
 *
 * @return AccelerationStructureCommandEncoder* New encoder instance, or nullptr on failure.
 */

/**
 * @brief Create an acceleration-structure command encoder configured with a pass descriptor.
 *
 * @param descriptor Descriptor configuring the acceleration-structure pass.
 * @return AccelerationStructureCommandEncoder* New encoder instance, or nullptr on failure.
 */

/**
 * @brief Register a block to be called when the command buffer completes.
 *
 * @param block Block invoked with the command buffer when it completes; may be nullptr.
 */

/**
 * @brief Register a std::function to be called when the command buffer completes.
 *
 * @param function Function invoked with the command buffer when it completes.
 */

/**
 * @brief Register a block to be called when the command buffer is scheduled.
 *
 * @param block Block invoked with the command buffer when it is scheduled; may be nullptr.
 */

/**
 * @brief Register a std::function to be called when the command buffer is scheduled.
 *
 * @param function Function invoked with the command buffer when it is scheduled.
 */

/**
 * @brief Create a blit command encoder for this command buffer.
 *
 * @return BlitCommandEncoder* New blit encoder instance, or nullptr on failure.
 */

/**
 * @brief Create a blit command encoder configured with a blit pass descriptor.
 *
 * @param blitPassDescriptor Descriptor configuring the blit pass.
 * @return BlitCommandEncoder* New blit encoder instance, or nullptr on failure.
 */

/**
 * @brief The command queue that submitted this command buffer.
 *
 * @return CommandQueue* Associated CommandQueue, or nullptr if unavailable.
 */

/**
 * @brief Submit the command buffer for execution.
 */

/**
 * @brief Create a compute command encoder configured with a compute pass descriptor.
 *
 * @param computePassDescriptor Descriptor configuring the compute pass.
 * @return ComputeCommandEncoder* New compute encoder instance, or nullptr on failure.
 */

/**
 * @brief Create a default compute command encoder for this command buffer.
 *
 * @return ComputeCommandEncoder* New compute encoder instance, or nullptr on failure.
 */

/**
 * @brief Create a compute command encoder with a specified dispatch type.
 *
 * @param dispatchType DispatchType specifying serial or concurrent dispatch behavior.
 * @return ComputeCommandEncoder* New compute encoder instance, or nullptr on failure.
 */

/**
 * @brief The device that created this command buffer.
 *
 * @return Device* Associated Device, or nullptr if unavailable.
 */

/**
 * @brief Encode a signal to an event with the given value.
 *
 * @param event The Event to signal.
 * @param value The value to signal into the event.
 */

/**
 * @brief Encode a wait on an event until it reaches the specified value.
 *
 * @param event The Event to wait on.
 * @param value The value to wait for.
 */

/**
 * @brief Enqueue the command buffer for scheduling.
 */

/**
 * @brief Error describing a failure that occurred while executing the command buffer, if any.
 *
 * @return NS::Error* Error object describing the failure, or nullptr if none.
 */

/**
 * @brief The error reporting options currently set on this command buffer.
 *
 * @return CommandBufferErrorOption Current error reporting flags.
 */

/**
 * @brief Kernel end time recorded for this command buffer.
 *
 * @return CFTimeInterval Timestamp when kernel execution finished.
 */

/**
 * @brief Kernel start time recorded for this command buffer.
 *
 * @return CFTimeInterval Timestamp when kernel execution began.
 */

/**
 * @brief Human-readable label for the command buffer.
 *
 * @return NS::String* Label string, or nullptr if not set.
 */

/**
 * @brief Container of logs associated with this command buffer.
 *
 * @return LogContainer* LogContainer instance, or nullptr if none.
 */

/**
 * @brief Create a parallel render command encoder configured with a render pass descriptor.
 *
 * @param renderPassDescriptor Descriptor configuring the render pass.
 * @return ParallelRenderCommandEncoder* New parallel render encoder instance, or nullptr on failure.
 */

/**
 * @brief End the current debug group previously started with pushDebugGroup.
 */

/**
 * @brief Present a drawable on the next drawable-present event.
 *
 * @param drawable The drawable to present.
 */

/**
 * @brief Present a drawable after at least the specified duration has elapsed.
 *
 * @param drawable The drawable to present.
 * @param duration Minimum duration to wait before presenting, in seconds.
 */

/**
 * @brief Schedule presentation of a drawable at the specified presentation time.
 *
 * @param drawable The drawable to present.
 * @param presentationTime Absolute time (CFTimeInterval) to present the drawable.
 */

/**
 * @brief Begin a new debug group with the given label.
 *
 * @param string Label for the debug group.
 */

/**
 * @brief Create a render command encoder configured with a render pass descriptor.
 *
 * @param renderPassDescriptor Descriptor configuring the render pass.
 * @return RenderCommandEncoder* New render encoder instance, or nullptr on failure.
 */

/**
 * @brief Create a resource-state command encoder for this command buffer.
 *
 * @return ResourceStateCommandEncoder* New resource state encoder instance, or nullptr on failure.
 */

/**
 * @brief Create a resource-state command encoder configured with a resource state pass descriptor.
 *
 * @param resourceStatePassDescriptor Descriptor configuring the resource state pass.
 * @return ResourceStateCommandEncoder* New resource state encoder instance, or nullptr on failure.
 */

/**
 * @brief Whether this command buffer holds retained (strong) references to resources.
 *
 * @return bool `true` if retained references are enabled, `false` otherwise.
 */

/**
 * @brief Set a human-readable label for the command buffer.
 *
 * @param label Label string to assign; may be nullptr to clear.
 */

/**
 * @brief Current status of the command buffer.
 *
 * @return CommandBufferStatus Current lifecycle status.
 */

/**
 * @brief Make the command buffer use the provided residency set for resource residency tracking.
 *
 * @param residencySet The ResidencySet to use.
 */

/**
 * @brief Make the command buffer use multiple residency sets.
 *
 * @param residencySets Array of ResidencySet pointers to use.
 * @param count Number of residency sets in the array.
 */

/**
 * @brief Block until the command buffer has finished execution.
 */

/**
 * @brief Block until the command buffer has been scheduled for execution.
 */
_MTL_OPTIONS(NS::UInteger, CommandBufferErrorOption) {
    CommandBufferErrorOptionNone = 0,
    CommandBufferErrorOptionEncoderExecutionStatus = 1,
};

using CommandBufferHandler = void (^)(CommandBuffer*);
using HandlerFunction = std::function<void(CommandBuffer*)>;

class CommandBufferDescriptor : public NS::Copying<CommandBufferDescriptor>
{
public:
    static CommandBufferDescriptor* alloc();

    CommandBufferErrorOption        errorOptions() const;

    CommandBufferDescriptor*        init();

    LogState*                       logState() const;

    bool                            retainedReferences() const;

    void                            setErrorOptions(MTL::CommandBufferErrorOption errorOptions);

    void                            setLogState(const MTL::LogState* logState);

    void                            setRetainedReferences(bool retainedReferences);
};
class CommandBufferEncoderInfo : public NS::Referencing<CommandBufferEncoderInfo>
{
public:
    NS::Array*               debugSignposts() const;

    CommandEncoderErrorState errorState() const;

    NS::String*              label() const;
};
class CommandBuffer : public NS::Referencing<CommandBuffer>
{
public:
    CFTimeInterval                       GPUEndTime() const;

    CFTimeInterval                       GPUStartTime() const;

    AccelerationStructureCommandEncoder* accelerationStructureCommandEncoder();
    AccelerationStructureCommandEncoder* accelerationStructureCommandEncoder(const MTL::AccelerationStructurePassDescriptor* descriptor);

    void                                 addCompletedHandler(const MTL::CommandBufferHandler block);
    void                                 addCompletedHandler(const MTL::HandlerFunction& function);

    void                                 addScheduledHandler(const MTL::CommandBufferHandler block);
    void                                 addScheduledHandler(const MTL::HandlerFunction& function);

    BlitCommandEncoder*                  blitCommandEncoder();
    BlitCommandEncoder*                  blitCommandEncoder(const MTL::BlitPassDescriptor* blitPassDescriptor);

    CommandQueue*                        commandQueue() const;

    void                                 commit();

    ComputeCommandEncoder*               computeCommandEncoder(const MTL::ComputePassDescriptor* computePassDescriptor);
    ComputeCommandEncoder*               computeCommandEncoder();
    ComputeCommandEncoder*               computeCommandEncoder(MTL::DispatchType dispatchType);

    Device*                              device() const;

    void                                 encodeSignalEvent(const MTL::Event* event, uint64_t value);

    void                                 encodeWait(const MTL::Event* event, uint64_t value);

    void                                 enqueue();

    NS::Error*                           error() const;
    CommandBufferErrorOption             errorOptions() const;

    CFTimeInterval                       kernelEndTime() const;

    CFTimeInterval                       kernelStartTime() const;

    NS::String*                          label() const;

    LogContainer*                        logs() const;

    ParallelRenderCommandEncoder*        parallelRenderCommandEncoder(const MTL::RenderPassDescriptor* renderPassDescriptor);

    void                                 popDebugGroup();

    void                                 presentDrawable(const MTL::Drawable* drawable);
    void                                 presentDrawableAfterMinimumDuration(const MTL::Drawable* drawable, CFTimeInterval duration);

    void                                 presentDrawableAtTime(const MTL::Drawable* drawable, CFTimeInterval presentationTime);

    void                                 pushDebugGroup(const NS::String* string);

    RenderCommandEncoder*                renderCommandEncoder(const MTL::RenderPassDescriptor* renderPassDescriptor);

    ResourceStateCommandEncoder*         resourceStateCommandEncoder();
    ResourceStateCommandEncoder*         resourceStateCommandEncoder(const MTL::ResourceStatePassDescriptor* resourceStatePassDescriptor);

    bool                                 retainedReferences() const;

    void                                 setLabel(const NS::String* label);

    CommandBufferStatus                  status() const;

    void                                 useResidencySet(const MTL::ResidencySet* residencySet);
    void                                 useResidencySets(const MTL::ResidencySet* const residencySets[], NS::UInteger count);

    void                                 waitUntilCompleted();

    void                                 waitUntilScheduled();
};

}
/**
 * @brief Allocate a new CommandBufferDescriptor instance.
 *
 * The returned object is allocated but not initialized; call init() on the result before use.
 *
 * @return CommandBufferDescriptor* A newly allocated, uninitialized CommandBufferDescriptor instance.
 */
_MTL_INLINE MTL::CommandBufferDescriptor* MTL::CommandBufferDescriptor::alloc()
{
    return NS::Object::alloc<MTL::CommandBufferDescriptor>(_MTL_PRIVATE_CLS(MTLCommandBufferDescriptor));
}

/**
 * @brief Retrieves the error reporting options configured for this command buffer descriptor.
 *
 * @return MTL::CommandBufferErrorOption Bitmask indicating which error reporting options are enabled.
 */
_MTL_INLINE MTL::CommandBufferErrorOption MTL::CommandBufferDescriptor::errorOptions() const
{
    return Object::sendMessage<MTL::CommandBufferErrorOption>(this, _MTL_PRIVATE_SEL(errorOptions));
}

/**
 * @brief Initialize a newly allocated CommandBufferDescriptor.
 *
 * Prepares the descriptor instance for use after allocation.
 *
 * @return MTL::CommandBufferDescriptor* The initialized descriptor instance, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::CommandBufferDescriptor* MTL::CommandBufferDescriptor::init()
{
    return NS::Object::init<MTL::CommandBufferDescriptor>();
}

/**
 * @brief Retrieves the log state associated with this command buffer descriptor.
 *
 * @return MTL::LogState* Pointer to the associated LogState, or `nullptr` if no log state is set.
 */
_MTL_INLINE MTL::LogState* MTL::CommandBufferDescriptor::logState() const
{
    return Object::sendMessage<MTL::LogState*>(this, _MTL_PRIVATE_SEL(logState));
}

/**
 * @brief Indicates whether command buffers created from this descriptor retain object references.
 *
 * When enabled, command buffers created with this descriptor keep strong references to resources
 * they reference for the duration of their lifetime.
 *
 * @return `true` if retained references are enabled, `false` otherwise.
 */
_MTL_INLINE bool MTL::CommandBufferDescriptor::retainedReferences() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(retainedReferences));
}

/**
 * @brief Configure which error reporting options will be applied to command buffers created from this descriptor.
 *
 * Sets the CommandBufferErrorOption flags that control how errors are reported for command buffers instantiated with this descriptor.
 *
 * @param errorOptions Bitmask of CommandBufferErrorOption values specifying the desired error reporting behavior.
 */
_MTL_INLINE void MTL::CommandBufferDescriptor::setErrorOptions(MTL::CommandBufferErrorOption errorOptions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setErrorOptions_), errorOptions);
}

/**
 * @brief Associates a LogState with this command buffer descriptor.
 *
 * @param logState Pointer to the LogState to assign; pass `nullptr` to clear the descriptor's log state.
 */
_MTL_INLINE void MTL::CommandBufferDescriptor::setLogState(const MTL::LogState* logState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLogState_), logState);
}

/**
 * @brief Enable or disable retained (strong) references for resources used by the command buffer.
 *
 * When enabled, the command buffer retains strong references to resources it uses for the
 * duration of the command buffer's lifetime; when disabled, resources may be released earlier
 * according to the system's residency and lifetime management.
 *
 * @param retainedReferences `true` to retain references for the command buffer's lifetime, `false` to allow earlier release.
 */
_MTL_INLINE void MTL::CommandBufferDescriptor::setRetainedReferences(bool retainedReferences)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRetainedReferences_), retainedReferences);
}

/**
 * @brief Provides the debug signposts associated with this encoder.
 *
 * @return NS::Array* An array of debug signposts (typically `NS::String` objects) for the encoder; may be empty.
 */
_MTL_INLINE NS::Array* MTL::CommandBufferEncoderInfo::debugSignposts() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(debugSignposts));
}

/**
 * @brief Retrieves the error state of this command encoder.
 *
 * @return MTL::CommandEncoderErrorState The current encoder error state: `Unknown`, `Completed`, `Affected`, `Pending`, or `Faulted`.
 */
_MTL_INLINE MTL::CommandEncoderErrorState MTL::CommandBufferEncoderInfo::errorState() const
{
    return Object::sendMessage<MTL::CommandEncoderErrorState>(this, _MTL_PRIVATE_SEL(errorState));
}

/**
 * @brief Retrieves the human-readable label associated with this encoder info.
 *
 * @return NS::String* The label string for the encoder info, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::CommandBufferEncoderInfo::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Get the GPU end timestamp for the command buffer.
 *
 * @return CFTimeInterval The GPU time, in seconds, at which the command buffer finished execution.
 */
_MTL_INLINE CFTimeInterval MTL::CommandBuffer::GPUEndTime() const
{
    return Object::sendMessage<CFTimeInterval>(this, _MTL_PRIVATE_SEL(GPUEndTime));
}

/**
 * @brief Query the GPU timestamp at which this command buffer began execution.
 *
 * @return CFTimeInterval GPU start time in seconds representing when the GPU began executing this command buffer.
 */
_MTL_INLINE CFTimeInterval MTL::CommandBuffer::GPUStartTime() const
{
    return Object::sendMessage<CFTimeInterval>(this, _MTL_PRIVATE_SEL(GPUStartTime));
}

/**
 * @brief Creates and returns a command encoder for encoding acceleration-structure commands.
 *
 * @return MTL::AccelerationStructureCommandEncoder* A command encoder configured for acceleration-structure operations, or nullptr if an encoder could not be created.
 */
_MTL_INLINE MTL::AccelerationStructureCommandEncoder* MTL::CommandBuffer::accelerationStructureCommandEncoder()
{
    return Object::sendMessage<MTL::AccelerationStructureCommandEncoder*>(this, _MTL_PRIVATE_SEL(accelerationStructureCommandEncoder));
}

/**
 * @brief Creates an acceleration structure command encoder configured by the given pass descriptor.
 *
 * @param descriptor Descriptor that specifies pass configuration used to create the encoder.
 * @return MTL::AccelerationStructureCommandEncoder* Pointer to an encoder for encoding acceleration-structure commands.
 */
_MTL_INLINE MTL::AccelerationStructureCommandEncoder* MTL::CommandBuffer::accelerationStructureCommandEncoder(const MTL::AccelerationStructurePassDescriptor* descriptor)
{
    return Object::sendMessage<MTL::AccelerationStructureCommandEncoder*>(this, _MTL_PRIVATE_SEL(accelerationStructureCommandEncoderWithDescriptor_), descriptor);
}

/**
 * @brief Registers a handler to be invoked when the command buffer has completed execution.
 *
 * The provided `block` will be called with this CommandBuffer as its argument once the buffer reaches a completed state.
 *
 * @param block Block to execute on completion; receives the completed CommandBuffer.
 */
_MTL_INLINE void MTL::CommandBuffer::addCompletedHandler(const MTL::CommandBufferHandler block)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(addCompletedHandler_), block);
}

/**
 * @brief Registers a completion handler to be invoked when the command buffer finishes.
 *
 * @param function Callable that will be invoked with the completed `MTL::CommandBuffer*`.
 */
_MTL_INLINE void MTL::CommandBuffer::addCompletedHandler(const MTL::HandlerFunction& function)
{
    __block HandlerFunction blockFunction = function;
    addCompletedHandler(^(MTL::CommandBuffer* pCommandBuffer) { blockFunction(pCommandBuffer); });
}

/**
 * @brief Registers a handler to be invoked when the command buffer is scheduled.
 *
 * @param block Block called once the command buffer has been scheduled; receives the scheduled `CommandBuffer*` as its sole argument.
 */
_MTL_INLINE void MTL::CommandBuffer::addScheduledHandler(const MTL::CommandBufferHandler block)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(addScheduledHandler_), block);
}

/**
 * @brief Registers a callback to be invoked when the command buffer is scheduled for execution.
 *
 * The provided `function` will be called with this CommandBuffer as its argument when the buffer transitions
 * to the scheduled state.
 *
 * @param function Callable invoked with the scheduled CommandBuffer.
 */
_MTL_INLINE void MTL::CommandBuffer::addScheduledHandler(const MTL::HandlerFunction& function)
{
    __block HandlerFunction blockFunction = function;
    addScheduledHandler(^(MTL::CommandBuffer* pCommandBuffer) { blockFunction(pCommandBuffer); });
}

/**
 * @brief Creates and returns a blit command encoder for encoding buffer and texture copy/clear operations.
 *
 * @return MTL::BlitCommandEncoder* A blit command encoder associated with this command buffer.
 */
_MTL_INLINE MTL::BlitCommandEncoder* MTL::CommandBuffer::blitCommandEncoder()
{
    return Object::sendMessage<MTL::BlitCommandEncoder*>(this, _MTL_PRIVATE_SEL(blitCommandEncoder));
}

/**
 * @brief Creates a blit command encoder configured with the specified blit pass descriptor.
 *
 * @param blitPassDescriptor Descriptor that configures the returned blit command encoder.
 * @return MTL::BlitCommandEncoder* Pointer to a BlitCommandEncoder configured using `blitPassDescriptor`.
 */
_MTL_INLINE MTL::BlitCommandEncoder* MTL::CommandBuffer::blitCommandEncoder(const MTL::BlitPassDescriptor* blitPassDescriptor)
{
    return Object::sendMessage<MTL::BlitCommandEncoder*>(this, _MTL_PRIVATE_SEL(blitCommandEncoderWithDescriptor_), blitPassDescriptor);
}

/**
 * @brief Obtain the CommandQueue associated with this command buffer.
 *
 * @return MTL::CommandQueue* Pointer to the CommandQueue that created or owns this command buffer, or nullptr if no queue is associated.
 */
_MTL_INLINE MTL::CommandQueue* MTL::CommandBuffer::commandQueue() const
{
    return Object::sendMessage<MTL::CommandQueue*>(this, _MTL_PRIVATE_SEL(commandQueue));
}

/**
 * @brief Submits the command buffer to its associated command queue for execution.
 *
 * After calling commit, the command buffer is scheduled for GPU execution; further modifications to the buffer's recorded commands have no effect on this submission.
 */
_MTL_INLINE void MTL::CommandBuffer::commit()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(commit));
}

/**
 * @brief Create a compute command encoder configured for the given compute pass descriptor.
 *
 * @param computePassDescriptor Descriptor that configures the compute pass used to create the encoder.
 * @return MTL::ComputeCommandEncoder* Compute command encoder configured with the provided descriptor.
 */
_MTL_INLINE MTL::ComputeCommandEncoder* MTL::CommandBuffer::computeCommandEncoder(const MTL::ComputePassDescriptor* computePassDescriptor)
{
    return Object::sendMessage<MTL::ComputeCommandEncoder*>(this, _MTL_PRIVATE_SEL(computeCommandEncoderWithDescriptor_), computePassDescriptor);
}

/**
 * @brief Obtain a compute command encoder for this command buffer.
 *
 * The returned encoder is used to record compute commands that will be submitted with the command buffer.
 *
 * @return MTL::ComputeCommandEncoder* Pointer to a compute command encoder for encoding compute workloads.
 */
_MTL_INLINE MTL::ComputeCommandEncoder* MTL::CommandBuffer::computeCommandEncoder()
{
    return Object::sendMessage<MTL::ComputeCommandEncoder*>(this, _MTL_PRIVATE_SEL(computeCommandEncoder));
}

/**
 * @brief Creates a compute command encoder configured with the given dispatch type.
 *
 * @param dispatchType The dispatch strategy for the encoder (e.g., Serial or Concurrent).
 * @return MTL::ComputeCommandEncoder* A compute command encoder configured to use the specified dispatch type.
 */
_MTL_INLINE MTL::ComputeCommandEncoder* MTL::CommandBuffer::computeCommandEncoder(MTL::DispatchType dispatchType)
{
    return Object::sendMessage<MTL::ComputeCommandEncoder*>(this, _MTL_PRIVATE_SEL(computeCommandEncoderWithDispatchType_), dispatchType);
}

/**
 * @brief Returns the Device associated with this command buffer.
 *
 * @return MTL::Device* Pointer to the MTL::Device that created or is associated with this command buffer.
 */
_MTL_INLINE MTL::Device* MTL::CommandBuffer::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Encode a signal to a GPU event with a specified value.
 *
 * Enqueues a signal operation that will set the given event's payload to the provided 64-bit value
 * when the command buffer reaches that point in execution.
 *
 * @param event The event object to signal.
 * @param value The 64-bit value to write into the event. 
 */
_MTL_INLINE void MTL::CommandBuffer::encodeSignalEvent(const MTL::Event* event, uint64_t value)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(encodeSignalEvent_value_), event, value);
}

/**
 * @brief Encodes a wait operation on an event into this command buffer.
 *
 * The encoded wait stalls execution of commands in this command buffer until the
 * specified event's value is greater than or equal to the provided value.
 *
 * @param event The event to wait on.
 * @param value The target value to wait for on the event.
 */
_MTL_INLINE void MTL::CommandBuffer::encodeWait(const MTL::Event* event, uint64_t value)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(encodeWaitForEvent_value_), event, value);
}

/**
 * @brief Enqueues the command buffer for scheduling on its associated command queue.
 *
 * After calling this, the command buffer becomes eligible to be scheduled for execution by the queue.
 */
_MTL_INLINE void MTL::CommandBuffer::enqueue()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(enqueue));
}

/**
 * @brief Provides the error associated with the command buffer, if one occurred.
 *
 * @return NS::Error* Pointer to an NSError describing the command buffer's failure, or `nullptr` if no error occurred.
 */
_MTL_INLINE NS::Error* MTL::CommandBuffer::error() const
{
    return Object::sendMessage<NS::Error*>(this, _MTL_PRIVATE_SEL(error));
}

/**
 * @brief Query the command buffer's configured error reporting options.
 *
 * Returns the set of CommandBufferErrorOption flags that control which error
 * conditions the command buffer reports.
 *
 * @return MTL::CommandBufferErrorOption The current error-options flags.
 */
_MTL_INLINE MTL::CommandBufferErrorOption MTL::CommandBuffer::errorOptions() const
{
    return Object::sendMessage<MTL::CommandBufferErrorOption>(this, _MTL_PRIVATE_SEL(errorOptions));
}

/**
 * @brief Query the kernel execution end time for this command buffer.
 *
 * @return CFTimeInterval Kernel execution end time, in seconds.
 */
_MTL_INLINE CFTimeInterval MTL::CommandBuffer::kernelEndTime() const
{
    return Object::sendMessage<CFTimeInterval>(this, _MTL_PRIVATE_SEL(kernelEndTime));
}

/**
 * @brief Retrieves the GPU kernel start time for this command buffer.
 *
 * @return CFTimeInterval The timestamp, in seconds, indicating when GPU kernel execution began for the command buffer.
 */
_MTL_INLINE CFTimeInterval MTL::CommandBuffer::kernelStartTime() const
{
    return Object::sendMessage<CFTimeInterval>(this, _MTL_PRIVATE_SEL(kernelStartTime));
}

/**
 * @brief Retrieve the human-readable label for the command buffer.
 *
 * @return NS::String* The label string, or `nullptr` if no label has been set.
 */
_MTL_INLINE NS::String* MTL::CommandBuffer::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Retrieves the log container associated with this command buffer.
 *
 * @return MTL::LogContainer* Pointer to a LogContainer holding logs produced by the command buffer, or `nullptr` if no logs are available.
 */
_MTL_INLINE MTL::LogContainer* MTL::CommandBuffer::logs() const
{
    return Object::sendMessage<MTL::LogContainer*>(this, _MTL_PRIVATE_SEL(logs));
}

/**
 * @brief Creates a parallel render command encoder for the given render pass.
 *
 * Initializes and returns a ParallelRenderCommandEncoder configured using the provided render pass descriptor.
 *
 * @param renderPassDescriptor Descriptor that configures the render pass for the returned encoder.
 * @return MTL::ParallelRenderCommandEncoder* Pointer to a configured parallel render command encoder, or `nullptr` if one could not be created.
 */
_MTL_INLINE MTL::ParallelRenderCommandEncoder* MTL::CommandBuffer::parallelRenderCommandEncoder(const MTL::RenderPassDescriptor* renderPassDescriptor)
{
    return Object::sendMessage<MTL::ParallelRenderCommandEncoder*>(this, _MTL_PRIVATE_SEL(parallelRenderCommandEncoderWithDescriptor_), renderPassDescriptor);
}

/**
 * @brief Ends the most recently pushed debug group on the command buffer.
 *
 * This closes the active debug group started by a previous call to pushDebugGroup(),
 * restoring the previous debug grouping context used for GPU debugging and profiling.
 */
_MTL_INLINE void MTL::CommandBuffer::popDebugGroup()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(popDebugGroup));
}

/**
 * @brief Presents the specified drawable to the display as soon as the command buffer is executed.
 *
 * @param drawable The drawable to present.
 */
_MTL_INLINE void MTL::CommandBuffer::presentDrawable(const MTL::Drawable* drawable)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(presentDrawable_), drawable);
}

/**
 * @brief Schedules presentation of a drawable no earlier than the specified minimum duration.
 *
 * @param drawable The drawable to present.
 * @param duration Minimum time interval, in seconds, to wait before presenting the drawable.
 */
_MTL_INLINE void MTL::CommandBuffer::presentDrawableAfterMinimumDuration(const MTL::Drawable* drawable, CFTimeInterval duration)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(presentDrawable_afterMinimumDuration_), drawable, duration);
}

/**
 * @brief Schedules the specified drawable to be presented at an exact system time.
 *
 * Requests presentation of `drawable` at the provided `presentationTime` (CFTimeInterval, in seconds since the system reference time).
 *
 * @param drawable The drawable to present.
 * @param presentationTime The desired presentation time in seconds since the system reference clock.
 */
_MTL_INLINE void MTL::CommandBuffer::presentDrawableAtTime(const MTL::Drawable* drawable, CFTimeInterval presentationTime)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(presentDrawable_atTime_), drawable, presentationTime);
}

/**
 * @brief Begins a labeled debug group on the command buffer for grouping GPU work and debug markers.
 *
 * The provided string becomes the group's label; subsequent encoded commands are associated with this group
 * until a matching popDebugGroup() is called.
 *
 * @param string Human-readable label for the debug group.
 */
_MTL_INLINE void MTL::CommandBuffer::pushDebugGroup(const NS::String* string)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(pushDebugGroup_), string);
}

/**
 * @brief Creates a render command encoder configured with the given render pass descriptor.
 *
 * @param renderPassDescriptor Descriptor that specifies attachments, load/store actions, and clear values for the render pass.
 * @return MTL::RenderCommandEncoder* Render command encoder for encoding draw and state commands for the specified render pass.
 */
_MTL_INLINE MTL::RenderCommandEncoder* MTL::CommandBuffer::renderCommandEncoder(const MTL::RenderPassDescriptor* renderPassDescriptor)
{
    return Object::sendMessage<MTL::RenderCommandEncoder*>(this, _MTL_PRIVATE_SEL(renderCommandEncoderWithDescriptor_), renderPassDescriptor);
}

/**
 * @brief Creates a command encoder for recording resource state transitions.
 *
 * The returned encoder is used to encode resource state updates and synchronization
 * operations for resources referenced by this command buffer.
 *
 * @return MTL::ResourceStateCommandEncoder* Pointer to a command encoder for encoding resource state transitions.
 */
_MTL_INLINE MTL::ResourceStateCommandEncoder* MTL::CommandBuffer::resourceStateCommandEncoder()
{
    return Object::sendMessage<MTL::ResourceStateCommandEncoder*>(this, _MTL_PRIVATE_SEL(resourceStateCommandEncoder));
}

/**
 * @brief Creates a resource-state command encoder configured using the provided descriptor.
 *
 * @param resourceStatePassDescriptor Descriptor that specifies how the encoder will manage resource state transitions; may be `nullptr` to use default settings.
 * @return MTL::ResourceStateCommandEncoder* An encoder for encoding resource state transitions configured according to the descriptor.
 */
_MTL_INLINE MTL::ResourceStateCommandEncoder* MTL::CommandBuffer::resourceStateCommandEncoder(const MTL::ResourceStatePassDescriptor* resourceStatePassDescriptor)
{
    return Object::sendMessage<MTL::ResourceStateCommandEncoder*>(this, _MTL_PRIVATE_SEL(resourceStateCommandEncoderWithDescriptor_), resourceStatePassDescriptor);
}

/**
 * @brief Indicates whether the command buffer retains references to its encoded resources.
 *
 * @return `true` if retained references are enabled, `false` otherwise.
 */
_MTL_INLINE bool MTL::CommandBuffer::retainedReferences() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(retainedReferences));
}

/**
 * @brief Set a human-readable label for the command buffer.
 *
 * @param label Human-readable label to assign to the command buffer. Passing `nullptr` clears any existing label.
 */
_MTL_INLINE void MTL::CommandBuffer::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Query the current lifecycle status of the command buffer.
 *
 * @return MTL::CommandBufferStatus indicating the command buffer's current lifecycle state:
 * `NotEnqueued`, `Enqueued`, `Committed`, `Scheduled`, `Completed`, or `Error`.
 */
_MTL_INLINE MTL::CommandBufferStatus MTL::CommandBuffer::status() const
{
    return Object::sendMessage<MTL::CommandBufferStatus>(this, _MTL_PRIVATE_SEL(status));
}

/**
 * @brief Registers a residency set so its resources are kept resident for this command buffer.
 *
 * Marks the contents of `residencySet` as required for execution of this command buffer, ensuring
 * those resources are considered for residency management during scheduling and execution.
 *
 * @param residencySet Residency set containing resources that must remain resident while the command buffer executes.
 */
_MTL_INLINE void MTL::CommandBuffer::useResidencySet(const MTL::ResidencySet* residencySet)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(useResidencySet_), residencySet);
}

/**
 * @brief Registers one or more residency sets to be used by the command buffer.
 *
 * Associates the provided residency sets with this command buffer so their resources
 * are considered resident for the duration of the command buffer's execution.
 *
 * @param residencySets Pointer to an array of pointers to ResidencySet objects to use.
 * @param count Number of residency sets in the `residencySets` array.
 */
_MTL_INLINE void MTL::CommandBuffer::useResidencySets(const MTL::ResidencySet* const residencySets[], NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(useResidencySets_count_), residencySets, count);
}

/**
 * @brief Blocks the calling thread until the command buffer has completed execution.
 *
 * Waits synchronously for the command buffer to finish on the GPU or reach a terminal state (completed or error).
 */
_MTL_INLINE void MTL::CommandBuffer::waitUntilCompleted()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(waitUntilCompleted));
}

/**
 * @brief Blocks the calling thread until the command buffer has been scheduled for execution.
 *
 * This call does not wait for GPU execution to complete; it returns once the command buffer is scheduled on a queue.
 */
_MTL_INLINE void MTL::CommandBuffer::waitUntilScheduled()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(waitUntilScheduled));
}