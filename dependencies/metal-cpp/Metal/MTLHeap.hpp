//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLHeap.hpp
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
#include "MTLAllocation.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLResource.hpp"

namespace MTL
{
class AccelerationStructure;
class AccelerationStructureDescriptor;
class Buffer;
class Device;
class HeapDescriptor;
class Texture;
class TextureDescriptor;
/**
 * @brief Types of heaps that describe allocation behavior and placement.
 *
 * @enum HeapType
 */

/**
 * @brief Allocate a new HeapDescriptor instance.
 *
 * @return HeapDescriptor* Newly allocated but uninitialized descriptor.
 */

/**
 * @brief Returns the CPU cache mode to be used for resources created from this descriptor.
 *
 * @return CPUCacheMode The configured CPU cache mode.
 */

/**
 * @brief Returns the hazard tracking mode used for resources created from this descriptor.
 *
 * @return HazardTrackingMode The configured hazard tracking mode.
 */

/**
 * @brief Initialize the HeapDescriptor instance.
 *
 * @return HeapDescriptor* The initialized descriptor (typically `this`) or `nullptr` on failure.
 */

/**
 * @brief Returns the maximum sparse page size that can be used for placement on this heap.
 *
 * @return SparsePageSize The maximum compatible placement sparse page size.
 */

/**
 * @brief Returns the resource options that will be applied to resources created from this descriptor.
 *
 * @return ResourceOptions The configured resource options.
 */

/**
 * @brief Set the CPU cache mode for resources created from this descriptor.
 *
 * @param cpuCacheMode The CPU cache mode to apply.
 */

/**
 * @brief Set the hazard tracking mode for resources created from this descriptor.
 *
 * @param hazardTrackingMode The hazard tracking mode to apply.
 */

/**
 * @brief Set the maximum compatible sparse page size for placement allocations.
 *
 * @param maxCompatiblePlacementSparsePageSize The maximum sparse page size to permit for placement.
 */

/**
 * @brief Set the resource options to apply to resources created from this descriptor.
 *
 * @param resourceOptions The resource options to set.
 */

/**
 * @brief Set the total size of the heap described by this descriptor.
 *
 * @param size The heap size, in bytes.
 */

/**
 * @brief Set the sparse page size preference for resources created from this descriptor.
 *
 * @param sparsePageSize The sparse page size to set.
 */

/**
 * @brief Set the storage mode for resources created from this descriptor.
 *
 * @param storageMode The storage mode to apply.
 */

/**
 * @brief Set the heap type described by this descriptor.
 *
 * @param type The HeapType to set.
 */

/**
 * @brief Returns the configured size for the described heap.
 *
 * @return NS::UInteger The descriptor's heap size, in bytes.
 */

/**
 * @brief Returns the configured sparse page size preference for the descriptor.
 *
 * @return SparsePageSize The descriptor's sparse page size.
 */

/**
 * @brief Returns the storage mode configured for the descriptor.
 *
 * @return StorageMode The descriptor's storage mode.
 */

/**
 * @brief Returns the heap type configured by the descriptor.
 *
 * @return HeapType The descriptor's heap type.
 */

/**
 * @brief Returns the CPU cache mode currently in use by this heap.
 *
 * @return CPUCacheMode The heap's CPU cache mode.
 */

/**
 * @brief Returns the current number of bytes allocated from this heap.
 *
 * @return NS::UInteger The current allocated size, in bytes.
 */

/**
 * @brief Returns the device associated with this heap.
 *
 * @return Device* Pointer to the Device that owns the heap.
 */

/**
 * @brief Returns the hazard tracking mode used by this heap.
 *
 * @return HazardTrackingMode The heap's hazard tracking mode.
 */

/**
 * @brief Returns the user-visible label for this heap.
 *
 * @return NS::String* The heap's label, or `nullptr` if none is set.
 */

/**
 * @brief Compute the maximum contiguous allocation size available in the heap for a given alignment.
 *
 * @param alignment Byte alignment required for the allocation.
 * @return NS::UInteger The maximum allocatable size in bytes that satisfies the alignment.
 */

/**
 * @brief Create a new acceleration structure allocated from this heap with the given size.
 *
 * @param size Size in bytes for the acceleration structure.
 * @return AccelerationStructure* Newly created acceleration structure, or `nullptr` on failure.
 */

/**
 * @brief Create a new acceleration structure allocated from this heap using a descriptor.
 *
 * @param descriptor Descriptor that specifies the acceleration structure configuration.
 * @return AccelerationStructure* Newly created acceleration structure, or `nullptr` on failure.
 */

/**
 * @brief Create a new acceleration structure allocated from this heap at a specific offset.
 *
 * @param size Size in bytes for the acceleration structure.
 * @param offset Byte offset within the heap where the allocation should start.
 * @return AccelerationStructure* Newly created acceleration structure, or `nullptr` on failure.
 */

/**
 * @brief Create a new acceleration structure allocated from this heap at a specific offset using a descriptor.
 *
 * @param descriptor Descriptor that specifies the acceleration structure configuration.
 * @param offset Byte offset within the heap where the allocation should start.
 * @return AccelerationStructure* Newly created acceleration structure, or `nullptr` on failure.
 */

/**
 * @brief Create a new buffer allocated from this heap with the specified length and resource options.
 *
 * @param length Buffer length in bytes.
 * @param options Resource options to apply to the buffer.
 * @return Buffer* Newly created buffer, or `nullptr` on failure.
 */

/**
 * @brief Create a new buffer allocated from this heap at a specific offset with the specified length and options.
 *
 * @param length Buffer length in bytes.
 * @param options Resource options to apply to the buffer.
 * @param offset Byte offset within the heap where the buffer should be placed.
 * @return Buffer* Newly created buffer, or `nullptr` on failure.
 */

/**
 * @brief Create a new texture allocated from this heap using the provided descriptor.
 *
 * @param descriptor Descriptor that specifies the texture configuration.
 * @return Texture* Newly created texture, or `nullptr` on failure.
 */

/**
 * @brief Create a new texture allocated from this heap at a specific offset using the provided descriptor.
 *
 * @param descriptor Descriptor that specifies the texture configuration.
 * @param offset Byte offset within the heap where the texture storage should start.
 * @return Texture* Newly created texture, or `nullptr` on failure.
 */

/**
 * @brief Returns the resource options currently in effect for this heap.
 *
 * @return ResourceOptions The heap's resource options.
 */

/**
 * @brief Set the user-visible label for this heap.
 *
 * @param label The label string to assign to the heap.
 */

/**
 * @brief Set the purgeable state of the heap.
 *
 * @param state The purgeable state to transition to.
 * @return PurgeableState The resulting purgeable state after the transition.
 */

/**
 * @brief Returns the total size of this heap.
 *
 * @return NS::UInteger The heap size, in bytes.
 */

/**
 * @brief Returns the storage mode of this heap.
 *
 * @return StorageMode The heap's storage mode.
 */

/**
 * @brief Returns the heap type.
 *
 * @return HeapType The heap's type.
 */

/**
 * @brief Returns the number of bytes currently used within this heap.
 *
 * @return NS::UInteger The used size in bytes.
 */
_MTL_ENUM(NS::Integer, HeapType) {
    HeapTypeAutomatic = 0,
    HeapTypePlacement = 1,
    HeapTypeSparse = 2,
};

class HeapDescriptor : public NS::Copying<HeapDescriptor>
{
public:
    static HeapDescriptor* alloc();

    CPUCacheMode           cpuCacheMode() const;

    HazardTrackingMode     hazardTrackingMode() const;

    HeapDescriptor*        init();

    SparsePageSize         maxCompatiblePlacementSparsePageSize() const;

    ResourceOptions        resourceOptions() const;

    void                   setCpuCacheMode(MTL::CPUCacheMode cpuCacheMode);

    void                   setHazardTrackingMode(MTL::HazardTrackingMode hazardTrackingMode);

    void                   setMaxCompatiblePlacementSparsePageSize(MTL::SparsePageSize maxCompatiblePlacementSparsePageSize);

    void                   setResourceOptions(MTL::ResourceOptions resourceOptions);

    void                   setSize(NS::UInteger size);

    void                   setSparsePageSize(MTL::SparsePageSize sparsePageSize);

    void                   setStorageMode(MTL::StorageMode storageMode);

    void                   setType(MTL::HeapType type);

    NS::UInteger           size() const;
    SparsePageSize         sparsePageSize() const;

    StorageMode            storageMode() const;

    HeapType               type() const;
};
class Heap : public NS::Referencing<Heap, Allocation>
{
public:
    CPUCacheMode           cpuCacheMode() const;

    NS::UInteger           currentAllocatedSize() const;

    Device*                device() const;

    HazardTrackingMode     hazardTrackingMode() const;

    NS::String*            label() const;

    NS::UInteger           maxAvailableSize(NS::UInteger alignment);

    AccelerationStructure* newAccelerationStructure(NS::UInteger size);
    AccelerationStructure* newAccelerationStructure(const MTL::AccelerationStructureDescriptor* descriptor);
    AccelerationStructure* newAccelerationStructure(NS::UInteger size, NS::UInteger offset);
    AccelerationStructure* newAccelerationStructure(const MTL::AccelerationStructureDescriptor* descriptor, NS::UInteger offset);

    Buffer*                newBuffer(NS::UInteger length, MTL::ResourceOptions options);
    Buffer*                newBuffer(NS::UInteger length, MTL::ResourceOptions options, NS::UInteger offset);

    Texture*               newTexture(const MTL::TextureDescriptor* descriptor);
    Texture*               newTexture(const MTL::TextureDescriptor* descriptor, NS::UInteger offset);

    ResourceOptions        resourceOptions() const;

    void                   setLabel(const NS::String* label);

    PurgeableState         setPurgeableState(MTL::PurgeableState state);

    NS::UInteger           size() const;

    StorageMode            storageMode() const;

    HeapType               type() const;

    NS::UInteger           usedSize() const;
};

}
/**
 * @brief Allocates and returns a new heap descriptor instance.
 *
 * @return MTL::HeapDescriptor* Pointer to a newly allocated HeapDescriptor.
 */
_MTL_INLINE MTL::HeapDescriptor* MTL::HeapDescriptor::alloc()
{
    return NS::Object::alloc<MTL::HeapDescriptor>(_MTL_PRIVATE_CLS(MTLHeapDescriptor));
}

/**
 * @brief Retrieves the CPU cache mode configured on this heap descriptor.
 *
 * @return MTL::CPUCacheMode The CPU cache mode of the descriptor.
 */
_MTL_INLINE MTL::CPUCacheMode MTL::HeapDescriptor::cpuCacheMode() const
{
    return Object::sendMessage<MTL::CPUCacheMode>(this, _MTL_PRIVATE_SEL(cpuCacheMode));
}

/**
 * @brief Gets the hazard tracking mode for this heap descriptor.
 *
 * @return MTL::HazardTrackingMode The descriptor's hazard tracking mode.
 */
_MTL_INLINE MTL::HazardTrackingMode MTL::HeapDescriptor::hazardTrackingMode() const
{
    return Object::sendMessage<MTL::HazardTrackingMode>(this, _MTL_PRIVATE_SEL(hazardTrackingMode));
}

/**
 * @brief Initialize a HeapDescriptor instance.
 *
 * @return MTL::HeapDescriptor* Initialized HeapDescriptor instance, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::HeapDescriptor* MTL::HeapDescriptor::init()
{
    return NS::Object::init<MTL::HeapDescriptor>();
}

/**
 * @brief Gets the maximum sparse page size compatible with placement allocations for this heap descriptor.
 *
 * @return MTL::SparsePageSize The maximum sparse page size compatible with placement allocations for this descriptor.
 */
_MTL_INLINE MTL::SparsePageSize MTL::HeapDescriptor::maxCompatiblePlacementSparsePageSize() const
{
    return Object::sendMessage<MTL::SparsePageSize>(this, _MTL_PRIVATE_SEL(maxCompatiblePlacementSparsePageSize));
}

/**
 * @brief Retrieve the resource options configured for this heap descriptor.
 *
 * @return MTL::ResourceOptions The resource options bitmask used for resources created from this descriptor.
 */
_MTL_INLINE MTL::ResourceOptions MTL::HeapDescriptor::resourceOptions() const
{
    return Object::sendMessage<MTL::ResourceOptions>(this, _MTL_PRIVATE_SEL(resourceOptions));
}

/**
 * @brief Set the CPU cache mode for this heap descriptor.
 *
 * @param cpuCacheMode The CPU cache mode to apply to allocated resources.
 */
_MTL_INLINE void MTL::HeapDescriptor::setCpuCacheMode(MTL::CPUCacheMode cpuCacheMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCpuCacheMode_), cpuCacheMode);
}

/**
 * @brief Sets the heap descriptor's hazard tracking mode.
 *
 * @param hazardTrackingMode The hazard tracking mode to apply to this descriptor.
 */
_MTL_INLINE void MTL::HeapDescriptor::setHazardTrackingMode(MTL::HazardTrackingMode hazardTrackingMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setHazardTrackingMode_), hazardTrackingMode);
}

/**
 * @brief Set the maximum compatible placement sparse page size.
 *
 * @param maxCompatiblePlacementSparsePageSize The maximum sparse page size that placement heaps created from this descriptor may use.
 */
_MTL_INLINE void MTL::HeapDescriptor::setMaxCompatiblePlacementSparsePageSize(MTL::SparsePageSize maxCompatiblePlacementSparsePageSize)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxCompatiblePlacementSparsePageSize_), maxCompatiblePlacementSparsePageSize);
}

/**
 * @brief Set the resource options to apply to resources created from this heap descriptor.
 *
 * @param resourceOptions Bitmask specifying allocation-related options (storage mode, CPU cache mode, and related flags) to apply when creating resources from the heap described by this descriptor.
 */
_MTL_INLINE void MTL::HeapDescriptor::setResourceOptions(MTL::ResourceOptions resourceOptions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setResourceOptions_), resourceOptions);
}

/**
 * @brief Sets the heap size for the descriptor.
 *
 * Specifies the desired heap size in bytes to be used when creating a Heap from this descriptor.
 *
 * @param size Size in bytes.
 */
_MTL_INLINE void MTL::HeapDescriptor::setSize(NS::UInteger size)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSize_), size);
}

/**
 * @brief Sets the sparse page size used by the heap descriptor.
 *
 * @param sparsePageSize The sparse page size to use for resources allocated from heaps created with this descriptor.
 */
_MTL_INLINE void MTL::HeapDescriptor::setSparsePageSize(MTL::SparsePageSize sparsePageSize)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSparsePageSize_), sparsePageSize);
}

/**
 * @brief Set the heap's storage mode determining where its memory is allocated and its CPU/GPU accessibility.
 *
 * @param storageMode The storage mode to assign to this heap.
 */
_MTL_INLINE void MTL::HeapDescriptor::setStorageMode(MTL::StorageMode storageMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStorageMode_), storageMode);
}

/**
 * @brief Set the heap's type.
 *
 * @param type The heap type to assign (e.g., HeapTypeAutomatic, HeapTypePlacement, HeapTypeSparse).
 */
_MTL_INLINE void MTL::HeapDescriptor::setType(MTL::HeapType type)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setType_), type);
}

/**
 * @brief Retrieves the descriptor's size.
 *
 * @return NS::UInteger The size configured in the heap descriptor, in bytes.
 */
_MTL_INLINE NS::UInteger MTL::HeapDescriptor::size() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(size));
}

/**
 * @brief Retrieves the sparse page size configured for this heap descriptor.
 *
 * @return MTL::SparsePageSize The sparse page size to use for placement of sparse resources created from this descriptor.
 */
_MTL_INLINE MTL::SparsePageSize MTL::HeapDescriptor::sparsePageSize() const
{
    return Object::sendMessage<MTL::SparsePageSize>(this, _MTL_PRIVATE_SEL(sparsePageSize));
}

/**
 * @brief Gets the storage mode configured for this heap descriptor.
 *
 * @return MTL::StorageMode The storage mode configured for the descriptor.
 */
_MTL_INLINE MTL::StorageMode MTL::HeapDescriptor::storageMode() const
{
    return Object::sendMessage<MTL::StorageMode>(this, _MTL_PRIVATE_SEL(storageMode));
}

/**
 * @brief Returns the heap type specified by this descriptor.
 *
 * @return MTL::HeapType The configured heap type (for example: HeapTypeAutomatic, HeapTypePlacement, or HeapTypeSparse).
 */
_MTL_INLINE MTL::HeapType MTL::HeapDescriptor::type() const
{
    return Object::sendMessage<MTL::HeapType>(this, _MTL_PRIVATE_SEL(type));
}

/**
 * @brief Retrieves the CPU cache mode for this heap.
 *
 * @return MTL::CPUCacheMode The CPU cache mode used for resources allocated from the heap.
 */
_MTL_INLINE MTL::CPUCacheMode MTL::Heap::cpuCacheMode() const
{
    return Object::sendMessage<MTL::CPUCacheMode>(this, _MTL_PRIVATE_SEL(cpuCacheMode));
}

/**
 * @brief Reports the heap's current allocated size.
 *
 * @return NS::UInteger The number of bytes currently allocated within the heap.
 */
_MTL_INLINE NS::UInteger MTL::Heap::currentAllocatedSize() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(currentAllocatedSize));
}

/**
 * @brief Get the device associated with this heap.
 *
 * @return MTL::Device* Pointer to the device associated with the heap.
 */
_MTL_INLINE MTL::Device* MTL::Heap::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Retrieve the heap's hazard tracking mode.
 *
 * @return MTL::HazardTrackingMode The current hazard tracking mode for this heap.
 */
_MTL_INLINE MTL::HazardTrackingMode MTL::Heap::hazardTrackingMode() const
{
    return Object::sendMessage<MTL::HazardTrackingMode>(this, _MTL_PRIVATE_SEL(hazardTrackingMode));
}

/**
 * @brief Retrieve the heap's label.
 *
 * @return NS::String* The label of the heap, or `nullptr` if no label has been set.
 */
_MTL_INLINE NS::String* MTL::Heap::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Compute the maximum contiguous allocatable size from this heap for a given alignment.
 *
 * @param alignment Alignment in bytes required for the allocation.
 * @return NS::UInteger The largest contiguous free size in bytes that can be allocated from the heap using the specified alignment.
 */
_MTL_INLINE NS::UInteger MTL::Heap::maxAvailableSize(NS::UInteger alignment)
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxAvailableSizeWithAlignment_), alignment);
}

/**
 * @brief Create a new acceleration structure allocated from this heap.
 *
 * @param size Size in bytes of the acceleration structure to allocate.
 * @return MTL::AccelerationStructure* Pointer to the newly created acceleration structure, or `nullptr` if allocation failed.
 */
_MTL_INLINE MTL::AccelerationStructure* MTL::Heap::newAccelerationStructure(NS::UInteger size)
{
    return Object::sendMessage<MTL::AccelerationStructure*>(this, _MTL_PRIVATE_SEL(newAccelerationStructureWithSize_), size);
}

/**
 * @brief Creates a new acceleration structure configured by the given descriptor.
 *
 * @param descriptor Descriptor that specifies the properties of the acceleration structure to create.
 * @return MTL::AccelerationStructure* Pointer to the newly created acceleration structure.
 */
_MTL_INLINE MTL::AccelerationStructure* MTL::Heap::newAccelerationStructure(const MTL::AccelerationStructureDescriptor* descriptor)
{
    return Object::sendMessage<MTL::AccelerationStructure*>(this, _MTL_PRIVATE_SEL(newAccelerationStructureWithDescriptor_), descriptor);
}

/**
 * @brief Creates a new acceleration structure allocated from this heap.
 *
 * @param size Size in bytes of the acceleration structure to allocate.
 * @param offset Byte offset within the heap where the allocation should begin.
 * @return MTL::AccelerationStructure* Pointer to the newly created acceleration structure, or `nullptr` on failure.
 */
_MTL_INLINE MTL::AccelerationStructure* MTL::Heap::newAccelerationStructure(NS::UInteger size, NS::UInteger offset)
{
    return Object::sendMessage<MTL::AccelerationStructure*>(this, _MTL_PRIVATE_SEL(newAccelerationStructureWithSize_offset_), size, offset);
}

/**
 * @brief Creates an acceleration structure from the given descriptor and places it at the specified offset within the heap.
 *
 * @param descriptor Descriptor describing the acceleration structure to create.
 * @param offset Byte offset into the heap where the acceleration structure will be placed.
 * @return MTL::AccelerationStructure* Pointer to the newly created acceleration structure.
 */
_MTL_INLINE MTL::AccelerationStructure* MTL::Heap::newAccelerationStructure(const MTL::AccelerationStructureDescriptor* descriptor, NS::UInteger offset)
{
    return Object::sendMessage<MTL::AccelerationStructure*>(this, _MTL_PRIVATE_SEL(newAccelerationStructureWithDescriptor_offset_), descriptor, offset);
}

/**
 * @brief Creates a new buffer allocated from this heap with the specified size and resource options.
 *
 * @param length Size in bytes of the buffer to allocate.
 * @param options Resource options describing storage/cache/hazard behavior for the buffer.
 * @return MTL::Buffer* Pointer to the created buffer, or `nullptr` if allocation failed.
 */
_MTL_INLINE MTL::Buffer* MTL::Heap::newBuffer(NS::UInteger length, MTL::ResourceOptions options)
{
    return Object::sendMessage<MTL::Buffer*>(this, _MTL_PRIVATE_SEL(newBufferWithLength_options_), length, options);
}

/**
 * @brief Creates a new buffer allocated from this heap.
 *
 * Allocates a buffer of the specified byte length from the heap using the given resource options and placement offset within the heap.
 *
 * @param length Size in bytes of the buffer to allocate.
 * @param options Resource options that control storage and cache behavior for the buffer.
 * @param offset Byte offset within the heap where the buffer should be placed.
 * @return MTL::Buffer* Pointer to the newly created buffer.
 */
_MTL_INLINE MTL::Buffer* MTL::Heap::newBuffer(NS::UInteger length, MTL::ResourceOptions options, NS::UInteger offset)
{
    return Object::sendMessage<MTL::Buffer*>(this, _MTL_PRIVATE_SEL(newBufferWithLength_options_offset_), length, options, offset);
}

/**
 * @brief Creates a new texture described by `descriptor` and allocates it from this heap.
 *
 * @param descriptor Descriptor that specifies the texture's properties.
 * @return MTL::Texture* Pointer to the newly created texture allocated from the heap, or `nullptr` if allocation fails.
 */
_MTL_INLINE MTL::Texture* MTL::Heap::newTexture(const MTL::TextureDescriptor* descriptor)
{
    return Object::sendMessage<MTL::Texture*>(this, _MTL_PRIVATE_SEL(newTextureWithDescriptor_), descriptor);
}

/**
 * @brief Creates a texture in this heap using the provided descriptor at a specific byte offset.
 *
 * @param descriptor Descriptor that describes the texture to create.
 * @param offset Byte offset within the heap where the texture's storage should begin.
 * @return MTL::Texture* Pointer to the created Texture object, or `nullptr` if creation/allocation fails.
 */
_MTL_INLINE MTL::Texture* MTL::Heap::newTexture(const MTL::TextureDescriptor* descriptor, NS::UInteger offset)
{
    return Object::sendMessage<MTL::Texture*>(this, _MTL_PRIVATE_SEL(newTextureWithDescriptor_offset_), descriptor, offset);
}

/**
 * @brief Query the resource options configured for this heap.
 *
 * @return MTL::ResourceOptions Bitmask describing the resource options (CPU cache mode, storage mode, and related allocation flags) that will be applied to resources created from this heap.
 */
_MTL_INLINE MTL::ResourceOptions MTL::Heap::resourceOptions() const
{
    return Object::sendMessage<MTL::ResourceOptions>(this, _MTL_PRIVATE_SEL(resourceOptions));
}

/**
 * @brief Sets the heap's label used for debugging and identification.
 *
 * @param label The label string to assign to the heap; may be nullptr to clear the label.
 */
_MTL_INLINE void MTL::Heap::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Sets the heap's purgeable state.
 *
 * @param state The desired purgeable state to apply to the heap.
 * @return MTL::PurgeableState The heap's resulting purgeable state after the operation.
 */
_MTL_INLINE MTL::PurgeableState MTL::Heap::setPurgeableState(MTL::PurgeableState state)
{
    return Object::sendMessage<MTL::PurgeableState>(this, _MTL_PRIVATE_SEL(setPurgeableState_), state);
}

/**
 * @brief Get the total size of the heap in bytes.
 *
 * @return NS::UInteger The total capacity of the heap, in bytes.
 */
_MTL_INLINE NS::UInteger MTL::Heap::size() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(size));
}

/**
 * @brief Query the storage mode of the heap.
 *
 * @return MTL::StorageMode The heap's storage mode.
 */
_MTL_INLINE MTL::StorageMode MTL::Heap::storageMode() const
{
    return Object::sendMessage<MTL::StorageMode>(this, _MTL_PRIVATE_SEL(storageMode));
}

/**
 * @brief Retrieve the heap's type classification.
 *
 * @return MTL::HeapType The heap's type as an MTL::HeapType enumeration.
 */
_MTL_INLINE MTL::HeapType MTL::Heap::type() const
{
    return Object::sendMessage<MTL::HeapType>(this, _MTL_PRIVATE_SEL(type));
}

/**
 * @brief Reports the amount of heap memory currently allocated.
 *
 * @return NS::UInteger The number of bytes currently allocated from this heap.
 */
_MTL_INLINE NS::UInteger MTL::Heap::usedSize() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(usedSize));
}