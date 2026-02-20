//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4CommandEncoder.hpp
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
#include "MTLCommandEncoder.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"

namespace MTL4
{
class CommandBuffer;
}

namespace MTL
{
class Fence;
}

namespace MTL4
{
/**
 * @brief Options that control resource visibility for barrier operations.
 *
 * Use these flags to specify which resources or scopes must be visible
 * when issuing barriers.
 */
_MTL_OPTIONS(NS::UInteger, VisibilityOptions) {
    VisibilityOptionNone = 0,
    VisibilityOptionDevice = 1,
    VisibilityOptionResourceAlias = 1 << 1,
};

class CommandEncoder : public NS::Referencing<CommandEncoder>
{
public:
    void           barrierAfterEncoderStages(MTL::Stages afterEncoderStages, MTL::Stages beforeEncoderStages, MTL4::VisibilityOptions visibilityOptions);

    void           barrierAfterQueueStages(MTL::Stages afterQueueStages, MTL::Stages beforeStages, MTL4::VisibilityOptions visibilityOptions);

    void           barrierAfterStages(MTL::Stages afterStages, MTL::Stages beforeQueueStages, MTL4::VisibilityOptions visibilityOptions);

    CommandBuffer* commandBuffer() const;

    void           endEncoding();

    void           insertDebugSignpost(const NS::String* string);

    NS::String*    label() const;

    void           popDebugGroup();

    void           pushDebugGroup(const NS::String* string);

    void           setLabel(const NS::String* label);

    void           updateFence(const MTL::Fence* fence, MTL::Stages afterEncoderStages);

    void           waitForFence(const MTL::Fence* fence, MTL::Stages beforeEncoderStages);
};

}
/**
 * @brief Issues a resource barrier that takes effect after the specified encoder stages.
 *
 * Ensures that work in `afterEncoderStages` completes before work in `beforeEncoderStages` begins, and applies the provided visibility options to control which resources or devices observe the barrier.
 *
 * @param afterEncoderStages Encoder stages after which the barrier is issued.
 * @param beforeEncoderStages Encoder stages that must wait for the barrier before executing.
 * @param visibilityOptions Controls resource/device visibility for the barrier (e.g., device visibility, resource aliasing).
 */
_MTL_INLINE void MTL4::CommandEncoder::barrierAfterEncoderStages(MTL::Stages afterEncoderStages, MTL::Stages beforeEncoderStages, MTL4::VisibilityOptions visibilityOptions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(barrierAfterEncoderStages_beforeEncoderStages_visibilityOptions_), afterEncoderStages, beforeEncoderStages, visibilityOptions);
}

/**
 * @brief Issues a synchronization barrier placed after specified queue stages and before specified stages with the given visibility options.
 *
 * @param afterQueueStages Queue stages after which the barrier becomes effective.
 * @param beforeStages Stages that must wait for the barrier before executing.
 * @param visibilityOptions Controls resource visibility for the barrier (e.g., device-wide or aliasing visibility).
 */
_MTL_INLINE void MTL4::CommandEncoder::barrierAfterQueueStages(MTL::Stages afterQueueStages, MTL::Stages beforeStages, MTL4::VisibilityOptions visibilityOptions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(barrierAfterQueueStages_beforeStages_visibilityOptions_), afterQueueStages, beforeStages, visibilityOptions);
}

/**
 * @brief Issues a synchronization barrier after the specified encoder stages.
 *
 * Inserts a barrier that ensures work from the given `afterStages` is completed before stages
 * specified by `beforeQueueStages` are executed, with resource visibility controlled by
 * `visibilityOptions`.
 *
 * @param afterStages Encoder stages after which the barrier is applied.
 * @param beforeQueueStages Queue stages that must wait until `afterStages` complete.
 * @param visibilityOptions Controls which resources or devices observe the barrier (e.g., device or resource alias visibility).
 */
_MTL_INLINE void MTL4::CommandEncoder::barrierAfterStages(MTL::Stages afterStages, MTL::Stages beforeQueueStages, MTL4::VisibilityOptions visibilityOptions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(barrierAfterStages_beforeQueueStages_visibilityOptions_), afterStages, beforeQueueStages, visibilityOptions);
}

/**
 * @brief Retrieves the command buffer associated with this encoder.
 *
 * @return MTL4::CommandBuffer* Pointer to the associated command buffer.
 */
_MTL_INLINE MTL4::CommandBuffer* MTL4::CommandEncoder::commandBuffer() const
{
    return Object::sendMessage<MTL4::CommandBuffer*>(this, _MTL_PRIVATE_SEL(commandBuffer));
}

/**
 * @brief Ends encoding on this command encoder.
 *
 * After calling this, no further commands may be encoded with this encoder.
 */
_MTL_INLINE void MTL4::CommandEncoder::endEncoding()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(endEncoding));
}

/**
 * @brief Inserts a debug signpost into the encoder's debug stream.
 *
 * @param string The signpost text to record.
 */
_MTL_INLINE void MTL4::CommandEncoder::insertDebugSignpost(const NS::String* string)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(insertDebugSignpost_), string);
}

/**
 * @brief Retrieves the encoder's label.
 *
 * @return NS::String* Pointer to the encoder's label string; `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL4::CommandEncoder::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Pops the most recently pushed debug group on this command encoder.
 *
 * Removes the active debug group started by a prior pushDebugGroup call so subsequent
 * debug markers are associated with the previous group.
 */
_MTL_INLINE void MTL4::CommandEncoder::popDebugGroup()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(popDebugGroup));
}

/**
 * @brief Pushes a new debug group onto the encoder's debug group stack.
 *
 * The pushed group will be associated with subsequently encoded commands until it is popped.
 *
 * @param string The label text for the debug group.
 */
_MTL_INLINE void MTL4::CommandEncoder::pushDebugGroup(const NS::String* string)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(pushDebugGroup_), string);
}

/**
 * @brief Assigns a human-readable label to this command encoder.
 *
 * @param label Label string to associate with the encoder (used for debugging and profiling).
 */
_MTL_INLINE void MTL4::CommandEncoder::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Signals the provided fence after the specified encoder stages complete.
 *
 * @param fence The fence to update; it will be marked signaled when the given stages finish.
 * @param afterEncoderStages Encoder stages after which the fence will be signaled.
 */
_MTL_INLINE void MTL4::CommandEncoder::updateFence(const MTL::Fence* fence, MTL::Stages afterEncoderStages)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(updateFence_afterEncoderStages_), fence, afterEncoderStages);
}

/**
 * @brief Waits on the provided fence so subsequent work does not begin until the fence is signaled.
 *
 * Blocks progression of the command encoder until `fence` is reached, ensuring that the specified
 * encoder stages in `beforeEncoderStages` do not execute until the fence is signaled.
 *
 * @param fence The fence to wait on.
 * @param beforeEncoderStages Encoder stages that must be stalled until `fence` is signaled.
 */
_MTL_INLINE void MTL4::CommandEncoder::waitForFence(const MTL::Fence* fence, MTL::Stages beforeEncoderStages)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(waitForFence_beforeEncoderStages_), fence, beforeEncoderStages);
}