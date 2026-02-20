//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4MachineLearningCommandEncoder.hpp
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
#include "MTL4CommandEncoder.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"

namespace MTL4
{
class ArgumentTable;
class MachineLearningPipelineState;
}

namespace MTL
{
class Heap;
}

namespace MTL4
{
class MachineLearningCommandEncoder : public NS::Referencing<MachineLearningCommandEncoder, CommandEncoder>
{
public:
    void dispatchNetwork(const MTL::Heap* heap);

    void setArgumentTable(const MTL4::ArgumentTable* argumentTable);

    void setPipelineState(const MTL4::MachineLearningPipelineState* pipelineState);
};

}
/**
 * @brief Dispatches the configured machine learning network using the provided intermediate heap.
 *
 * Dispatches the encoder's current machine learning pipeline to execute, using the given heap for intermediate resources required by the network.
 *
 * @param heap Pointer to an MTL::Heap that supplies intermediate storage for the dispatched network; may be nullptr if no intermediates are required.
 */
_MTL_INLINE void MTL4::MachineLearningCommandEncoder::dispatchNetwork(const MTL::Heap* heap)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(dispatchNetworkWithIntermediatesHeap_), heap);
}

/**
 * @brief Sets the argument table used by the machine learning command encoder.
 *
 * @param argumentTable Argument table that provides resource bindings for the network dispatch.
 */
_MTL_INLINE void MTL4::MachineLearningCommandEncoder::setArgumentTable(const MTL4::ArgumentTable* argumentTable)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setArgumentTable_), argumentTable);
}

/**
 * @brief Sets the machine learning pipeline state used by this encoder.
 *
 * @param pipelineState Pipeline state that configures the machine learning kernels and their resource/binding layout for subsequent dispatches.
 */
_MTL_INLINE void MTL4::MachineLearningCommandEncoder::setPipelineState(const MTL4::MachineLearningPipelineState* pipelineState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPipelineState_), pipelineState);
}