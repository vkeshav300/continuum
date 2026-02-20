//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLIntersectionFunctionTable.hpp
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
#include "MTLResource.hpp"
#include "MTLTypes.hpp"
#include <cstdint>

namespace MTL
{
class Buffer;
class FunctionHandle;
class IntersectionFunctionTableDescriptor;
class VisibleFunctionTable;

/**
 * @brief Bitmask describing enabled data and features for an intersection function.
 *
 * Use these flags to specify which optional inputs or behaviors an intersection
 * function requires or supports (e.g., instancing, motion, extra curve data,
 * an external intersection-function buffer, or user-provided data).
 */

/**
 * @brief Packed arguments describing an external intersection-function buffer binding.
 *
 * @param intersectionFunctionBuffer GPU-address or identifier of the buffer containing intersection data.
 * @param intersectionFunctionBufferSize Size in bytes of the intersection-function buffer.
 * @param intersectionFunctionStride Stride in bytes between consecutive entries in the buffer.
 */

/**
 * @brief Allocate a new IntersectionFunctionTableDescriptor instance.
 *
 * @return IntersectionFunctionTableDescriptor* Newly allocated descriptor (uninitialized).
 */

/**
 * @brief Number of intersection functions this descriptor describes.
 *
 * @return NS::UInteger The configured function count.
 */

/**
 * @brief Initialize an IntersectionFunctionTableDescriptor instance.
 *
 * @return IntersectionFunctionTableDescriptor* The initialized descriptor instance.
 */

/**
 * @brief Create and return a default/configured IntersectionFunctionTableDescriptor.
 *
 * @return IntersectionFunctionTableDescriptor* A descriptor instance configured for use.
 */

/**
 * @brief Set how many intersection functions this descriptor will contain.
 *
 * @param functionCount The total number of functions to be described.
 */

/**
 * @brief Retrieve the GPU resource identifier for this intersection function table.
 *
 * @return ResourceID The underlying GPU resource ID.
 */

/**
 * @brief Bind a buffer to the intersection function table at a specific slot.
 *
 * @param buffer The buffer to bind.
 * @param offset Byte offset within the buffer where data begins.
 * @param index The slot index to bind the buffer to.
 */

/**
 * @brief Bind multiple buffers with per-buffer offsets over a contiguous index range.
 *
 * @param buffers Array of buffers to bind.
 * @param offsets Array of byte offsets corresponding to each buffer.
 * @param range The contiguous range of slot indices to receive the bindings.
 */

/**
 * @brief Set a single function handle into the table at the specified index.
 *
 * @param function The function handle to set.
 * @param index The function slot index to assign.
 */

/**
 * @brief Set multiple function handles over a contiguous index range.
 *
 * @param functions Array of function handles to assign.
 * @param range The contiguous range of function slot indices to populate.
 */

/**
 * @brief Configure an opaque curve intersection function signature at a given index.
 *
 * The signature selects which optional inputs/features the opaque curve intersection
 * implementation will expect.
 *
 * @param signature Bitmask of IntersectionFunctionSignature flags describing the signature.
 * @param index The function slot index to configure.
 */

/**
 * @brief Configure an opaque curve intersection function signature over a contiguous range.
 *
 * @param signature Bitmask of IntersectionFunctionSignature flags describing the signature.
 * @param range The contiguous range of function slot indices to configure.
 */

/**
 * @brief Configure an opaque triangle intersection function signature at a given index.
 *
 * The signature selects which optional inputs/features the opaque triangle intersection
 * implementation will expect.
 *
 * @param signature Bitmask of IntersectionFunctionSignature flags describing the signature.
 * @param index The function slot index to configure.
 */

/**
 * @brief Configure an opaque triangle intersection function signature over a contiguous range.
 *
 * @param signature Bitmask of IntersectionFunctionSignature flags describing the signature.
 * @param range The contiguous range of function slot indices to configure.
 */

/**
 * @brief Bind a VisibleFunctionTable to a buffer index used by the intersection table.
 *
 * @param functionTable The visible function table to bind.
 * @param bufferIndex The buffer index slot to bind the visible function table to.
 */

/**
 * @brief Bind multiple VisibleFunctionTables over a contiguous buffer index range.
 *
 * @param functionTables Array of visible function tables to bind.
 * @param bufferRange The contiguous range of buffer index slots to receive the bindings.
 */
_MTL_OPTIONS(NS::UInteger, IntersectionFunctionSignature) {
    IntersectionFunctionSignatureNone = 0,
    IntersectionFunctionSignatureInstancing = 1,
    IntersectionFunctionSignatureTriangleData = 1 << 1,
    IntersectionFunctionSignatureWorldSpaceData = 1 << 2,
    IntersectionFunctionSignatureInstanceMotion = 1 << 3,
    IntersectionFunctionSignaturePrimitiveMotion = 1 << 4,
    IntersectionFunctionSignatureExtendedLimits = 1 << 5,
    IntersectionFunctionSignatureMaxLevels = 1 << 6,
    IntersectionFunctionSignatureCurveData = 1 << 7,
    IntersectionFunctionSignatureIntersectionFunctionBuffer = 1 << 8,
    IntersectionFunctionSignatureUserData = 1 << 9,
};

struct IntersectionFunctionBufferArguments
{
    uint64_t intersectionFunctionBuffer;
    uint64_t intersectionFunctionBufferSize;
    uint64_t intersectionFunctionStride;
} _MTL_PACKED;

class IntersectionFunctionTableDescriptor : public NS::Copying<IntersectionFunctionTableDescriptor>
{
public:
    static IntersectionFunctionTableDescriptor* alloc();

    NS::UInteger                                functionCount() const;

    IntersectionFunctionTableDescriptor*        init();

    static IntersectionFunctionTableDescriptor* intersectionFunctionTableDescriptor();

    void                                        setFunctionCount(NS::UInteger functionCount);
};
class IntersectionFunctionTable : public NS::Referencing<IntersectionFunctionTable, Resource>
{
public:
    ResourceID gpuResourceID() const;

    void       setBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index);
    void       setBuffers(const MTL::Buffer* const buffers[], const NS::UInteger offsets[], NS::Range range);

    void       setFunction(const MTL::FunctionHandle* function, NS::UInteger index);
    void       setFunctions(const MTL::FunctionHandle* const functions[], NS::Range range);

    void       setOpaqueCurveIntersectionFunction(MTL::IntersectionFunctionSignature signature, NS::UInteger index);
    void       setOpaqueCurveIntersectionFunction(MTL::IntersectionFunctionSignature signature, NS::Range range);

    void       setOpaqueTriangleIntersectionFunction(MTL::IntersectionFunctionSignature signature, NS::UInteger index);
    void       setOpaqueTriangleIntersectionFunction(MTL::IntersectionFunctionSignature signature, NS::Range range);

    void       setVisibleFunctionTable(const MTL::VisibleFunctionTable* functionTable, NS::UInteger bufferIndex);
    void       setVisibleFunctionTables(const MTL::VisibleFunctionTable* const functionTables[], NS::Range bufferRange);
};

}

/**
 * @brief Allocate a new IntersectionFunctionTableDescriptor instance.
 *
 * @return MTL::IntersectionFunctionTableDescriptor* A newly allocated descriptor instance.
 */
_MTL_INLINE MTL::IntersectionFunctionTableDescriptor* MTL::IntersectionFunctionTableDescriptor::alloc()
{
    return NS::Object::alloc<MTL::IntersectionFunctionTableDescriptor>(_MTL_PRIVATE_CLS(MTLIntersectionFunctionTableDescriptor));
}

/**
 * @brief Query the number of intersection functions configured in this descriptor.
 *
 * @return NS::UInteger The number of functions in the descriptor.
 */
_MTL_INLINE NS::UInteger MTL::IntersectionFunctionTableDescriptor::functionCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(functionCount));
}

/**
 * @brief Initialize this IntersectionFunctionTableDescriptor instance.
 *
 * @return IntersectionFunctionTableDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::IntersectionFunctionTableDescriptor* MTL::IntersectionFunctionTableDescriptor::init()
{
    return NS::Object::init<MTL::IntersectionFunctionTableDescriptor>();
}

/**
 * @brief Creates a new intersection function table descriptor initialized with default settings.
 *
 * @return IntersectionFunctionTableDescriptor* Pointer to a descriptor initialized with default values.
 */
_MTL_INLINE MTL::IntersectionFunctionTableDescriptor* MTL::IntersectionFunctionTableDescriptor::intersectionFunctionTableDescriptor()
{
    return Object::sendMessage<MTL::IntersectionFunctionTableDescriptor*>(_MTL_PRIVATE_CLS(MTLIntersectionFunctionTableDescriptor), _MTL_PRIVATE_SEL(intersectionFunctionTableDescriptor));
}

/**
 * @brief Set the number of intersection functions the descriptor will contain.
 *
 * @param functionCount The number of function slots to allocate for the intersection function table.
 */
_MTL_INLINE void MTL::IntersectionFunctionTableDescriptor::setFunctionCount(NS::UInteger functionCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFunctionCount_), functionCount);
}

/**
 * @brief Obtain the underlying GPU resource identifier for this intersection function table.
 *
 * @return MTL::ResourceID GPU resource identifier associated with this intersection function table.
 */
_MTL_INLINE MTL::ResourceID MTL::IntersectionFunctionTable::gpuResourceID() const
{
    return Object::sendMessage<MTL::ResourceID>(this, _MTL_PRIVATE_SEL(gpuResourceID));
}

/**
 * @brief Binds a buffer to this intersection function table at a specific buffer index with an offset.
 *
 * @param buffer Pointer to the buffer to bind.
 * @param offset Byte offset into the buffer.
 * @param index Buffer slot index within the intersection function table.
 */
_MTL_INLINE void MTL::IntersectionFunctionTable::setBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBuffer_offset_atIndex_), buffer, offset, index);
}

/**
 * @brief Binds an array of GPU buffers with per-buffer byte offsets into this intersection function table over a consecutive index range.
 *
 * @param buffers Array of buffer pointers to bind; entries correspond to table indices starting at range.location.
 * @param offsets Array of byte offsets for each buffer in `buffers`; entries correspond one-to-one with `buffers`.
 * @param range Range of indices in the intersection function table to update; `range.length` buffers from `range.location` are bound.
 */
_MTL_INLINE void MTL::IntersectionFunctionTable::setBuffers(const MTL::Buffer* const buffers[], const NS::UInteger offsets[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBuffers_offsets_withRange_), buffers, offsets, range);
}

/**
 * @brief Assigns a function handle to the intersection function table at the specified slot.
 *
 * @param function Function handle to assign to the table slot; may be nullptr to clear the slot.
 * @param index   Slot index within the intersection function table where the function will be set.
 */
_MTL_INLINE void MTL::IntersectionFunctionTable::setFunction(const MTL::FunctionHandle* function, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFunction_atIndex_), function, index);
}

/**
 * @brief Sets a contiguous range of intersection function handles in the table.
 *
 * Populates the entries in the intersection function table specified by `range` with the corresponding
 * function handles from `functions`.
 *
 * @param functions Array of `MTL::FunctionHandle` pointers; must contain at least `range.length` entries.
 * @param range Range of indices in the intersection function table to populate (location and length).
 */
_MTL_INLINE void MTL::IntersectionFunctionTable::setFunctions(const MTL::FunctionHandle* const functions[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFunctions_withRange_), functions, range);
}

/**
 * @brief Sets an opaque curve intersection function signature for the entry at the specified index in the intersection function table.
 *
 * @param signature Bitmask of IntersectionFunctionSignature flags describing the intersection function's expected inputs and layout.
 * @param index Table index at which to assign the opaque curve intersection signature.
 */
_MTL_INLINE void MTL::IntersectionFunctionTable::setOpaqueCurveIntersectionFunction(MTL::IntersectionFunctionSignature signature, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOpaqueCurveIntersectionFunctionWithSignature_atIndex_), signature, index);
}

/**
 * @brief Sets the opaque curve intersection function signature for a range of function entries.
 *
 * Applies the given IntersectionFunctionSignature flags to each opaque curve intersection function entry within the specified index range of this intersection function table.
 *
 * @param signature Bitmask of IntersectionFunctionSignature flags to apply to each function entry in the range.
 * @param range Range of indices in the intersection function table to update.
 */
_MTL_INLINE void MTL::IntersectionFunctionTable::setOpaqueCurveIntersectionFunction(MTL::IntersectionFunctionSignature signature, NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOpaqueCurveIntersectionFunctionWithSignature_withRange_), signature, range);
}

/**
 * @brief Assigns an opaque triangle intersection function signature to a specific slot in the table.
 *
 * Associates the provided intersection function signature with the function entry at the given index.
 *
 * @param signature Bitmask describing which intersection-related data and features the function expects.
 * @param index Index of the function slot in the intersection function table to set.
 */
_MTL_INLINE void MTL::IntersectionFunctionTable::setOpaqueTriangleIntersectionFunction(MTL::IntersectionFunctionSignature signature, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOpaqueTriangleIntersectionFunctionWithSignature_atIndex_), signature, index);
}

/**
 * @brief Set the opaque triangle intersection function signature for a range of function slots.
 *
 * @param signature Bitmask of IntersectionFunctionSignature flags that describe the inputs and behavior for the opaque triangle intersection functions.
 * @param range Range of function indices within the intersection function table to which the signature will be applied.
 */
_MTL_INLINE void MTL::IntersectionFunctionTable::setOpaqueTriangleIntersectionFunction(MTL::IntersectionFunctionSignature signature, NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOpaqueTriangleIntersectionFunctionWithSignature_withRange_), signature, range);
}

/**
 * @brief Binds a VisibleFunctionTable to the specified buffer index of this IntersectionFunctionTable.
 *
 * @param functionTable The VisibleFunctionTable to bind; may be `nullptr` to unbind the slot.
 * @param bufferIndex The buffer slot index at which to bind the visible function table.
 */
_MTL_INLINE void MTL::IntersectionFunctionTable::setVisibleFunctionTable(const MTL::VisibleFunctionTable* functionTable, NS::UInteger bufferIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVisibleFunctionTable_atBufferIndex_), functionTable, bufferIndex);
}

/**
 * @brief Binds an array of visible function tables to a contiguous range of buffer indices.
 *
 * Assigns each entry in `functionTables` to successive buffer indices beginning at `bufferRange.location`
 * for `bufferRange.length` entries.
 *
 * @param functionTables Array of pointers to VisibleFunctionTable objects to bind.
 * @param bufferRange NS::Range describing the starting buffer index and number of entries to set.
 */
_MTL_INLINE void MTL::IntersectionFunctionTable::setVisibleFunctionTables(const MTL::VisibleFunctionTable* const functionTables[], NS::Range bufferRange)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVisibleFunctionTables_withBufferRange_), functionTables, bufferRange);
}