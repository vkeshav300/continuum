//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4MachineLearningPipeline.hpp
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
#include "MTL4PipelineState.hpp"
#include "MTLAllocation.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"

namespace MTL4
{
class FunctionDescriptor;
class MachineLearningPipelineDescriptor;
class MachineLearningPipelineReflection;
}

namespace MTL
{
class Device;
class TensorExtents;
}

namespace MTL4
{
class MachineLearningPipelineDescriptor : public NS::Copying<MachineLearningPipelineDescriptor, PipelineDescriptor>
{
public:
    static MachineLearningPipelineDescriptor* alloc();

    MachineLearningPipelineDescriptor*        init();

    MTL::TensorExtents*                       inputDimensionsAtBufferIndex(NS::Integer bufferIndex);

    NS::String*                               label() const;

    FunctionDescriptor*                       machineLearningFunctionDescriptor() const;

    void                                      reset();

    void                                      setInputDimensions(const MTL::TensorExtents* dimensions, NS::Integer bufferIndex);
    void                                      setInputDimensions(const NS::Array* dimensions, NS::Range range);

    void                                      setLabel(const NS::String* label);

    void                                      setMachineLearningFunctionDescriptor(const MTL4::FunctionDescriptor* machineLearningFunctionDescriptor);
};
class MachineLearningPipelineReflection : public NS::Referencing<MachineLearningPipelineReflection>
{
public:
    static MachineLearningPipelineReflection* alloc();

    NS::Array*                                bindings() const;

    MachineLearningPipelineReflection*        init();
};
class MachineLearningPipelineState : public NS::Referencing<MachineLearningPipelineState, MTL::Allocation>
{
public:
    MTL::Device*                       device() const;

    NS::UInteger                       intermediatesHeapSize() const;

    NS::String*                        label() const;

    MachineLearningPipelineReflection* reflection() const;
};

}
/**
 * @brief Allocates a new MachineLearningPipelineDescriptor instance.
 *
 * @return MTL4::MachineLearningPipelineDescriptor* Pointer to a newly allocated descriptor object that is not yet initialized.
 */
_MTL_INLINE MTL4::MachineLearningPipelineDescriptor* MTL4::MachineLearningPipelineDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::MachineLearningPipelineDescriptor>(_MTL_PRIVATE_CLS(MTL4MachineLearningPipelineDescriptor));
}

/**
 * @brief Initializes a newly allocated MachineLearningPipelineDescriptor.
 *
 * @return MachineLearningPipelineDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL4::MachineLearningPipelineDescriptor* MTL4::MachineLearningPipelineDescriptor::init()
{
    return NS::Object::init<MTL4::MachineLearningPipelineDescriptor>();
}

/**
 * @brief Retrieve the input tensor extents for a specific buffer index.
 *
 * @param bufferIndex Index of the buffer whose input tensor extents are requested.
 * @return MTL::TensorExtents* The input tensor extents associated with the specified buffer index.
 */
_MTL_INLINE MTL::TensorExtents* MTL4::MachineLearningPipelineDescriptor::inputDimensionsAtBufferIndex(NS::Integer bufferIndex)
{
    return Object::sendMessage<MTL::TensorExtents*>(this, _MTL_PRIVATE_SEL(inputDimensionsAtBufferIndex_), bufferIndex);
}

/**
 * @brief Retrieves the descriptor's label.
 *
 * @return NS::String* The label (name) of the pipeline descriptor, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL4::MachineLearningPipelineDescriptor::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Retrieves the machine learning function descriptor associated with this pipeline descriptor.
 *
 * @return MTL4::FunctionDescriptor* The associated FunctionDescriptor, or `nullptr` if no function descriptor is set.
 */
_MTL_INLINE MTL4::FunctionDescriptor* MTL4::MachineLearningPipelineDescriptor::machineLearningFunctionDescriptor() const
{
    return Object::sendMessage<MTL4::FunctionDescriptor*>(this, _MTL_PRIVATE_SEL(machineLearningFunctionDescriptor));
}

/**
 * @brief Reset the descriptor to its default state.
 *
 * Clears any configured properties (such as input dimensions, label, and associated
 * machine learning function descriptor) so the object behaves as newly created.
 */
_MTL_INLINE void MTL4::MachineLearningPipelineDescriptor::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

/**
 * @brief Associate input tensor dimensions with a specific buffer index.
 *
 * Sets the input tensor extents used by the pipeline for the given buffer index.
 *
 * @param dimensions Tensor extents describing the input shape to assign.
 * @param bufferIndex Index of the input buffer to which the dimensions apply.
 */
_MTL_INLINE void MTL4::MachineLearningPipelineDescriptor::setInputDimensions(const MTL::TensorExtents* dimensions, NS::Integer bufferIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInputDimensions_atBufferIndex_), dimensions, bufferIndex);
}

/**
 * @brief Sets input tensor dimensions for a contiguous range of buffer indices.
 *
 * @param dimensions An array of `MTL::TensorExtents` objects specifying the input dimensions to assign.
 * @param range The `NS::Range` of buffer indices to which the provided dimensions array will be applied.
 */
_MTL_INLINE void MTL4::MachineLearningPipelineDescriptor::setInputDimensions(const NS::Array* dimensions, NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInputDimensions_withRange_), dimensions, range);
}

/**
 * @brief Sets the descriptor's label.
 *
 * @param label The label string to assign to this MachineLearningPipelineDescriptor.
 */
_MTL_INLINE void MTL4::MachineLearningPipelineDescriptor::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Associates a FunctionDescriptor with this machine learning pipeline descriptor.
 *
 * @param machineLearningFunctionDescriptor The FunctionDescriptor to associate with the pipeline descriptor (may be `nullptr` to clear the association).
 */
_MTL_INLINE void MTL4::MachineLearningPipelineDescriptor::setMachineLearningFunctionDescriptor(const MTL4::FunctionDescriptor* machineLearningFunctionDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMachineLearningFunctionDescriptor_), machineLearningFunctionDescriptor);
}

/**
 * @brief Allocate a new MachineLearningPipelineReflection instance.
 *
 * @return MTL4::MachineLearningPipelineReflection* Pointer to the newly allocated MachineLearningPipelineReflection object, or `nullptr` if allocation fails.
 */
_MTL_INLINE MTL4::MachineLearningPipelineReflection* MTL4::MachineLearningPipelineReflection::alloc()
{
    return NS::Object::alloc<MTL4::MachineLearningPipelineReflection>(_MTL_PRIVATE_CLS(MTL4MachineLearningPipelineReflection));
}

/**
 * @brief Get the bindings associated with this machine learning pipeline reflection.
 *
 * @return NS::Array* Array of binding descriptors associated with the pipeline reflection.
 */
_MTL_INLINE NS::Array* MTL4::MachineLearningPipelineReflection::bindings() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(bindings));
}

/**
 * @brief Initializes a MachineLearningPipelineReflection instance.
 *
 * @return MTL4::MachineLearningPipelineReflection* Initialized instance, or nullptr if initialization fails.
 */
_MTL_INLINE MTL4::MachineLearningPipelineReflection* MTL4::MachineLearningPipelineReflection::init()
{
    return NS::Object::init<MTL4::MachineLearningPipelineReflection>();
}

/**
 * @brief Retrieves the device associated with this machine learning pipeline state.
 *
 * @return MTL::Device* The MTL device that created or is hosting the pipeline state, or `nullptr` if not available.
 */
_MTL_INLINE MTL::Device* MTL4::MachineLearningPipelineState::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Retrieves the required size, in bytes, of the intermediates heap for this pipeline state.
 *
 * @return NS::UInteger Size in bytes of the intermediates heap.
 */
_MTL_INLINE NS::UInteger MTL4::MachineLearningPipelineState::intermediatesHeapSize() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(intermediatesHeapSize));
}

/**
 * @brief The human-readable label for this pipeline state.
 *
 * @return NS::String* The pipeline state's label string, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL4::MachineLearningPipelineState::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Obtain the machine learning pipeline reflection for this pipeline state.
 *
 * @return MTL4::MachineLearningPipelineReflection* A pointer to the pipeline's reflection object, or `nullptr` if no reflection is available.
 */
_MTL_INLINE MTL4::MachineLearningPipelineReflection* MTL4::MachineLearningPipelineState::reflection() const
{
    return Object::sendMessage<MTL4::MachineLearningPipelineReflection*>(this, _MTL_PRIVATE_SEL(reflection));
}