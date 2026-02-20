//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLFunctionConstantValues.hpp
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
#include "MTLDataType.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"

namespace MTL
{
class FunctionConstantValues;

class FunctionConstantValues : public NS::Copying<FunctionConstantValues>
{
public:
    static FunctionConstantValues* alloc();

    FunctionConstantValues*        init();

    void                           reset();

    void                           setConstantValue(const void* value, MTL::DataType type, NS::UInteger index);
    void                           setConstantValue(const void* value, MTL::DataType type, const NS::String* name);
    void                           setConstantValues(const void* values, MTL::DataType type, NS::Range range);
};

}
/**
 * @brief Allocate a new FunctionConstantValues instance.
 *
 * Allocates an instance of MTL::FunctionConstantValues backed by the internal
 * MTLFunctionConstantValues class.
 *
 * @return MTL::FunctionConstantValues* Pointer to the newly allocated instance.
 */
_MTL_INLINE MTL::FunctionConstantValues* MTL::FunctionConstantValues::alloc()
{
    return NS::Object::alloc<MTL::FunctionConstantValues>(_MTL_PRIVATE_CLS(MTLFunctionConstantValues));
}

/**
 * @brief Initializes a FunctionConstantValues instance.
 *
 * Initializes the receiver and prepares it for use configuring function constant values.
 *
 * @return FunctionConstantValues* Pointer to the initialized `FunctionConstantValues` instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::FunctionConstantValues* MTL::FunctionConstantValues::init()
{
    return NS::Object::init<MTL::FunctionConstantValues>();
}

/**
 * @brief Clears all function constant values previously set on this object.
 *
 * After calling this method, the receiver contains no user-specified constant
 * values and behaves as if freshly initialized with default constants.
 */
_MTL_INLINE void MTL::FunctionConstantValues::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

/**
 * @brief Sets a function constant value by index.
 *
 * Sets the raw bytes of a function constant identified by its zero-based index, interpreting the provided bytes according to `type`.
 *
 * @param value Pointer to the source bytes for the constant.
 * @param type The MTL::DataType that describes the layout and size of `value`.
 * @param index The zero-based index of the function constant to set.
 */
_MTL_INLINE void MTL::FunctionConstantValues::setConstantValue(const void* value, MTL::DataType type, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setConstantValue_type_atIndex_), value, type, index);
}

/**
 * @brief Sets the value of a function constant identified by name.
 *
 * Assigns the provided raw value to the function constant with the given name using the specified data type.
 *
 * @param value Pointer to the value data; must point to memory representing a value of the specified `type`.
 * @param type  The `MTL::DataType` that describes the type of the value being provided.
 * @param name  The name of the function constant to set.
 */
_MTL_INLINE void MTL::FunctionConstantValues::setConstantValue(const void* value, MTL::DataType type, const NS::String* name)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setConstantValue_type_withName_), value, type, name);
}

/**
 * @brief Sets multiple function constant values for a contiguous range of constant indices.
 *
 * The `values` pointer must refer to an array of elements of the specified `type`, with
 * at least `range.length` elements. The constants are applied starting at `range.location`
 * and cover `range.length` consecutive indices.
 *
 * @param values Pointer to the first element of a contiguous array of constant values.
 * @param type The data type of each value in `values`.
 * @param range The range of constant indices to set; `location` is the start index and
 *              `length` is the number of consecutive constants to set.
 */
_MTL_INLINE void MTL::FunctionConstantValues::setConstantValues(const void* values, MTL::DataType type, NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setConstantValues_type_withRange_), values, type, range);
}