//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4BinaryFunctionDescriptor.hpp
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

namespace MTL4
{
class BinaryFunctionDescriptor;
class FunctionDescriptor;

/**
 * @brief Bitflags that configure behavior of a binary function descriptor.
 *
 * BinaryFunctionOptions contains option flags that control binary function
 * behavior and interoperability.
 *
 * - BinaryFunctionOptionNone: No options set.
 * - BinaryFunctionOptionPipelineIndependent: Indicates the binary function is
 *   pipeline-independent.
 */

/**
 * @brief Allocate a new BinaryFunctionDescriptor instance.
 *
 * @return BinaryFunctionDescriptor* A freshly allocated, uninitialized descriptor.
 */

/**
 * @brief Retrieve the associated FunctionDescriptor.
 *
 * @return FunctionDescriptor* The FunctionDescriptor currently associated with this descriptor, or nullptr if none.
 */

/**
 * @brief Initialize the BinaryFunctionDescriptor instance.
 *
 * @return BinaryFunctionDescriptor* The initialized descriptor (typically `this`) or nullptr on failure.
 */

/**
 * @brief Get the descriptor's name.
 *
 * @return NS::String* The name assigned to this descriptor, or nullptr if no name is set.
 */

/**
 * @brief Get the descriptor's option flags.
 *
 * @return BinaryFunctionOptions The currently set BinaryFunctionOptions flags.
 */

/**
 * @brief Set the associated FunctionDescriptor.
 *
 * @param functionDescriptor Pointer to the FunctionDescriptor to associate with this descriptor.
 */

/**
 * @brief Set the descriptor's name.
 *
 * @param name The name to assign to this descriptor.
 */

/**
 * @brief Set the descriptor's option flags.
 *
 * @param options The BinaryFunctionOptions flags to apply to this descriptor.
 */
_MTL_OPTIONS(NS::UInteger, BinaryFunctionOptions) {
    BinaryFunctionOptionNone = 0,
    BinaryFunctionOptionPipelineIndependent = 1 << 1,
};

class BinaryFunctionDescriptor : public NS::Copying<BinaryFunctionDescriptor>
{
public:
    static BinaryFunctionDescriptor* alloc();

    FunctionDescriptor*              functionDescriptor() const;

    BinaryFunctionDescriptor*        init();

    NS::String*                      name() const;

    BinaryFunctionOptions            options() const;

    void                             setFunctionDescriptor(const MTL4::FunctionDescriptor* functionDescriptor);

    void                             setName(const NS::String* name);

    void                             setOptions(MTL4::BinaryFunctionOptions options);
};

}
/**
 * @brief Allocate a new BinaryFunctionDescriptor instance.
 *
 * @return MTL4::BinaryFunctionDescriptor* Newly allocated BinaryFunctionDescriptor instance.
 */
_MTL_INLINE MTL4::BinaryFunctionDescriptor* MTL4::BinaryFunctionDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::BinaryFunctionDescriptor>(_MTL_PRIVATE_CLS(MTL4BinaryFunctionDescriptor));
}

/**
 * @brief Retrieve the FunctionDescriptor associated with this BinaryFunctionDescriptor.
 *
 * @return MTL4::FunctionDescriptor* The associated FunctionDescriptor pointer, or `nullptr` if no descriptor is set.
 */
_MTL_INLINE MTL4::FunctionDescriptor* MTL4::BinaryFunctionDescriptor::functionDescriptor() const
{
    return Object::sendMessage<MTL4::FunctionDescriptor*>(this, _MTL_PRIVATE_SEL(functionDescriptor));
}

/**
 * @brief Initializes a BinaryFunctionDescriptor instance.
 *
 * Performs default initialization for this object and returns the initialized instance.
 *
 * @return MTL4::BinaryFunctionDescriptor* The initialized BinaryFunctionDescriptor.
 */
_MTL_INLINE MTL4::BinaryFunctionDescriptor* MTL4::BinaryFunctionDescriptor::init()
{
    return NS::Object::init<MTL4::BinaryFunctionDescriptor>();
}

/**
 * @brief Retrieves the descriptor's name.
 *
 * @return NS::String* The descriptor's name.
 */
_MTL_INLINE NS::String* MTL4::BinaryFunctionDescriptor::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Retrieves the binary function descriptor's options.
 *
 * The returned value is a bitmask of BinaryFunctionOptions that configures this descriptor.
 *
 * @return MTL4::BinaryFunctionOptions Bitmask containing one or more options (for example `BinaryFunctionOptionNone` or `BinaryFunctionOptionPipelineIndependent`).
 */
_MTL_INLINE MTL4::BinaryFunctionOptions MTL4::BinaryFunctionDescriptor::options() const
{
    return Object::sendMessage<MTL4::BinaryFunctionOptions>(this, _MTL_PRIVATE_SEL(options));
}

/**
 * @brief Associate a FunctionDescriptor with this BinaryFunctionDescriptor.
 *
 * @param functionDescriptor Pointer to the FunctionDescriptor to associate with this descriptor.
 */
_MTL_INLINE void MTL4::BinaryFunctionDescriptor::setFunctionDescriptor(const MTL4::FunctionDescriptor* functionDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFunctionDescriptor_), functionDescriptor);
}

/**
 * @brief Set the descriptor's name.
 *
 * @param name The name to assign to this BinaryFunctionDescriptor.
 */
_MTL_INLINE void MTL4::BinaryFunctionDescriptor::setName(const NS::String* name)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setName_), name);
}

/**
 * @brief Set configuration flags for the binary function descriptor.
 *
 * @param options Bitmask of BinaryFunctionOptions that control descriptor behavior.
 *                For example, `BinaryFunctionOptionPipelineIndependent` marks the
 *                binary function as pipeline-independent.
 */
_MTL_INLINE void MTL4::BinaryFunctionDescriptor::setOptions(MTL4::BinaryFunctionOptions options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOptions_), options);
}