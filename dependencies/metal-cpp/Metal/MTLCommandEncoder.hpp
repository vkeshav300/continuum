//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLCommandEncoder.hpp
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
class Device;

_MTL_OPTIONS(NS::UInteger, ResourceUsage) {
    ResourceUsageRead = 1,
    ResourceUsageWrite = 1 << 1,
    ResourceUsageSample = 1 << 2,
};

_MTL_OPTIONS(NS::UInteger, BarrierScope) {
    BarrierScopeBuffers = 1,
    BarrierScopeTextures = 1 << 1,
    BarrierScopeRenderTargets = 1 << 2,
};

/**
 * @brief Bitflag options identifying pipeline stages for resource and barrier tracking.
 *
 * Individual flags represent discrete GPU pipeline or work stages. Combine flags with bitwise OR to
 * target multiple stages. Use `StageAll` to represent all stages.
 */

/**
 * @brief Request a synchronization barrier after `afterQueueStages` and before `beforeStages`.
 *
 * @param afterQueueStages Pipeline stages after which the barrier will be applied.
 * @param beforeStages Pipeline stages before which the barrier will take effect.
 */

/**
 * @brief Retrieve the device associated with this command encoder.
 *
 * @return Device* Pointer to the associated MTL::Device.
 */

/**
 * @brief End encoding for this command encoder.
 */

/**
 * @brief Insert a debug signpost with the provided text.
 *
 * @param string Text to include in the signpost.
 */

/**
 * @brief Return the label assigned to this command encoder.
 *
 * @return NS::String* The encoder's label, or `nullptr` if no label is set.
 */

/**
 * @brief Pop the most recently pushed debug group.
 */

/**
 * @brief Push a new debug group with the provided text.
 *
 * @param string Text identifying the debug group.
 */

/**
 * @brief Set the label for this command encoder.
 *
 * @param label New label string, or `nullptr` to clear the label.
 */
_MTL_OPTIONS(NS::UInteger, Stages) {
    StageVertex = 1,
    StageFragment = 1 << 1,
    StageTile = 1 << 2,
    StageObject = 1 << 3,
    StageMesh = 1 << 4,
    StageResourceState = 1 << 26,
    StageDispatch = 1 << 27,
    StageBlit = 1 << 28,
    StageAccelerationStructure = 1 << 29,
    StageMachineLearning = 1 << 30,
    StageAll = 9223372036854775807,
};

class CommandEncoder : public NS::Referencing<CommandEncoder>
{
public:
    void        barrierAfterQueueStages(MTL::Stages afterQueueStages, MTL::Stages beforeStages);

    Device*     device() const;

    void        endEncoding();

    void        insertDebugSignpost(const NS::String* string);

    NS::String* label() const;

    void        popDebugGroup();

    void        pushDebugGroup(const NS::String* string);

    void        setLabel(const NS::String* label);
};

}
/**
 * @brief Requests a pipeline barrier that synchronizes resource/state transitions between pipeline stages.
 *
 * Inserts a barrier that takes effect after the specified queue-side stages and before the specified subsequent stages,
 * constraining visibility and ordering of resource accesses between those stage groups.
 *
 * @param afterQueueStages Bitfield of stages after which the barrier is applied.
 * @param beforeStages Bitfield of stages before which the barrier is applied.
 */
_MTL_INLINE void MTL::CommandEncoder::barrierAfterQueueStages(MTL::Stages afterQueueStages, MTL::Stages beforeStages)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(barrierAfterQueueStages_beforeStages_), afterQueueStages, beforeStages);
}

/**
 * @brief Retrieve the device associated with this command encoder.
 *
 * @return MTL::Device* Pointer to the associated device.
 */
_MTL_INLINE MTL::Device* MTL::CommandEncoder::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Ends encoding for this command encoder.
 *
 * Marks the command encoder as finished recording commands; no further commands
 * may be encoded after this call.
 */
_MTL_INLINE void MTL::CommandEncoder::endEncoding()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(endEncoding));
}

/**
 * @brief Inserts a debug signpost into the command encoder's debug stream.
 *
 * @param string Text to associate with the signpost.
 */
_MTL_INLINE void MTL::CommandEncoder::insertDebugSignpost(const NS::String* string)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(insertDebugSignpost_), string);
}

/**
 * @brief Gets the command encoder's label.
 *
 * @return NS::String* Pointer to the label string, or nullptr if no label is set.
 */
_MTL_INLINE NS::String* MTL::CommandEncoder::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Pops the most recently pushed debug group for this command encoder.
 *
 * Removes the current debug group marker so subsequent debug markers revert to the previous group.
 */
_MTL_INLINE void MTL::CommandEncoder::popDebugGroup()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(popDebugGroup));
}

/**
 * @brief Pushes a new debug group onto the command encoder's debug group stack.
 *
 * @param string The label for the debug group; used to group and annotate subsequent encoded commands for debugging and profiling.
 */
_MTL_INLINE void MTL::CommandEncoder::pushDebugGroup(const NS::String* string)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(pushDebugGroup_), string);
}

/**
 * @brief Set the human-readable label for the command encoder.
 *
 * @param label The label to assign to the encoder; may be nullptr to clear the existing label.
 */
_MTL_INLINE void MTL::CommandEncoder::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}