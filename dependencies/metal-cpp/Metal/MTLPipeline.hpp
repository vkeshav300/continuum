//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLPipeline.hpp
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
class PipelineBufferDescriptor;
class PipelineBufferDescriptorArray;
_MTL_ENUM(NS::UInteger, Mutability) {
    MutabilityDefault = 0,
    MutabilityMutable = 1,
    MutabilityImmutable = 2,
};

/**
 * @brief Controls shader validation behavior for pipeline creation and compilation.
 *
 * Values:
 * - `ShaderValidationDefault` — use the system or device default behavior.
 * - `ShaderValidationEnabled` — enable shader validation.
 * - `ShaderValidationDisabled` — disable shader validation.
 */

/**
 * @brief Allocate a new PipelineBufferDescriptor.
 *
 * @return PipelineBufferDescriptor* Newly allocated, uninitialized descriptor object.
 */

/**
 * @brief Initialize a PipelineBufferDescriptor instance.
 *
 * @return PipelineBufferDescriptor* The initialized descriptor, or `nullptr` on failure.
 */

/**
 * @brief Get the buffer mutability setting.
 *
 * @return Mutability The current mutability value.
 */

/**
 * @brief Set the buffer mutability.
 *
 * @param mutability Desired mutability to apply to the descriptor.
 */

/**
 * @brief Allocate a new PipelineBufferDescriptorArray.
 *
 * @return PipelineBufferDescriptorArray* Newly allocated, uninitialized descriptor array object.
 */

/**
 * @brief Initialize a PipelineBufferDescriptorArray instance.
 *
 * @return PipelineBufferDescriptorArray* The initialized descriptor array, or `nullptr` on failure.
 */

/**
 * @brief Retrieve the pipeline buffer descriptor at the specified index.
 *
 * @param bufferIndex Index of the buffer descriptor to retrieve.
 * @return PipelineBufferDescriptor* The descriptor at `bufferIndex`, or `nullptr` if none is set.
 */

/**
 * @brief Assign a pipeline buffer descriptor at the specified index.
 *
 * @param buffer Descriptor to assign; may be `nullptr` to clear the entry.
 * @param bufferIndex Index at which to set the descriptor.
 */
_MTL_ENUM(NS::Integer, ShaderValidation) {
    ShaderValidationDefault = 0,
    ShaderValidationEnabled = 1,
    ShaderValidationDisabled = 2,
};

class PipelineBufferDescriptor : public NS::Copying<PipelineBufferDescriptor>
{
public:
    static PipelineBufferDescriptor* alloc();

    PipelineBufferDescriptor*        init();

    Mutability                       mutability() const;
    void                             setMutability(MTL::Mutability mutability);
};
class PipelineBufferDescriptorArray : public NS::Referencing<PipelineBufferDescriptorArray>
{
public:
    static PipelineBufferDescriptorArray* alloc();

    PipelineBufferDescriptorArray*        init();

    PipelineBufferDescriptor*             object(NS::UInteger bufferIndex);
    void                                  setObject(const MTL::PipelineBufferDescriptor* buffer, NS::UInteger bufferIndex);
};

}
/**
 * @brief Allocate a new PipelineBufferDescriptor instance.
 *
 * The returned object is allocated and should be initialized (for example, by calling init()) before use.
 *
 * @return PipelineBufferDescriptor* Pointer to the newly allocated PipelineBufferDescriptor.
 */
_MTL_INLINE MTL::PipelineBufferDescriptor* MTL::PipelineBufferDescriptor::alloc()
{
    return NS::Object::alloc<MTL::PipelineBufferDescriptor>(_MTL_PRIVATE_CLS(MTLPipelineBufferDescriptor));
}

/**
 * @brief Initialize a newly allocated PipelineBufferDescriptor instance.
 *
 * @return PipelineBufferDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::PipelineBufferDescriptor* MTL::PipelineBufferDescriptor::init()
{
    return NS::Object::init<MTL::PipelineBufferDescriptor>();
}

/**
 * @brief Retrieves the mutability setting of the pipeline buffer descriptor.
 *
 * @return MTL::Mutability The descriptor's mutability: `MutabilityDefault`, `MutabilityMutable`, or `MutabilityImmutable`.
 */
_MTL_INLINE MTL::Mutability MTL::PipelineBufferDescriptor::mutability() const
{
    return Object::sendMessage<MTL::Mutability>(this, _MTL_PRIVATE_SEL(mutability));
}

/**
 * @brief Sets the mutability of the pipeline buffer descriptor.
 *
 * @param mutability The mutability value to assign to this descriptor.
 */
_MTL_INLINE void MTL::PipelineBufferDescriptor::setMutability(MTL::Mutability mutability)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMutability_), mutability);
}

/**
 * @brief Allocates a new PipelineBufferDescriptorArray instance.
 *
 * @return PipelineBufferDescriptorArray* Newly allocated, uninitialized PipelineBufferDescriptorArray.
 */
_MTL_INLINE MTL::PipelineBufferDescriptorArray* MTL::PipelineBufferDescriptorArray::alloc()
{
    return NS::Object::alloc<MTL::PipelineBufferDescriptorArray>(_MTL_PRIVATE_CLS(MTLPipelineBufferDescriptorArray));
}

/**
 * @brief Initializes a PipelineBufferDescriptorArray instance.
 *
 * @return PipelineBufferDescriptorArray* Pointer to the initialized descriptor array, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::PipelineBufferDescriptorArray* MTL::PipelineBufferDescriptorArray::init()
{
    return NS::Object::init<MTL::PipelineBufferDescriptorArray>();
}

/**
 * @brief Accesses the pipeline buffer descriptor at the specified index.
 *
 * @param bufferIndex Index of the buffer descriptor to retrieve.
 * @return MTL::PipelineBufferDescriptor* Pointer to the pipeline buffer descriptor at the given index, or `nullptr` if no descriptor is set at that index.
 */
_MTL_INLINE MTL::PipelineBufferDescriptor* MTL::PipelineBufferDescriptorArray::object(NS::UInteger bufferIndex)
{
    return Object::sendMessage<MTL::PipelineBufferDescriptor*>(this, _MTL_PRIVATE_SEL(objectAtIndexedSubscript_), bufferIndex);
}

/**
 * @brief Sets the pipeline buffer descriptor at the specified index.
 *
 * @param buffer PipelineBufferDescriptor to store at the given index.
 * @param bufferIndex Index at which to set (or replace) the descriptor.
 */
_MTL_INLINE void MTL::PipelineBufferDescriptorArray::setObject(const MTL::PipelineBufferDescriptor* buffer, NS::UInteger bufferIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObject_atIndexedSubscript_), buffer, bufferIndex);
}