//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4SpecializedFunctionDescriptor.hpp
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
#include "MTL4FunctionDescriptor.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"

namespace MTL4
{
class FunctionDescriptor;
class SpecializedFunctionDescriptor;
}

namespace MTL
{
class FunctionConstantValues;
}

namespace MTL4
{
class SpecializedFunctionDescriptor : public NS::Copying<SpecializedFunctionDescriptor, FunctionDescriptor>
{
public:
    static SpecializedFunctionDescriptor* alloc();

    MTL::FunctionConstantValues*          constantValues() const;

    FunctionDescriptor*                   functionDescriptor() const;

    SpecializedFunctionDescriptor*        init();

    void                                  setConstantValues(const MTL::FunctionConstantValues* constantValues);

    void                                  setFunctionDescriptor(const MTL4::FunctionDescriptor* functionDescriptor);

    void                                  setSpecializedName(const NS::String* specializedName);
    NS::String*                           specializedName() const;
};

}
/**
 * @brief Allocates a new SpecializedFunctionDescriptor.
 *
 * @return MTL4::SpecializedFunctionDescriptor* A newly allocated descriptor, or `nullptr` if allocation fails.
 */
_MTL_INLINE MTL4::SpecializedFunctionDescriptor* MTL4::SpecializedFunctionDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::SpecializedFunctionDescriptor>(_MTL_PRIVATE_CLS(MTL4SpecializedFunctionDescriptor));
}

/**
 * @brief Retrieves the function constant values associated with this specialized descriptor.
 *
 * @return MTL::FunctionConstantValues* The associated `FunctionConstantValues` object, or `nullptr` if none is set.
 */
_MTL_INLINE MTL::FunctionConstantValues* MTL4::SpecializedFunctionDescriptor::constantValues() const
{
    return Object::sendMessage<MTL::FunctionConstantValues*>(this, _MTL_PRIVATE_SEL(constantValues));
}

/**
 * @brief Returns the underlying function descriptor associated with this specialized descriptor.
 *
 * @return MTL4::FunctionDescriptor* Pointer to the associated FunctionDescriptor, or `nullptr` if none is set.
 */
_MTL_INLINE MTL4::FunctionDescriptor* MTL4::SpecializedFunctionDescriptor::functionDescriptor() const
{
    return Object::sendMessage<MTL4::FunctionDescriptor*>(this, _MTL_PRIVATE_SEL(functionDescriptor));
}

/**
 * @brief Initializes the specialized function descriptor instance.
 *
 * Performs the standard NS::Object initialization for the receiver.
 *
 * @return SpecializedFunctionDescriptor* The initialized object, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL4::SpecializedFunctionDescriptor* MTL4::SpecializedFunctionDescriptor::init()
{
    return NS::Object::init<MTL4::SpecializedFunctionDescriptor>();
}

/**
 * @brief Sets the function constant values used to create the specialized function.
 *
 * @param constantValues Pointer to an MTL::FunctionConstantValues to associate with this descriptor.
 */
_MTL_INLINE void MTL4::SpecializedFunctionDescriptor::setConstantValues(const MTL::FunctionConstantValues* constantValues)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setConstantValues_), constantValues);
}

/**
 * @brief Associate a base function descriptor with this specialized descriptor.
 *
 * Associates the provided MTL4::FunctionDescriptor as the underlying (base)
 * function descriptor that this SpecializedFunctionDescriptor specializes.
 *
 * @param functionDescriptor Pointer to the base FunctionDescriptor to associate; may be `nullptr` to clear the association.
 */
_MTL_INLINE void MTL4::SpecializedFunctionDescriptor::setFunctionDescriptor(const MTL4::FunctionDescriptor* functionDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFunctionDescriptor_), functionDescriptor);
}

/**
 * @brief Sets the specialized name used to identify this specialized function descriptor.
 *
 * @param specializedName The name to assign to the specialized function descriptor.
 */
_MTL_INLINE void MTL4::SpecializedFunctionDescriptor::setSpecializedName(const NS::String* specializedName)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSpecializedName_), specializedName);
}

/**
 * @brief Retrieves the descriptor's specialized name.
 *
 * @return NS::String* The specialized name associated with this descriptor, or `nullptr` if no name has been set.
 */
_MTL_INLINE NS::String* MTL4::SpecializedFunctionDescriptor::specializedName() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(specializedName));
}