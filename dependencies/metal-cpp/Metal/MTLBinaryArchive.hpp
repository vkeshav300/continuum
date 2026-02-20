//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLBinaryArchive.hpp
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
class BinaryArchiveDescriptor;
class ComputePipelineDescriptor;
class Device;
class FunctionDescriptor;
class Library;
class MeshRenderPipelineDescriptor;
class RenderPipelineDescriptor;
class StitchedLibraryDescriptor;
class TileRenderPipelineDescriptor;
/**
 * @brief Error codes for Metal binary archive operations.
 *
 * Represents specific failure cases that can occur while creating,
 * modifying, or serializing a Metal binary archive.
 */

/**
 * @brief Error domain for BinaryArchive errors.
 *
 * Error domain under which `BinaryArchiveError` codes are reported.
 */

/**
 * @brief Descriptor used to configure and create a BinaryArchive.
 */

/**
 * @brief Initialize a newly allocated BinaryArchiveDescriptor.
 *
 * @return BinaryArchiveDescriptor* The initialized descriptor instance.
 */

/**
 * @brief Set the file URL associated with the descriptor.
 *
 * @param url Filesystem URL that identifies where the archive will be read from or written to.
 */

/**
 * @brief Get the file URL associated with the descriptor.
 *
 * @return NS::URL* The configured URL, or `nullptr` if none is set.
 */

/**
 * @brief A container for precompiled Metal functions and pipelines.
 *
 * Provides operations to populate, query, and serialize a Metal binary archive.
 */

/**
 * @brief Add compute pipeline functions described by a descriptor to the archive.
 *
 * @param descriptor Descriptor describing the compute pipeline functions to add.
 * @param error On failure, set to an `NS::Error*` describing the problem.
 * @return bool `true` on success, `false` otherwise.
 */

/**
 * @brief Add a single function to the archive using a function descriptor and its library.
 *
 * @param descriptor Descriptor describing the function to add.
 * @param library Library that provides the function implementation.
 * @param error On failure, set to an `NS::Error*` describing the problem.
 * @return bool `true` on success, `false` otherwise.
 */

/**
 * @brief Add a stitched library to the archive.
 *
 * @param descriptor Descriptor describing the stitched library to add.
 * @param error On failure, set to an `NS::Error*` describing the problem.
 * @return bool `true` on success, `false` otherwise.
 */

/**
 * @brief Add mesh render pipeline functions described by a descriptor to the archive.
 *
 * @param descriptor Descriptor describing the mesh render pipeline functions to add.
 * @param error On failure, set to an `NS::Error*` describing the problem.
 * @return bool `true` on success, `false` otherwise.
 */

/**
 * @brief Add render pipeline functions described by a descriptor to the archive.
 *
 * @param descriptor Descriptor describing the render pipeline functions to add.
 * @param error On failure, set to an `NS::Error*` describing the problem.
 * @return bool `true` on success, `false` otherwise.
 */

/**
 * @brief Add tile render pipeline functions described by a descriptor to the archive.
 *
 * @param descriptor Descriptor describing the tile render pipeline functions to add.
 * @param error On failure, set to an `NS::Error*` describing the problem.
 * @return bool `true` on success, `false` otherwise.
 */

/**
 * @brief Retrieve the device associated with this binary archive.
 *
 * @return Device* The `MTL::Device` used by the archive.
 */

/**
 * @brief Retrieve the human-readable label of the archive.
 *
 * @return NS::String* The archive label, or `nullptr` if none is set.
 */

/**
 * @brief Serialize the binary archive to the specified filesystem URL.
 *
 * @param url Destination URL where the archive will be written.
 * @param error On failure, set to an `NS::Error*` describing the problem.
 * @return bool `true` if serialization succeeded, `false` otherwise.
 */

/**
 * @brief Set a human-readable label for the archive.
 *
 * @param label The label string to associate with the archive.
 */
_MTL_ENUM(NS::UInteger, BinaryArchiveError) {
    BinaryArchiveErrorNone = 0,
    BinaryArchiveErrorInvalidFile = 1,
    BinaryArchiveErrorUnexpectedElement = 2,
    BinaryArchiveErrorCompilationFailure = 3,
    BinaryArchiveErrorInternalError = 4,
};

_MTL_CONST(NS::ErrorDomain, BinaryArchiveDomain);
class BinaryArchiveDescriptor : public NS::Copying<BinaryArchiveDescriptor>
{
public:
    static BinaryArchiveDescriptor* alloc();

    BinaryArchiveDescriptor*        init();

    void                            setUrl(const NS::URL* url);
    NS::URL*                        url() const;
};
class BinaryArchive : public NS::Referencing<BinaryArchive>
{
public:
    bool        addComputePipelineFunctions(const MTL::ComputePipelineDescriptor* descriptor, NS::Error** error);

    bool        addFunction(const MTL::FunctionDescriptor* descriptor, const MTL::Library* library, NS::Error** error);

    bool        addLibrary(const MTL::StitchedLibraryDescriptor* descriptor, NS::Error** error);

    bool        addMeshRenderPipelineFunctions(const MTL::MeshRenderPipelineDescriptor* descriptor, NS::Error** error);

    bool        addRenderPipelineFunctions(const MTL::RenderPipelineDescriptor* descriptor, NS::Error** error);

    bool        addTileRenderPipelineFunctions(const MTL::TileRenderPipelineDescriptor* descriptor, NS::Error** error);

    Device*     device() const;

    NS::String* label() const;

    bool        serializeToURL(const NS::URL* url, NS::Error** error);

    void        setLabel(const NS::String* label);
};

}
_MTL_PRIVATE_DEF_CONST(NS::ErrorDomain, BinaryArchiveDomain);
/**
 * @brief Allocates a new BinaryArchiveDescriptor instance.
 *
 * @return BinaryArchiveDescriptor* Pointer to a newly allocated descriptor. The returned object is uninitialized; call `init()` before using it.
 */
_MTL_INLINE MTL::BinaryArchiveDescriptor* MTL::BinaryArchiveDescriptor::alloc()
{
    return NS::Object::alloc<MTL::BinaryArchiveDescriptor>(_MTL_PRIVATE_CLS(MTLBinaryArchiveDescriptor));
}

/**
 * @brief Initializes a newly allocated BinaryArchiveDescriptor instance.
 *
 * @return MTL::BinaryArchiveDescriptor* The initialized descriptor instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::BinaryArchiveDescriptor* MTL::BinaryArchiveDescriptor::init()
{
    return NS::Object::init<MTL::BinaryArchiveDescriptor>();
}

/**
 * @brief Set the URL associated with this BinaryArchiveDescriptor.
 *
 * @param url The URL to assign to the descriptor.
 */
_MTL_INLINE void MTL::BinaryArchiveDescriptor::setUrl(const NS::URL* url)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setUrl_), url);
}

/**
 * @brief Returns the URL associated with this binary archive descriptor.
 *
 * @return NS::URL* The URL previously set on the descriptor, or nullptr if no URL has been set.
 */
_MTL_INLINE NS::URL* MTL::BinaryArchiveDescriptor::url() const
{
    return Object::sendMessage<NS::URL*>(this, _MTL_PRIVATE_SEL(url));
}

/**
 * @brief Adds compute pipeline functions described by the given descriptor to the binary archive.
 *
 * @param descriptor Descriptor that specifies the compute pipeline functions to add.
 * @param error If the operation fails, set to an NSError describing the failure.
 * @return `true` if the functions were added successfully, `false` otherwise.
 */
_MTL_INLINE bool MTL::BinaryArchive::addComputePipelineFunctions(const MTL::ComputePipelineDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(addComputePipelineFunctionsWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Adds a function described by `descriptor` from `library` into the binary archive.
 *
 * @param descriptor Descriptor that identifies the function to add.
 * @param library Library containing the function implementation.
 * @param error If non-null and the operation fails, set to an NSError describing the failure.
 * @return bool `true` if the function was successfully added to the archive, `false` otherwise.
 */
_MTL_INLINE bool MTL::BinaryArchive::addFunction(const MTL::FunctionDescriptor* descriptor, const MTL::Library* library, NS::Error** error)
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(addFunctionWithDescriptor_library_error_), descriptor, library, error);
}

/**
 * @brief Adds a stitched library to the binary archive.
 *
 * @param descriptor The stitched library descriptor to add to the archive.
 * @param error If non-null and the operation fails, set to an `NS::Error` describing the failure.
 * @return `true` if the library was added successfully, `false` otherwise.
 */
_MTL_INLINE bool MTL::BinaryArchive::addLibrary(const MTL::StitchedLibraryDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(addLibraryWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Adds mesh render pipeline functions described by a descriptor to the binary archive.
 *
 * @param descriptor Descriptor describing the mesh render pipeline functions to add.
 * @param error If non-null and the operation fails, set to an NSError describing the failure.
 * @return `true` if the functions were added successfully, `false` otherwise.
 */
_MTL_INLINE bool MTL::BinaryArchive::addMeshRenderPipelineFunctions(const MTL::MeshRenderPipelineDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(addMeshRenderPipelineFunctionsWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Adds the render pipeline functions described by `descriptor` to this binary archive.
 *
 * @param descriptor Descriptor that specifies the render pipeline functions to add.
 * @param error If non-null and the operation fails, set to an NSError describing the failure.
 * @return `true` if the functions were added successfully, `false` otherwise.
 */
_MTL_INLINE bool MTL::BinaryArchive::addRenderPipelineFunctions(const MTL::RenderPipelineDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(addRenderPipelineFunctionsWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Adds tile render pipeline functions described by the given descriptor to the binary archive.
 *
 * @param descriptor Descriptor specifying the tile render pipeline functions to add.
 * @param error If the operation fails, set to an `NS::Error` describing the failure; may be `nullptr` if the caller does not require error details.
 * @return bool `true` if the functions were added successfully, `false` otherwise.
 */
_MTL_INLINE bool MTL::BinaryArchive::addTileRenderPipelineFunctions(const MTL::TileRenderPipelineDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(addTileRenderPipelineFunctionsWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Get the device associated with this binary archive.
 *
 * @return MTL::Device* The device associated with the archive, or `nullptr` if none is available.
 */
_MTL_INLINE MTL::Device* MTL::BinaryArchive::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Retrieve the label associated with the binary archive.
 *
 * @return NS::String* The archive's label, or nullptr if no label is set.
 */
_MTL_INLINE NS::String* MTL::BinaryArchive::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Serialize the binary archive to the specified file URL.
 *
 * @param url Destination URL where the archive will be written.
 * @param error If non-null and the operation fails, set to an NSError describing the failure.
 * @return bool `true` if the archive was serialized successfully, `false` otherwise.
 */
_MTL_INLINE bool MTL::BinaryArchive::serializeToURL(const NS::URL* url, NS::Error** error)
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(serializeToURL_error_), url, error);
}

/**
 * @brief Assigns a user-visible label to the binary archive.
 *
 * @param label The string to use as the archive's label.
 */
_MTL_INLINE void MTL::BinaryArchive::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}