//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLLinkedFunctions.hpp
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

class LinkedFunctions : public NS::Copying<LinkedFunctions>
{
public:
    static LinkedFunctions* alloc();

    NS::Array*              binaryFunctions() const;
    NS::Array*              functions() const;

    NS::Dictionary*         groups() const;

    LinkedFunctions*        init();

    static LinkedFunctions* linkedFunctions();

    NS::Array*              privateFunctions() const;

    void                    setBinaryFunctions(const NS::Array* binaryFunctions);

    void                    setFunctions(const NS::Array* functions);

    void                    setGroups(const NS::Dictionary* groups);

    void                    setPrivateFunctions(const NS::Array* privateFunctions);
};

}
/**
 * @brief Allocates a new LinkedFunctions instance.
 *
 * Allocates and returns a LinkedFunctions object backed by the private MTLLinkedFunctions class.
 *
 * @return MTL::LinkedFunctions* Pointer to the newly allocated LinkedFunctions instance.
 */
_MTL_INLINE MTL::LinkedFunctions* MTL::LinkedFunctions::alloc()
{
    return NS::Object::alloc<MTL::LinkedFunctions>(_MTL_PRIVATE_CLS(MTLLinkedFunctions));
}

/**
 * @brief Retrieves the array of binary functions associated with this LinkedFunctions object.
 *
 * @return NS::Array* Array containing the binary functions, or `nullptr` if no binary functions are set.
 */
_MTL_INLINE NS::Array* MTL::LinkedFunctions::binaryFunctions() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(binaryFunctions));
}

/**
 * @brief Returns the array of functions associated with this LinkedFunctions object.
 *
 * @return NS::Array* Array containing the linked functions for this object; may be `nullptr` if no functions are present.
 */
_MTL_INLINE NS::Array* MTL::LinkedFunctions::functions() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(functions));
}

/**
 * @brief Returns the dictionary of function groups associated with this LinkedFunctions object.
 *
 * @return NS::Dictionary* Dictionary mapping group identifiers to their corresponding function collections.
 */
_MTL_INLINE NS::Dictionary* MTL::LinkedFunctions::groups() const
{
    return Object::sendMessage<NS::Dictionary*>(this, _MTL_PRIVATE_SEL(groups));
}

/**
 * @brief Initializes the LinkedFunctions instance.
 *
 * @return MTL::LinkedFunctions* The initialized object, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::LinkedFunctions* MTL::LinkedFunctions::init()
{
    return NS::Object::init<MTL::LinkedFunctions>();
}

/**
 * @brief Retrieves the platform's shared LinkedFunctions instance.
 *
 * @return MTL::LinkedFunctions* Pointer to a LinkedFunctions object, or `nullptr` if unavailable.
 */
_MTL_INLINE MTL::LinkedFunctions* MTL::LinkedFunctions::linkedFunctions()
{
    return Object::sendMessage<MTL::LinkedFunctions*>(_MTL_PRIVATE_CLS(MTLLinkedFunctions), _MTL_PRIVATE_SEL(linkedFunctions));
}

/**
 * @brief Accesses the array of private functions associated with this LinkedFunctions object.
 *
 * @return NS::Array* Pointer to an NSArray containing the private functions, or `nullptr` if none is set.
 */
_MTL_INLINE NS::Array* MTL::LinkedFunctions::privateFunctions() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(privateFunctions));
}

/**
 * @brief Assigns the collection of binary functions for this LinkedFunctions instance.
 *
 * @param binaryFunctions Array of binary function objects to associate with the linked functions; may be `nullptr` to clear the collection.
 */
_MTL_INLINE void MTL::LinkedFunctions::setBinaryFunctions(const NS::Array* binaryFunctions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBinaryFunctions_), binaryFunctions);
}

/**
 * @brief Sets the functions collection for this LinkedFunctions instance.
 *
 * @param functions An NSArray of function objects to associate with the linked functions.
 */
_MTL_INLINE void MTL::LinkedFunctions::setFunctions(const NS::Array* functions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFunctions_), functions);
}

/**
 * @brief Assigns the groups dictionary for this LinkedFunctions instance.
 *
 * @param groups Dictionary that maps group identifiers to their associated function group information.
 */
_MTL_INLINE void MTL::LinkedFunctions::setGroups(const NS::Dictionary* groups)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setGroups_), groups);
}

/**
 * @brief Sets the private functions array for this LinkedFunctions object.
 *
 * @param privateFunctions Array of function entries to assign as the private functions collection.
 */
_MTL_INLINE void MTL::LinkedFunctions::setPrivateFunctions(const NS::Array* privateFunctions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPrivateFunctions_), privateFunctions);
}