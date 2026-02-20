//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4RenderCommandEncoder.hpp
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
#include "MTL4CommandEncoder.hpp"
#include "MTL4Counters.hpp"
#include "MTLArgument.hpp"
#include "MTLDefines.hpp"
#include "MTLGPUAddress.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLRenderCommandEncoder.hpp"
#include "MTLRenderPass.hpp"
#include "MTLTypes.hpp"
#include <cstdint>

namespace MTL4
{
class ArgumentTable;
class CounterHeap;
}

namespace MTL
{
class DepthStencilState;
class IndirectCommandBuffer;
class LogicalToPhysicalColorAttachmentMap;
class RenderPipelineState;
struct ScissorRect;
struct VertexAmplificationViewMapping;
struct Viewport;

}
namespace MTL4
{
/**
 * @brief Dispatches a fixed number of threads per tile.
 *
 * @param threadsPerTile Number of threads to dispatch for each tile.
 */

/**
 * @brief Draws indexed primitives using a GPU index buffer.
 *
 * @param primitiveType Type of primitive to draw.
 * @param indexCount Number of indices to read from the index buffer.
 * @param indexType Type of indices stored in the index buffer.
 * @param indexBuffer GPU address of the index buffer.
 * @param indexBufferLength Length, in bytes, of the index buffer region to use.
 */

/**
 * @brief Draws indexed primitives with an instance count.
 *
 * @param primitiveType Type of primitive to draw.
 * @param indexCount Number of indices to read from the index buffer.
 * @param indexType Type of indices stored in the index buffer.
 * @param indexBuffer GPU address of the index buffer.
 * @param indexBufferLength Length, in bytes, of the index buffer region to use.
 * @param instanceCount Number of instances to draw.
 */

/**
 * @brief Draws indexed primitives with base vertex and base instance offsets.
 *
 * @param primitiveType Type of primitive to draw.
 * @param indexCount Number of indices to read from the index buffer.
 * @param indexType Type of indices stored in the index buffer.
 * @param indexBuffer GPU address of the index buffer.
 * @param indexBufferLength Length, in bytes, of the index buffer region to use.
 * @param instanceCount Number of instances to draw.
 * @param baseVertex Vertex index added to each index from the index buffer.
 * @param baseInstance Instance ID offset applied to each generated instance.
 */

/**
 * @brief Draws indexed primitives using an indirect index buffer.
 *
 * @param primitiveType Type of primitive to draw.
 * @param indexType Type of indices stored in the index buffer.
 * @param indexBuffer GPU address of the index buffer containing index data.
 * @param indexBufferLength Length, in bytes, of the index buffer region to use.
 * @param indirectBuffer GPU address of the indirect buffer providing draw parameters.
 */

/**
 * @brief Dispatches mesh threadgroups for a grid with specified per-object and per-mesh threadgroups.
 *
 * @param threadgroupsPerGrid Number of threadgroups per grid.
 * @param threadsPerObjectThreadgroup Threads per object threadgroup.
 * @param threadsPerMeshThreadgroup Threads per mesh threadgroup.
 */

/**
 * @brief Dispatches mesh threadgroups using an indirect buffer to provide threadgroup counts.
 *
 * @param indirectBuffer GPU address of the indirect buffer supplying threadgroup counts.
 * @param threadsPerObjectThreadgroup Threads per object threadgroup.
 * @param threadsPerMeshThreadgroup Threads per mesh threadgroup.
 */

/**
 * @brief Dispatches mesh threads for a grid with specified per-object and per-mesh threadgroups.
 *
 * @param threadsPerGrid Number of threads for the grid.
 * @param threadsPerObjectThreadgroup Threads per object threadgroup.
 * @param threadsPerMeshThreadgroup Threads per mesh threadgroup.
 */

/**
 * @brief Draws non-indexed primitives from a contiguous vertex range.
 *
 * @param primitiveType Type of primitive to draw.
 * @param vertexStart Starting vertex index.
 * @param vertexCount Number of vertices to read.
 */

/**
 * @brief Draws non-indexed primitives with instancing.
 *
 * @param primitiveType Type of primitive to draw.
 * @param vertexStart Starting vertex index.
 * @param vertexCount Number of vertices to read.
 * @param instanceCount Number of instances to draw.
 */

/**
 * @brief Draws non-indexed primitives with instancing and a base instance offset.
 *
 * @param primitiveType Type of primitive to draw.
 * @param vertexStart Starting vertex index.
 * @param vertexCount Number of vertices to read.
 * @param instanceCount Number of instances to draw.
 * @param baseInstance Instance ID offset applied to each generated instance.
 */

/**
 * @brief Draws non-indexed primitives using parameters supplied via an indirect buffer.
 *
 * @param primitiveType Type of primitive to draw.
 * @param indirectBuffer GPU address of the indirect buffer containing draw parameters.
 */

/**
 * @brief Executes a range of commands from an indirect command buffer.
 *
 * @param indirectCommandBuffer Indirect command buffer to execute commands from.
 * @param executionRange Range of commands within the indirect command buffer to execute.
 */

/**
 * @brief Executes commands from an indirect command buffer using an indirect range buffer.
 *
 * @param indirectCommandBuffer Indirect command buffer to execute commands from.
 * @param indirectRangeBuffer GPU address of the buffer that encodes the range(s) to execute.
 */

/**
 * @brief Binds an argument table for specified shader stages.
 *
 * @param argumentTable Argument table to bind.
 * @param stages Shader stages that will use the bound argument table.
 */

/**
 * @brief Sets the blend color used by blend operations.
 *
 * @param red Red component in linear color space.
 * @param green Green component in linear color space.
 * @param blue Blue component in linear color space.
 * @param alpha Alpha component.
 */

/**
 * @brief Sets a logical-to-physical color attachment mapping.
 *
 * @param mapping Mapping that translates logical color attachment indices to physical attachments.
 */

/**
 * @brief Sets the store action for a specific color attachment.
 *
 * @param storeAction Store action to apply when the render pass ends.
 * @param colorAttachmentIndex Index of the color attachment to configure.
 */

/**
 * @brief Sets the face culling mode.
 *
 * @param cullMode Culling mode to apply (none, front, back).
 */

/**
 * @brief Configures polygon depth bias parameters.
 *
 * @param depthBias Constant depth bias to add to fragment depths.
 * @param slopeScale Scale factor applied to the depth bias based on polygon slope.
 * @param clamp Maximum absolute depth bias value.
 */

/**
 * @brief Sets the depth clipping behavior for the rasterizer.
 *
 * @param depthClipMode Depth clip mode to apply.
 */

/**
 * @brief Binds a depth-stencil state object.
 *
 * @param depthStencilState Depth-stencil state to bind.
 */

/**
 * @brief Sets the depth buffer store action.
 *
 * @param storeAction Store action to apply to the depth attachment at the end of the pass.
 */

/**
 * @brief Sets depth test bounds used to accept or reject fragments.
 *
 * @param minBound Minimum depth bound.
 * @param maxBound Maximum depth bound.
 */

/**
 * @brief Sets the winding order considered front-facing.
 *
 * @param frontFacingWinding Winding order for front-facing primitives.
 */

/**
 * @brief Configures object-local threadgroup memory length for a shader function.
 *
 * @param length Length, in bytes, of the threadgroup memory region.
 * @param index Index identifying which object-local threadgroup memory slot to configure.
 */

/**
 * @brief Binds a render pipeline state for subsequent draw calls.
 *
 * @param pipelineState Render pipeline state to bind.
 */

/**
 * @brief Sets a single scissor rectangle.
 *
 * @param rect Scissor rectangle to apply.
 */

/**
 * @brief Sets multiple scissor rectangles.
 *
 * @param scissorRects Pointer to an array of scissor rectangles.
 * @param count Number of rectangles in the array.
 */

/**
 * @brief Sets a unified stencil reference value for both front and back faces.
 *
 * @param referenceValue Stencil reference value to use.
 */

/**
 * @brief Sets separate stencil reference values for front and back faces.
 *
 * @param frontReferenceValue Stencil reference value for front faces.
 * @param backReferenceValue Stencil reference value for back faces.
 */

/**
 * @brief Sets the stencil buffer store action.
 *
 * @param storeAction Store action to apply to the stencil attachment at the end of the pass.
 */

/**
 * @brief Sets threadgroup memory length with an offset for a specific index.
 *
 * @param length Length, in bytes, of the memory region.
 * @param offset Offset, in bytes, from the base of the threadgroup memory.
 * @param index Index identifying which threadgroup memory slot to configure.
 */

/**
 * @brief Sets the triangle fill mode used for rasterization.
 *
 * @param fillMode Fill mode to apply to triangle primitives.
 */

/**
 * @brief Configures vertex amplification for instanced drawing.
 *
 * @param count Number of amplified vertex streams.
 * @param viewMappings Mapping array that associates amplified views with render target indices.
 */

/**
 * @brief Sets a single viewport.
 *
 * @param viewport Viewport to apply.
 */

/**
 * @brief Sets multiple viewports.
 *
 * @param viewports Pointer to an array of viewports.
 * @param count Number of viewports in the array.
 */

/**
 * @brief Configures the visibility result mode and the destination offset.
 *
 * @param mode Visibility result mode to use.
 * @param offset Byte offset into the visibility buffer where results will be written.
 */

/**
 * @brief Returns the tile height used by tile-based rasterization.
 *
 * @return NS::UInteger Tile height in pixels.
 */

/**
 * @brief Returns the tile width used by tile-based rasterization.
 *
 * @return NS::UInteger Tile width in pixels.
 */

/**
 * @brief Writes a timestamp into a counter heap for the specified render stage and slot.
 *
 * @param granularity Timestamp granularity to use.
 * @param stage Render stage at which the timestamp is taken.
 * @param counterHeap Counter heap where the timestamp will be stored.
 * @param index Index into the counter heap where the timestamp will be written.
 */
_MTL_OPTIONS(NS::UInteger, RenderEncoderOptions) {
    RenderEncoderOptionNone = 0,
    RenderEncoderOptionSuspending = 1,
    RenderEncoderOptionResuming = 1 << 1,
};

class RenderCommandEncoder : public NS::Referencing<RenderCommandEncoder, CommandEncoder>
{
public:
    void         dispatchThreadsPerTile(MTL::Size threadsPerTile);

    void         drawIndexedPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger indexCount, MTL::IndexType indexType, MTL::GPUAddress indexBuffer, NS::UInteger indexBufferLength);
    void         drawIndexedPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger indexCount, MTL::IndexType indexType, MTL::GPUAddress indexBuffer, NS::UInteger indexBufferLength, NS::UInteger instanceCount);
    void         drawIndexedPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger indexCount, MTL::IndexType indexType, MTL::GPUAddress indexBuffer, NS::UInteger indexBufferLength, NS::UInteger instanceCount, NS::Integer baseVertex, NS::UInteger baseInstance);
    void         drawIndexedPrimitives(MTL::PrimitiveType primitiveType, MTL::IndexType indexType, MTL::GPUAddress indexBuffer, NS::UInteger indexBufferLength, MTL::GPUAddress indirectBuffer);

    void         drawMeshThreadgroups(MTL::Size threadgroupsPerGrid, MTL::Size threadsPerObjectThreadgroup, MTL::Size threadsPerMeshThreadgroup);
    void         drawMeshThreadgroups(MTL::GPUAddress indirectBuffer, MTL::Size threadsPerObjectThreadgroup, MTL::Size threadsPerMeshThreadgroup);

    void         drawMeshThreads(MTL::Size threadsPerGrid, MTL::Size threadsPerObjectThreadgroup, MTL::Size threadsPerMeshThreadgroup);

    void         drawPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger vertexStart, NS::UInteger vertexCount);
    void         drawPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger vertexStart, NS::UInteger vertexCount, NS::UInteger instanceCount);
    void         drawPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger vertexStart, NS::UInteger vertexCount, NS::UInteger instanceCount, NS::UInteger baseInstance);
    void         drawPrimitives(MTL::PrimitiveType primitiveType, MTL::GPUAddress indirectBuffer);

    void         executeCommandsInBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, NS::Range executionRange);
    void         executeCommandsInBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, MTL::GPUAddress indirectRangeBuffer);

    void         setArgumentTable(const MTL4::ArgumentTable* argumentTable, MTL::RenderStages stages);

    void         setBlendColor(float red, float green, float blue, float alpha);

    void         setColorAttachmentMap(const MTL::LogicalToPhysicalColorAttachmentMap* mapping);

    void         setColorStoreAction(MTL::StoreAction storeAction, NS::UInteger colorAttachmentIndex);

    void         setCullMode(MTL::CullMode cullMode);

    void         setDepthBias(float depthBias, float slopeScale, float clamp);

    void         setDepthClipMode(MTL::DepthClipMode depthClipMode);

    void         setDepthStencilState(const MTL::DepthStencilState* depthStencilState);

    void         setDepthStoreAction(MTL::StoreAction storeAction);

    void         setDepthTestBounds(float minBound, float maxBound);

    void         setFrontFacingWinding(MTL::Winding frontFacingWinding);

    void         setObjectThreadgroupMemoryLength(NS::UInteger length, NS::UInteger index);

    void         setRenderPipelineState(const MTL::RenderPipelineState* pipelineState);

    void         setScissorRect(MTL::ScissorRect rect);
    void         setScissorRects(const MTL::ScissorRect* scissorRects, NS::UInteger count);

    void         setStencilReferenceValue(uint32_t referenceValue);
    void         setStencilReferenceValues(uint32_t frontReferenceValue, uint32_t backReferenceValue);

    void         setStencilStoreAction(MTL::StoreAction storeAction);

    void         setThreadgroupMemoryLength(NS::UInteger length, NS::UInteger offset, NS::UInteger index);

    void         setTriangleFillMode(MTL::TriangleFillMode fillMode);

    void         setVertexAmplificationCount(NS::UInteger count, const MTL::VertexAmplificationViewMapping* viewMappings);

    void         setViewport(MTL::Viewport viewport);
    void         setViewports(const MTL::Viewport* viewports, NS::UInteger count);

    void         setVisibilityResultMode(MTL::VisibilityResultMode mode, NS::UInteger offset);

    NS::UInteger tileHeight() const;

    NS::UInteger tileWidth() const;

    void         writeTimestamp(MTL4::TimestampGranularity granularity, MTL::RenderStages stage, const MTL4::CounterHeap* counterHeap, NS::UInteger index);
};

}
/**
 * @brief Dispatches rendering threads per tile using the specified threadgroup size.
 *
 * @param threadsPerTile The threadgroup dimensions (width, height, depth) to dispatch for each tile.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::dispatchThreadsPerTile(MTL::Size threadsPerTile)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(dispatchThreadsPerTile_), threadsPerTile);
}

/**
 * @brief Encodes an indexed draw of primitives using an index buffer addressed by a GPU address.
 *
 * @param primitiveType The primitive topology to render (e.g., triangle, line).
 * @param indexCount The number of indices to read from the index buffer.
 * @param indexType The integer size of each index (e.g., 16-bit or 32-bit).
 * @param indexBuffer GPU address pointing to the start of the index buffer.
 * @param indexBufferLength The size in bytes of the index data region referenced by `indexBuffer`.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::drawIndexedPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger indexCount, MTL::IndexType indexType, MTL::GPUAddress indexBuffer, NS::UInteger indexBufferLength)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawIndexedPrimitives_indexCount_indexType_indexBuffer_indexBufferLength_), primitiveType, indexCount, indexType, indexBuffer, indexBufferLength);
}

/**
 * @brief Encode an indexed draw call that reads indices from a GPU address.
 *
 * @param primitiveType The primitive topology to render (e.g., triangle, line).
 * @param indexCount The number of indices to read from the index buffer.
 * @param indexType The type/size of each index element (e.g., 16-bit or 32-bit).
 * @param indexBuffer GPU address of the index buffer region to read from.
 * @param indexBufferLength Length in bytes of the index buffer region referenced by `indexBuffer`.
 * @param instanceCount Number of instances to draw.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::drawIndexedPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger indexCount, MTL::IndexType indexType, MTL::GPUAddress indexBuffer, NS::UInteger indexBufferLength, NS::UInteger instanceCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawIndexedPrimitives_indexCount_indexType_indexBuffer_indexBufferLength_instanceCount_), primitiveType, indexCount, indexType, indexBuffer, indexBufferLength, instanceCount);
}

/**
 * @brief Encodes an indexed draw call with per-draw vertex and instance offsets.
 *
 * @param primitiveType Type of primitives to render.
 * @param indexCount Number of indices to read from the index buffer.
 * @param indexType Size/type of each index value.
 * @param indexBuffer GPU virtual address of the index buffer.
 * @param indexBufferLength Byte offset into the index buffer where indices begin.
 * @param instanceCount Number of instances to draw.
 * @param baseVertex Value added to each index to form final vertex indices.
 * @param baseInstance Starting instance ID for the draw (added to per-instance values).
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::drawIndexedPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger indexCount, MTL::IndexType indexType, MTL::GPUAddress indexBuffer, NS::UInteger indexBufferLength, NS::UInteger instanceCount, NS::Integer baseVertex, NS::UInteger baseInstance)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawIndexedPrimitives_indexCount_indexType_indexBuffer_indexBufferLength_instanceCount_baseVertex_baseInstance_), primitiveType, indexCount, indexType, indexBuffer, indexBufferLength, instanceCount, baseVertex, baseInstance);
}

/**
 * @brief Issues an indexed draw using an indirect index buffer for draw parameters.
 *
 * @param primitiveType Type of primitives to render (points, lines, triangles, etc.).
 * @param indexType Format of indices stored in the index buffer.
 * @param indexBuffer GPU address of the index buffer containing index data.
 * @param indexBufferLength Byte length of the index buffer.
 * @param indirectBuffer GPU address of the buffer that contains indirect draw parameters (draw count, instance count, offsets, etc.).
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::drawIndexedPrimitives(MTL::PrimitiveType primitiveType, MTL::IndexType indexType, MTL::GPUAddress indexBuffer, NS::UInteger indexBufferLength, MTL::GPUAddress indirectBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawIndexedPrimitives_indexType_indexBuffer_indexBufferLength_indirectBuffer_), primitiveType, indexType, indexBuffer, indexBufferLength, indirectBuffer);
}

/**
 * @brief Encodes a mesh draw that dispatches threadgroups across a grid using separate object- and mesh-level threadgroup sizes.
 *
 * @param threadgroupsPerGrid The grid dimensions (width, height, depth) specifying how many threadgroups to execute.
 * @param threadsPerObjectThreadgroup The number of threads in each object-level threadgroup.
 * @param threadsPerMeshThreadgroup The number of threads in each mesh-level threadgroup.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::drawMeshThreadgroups(MTL::Size threadgroupsPerGrid, MTL::Size threadsPerObjectThreadgroup, MTL::Size threadsPerMeshThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawMeshThreadgroups_threadsPerObjectThreadgroup_threadsPerMeshThreadgroup_), threadgroupsPerGrid, threadsPerObjectThreadgroup, threadsPerMeshThreadgroup);
}

/**
 * @brief Issues a mesh-threadgroup draw specified by an indirect buffer.
 *
 * Dispatches mesh threadgroups using draw/dispatch parameters sourced from the indirect buffer at the specified GPU address, with the given per-object and per-mesh threadgroup sizes.
 *
 * @param indirectBuffer GPU address of the indirect buffer containing draw/dispatch parameters.
 * @param threadsPerObjectThreadgroup Number of threads in each object threadgroup.
 * @param threadsPerMeshThreadgroup Number of threads in each mesh threadgroup.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::drawMeshThreadgroups(MTL::GPUAddress indirectBuffer, MTL::Size threadsPerObjectThreadgroup, MTL::Size threadsPerMeshThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawMeshThreadgroupsWithIndirectBuffer_threadsPerObjectThreadgroup_threadsPerMeshThreadgroup_), indirectBuffer, threadsPerObjectThreadgroup, threadsPerMeshThreadgroup);
}

/**
 * @brief Dispatches a mesh shading workload using the provided grid and threadgroup dimensions.
 *
 * @param threadsPerGrid Total number of threads to execute across the dispatch grid (x, y, z).
 * @param threadsPerObjectThreadgroup Number of threads in each object-level threadgroup (x, y, z).
 * @param threadsPerMeshThreadgroup Number of threads in each mesh-level threadgroup (x, y, z).
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::drawMeshThreads(MTL::Size threadsPerGrid, MTL::Size threadsPerObjectThreadgroup, MTL::Size threadsPerMeshThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawMeshThreads_threadsPerObjectThreadgroup_threadsPerMeshThreadgroup_), threadsPerGrid, threadsPerObjectThreadgroup, threadsPerMeshThreadgroup);
}

/**
 * @brief Encodes a non-indexed draw of primitives.
 *
 * Encodes a draw call that renders `vertexCount` vertices as primitives of type `primitiveType`,
 * starting at vertex index `vertexStart`.
 *
 * @param primitiveType Type of primitives to render.
 * @param vertexStart Index of the first vertex to use.
 * @param vertexCount Number of vertices to render.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::drawPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger vertexStart, NS::UInteger vertexCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawPrimitives_vertexStart_vertexCount_), primitiveType, vertexStart, vertexCount);
}

/**
 * @brief Encodes a non‑indexed draw call that emits a sequence of primitives.
 *
 * Draws primitives of the specified type starting at `vertexStart` for `vertexCount`
 * vertices and repeats the draw `instanceCount` times for instanced rendering.
 *
 * @param primitiveType The kind of primitives to render (points, lines, triangles, etc.).
 * @param vertexStart Index of the first vertex to read from vertex buffers.
 * @param vertexCount Number of vertices to read per instance.
 * @param instanceCount Number of instances to draw.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::drawPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger vertexStart, NS::UInteger vertexCount, NS::UInteger instanceCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawPrimitives_vertexStart_vertexCount_instanceCount_), primitiveType, vertexStart, vertexCount, instanceCount);
}

/**
 * @brief Encodes a non-indexed draw of primitives into the render command stream.
 *
 * @param primitiveType Type of primitives to render.
 * @param vertexStart Starting vertex index within the vertex buffer.
 * @param vertexCount Number of vertices to draw per instance.
 * @param instanceCount Number of instances to draw.
 * @param baseInstance Value added to the per-instance attribute index for each instance.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::drawPrimitives(MTL::PrimitiveType primitiveType, NS::UInteger vertexStart, NS::UInteger vertexCount, NS::UInteger instanceCount, NS::UInteger baseInstance)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawPrimitives_vertexStart_vertexCount_instanceCount_baseInstance_), primitiveType, vertexStart, vertexCount, instanceCount, baseInstance);
}

/**
 * @brief Draws non-indexed primitives using parameters read from an indirect buffer.
 *
 * @param primitiveType The type of primitive to render (points, lines, triangles, etc.).
 * @param indirectBuffer GPU address of a buffer that contains the indirect draw parameters.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::drawPrimitives(MTL::PrimitiveType primitiveType, MTL::GPUAddress indirectBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(drawPrimitives_indirectBuffer_), primitiveType, indirectBuffer);
}

/**
 * @brief Executes commands encoded in an indirect command buffer over a specified range.
 *
 * @param indirectCommandBuffer The indirect command buffer containing encoded commands to execute.
 * @param executionRange The range of commands within the buffer to execute.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::executeCommandsInBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, NS::Range executionRange)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(executeCommandsInBuffer_withRange_), indirectCommandBuffer, executionRange);
}

/**
 * @brief Executes commands encoded in an indirect command buffer using a GPU-side range descriptor.
 *
 * Executes the commands recorded in `indirectCommandBuffer`, where `indirectRangeBuffer` is a GPU address pointing to a buffer that contains the indirect range(s) describing which commands (and how many) to execute.
 *
 * @param indirectCommandBuffer The indirect command buffer whose recorded commands will be executed.
 * @param indirectRangeBuffer GPU address of a buffer containing indirect range descriptors that select command ranges within the indirect command buffer.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::executeCommandsInBuffer(const MTL::IndirectCommandBuffer* indirectCommandBuffer, MTL::GPUAddress indirectRangeBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(executeCommandsInBuffer_indirectBuffer_), indirectCommandBuffer, indirectRangeBuffer);
}

/**
 * @brief Binds an argument table to the specified render stages.
 *
 * Associates the provided ArgumentTable with the given render pipeline stages so that those stages use
 * the table for resource binding during encoding.
 *
 * @param argumentTable Pointer to the ArgumentTable to bind (may be null to unbind).
 * @param stages Bitmask of MTL::RenderStages specifying which stages should use the argument table.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setArgumentTable(const MTL4::ArgumentTable* argumentTable, MTL::RenderStages stages)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setArgumentTable_atStages_), argumentTable, stages);
}

/**
 * @brief Sets the constant blend color used by subsequent blending operations.
 *
 * The provided RGBA components define the blend color applied by the pipeline when blend
 * factors or blend operations reference a constant color.
 *
 * @param red Red component of the blend color (typically 0.0 to 1.0).
 * @param green Green component of the blend color (typically 0.0 to 1.0).
 * @param blue Blue component of the blend color (typically 0.0 to 1.0).
 * @param alpha Alpha component of the blend color (typically 0.0 to 1.0).
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setBlendColor(float red, float green, float blue, float alpha)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBlendColorRed_green_blue_alpha_), red, green, blue, alpha);
}

/**
 * @brief Assigns a logical-to-physical color attachment mapping for subsequent draw operations.
 *
 * Associates the provided mapping with this render command encoder so that logical color
 * attachment indices used by the pipeline are translated to physical framebuffer attachments.
 *
 * @param mapping Pointer to a LogicalToPhysicalColorAttachmentMap describing the translation from logical to physical color attachments.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setColorAttachmentMap(const MTL::LogicalToPhysicalColorAttachmentMap* mapping)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setColorAttachmentMap_), mapping);
}

/**
 * @brief Configure how a specific color attachment's contents are stored after rendering.
 *
 * Sets the store action that will be used for the color attachment identified by the given index.
 *
 * @param storeAction The store action to apply to the color attachment.
 * @param colorAttachmentIndex The zero-based index of the color attachment to configure.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setColorStoreAction(MTL::StoreAction storeAction, NS::UInteger colorAttachmentIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setColorStoreAction_atIndex_), storeAction, colorAttachmentIndex);
}

/**
 * @brief Sets the triangle face culling mode used by subsequent draw calls.
 *
 * @param cullMode The culling mode to apply; controls which triangle faces are discarded
 *                 (for example `MTL::CullModeNone`, `MTL::CullModeFront`, `MTL::CullModeBack`).
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setCullMode(MTL::CullMode cullMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCullMode_), cullMode);
}

/**
 * @brief Sets the depth bias parameters used for fragment depth adjustment.
 *
 * Configures the constant depth bias, the slope-scaled bias factor, and the maximum bias clamp applied to fragment depths.
 *
 * @param depthBias Constant depth value added to each fragment's depth.
 * @param slopeScale Multiplier applied to the fragment's maximum depth slope.
 * @param clamp Maximum absolute value to clamp the computed depth bias.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setDepthBias(float depthBias, float slopeScale, float clamp)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthBias_slopeScale_clamp_), depthBias, slopeScale, clamp);
}

/**
 * @brief Sets the depth clipping mode for subsequent draw operations.
 *
 * Controls how geometry outside the depth range is treated during rasterization.
 *
 * @param depthClipMode The depth clip mode that determines how fragments outside the near/far depth range are clipped.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setDepthClipMode(MTL::DepthClipMode depthClipMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthClipMode_), depthClipMode);
}

/**
 * @brief Binds a depth–stencil state to the render encoder for subsequent draw operations.
 *
 * @param depthStencilState The depth–stencil state to set; nullptr clears the bound state.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setDepthStencilState(const MTL::DepthStencilState* depthStencilState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthStencilState_), depthStencilState);
}

/**
 * @brief Sets the store action for the depth attachment at the end of the render pass.
 *
 * @param storeAction Store action to apply to the depth attachment; controls whether depth data is stored, discarded, or resolved when rendering completes.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setDepthStoreAction(MTL::StoreAction storeAction)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthStoreAction_), storeAction);
}

/**
 * @brief Sets the depth test bounds used to compare fragment depths.
 *
 * Configures the minimum and maximum depth values used by the depth test; fragments with depth outside this [minBound, maxBound] range fail the depth test.
 *
 * @param minBound Minimum depth bound; fragments with depth less than this value fail the depth test.
 * @param maxBound Maximum depth bound; fragments with depth greater than this value fail the depth test.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setDepthTestBounds(float minBound, float maxBound)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthTestMinBound_maxBound_), minBound, maxBound);
}

/**
 * @brief Sets the front-face vertex winding used for triangle orientation.
 *
 * Configures which vertex winding (clockwise or counter-clockwise) is treated as the front face for subsequent drawing commands.
 *
 * @param frontFacingWinding The winding that defines a front-facing triangle.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setFrontFacingWinding(MTL::Winding frontFacingWinding)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFrontFacingWinding_), frontFacingWinding);
}

/**
 * @brief Configure the per-object threadgroup memory size for a specific binding index.
 *
 * Reserves `length` bytes of object-local threadgroup (shared) memory at the given `index` for use by subsequently encoded draw/dispatch operations that reference that object threadgroup memory slot.
 *
 * @param length Number of bytes to reserve.
 * @param index Binding index of the object threadgroup memory slot.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setObjectThreadgroupMemoryLength(NS::UInteger length, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObjectThreadgroupMemoryLength_atIndex_), length, index);
}

/**
 * @brief Binds the specified render pipeline state for subsequent draw and dispatch calls.
 *
 * @param pipelineState The render pipeline state to set for the encoder.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setRenderPipelineState(const MTL::RenderPipelineState* pipelineState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRenderPipelineState_), pipelineState);
}

/**
 * @brief Set the scissor rectangle that restricts rasterization and fragment processing.
 *
 * @param rect The scissor rectangle, in render target coordinates, that confines drawing to the specified region.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setScissorRect(MTL::ScissorRect rect)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setScissorRect_), rect);
}

/**
 * @brief Sets multiple scissor rectangles to be used for subsequent draw calls.
 *
 * @param scissorRects Pointer to an array of scissor rectangles; must contain at least `count` elements.
 * @param count Number of scissor rectangles in `scissorRects`.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setScissorRects(const MTL::ScissorRect* scissorRects, NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setScissorRects_count_), scissorRects, count);
}

/**
 * @brief Sets the stencil reference value used for subsequent draw operations.
 *
 * This value is used as the reference for stencil comparisons for both front and back faces.
 *
 * @param referenceValue Stencil reference value to use for stencil tests.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setStencilReferenceValue(uint32_t referenceValue)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStencilReferenceValue_), referenceValue);
}

/**
 * @brief Sets separate stencil reference values for front- and back-facing geometry.
 *
 * @param frontReferenceValue Reference value used for front-facing stencil tests.
 * @param backReferenceValue Reference value used for back-facing stencil tests.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setStencilReferenceValues(uint32_t frontReferenceValue, uint32_t backReferenceValue)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStencilFrontReferenceValue_backReferenceValue_), frontReferenceValue, backReferenceValue);
}

/**
 * @brief Sets the store action to use for the stencil attachment.
 *
 * Specifies how the stencil buffer contents are handled (kept, discarded, or resolved)
 * when the attachment is stored after rendering.
 *
 * @param storeAction The store action to apply to the stencil attachment.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setStencilStoreAction(MTL::StoreAction storeAction)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStencilStoreAction_), storeAction);
}

/**
 * @brief Configure the size and offset of a threadgroup memory binding at a given index.
 *
 * Sets the threadgroup memory length and byte offset for the specified threadgroup memory binding slot.
 *
 * @param length Size in bytes of the threadgroup memory region to bind.
 * @param offset Byte offset into the threadgroup memory where the binding begins.
 * @param index Index of the threadgroup memory binding to configure.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setThreadgroupMemoryLength(NS::UInteger length, NS::UInteger offset, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setThreadgroupMemoryLength_offset_atIndex_), length, offset, index);
}

/**
 * @brief Sets the triangle rasterization fill mode used for subsequent draw calls.
 *
 * @param fillMode The fill mode to apply when rasterizing triangles (controls whether triangles are filled or drawn as wireframe/lines).
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setTriangleFillMode(MTL::TriangleFillMode fillMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTriangleFillMode_), fillMode);
}

/**
 * @brief Configure the vertex amplification count and associated view mappings for subsequent draw calls.
 *
 * Sets how many vertex-amplified instances are generated per input vertex and optionally provides a mapping
 * from amplification view index to a target view.
 *
 * @param count Number of amplified vertices (vertex amplification factor).
 * @param viewMappings Pointer to an array of `MTL::VertexAmplificationViewMapping` entries that map each
 *        amplification view index to a target view; pass `nullptr` to use the default identity mapping.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setVertexAmplificationCount(NS::UInteger count, const MTL::VertexAmplificationViewMapping* viewMappings)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexAmplificationCount_viewMappings_), count, viewMappings);
}

/**
 * @brief Sets the current viewport used for subsequent draw calls.
 *
 * @param viewport The viewport defining the origin, size, and depth range to apply. 
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setViewport(MTL::Viewport viewport)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setViewport_), viewport);
}

/**
 * @brief Sets multiple viewports used for subsequent draw calls.
 *
 * Configures the render command encoder to use the provided array of viewports for rasterization.
 *
 * @param viewports Pointer to the first element of an array of viewports to bind.
 * @param count Number of viewports in the array.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setViewports(const MTL::Viewport* viewports, NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setViewports_count_), viewports, count);
}

/**
 * @brief Configure how and where visibility (occlusion) results are written.
 *
 * Sets the visibility result mode used for occlusion queries and the byte offset
 * within the visibility result buffer where results begin.
 *
 * @param mode The visibility result mode to use (e.g., disabled, boolean, counting).
 * @param offset Byte offset into the visibility result buffer where results will be stored.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::setVisibilityResultMode(MTL::VisibilityResultMode mode, NS::UInteger offset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVisibilityResultMode_offset_), mode, offset);
}

/**
 * @brief Tile height used by this render command encoder.
 *
 * @return Tile height in pixels.
 */
_MTL_INLINE NS::UInteger MTL4::RenderCommandEncoder::tileHeight() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(tileHeight));
}

/**
 * @brief Retrieve the tile width used by the current render command encoder.
 *
 * @return NS::UInteger Tile width in pixels.
 */
_MTL_INLINE NS::UInteger MTL4::RenderCommandEncoder::tileWidth() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(tileWidth));
}

/**
 * @brief Records a timestamp for the current encoding into a counter heap slot.
 *
 * Records a GPU timestamp with the specified granularity and render stage into the
 * provided counter heap at the given slot index.
 *
 * @param granularity The timestamp granularity to use.
 * @param stage The render stage(s) at which the timestamp is recorded.
 * @param counterHeap The counter heap to receive the timestamp.
 * @param index The slot index within the counter heap where the timestamp is written.
 */
_MTL_INLINE void MTL4::RenderCommandEncoder::writeTimestamp(MTL4::TimestampGranularity granularity, MTL::RenderStages stage, const MTL4::CounterHeap* counterHeap, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(writeTimestampWithGranularity_afterStage_intoHeap_atIndex_), granularity, stage, counterHeap, index);
}