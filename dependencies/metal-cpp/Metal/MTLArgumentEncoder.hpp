//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLArgumentEncoder.hpp
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
#include "MTLDepthStencil.hpp"

namespace MTL
{
class AccelerationStructure;
class ArgumentEncoder;
class Buffer;
class ComputePipelineState;
class Device;
class IndirectCommandBuffer;
class IntersectionFunctionTable;
class RenderPipelineState;
class SamplerState;
class Texture;
class VisibleFunctionTable;

static const NS::UInteger AttributeStrideStatic = NS::UIntegerMax;

class ArgumentEncoder : public NS::Referencing<ArgumentEncoder>
{
public:
    NS::UInteger     alignment() const;

    void*            constantData(NS::UInteger index);

    Device*          device() const;

    NS::UInteger     encodedLength() const;

    NS::String*      label() const;

    ArgumentEncoder* newArgumentEncoder(NS::UInteger index);

    void             setAccelerationStructure(const MTL::AccelerationStructure* accelerationStructure, NS::UInteger index);

    void             setArgumentBuffer(const MTL::Buffer* argumentBuffer, NS::UInteger offset);
    void             setArgumentBuffer(const MTL::Buffer* argumentBuffer, NS::UInteger startOffset, NS::UInteger arrayElement);

    void             setBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index);
    void             setBuffers(const MTL::Buffer* const buffers[], const NS::UInteger offsets[], NS::Range range);

    void             setComputePipelineState(const MTL::ComputePipelineState* pipeline, NS::UInteger index);
    void             setComputePipelineStates(const MTL::ComputePipelineState* const pipelines[], NS::Range range);

    void             setDepthStencilState(const MTL::DepthStencilState* depthStencilState, NS::UInteger index);
    void             setDepthStencilStates(const MTL::DepthStencilState* const depthStencilStates[], NS::Range range);

    void             setIndirectCommandBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, NS::UInteger index);
    void             setIndirectCommandBuffers(const MTL::IndirectCommandBuffer* const buffers[], NS::Range range);

    void             setIntersectionFunctionTable(const MTL::IntersectionFunctionTable* intersectionFunctionTable, NS::UInteger index);
    void             setIntersectionFunctionTables(const MTL::IntersectionFunctionTable* const intersectionFunctionTables[], NS::Range range);

    void             setLabel(const NS::String* label);

    void             setRenderPipelineState(const MTL::RenderPipelineState* pipeline, NS::UInteger index);
    void             setRenderPipelineStates(const MTL::RenderPipelineState* const pipelines[], NS::Range range);

    void             setSamplerState(const MTL::SamplerState* sampler, NS::UInteger index);
    void             setSamplerStates(const MTL::SamplerState* const samplers[], NS::Range range);

    void             setTexture(const MTL::Texture* texture, NS::UInteger index);
    void             setTextures(const MTL::Texture* const textures[], NS::Range range);

    void             setVisibleFunctionTable(const MTL::VisibleFunctionTable* visibleFunctionTable, NS::UInteger index);
    void             setVisibleFunctionTables(const MTL::VisibleFunctionTable* const visibleFunctionTables[], NS::Range range);
};

}

/**
 * @brief Retrieves the required byte alignment for data encoded by this argument encoder.
 *
 * @return NS::UInteger The alignment, in bytes, that encoded argument data must adhere to.
 */
_MTL_INLINE NS::UInteger MTL::ArgumentEncoder::alignment() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(alignment));
}

/**
 * @brief Accesses the encoder's constant data for a specific argument index.
 *
 * @param index Index of the constant argument within the encoder.
 * @return void* Pointer to the constant data for the argument at the specified index.
 */
_MTL_INLINE void* MTL::ArgumentEncoder::constantData(NS::UInteger index)
{
    return Object::sendMessage<void*>(this, _MTL_PRIVATE_SEL(constantDataAtIndex_), index);
}

/**
 * @brief Gets the Metal device associated with this argument encoder.
 *
 * @return MTL::Device* Pointer to the device associated with this encoder.
 */
_MTL_INLINE MTL::Device* MTL::ArgumentEncoder::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Query the total encoded length used by this argument encoder.
 *
 * @return NS::UInteger The total byte length of the encoded argument data.
 */
_MTL_INLINE NS::UInteger MTL::ArgumentEncoder::encodedLength() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(encodedLength));
}

/**
 * @brief The label assigned to this argument encoder.
 *
 * @return NS::String* Pointer to the encoder's label string, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::ArgumentEncoder::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Creates an argument encoder for the buffer at the specified index.
 *
 * Creates or retrieves an ArgumentEncoder configured to encode arguments into the buffer binding at `index`.
 *
 * @param index Buffer binding index to create the encoder for.
 * @return MTL::ArgumentEncoder* Pointer to an ArgumentEncoder for the buffer at `index`.
 */
_MTL_INLINE MTL::ArgumentEncoder* MTL::ArgumentEncoder::newArgumentEncoder(NS::UInteger index)
{
    return Object::sendMessage<MTL::ArgumentEncoder*>(this, _MTL_PRIVATE_SEL(newArgumentEncoderForBufferAtIndex_), index);
}

/**
 * @brief Sets an acceleration structure into the encoder at the specified binding index.
 *
 * @param accelerationStructure Pointer to the acceleration structure to bind.
 * @param index Binding index within the argument buffer where the acceleration structure will be placed.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setAccelerationStructure(const MTL::AccelerationStructure* accelerationStructure, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAccelerationStructure_atIndex_), accelerationStructure, index);
}

/**
 * @brief Assigns the destination buffer and byte offset used for encoding arguments.
 *
 * Sets the argument buffer that this encoder will write into and the byte offset within that buffer
 * where the encoded arguments begin.
 *
 * @param argumentBuffer Pointer to the buffer to receive encoded arguments.
 * @param offset Byte offset into `argumentBuffer` where encoding starts.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setArgumentBuffer(const MTL::Buffer* argumentBuffer, NS::UInteger offset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setArgumentBuffer_offset_), argumentBuffer, offset);
}

/**
 * @brief Associates an argument buffer with this encoder and specifies its position.
 *
 * Binds the provided buffer as the encoder's argument buffer using the given byte start offset
 * and selects which array element within the argument buffer's array-type binding to target.
 *
 * @param argumentBuffer Buffer to bind as the argument buffer.
 * @param startOffset Byte offset into the buffer where the encoder's arguments begin.
 * @param arrayElement Index of the array element within the argument binding to address.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setArgumentBuffer(const MTL::Buffer* argumentBuffer, NS::UInteger startOffset, NS::UInteger arrayElement)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setArgumentBuffer_startOffset_arrayElement_), argumentBuffer, startOffset, arrayElement);
}

/**
 * @brief Bind a buffer to this argument encoder at a specific argument index with a byte offset.
 *
 * @param buffer The buffer to bind.
 * @param offset Byte offset into the buffer where the binding should start.
 * @param index The argument index within the encoder to set the buffer.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBuffer_offset_atIndex_), buffer, offset, index);
}

/**
 * @brief Sets multiple buffer bindings and their corresponding offsets over a contiguous range of argument indices.
 *
 * @param buffers Array of pointers to `MTL::Buffer` objects; each element is bound to the argument index at (range.location + i).
 * @param offsets Array of byte offsets for each buffer; `offsets[i]` applies to `buffers[i]`. The array must contain at least `range.length` entries.
 * @param range The starting argument index (`location`) and number of entries (`length`) to update.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setBuffers(const MTL::Buffer* const buffers[], const NS::UInteger offsets[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBuffers_offsets_withRange_), buffers, offsets, range);
}

/**
 * @brief Binds a compute pipeline state to the encoder at the specified argument index.
 *
 * Associates the provided compute pipeline state with the encoder so the pipeline is used
 * when the argument at `index` is accessed during encoding or execution.
 *
 * @param pipeline Compute pipeline state to bind.
 * @param index Index of the argument slot to which the pipeline state will be bound.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setComputePipelineState(const MTL::ComputePipelineState* pipeline, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setComputePipelineState_atIndex_), pipeline, index);
}

/**
 * @brief Sets multiple compute pipeline state objects for the specified binding range.
 *
 * @param pipelines Array of pointers to ComputePipelineState; elements corresponding to `range` will be bound.
 * @param range The contiguous range of argument indices to populate from `pipelines`.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setComputePipelineStates(const MTL::ComputePipelineState* const pipelines[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setComputePipelineStates_withRange_), pipelines, range);
}

/**
 * @brief Sets the depth-stencil state bound to the argument encoder at the specified index.
 *
 * @param depthStencilState DepthStencilState to bind at the given index.
 * @param index Binding index within the argument encoder where the depth-stencil state will be set.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setDepthStencilState(const MTL::DepthStencilState* depthStencilState, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthStencilState_atIndex_), depthStencilState, index);
}

/**
 * @brief Sets multiple depth-stencil state objects into the argument encoder over a contiguous binding range.
 *
 * @param depthStencilStates Array of pointers to MTL::DepthStencilState whose elements are bound to the encoder; each element maps to a consecutive index within `range`.
 * @param range The contiguous range of argument indices to which the provided states will be applied.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setDepthStencilStates(const MTL::DepthStencilState* const depthStencilStates[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthStencilStates_withRange_), depthStencilStates, range);
}

/**
 * @brief Binds an indirect command buffer to this encoder at the specified argument index.
 *
 * @param indirectCommandBuffer Pointer to the indirect command buffer to bind; pass `nullptr` to clear the binding.
 * @param index Argument index within the encoder where the buffer will be set.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setIndirectCommandBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIndirectCommandBuffer_atIndex_), indirectCommandBuffer, index);
}

/**
 * @brief Sets multiple indirect command buffers into the encoder for a consecutive range of bindings.
 *
 * The provided array supplies pointers to IndirectCommandBuffer objects that are bound to the encoder
 * at consecutive indices starting from range.location. Exactly range.length entries from the buffers
 * array are consumed.
 *
 * @param buffers Array of pointers to IndirectCommandBuffer objects to bind.
 * @param range  Range of binding indices to populate (start index in `location` and number in `length`).
 */
_MTL_INLINE void MTL::ArgumentEncoder::setIndirectCommandBuffers(const MTL::IndirectCommandBuffer* const buffers[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIndirectCommandBuffers_withRange_), buffers, range);
}

/**
 * @brief Sets the intersection function table for the specified argument index.
 *
 * Binds the provided IntersectionFunctionTable to this encoder at the given argument slot.
 *
 * @param intersectionFunctionTable Pointer to the IntersectionFunctionTable to bind; may be `nullptr` to unbind.
 * @param index Argument slot index at which to set the table.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setIntersectionFunctionTable(const MTL::IntersectionFunctionTable* intersectionFunctionTable, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIntersectionFunctionTable_atIndex_), intersectionFunctionTable, index);
}

/**
 * @brief Binds multiple intersection function tables to the encoder for a contiguous range of argument indices.
 *
 * Associates each entry in `intersectionFunctionTables` with the corresponding argument index within `range`.
 *
 * @param intersectionFunctionTables Array of pointers to IntersectionFunctionTable objects to bind. The array must contain at least `range.length` entries.
 * @param range Range of argument indices to set; `range.location` is the first index and `range.length` is the number of consecutive slots to populate.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setIntersectionFunctionTables(const MTL::IntersectionFunctionTable* const intersectionFunctionTables[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIntersectionFunctionTables_withRange_), intersectionFunctionTables, range);
}

/**
 * @brief Sets the encoder's human-readable label.
 *
 * @param label The label to assign to the encoder; pass `nullptr` to clear the label.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Sets the render pipeline state for the encoder at the specified argument index.
 *
 * @param pipeline The render pipeline state to bind into the argument encoder.
 * @param index The argument buffer index at which to set the pipeline state.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setRenderPipelineState(const MTL::RenderPipelineState* pipeline, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRenderPipelineState_atIndex_), pipeline, index);
}

/**
 * @brief Sets multiple render pipeline states for consecutive argument indices.
 *
 * @param pipelines Array of pointers to RenderPipelineState objects; elements correspond to argument indices starting at `range.location`.
 * @param range The location and length within `pipelines` to apply.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setRenderPipelineStates(const MTL::RenderPipelineState* const pipelines[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRenderPipelineStates_withRange_), pipelines, range);
}

/**
 * @brief Assigns a sampler state to the argument encoder at the given binding index.
 *
 * @param sampler The sampler state to bind to the encoder.
 * @param index The binding index within the argument encoder where the sampler will be set.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setSamplerState(const MTL::SamplerState* sampler, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSamplerState_atIndex_), sampler, index);
}

/**
 * @brief Sets sampler states for a consecutive range of argument indices.
 *
 * Assigns the sampler state pointers from `samplers` to the argument encoder slots specified by `range`.
 *
 * @param samplers Array of sampler state pointers; each element maps to a slot within `range`.
 * @param range Range of argument indices to set (location is the first index, length is the number of slots).
 */
_MTL_INLINE void MTL::ArgumentEncoder::setSamplerStates(const MTL::SamplerState* const samplers[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSamplerStates_withRange_), samplers, range);
}

/**
 * @brief Bind a texture to the argument encoder at the specified slot.
 *
 * @param texture The texture to assign to the encoder slot.
 * @param index The argument index (slot) within the encoder where the texture will be set.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setTexture(const MTL::Texture* texture, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTexture_atIndex_), texture, index);
}

/**
 * @brief Binds an array of textures into the encoder for a contiguous range of argument indices.
 *
 * Sets the encoder's texture bindings starting at `range.location` for `range.length` entries using the pointers in `textures`.
 *
 * @param textures Array of pointers to `MTL::Texture` objects to bind; elements correspond to consecutive indices starting at `range.location`.
 * @param range The contiguous range of argument indices to set.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setTextures(const MTL::Texture* const textures[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTextures_withRange_), textures, range);
}

/**
 * @brief Binds a visible function table to this argument encoder at the specified argument index.
 *
 * @param visibleFunctionTable The visible function table to bind; pass `nullptr` to clear the binding.
 * @param index The argument index where the visible function table will be placed.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setVisibleFunctionTable(const MTL::VisibleFunctionTable* visibleFunctionTable, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVisibleFunctionTable_atIndex_), visibleFunctionTable, index);
}

/**
 * @brief Sets multiple visible function tables into the encoder for a contiguous range of argument indices.
 *
 * @param visibleFunctionTables Array of pointers to VisibleFunctionTable objects to bind; entries are bound in order to the indices specified by `range`.
 * @param range Range of argument indices specifying where to bind the tables; the array must contain at least `range.length` elements.
 */
_MTL_INLINE void MTL::ArgumentEncoder::setVisibleFunctionTables(const MTL::VisibleFunctionTable* const visibleFunctionTables[], NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVisibleFunctionTables_withRange_), visibleFunctionTables, range);
}