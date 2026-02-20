//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLDynamicLibrary.hpp
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
/**
 * @brief Error codes that describe failures when working with a Metal dynamic library.
 *
 * Values indicate the specific reason an operation on a DynamicLibrary failed.
 *
 * - DynamicLibraryErrorNone: No error.
 * - DynamicLibraryErrorInvalidFile: The provided file is not a valid dynamic library.
 * - DynamicLibraryErrorCompilationFailure: The library failed to compile.
 * - DynamicLibraryErrorUnresolvedInstallName: The library's install name could not be resolved.
 * - DynamicLibraryErrorDependencyLoadFailure: A dependency of the library failed to load.
 * - DynamicLibraryErrorUnsupported: The operation or format is unsupported.
 */
 
/**
 * @brief Retrieve the Metal device associated with this dynamic library.
 *
 * @return Device* Pointer to the associated Device.
 */

/**
 * @brief Get the install name of the dynamic library.
 *
 * @return NS::String* The dynamic library's install name.
 */

/**
 * @brief Get the user-facing label for the dynamic library.
 *
 * @return NS::String* The label string.
 */

/**
 * @brief Serialize the dynamic library to the given file URL.
 *
 * If serialization fails and an error pointer is provided, the error may be set
 * to describe the failure (see DynamicLibraryError).
 *
 * @param url The destination file URL to write the serialized library to.
 * @param error Optional out-parameter that will be set with an NSError describing the failure.
 * @return bool `true` if serialization succeeded, `false` otherwise.
 */

/**
 * @brief Set the user-facing label for the dynamic library.
 *
 * @param label The new label string to assign to the library.
 */
_MTL_ENUM(NS::UInteger, DynamicLibraryError) {
    DynamicLibraryErrorNone = 0,
    DynamicLibraryErrorInvalidFile = 1,
    DynamicLibraryErrorCompilationFailure = 2,
    DynamicLibraryErrorUnresolvedInstallName = 3,
    DynamicLibraryErrorDependencyLoadFailure = 4,
    DynamicLibraryErrorUnsupported = 5,
};

class DynamicLibrary : public NS::Referencing<DynamicLibrary>
{
public:
    Device*     device() const;

    NS::String* installName() const;

    NS::String* label() const;

    bool        serializeToURL(const NS::URL* url, NS::Error** error);

    void        setLabel(const NS::String* label);
};

}
/**
 * @brief Returns the Device associated with this dynamic library.
 *
 * @return MTL::Device* Pointer to the associated Device, or nullptr if no device is available.
 */
_MTL_INLINE MTL::Device* MTL::DynamicLibrary::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Get the dynamic library's install name.
 *
 * @return NS::String* The install name of the dynamic library, or `nullptr` if not available.
 */
_MTL_INLINE NS::String* MTL::DynamicLibrary::installName() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(installName));
}

/**
 * @brief Gets the user-visible label of the dynamic library.
 *
 * @return NS::String* The label of the dynamic library, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::DynamicLibrary::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Serializes the dynamic library to the specified URL.
 *
 * Attempts to write the dynamic library to the provided destination URL.
 *
 * @param url Destination file URL where the dynamic library will be written.
 * @param error If non-null and serialization fails, populated with an NSError describing the failure.
 * @return bool `true` if serialization succeeded, `false` otherwise.
 */
_MTL_INLINE bool MTL::DynamicLibrary::serializeToURL(const NS::URL* url, NS::Error** error)
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(serializeToURL_error_), url, error);
}

/**
 * @brief Sets the dynamic library's user-visible label.
 *
 * @param label The string to assign as the dynamic library's label.
 */
_MTL_INLINE void MTL::DynamicLibrary::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}