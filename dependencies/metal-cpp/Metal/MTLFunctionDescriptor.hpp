//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLFunctionDescriptor.hpp
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
class FunctionConstantValues;
class FunctionDescriptor;
class IntersectionFunctionDescriptor;

/**
 * @brief Bitmask options that modify function descriptor behavior.
 *
 * Controls how a function is compiled, stored, and handled with respect to binary archives
 * and pipeline independence.
 */

/**
 * @brief Allocate a new, uninitialized FunctionDescriptor.
 *
 * @return FunctionDescriptor* Newly allocated FunctionDescriptor instance; must be initialized with init().
 */

/**
 * @brief Returns the collection of binary archive references associated with the descriptor.
 *
 * @return NS::Array* Array of binary archive objects used when resolving or compiling the function.
 */

/**
 * @brief Returns the FunctionConstantValues object that specifies specialization constants for the function.
 *
 * @return FunctionConstantValues* The constant values used to specialize the function, or nullptr if none are set.
 */

/**
 * @brief Create and return a new autoreleased FunctionDescriptor instance.
 *
 * @return FunctionDescriptor* A configured FunctionDescriptor instance.
 */

/**
 * @brief Initialize a newly allocated FunctionDescriptor.
 *
 * @return FunctionDescriptor* The initialized descriptor instance.
 */

/**
 * @brief Returns the base name of the function described by this descriptor.
 *
 * @return NS::String* The function name.
 */

/**
 * @brief Returns the configured FunctionOptions bitmask for this descriptor.
 *
 * @return FunctionOptions The bitmask of options affecting compilation and storage behavior.
 */

/**
 * @brief Set the collection of binary archives to consult when resolving or compiling the function.
 *
 * @param binaryArchives Array of binary archive objects to associate with the descriptor.
 */

/**
 * @brief Set the FunctionConstantValues object that provides specialization constants for the function.
 *
 * @param constantValues The constant values to apply when specializing the function.
 */

/**
 * @brief Set the base name of the function described by this descriptor.
 *
 * @param name The function name to assign to the descriptor.
 */

/**
 * @brief Set the FunctionOptions bitmask for this descriptor.
 *
 * @param options Bitmask of options that control compilation and storage behavior.
 */

/**
 * @brief Set the specialized name to identify a specialized variant of the function.
 *
 * @param specializedName The specialized function name.
 */

/**
 * @brief Returns the specialized name for the function, if any.
 *
 * @return NS::String* The specialized function name, or nullptr if not set.
 */

/**
 * @brief Allocate a new, uninitialized IntersectionFunctionDescriptor.
 *
 * @return IntersectionFunctionDescriptor* Newly allocated IntersectionFunctionDescriptor instance; must be initialized with init().
 */

/**
 * @brief Initialize a newly allocated IntersectionFunctionDescriptor.
 *
 * @return IntersectionFunctionDescriptor* The initialized intersection function descriptor instance.
 */
_MTL_OPTIONS(NS::UInteger, FunctionOptions) {
    FunctionOptionNone = 0,
    FunctionOptionCompileToBinary = 1,
    FunctionOptionStoreFunctionInMetalPipelinesScript = 1 << 1,
    FunctionOptionStoreFunctionInMetalScript = 1 << 1,
    FunctionOptionFailOnBinaryArchiveMiss = 1 << 2,
    FunctionOptionPipelineIndependent = 1 << 3,
};

class FunctionDescriptor : public NS::Copying<FunctionDescriptor>
{
public:
    static FunctionDescriptor* alloc();

    NS::Array*                 binaryArchives() const;

    FunctionConstantValues*    constantValues() const;

    static FunctionDescriptor* functionDescriptor();

    FunctionDescriptor*        init();

    NS::String*                name() const;

    FunctionOptions            options() const;

    void                       setBinaryArchives(const NS::Array* binaryArchives);

    void                       setConstantValues(const MTL::FunctionConstantValues* constantValues);

    void                       setName(const NS::String* name);

    void                       setOptions(MTL::FunctionOptions options);

    void                       setSpecializedName(const NS::String* specializedName);
    NS::String*                specializedName() const;
};
class IntersectionFunctionDescriptor : public NS::Copying<IntersectionFunctionDescriptor, FunctionDescriptor>
{
public:
    static IntersectionFunctionDescriptor* alloc();

    IntersectionFunctionDescriptor*        init();
};

}
/**
 * @brief Allocate a new FunctionDescriptor instance.
 *
 * The returned object is a newly allocated FunctionDescriptor; initialize it (for example by calling
 * `init()`) before use.
 *
 * @return FunctionDescriptor* Newly allocated FunctionDescriptor object.
 */
_MTL_INLINE MTL::FunctionDescriptor* MTL::FunctionDescriptor::alloc()
{
    return NS::Object::alloc<MTL::FunctionDescriptor>(_MTL_PRIVATE_CLS(MTLFunctionDescriptor));
}

/**
 * @brief Returns the binary archives associated with this function descriptor.
 *
 * Provides the array of binary archive objects used for the function's compiled binaries.
 *
 * @return NS::Array* Array of binary archives, or `nullptr` if no archives are set.
 */
_MTL_INLINE NS::Array* MTL::FunctionDescriptor::binaryArchives() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(binaryArchives));
}

/**
 * @brief Retrieves the function constant values used to specialize the descriptor.
 *
 * Returns the FunctionConstantValues instance configured for this descriptor, or nullptr if no constant values are set.
 *
 * @return MTL::FunctionConstantValues* The configured function constant values, or `nullptr` when unset.
 */
_MTL_INLINE MTL::FunctionConstantValues* MTL::FunctionDescriptor::constantValues() const
{
    return Object::sendMessage<MTL::FunctionConstantValues*>(this, _MTL_PRIVATE_SEL(constantValues));
}

/**
 * @brief Creates a new FunctionDescriptor instance.
 *
 * @return MTL::FunctionDescriptor* A newly created FunctionDescriptor instance.
 */
_MTL_INLINE MTL::FunctionDescriptor* MTL::FunctionDescriptor::functionDescriptor()
{
    return Object::sendMessage<MTL::FunctionDescriptor*>(_MTL_PRIVATE_CLS(MTLFunctionDescriptor), _MTL_PRIVATE_SEL(functionDescriptor));
}

/**
 * @brief Initialize the FunctionDescriptor instance.
 *
 * @return FunctionDescriptor* Pointer to the initialized FunctionDescriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::FunctionDescriptor* MTL::FunctionDescriptor::init()
{
    return NS::Object::init<MTL::FunctionDescriptor>();
}

/**
 * @brief Obtains the descriptor's function name.
 *
 * @return NS::String* containing the function name, or nullptr if no name is set.
 */
_MTL_INLINE NS::String* MTL::FunctionDescriptor::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Retrieve the option flags configured on this function descriptor.
 *
 * @return MTL::FunctionOptions Bitmask of FunctionOptions currently set on the descriptor.
 */
_MTL_INLINE MTL::FunctionOptions MTL::FunctionDescriptor::options() const
{
    return Object::sendMessage<MTL::FunctionOptions>(this, _MTL_PRIVATE_SEL(options));
}

/**
 * @brief Associate a collection of binary archives with this function descriptor.
 *
 * @param binaryArchives An NSArray of binary archive objects to attach to the descriptor.
 */
_MTL_INLINE void MTL::FunctionDescriptor::setBinaryArchives(const NS::Array* binaryArchives)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBinaryArchives_), binaryArchives);
}

/**
 * @brief Configure the function's compile-time constant values.
 *
 * Associates the provided FunctionConstantValues with this descriptor so the function is created or specialized using those constants.
 *
 * @param constantValues The constant values to apply to the function descriptor (may be nullptr to clear).
 */
_MTL_INLINE void MTL::FunctionDescriptor::setConstantValues(const MTL::FunctionConstantValues* constantValues)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setConstantValues_), constantValues);
}

/**
 * @brief Sets the base name of the function descriptor.
 *
 * @param name The function's base name to identify the shader function; pass `nullptr` to clear the name.
 */
_MTL_INLINE void MTL::FunctionDescriptor::setName(const NS::String* name)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setName_), name);
}

/**
 * @brief Sets the behavior flags for this function descriptor.
 *
 * @param options Bitwise OR of MTL::FunctionOptions flags that control compilation, storage, and pipeline-related behavior for the described function.
 */
_MTL_INLINE void MTL::FunctionDescriptor::setOptions(MTL::FunctionOptions options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOptions_), options);
}

/**
 * @brief Sets the descriptor's specialized function name.
 *
 * Sets the specialized name used to identify a specialized variant of the shader function when creating or looking up compiled or specialized versions.
 *
 * @param specializedName The specialized function name to assign. Pass `nullptr` to clear any previously set specialized name.
 */
_MTL_INLINE void MTL::FunctionDescriptor::setSpecializedName(const NS::String* specializedName)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSpecializedName_), specializedName);
}

/**
 * @brief Get the specialized name associated with this function descriptor.
 *
 * @return NS::String* The specialized name, or `nullptr` if no specialized name is set.
 */
_MTL_INLINE NS::String* MTL::FunctionDescriptor::specializedName() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(specializedName));
}

/**
 * @brief Allocate a new uninitialized IntersectionFunctionDescriptor instance.
 *
 * Creates and returns a raw, uninitialized Objective-C-backed IntersectionFunctionDescriptor
 * object suitable for initialization via `init()`.
 *
 * @return MTL::IntersectionFunctionDescriptor* A newly allocated IntersectionFunctionDescriptor instance.
 */
_MTL_INLINE MTL::IntersectionFunctionDescriptor* MTL::IntersectionFunctionDescriptor::alloc()
{
    return NS::Object::alloc<MTL::IntersectionFunctionDescriptor>(_MTL_PRIVATE_CLS(MTLIntersectionFunctionDescriptor));
}

/**
 * @brief Initialize an IntersectionFunctionDescriptor instance.
 *
 * @return Pointer to the initialized IntersectionFunctionDescriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::IntersectionFunctionDescriptor* MTL::IntersectionFunctionDescriptor::init()
{
    return NS::Object::init<MTL::IntersectionFunctionDescriptor>();
}