//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLBuffer.hpp
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
#include "MTLGPUAddress.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLResource.hpp"

namespace MTL
{
class Buffer;
class Device;
class Tensor;
class TensorDescriptor;
class Texture;
class TextureDescriptor;

class Buffer : public NS::Referencing<Buffer, Resource>
{
public:
    void             addDebugMarker(const NS::String* marker, NS::Range range);

    void*            contents();

    void             didModifyRange(NS::Range range);

    GPUAddress       gpuAddress() const;

    NS::UInteger     length() const;

    Buffer*          newRemoteBufferViewForDevice(const MTL::Device* device);

    Tensor*          newTensor(const MTL::TensorDescriptor* descriptor, NS::UInteger offset, NS::Error** error);

    Texture*         newTexture(const MTL::TextureDescriptor* descriptor, NS::UInteger offset, NS::UInteger bytesPerRow);

    Buffer*          remoteStorageBuffer() const;

    void             removeAllDebugMarkers();

    BufferSparseTier sparseBufferTier() const;
};

}
/**
 * @brief Adds a debug marker label to the buffer covering the specified byte range.
 *
 * @param marker A string label for the debug marker.
 * @param range The byte range within the buffer that the marker covers.
 */
_MTL_INLINE void MTL::Buffer::addDebugMarker(const NS::String* marker, NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(addDebugMarker_range_), marker, range);
}

/**
 * @brief Provides direct access to the buffer's CPU-accessible memory.
 *
 * Returns a pointer to the start of the buffer's contents for reading or writing.
 *
 * @return void* Pointer to the buffer contents, or `nullptr` if the contents are not accessible.
 */
_MTL_INLINE void* MTL::Buffer::contents()
{
    return Object::sendMessage<void*>(this, _MTL_PRIVATE_SEL(contents));
}

/**
 * @brief Notify the system that a region of the buffer's contents was modified.
 *
 * Marks the specified byte range of the buffer as having been changed so the
 * system can update any caches, synchronize with GPU-visible memory, and
 * propagate the modification to dependent views or operations.
 *
 * @param range The byte range within the buffer that was modified.
 */
_MTL_INLINE void MTL::Buffer::didModifyRange(NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(didModifyRange_), range);
}

/**
 * @brief Retrieve the GPU address associated with this buffer.
 *
 * @return MTL::GPUAddress The GPU address that devices can use to access the buffer's memory.
 */
_MTL_INLINE MTL::GPUAddress MTL::Buffer::gpuAddress() const
{
    return Object::sendMessage<MTL::GPUAddress>(this, _MTL_PRIVATE_SEL(gpuAddress));
}

/**
 * @brief Get the total size of the buffer in bytes.
 *
 * @return NS::UInteger Total length of the buffer in bytes.
 */
_MTL_INLINE NS::UInteger MTL::Buffer::length() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(length));
}

/**
 * @brief Create a remote buffer view for the specified device.
 *
 * @param device The device for which to create the remote buffer view.
 * @return MTL::Buffer* Pointer to a new Buffer configured as a remote view for the specified device, or `nullptr` on failure.
 */
_MTL_INLINE MTL::Buffer* MTL::Buffer::newRemoteBufferViewForDevice(const MTL::Device* device)
{
    return Object::sendMessage<MTL::Buffer*>(this, _MTL_PRIVATE_SEL(newRemoteBufferViewForDevice_), device);
}

/**
 * @brief Creates a Tensor view backed by a region of this buffer.
 *
 * Constructs and returns a tensor that interprets the buffer memory described by `descriptor`
 * starting at `offset`.
 *
 * @param descriptor Descriptor that specifies the tensor's layout, shape, and data format.
 * @param offset Byte offset within the buffer where the tensor's data begins.
 * @param error Optional out-parameter that, if non-null, will be set to an `NSError` describing
 *              why creation failed.
 * @return MTL::Tensor* The newly created tensor view, or `nullptr` if creation fails.
 */
_MTL_INLINE MTL::Tensor* MTL::Buffer::newTensor(const MTL::TensorDescriptor* descriptor, NS::UInteger offset, NS::Error** error)
{
    return Object::sendMessage<MTL::Tensor*>(this, _MTL_PRIVATE_SEL(newTensorWithDescriptor_offset_error_), descriptor, offset, error);
}

/**
 * @brief Creates a texture view that maps a region of this buffer.
 *
 * @param descriptor Descriptor that specifies the texture's format, size and usage.
 * @param offset Byte offset into the buffer where the texture data begins.
 * @param bytesPerRow Number of bytes in a single row of the texture image.
 * @return MTL::Texture* A new texture backed by this buffer, or `nullptr` if the view cannot be created.
 */
_MTL_INLINE MTL::Texture* MTL::Buffer::newTexture(const MTL::TextureDescriptor* descriptor, NS::UInteger offset, NS::UInteger bytesPerRow)
{
    return Object::sendMessage<MTL::Texture*>(this, _MTL_PRIVATE_SEL(newTextureWithDescriptor_offset_bytesPerRow_), descriptor, offset, bytesPerRow);
}

/**
 * @brief Obtains the remote storage buffer associated with this buffer.
 *
 * @return MTL::Buffer* Pointer to the remote storage buffer, or `nullptr` if no remote storage is associated.
 */
_MTL_INLINE MTL::Buffer* MTL::Buffer::remoteStorageBuffer() const
{
    return Object::sendMessage<MTL::Buffer*>(this, _MTL_PRIVATE_SEL(remoteStorageBuffer));
}

/**
 * @brief Remove all debug markers from the buffer.
 *
 * Clears any debug labels or markers previously associated with this buffer so subsequent
 * debugging or profiling queries will not see those markers.
 */
_MTL_INLINE void MTL::Buffer::removeAllDebugMarkers()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(removeAllDebugMarkers));
}

/**
 * @brief Report the sparse-buffer tier supported by this buffer.
 *
 * @return MTL::BufferSparseTier The buffer's sparse tier. 
 */
_MTL_INLINE MTL::BufferSparseTier MTL::Buffer::sparseBufferTier() const
{
    return Object::sendMessage<MTL::BufferSparseTier>(this, _MTL_PRIVATE_SEL(sparseBufferTier));
}