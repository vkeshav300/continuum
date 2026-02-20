//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLIndirectCommandBuffer.hpp
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
class IndirectCommandBufferDescriptor;
class IndirectComputeCommand;
class IndirectRenderCommand;

/**
 * @brief Bitflags describing which indirect command types are supported.
 *
 * Combines values to indicate supported indirect command operations such as
 * draws, indexed draws, patch draws, concurrent dispatches, and mesh draws.
 */

/**
 * @brief Range of commands within an indirect command buffer.
 *
 * Represents a contiguous region by a starting command index (`location`) and
 * a number of commands (`length`).
 *
 * @note Packed to match the runtime layout.
 */

/**
 * @brief Descriptor configuring the capabilities and inheritance behavior of an indirect command buffer.
 */

/**
 * @brief Allocate a new descriptor instance.
 *
 * @return IndirectCommandBufferDescriptor* A newly allocated descriptor object.
 */

/**
 * @brief The set of command types enabled for the descriptor.
 *
 * @return IndirectCommandType Bitflags indicating which indirect command types are allowed.
 */

/**
 * @brief Whether commands inherit buffer bindings from the issuing encoder.
 *
 * @return bool `true` if buffer bindings are inherited, `false` otherwise.
 */

/**
 * @brief Whether commands inherit the cull mode state from the issuing encoder.
 *
 * @return bool `true` if cull mode is inherited, `false` otherwise.
 */

/**
 * @brief Whether commands inherit depth bias state from the issuing encoder.
 *
 * @return bool `true` if depth bias is inherited, `false` otherwise.
 */

/**
 * @brief Whether commands inherit depth clip mode from the issuing encoder.
 *
 * @return bool `true` if depth clip mode is inherited, `false` otherwise.
 */

/**
 * @brief Whether commands inherit depth-stencil state from the issuing encoder.
 *
 * @return bool `true` if depth-stencil state is inherited, `false` otherwise.
 */

/**
 * @brief Whether commands inherit front-facing winding from the issuing encoder.
 *
 * @return bool `true` if front-facing winding is inherited, `false` otherwise.
 */

/**
 * @brief Whether commands inherit pipeline state from the issuing encoder.
 *
 * @return bool `true` if pipeline state is inherited, `false` otherwise.
 */

/**
 * @brief Whether commands inherit triangle fill mode from the issuing encoder.
 *
 * @return bool `true` if triangle fill mode is inherited, `false` otherwise.
 */

/**
 * @brief Initialize a newly allocated descriptor.
 *
 * @return IndirectCommandBufferDescriptor* The initialized descriptor instance.
 */

/**
 * @brief Maximum number of fragment buffers that can be bound by commands.
 *
 * @return NS::UInteger The maximum fragment buffer bind count.
 */

/**
 * @brief Maximum number of kernel buffers that can be bound by commands.
 *
 * @return NS::UInteger The maximum kernel buffer bind count.
 */

/**
 * @brief Maximum number of kernel threadgroup memory bindings available to commands.
 *
 * @return NS::UInteger The maximum kernel threadgroup memory bind count.
 */

/**
 * @brief Maximum number of mesh-stage buffers that can be bound by commands.
 *
 * @return NS::UInteger The maximum mesh buffer bind count.
 */

/**
 * @brief Maximum number of object-stage buffers that can be bound by commands.
 *
 * @return NS::UInteger The maximum object buffer bind count.
 */

/**
 * @brief Maximum number of object-stage threadgroup memory bindings available to commands.
 *
 * @return NS::UInteger The maximum object threadgroup memory bind count.
 */

/**
 * @brief Maximum number of vertex buffers that can be bound by commands.
 *
 * @return NS::UInteger The maximum vertex buffer bind count.
 */

/**
 * @brief Set which indirect command types are enabled for the descriptor.
 *
 * @param commandTypes Bitflags specifying allowed indirect command types.
 */

/**
 * @brief Configure whether commands inherit buffer bindings from the issuing encoder.
 *
 * @param inheritBuffers `true` to inherit buffer bindings, `false` to require explicit bindings.
 */

/**
 * @brief Configure whether commands inherit cull mode from the issuing encoder.
 *
 * @param inheritCullMode `true` to inherit cull mode, `false` otherwise.
 */

/**
 * @brief Configure whether commands inherit depth bias from the issuing encoder.
 *
 * @param inheritDepthBias `true` to inherit depth bias, `false` otherwise.
 */

/**
 * @brief Configure whether commands inherit depth clip mode from the issuing encoder.
 *
 * @param inheritDepthClipMode `true` to inherit depth clip mode, `false` otherwise.
 */

/**
 * @brief Configure whether commands inherit depth-stencil state from the issuing encoder.
 *
 * @param inheritDepthStencilState `true` to inherit depth-stencil state, `false` otherwise.
 */

/**
 * @brief Configure whether commands inherit front-facing winding from the issuing encoder.
 *
 * @param inheritFrontFacingWinding `true` to inherit front-facing winding, `false` otherwise.
 */

/**
 * @brief Configure whether commands inherit pipeline state from the issuing encoder.
 *
 * @param inheritPipelineState `true` to inherit pipeline state, `false` otherwise.
 */

/**
 * @brief Configure whether commands inherit triangle fill mode from the issuing encoder.
 *
 * @param inheritTriangleFillMode `true` to inherit triangle fill mode, `false` otherwise.
 */

/**
 * @brief Set the maximum fragment buffer bind count for commands.
 *
 * @param maxFragmentBufferBindCount The maximum number of fragment buffers commands may bind.
 */

/**
 * @brief Set the maximum kernel buffer bind count for commands.
 *
 * @param maxKernelBufferBindCount The maximum number of kernel buffers commands may bind.
 */

/**
 * @brief Set the maximum kernel threadgroup memory bind count for commands.
 *
 * @param maxKernelThreadgroupMemoryBindCount The maximum number of threadgroup memory bindings for kernels.
 */

/**
 * @brief Set the maximum mesh buffer bind count for commands.
 *
 * @param maxMeshBufferBindCount The maximum number of mesh-stage buffers commands may bind.
 */

/**
 * @brief Set the maximum object buffer bind count for commands.
 *
 * @param maxObjectBufferBindCount The maximum number of object-stage buffers commands may bind.
 */

/**
 * @brief Set the maximum object threadgroup memory bind count for commands.
 *
 * @param maxObjectThreadgroupMemoryBindCount The maximum number of object-stage threadgroup memory bindings.
 */

/**
 * @brief Set the maximum vertex buffer bind count for commands.
 *
 * @param maxVertexBufferBindCount The maximum number of vertex buffers commands may bind.
 */

/**
 * @brief Enable or disable color attachment mapping support for the descriptor.
 *
 * @param supportColorAttachmentMapping `true` to enable color attachment mapping support, `false` to disable.
 */

/**
 * @brief Enable or disable dynamic attribute stride support for the descriptor.
 *
 * @param supportDynamicAttributeStride `true` to enable dynamic attribute stride, `false` to disable.
 */

/**
 * @brief Enable or disable ray tracing support for the descriptor.
 *
 * @param supportRayTracing `true` to enable ray tracing support, `false` to disable.
 */

/**
 * @brief Whether color attachment mapping is supported by commands created from this descriptor.
 *
 * @return bool `true` if color attachment mapping is supported, `false` otherwise.
 */

/**
 * @brief Whether dynamic attribute stride is supported by commands created from this descriptor.
 *
 * @return bool `true` if dynamic attribute stride is supported, `false` otherwise.
 */

/**
 * @brief Whether ray tracing is supported by commands created from this descriptor.
 *
 * @return bool `true` if ray tracing is supported, `false` otherwise.
 */

/**
 * @brief Returns the GPU resource identifier for the indirect command buffer.
 *
 * @return ResourceID The identifier of the underlying GPU resource.
 */

/**
 * @brief Retrieve an indirect compute command at the given index.
 *
 * @param commandIndex The index of the command to retrieve.
 * @return IndirectComputeCommand* Pointer to the indirect compute command, or `nullptr` if out of range.
 */

/**
 * @brief Retrieve an indirect render command at the given index.
 *
 * @param commandIndex The index of the command to retrieve.
 * @return IndirectRenderCommand* Pointer to the indirect render command, or `nullptr` if out of range.
 */

/**
 * @brief Reset the state of commands within the specified range.
 *
 * @param range The range of commands to reset (location and length).
 */

/**
 * @brief The current number of command slots or capacity of the indirect command buffer.
 *
 * @return NS::UInteger The buffer's size in commands.
 */
_MTL_OPTIONS(NS::UInteger, IndirectCommandType) {
    IndirectCommandTypeDraw = 1,
    IndirectCommandTypeDrawIndexed = 1 << 1,
    IndirectCommandTypeDrawPatches = 1 << 2,
    IndirectCommandTypeDrawIndexedPatches = 1 << 3,
    IndirectCommandTypeConcurrentDispatch = 1 << 5,
    IndirectCommandTypeConcurrentDispatchThreads = 1 << 6,
    IndirectCommandTypeDrawMeshThreadgroups = 1 << 7,
    IndirectCommandTypeDrawMeshThreads = 1 << 8,
};

struct IndirectCommandBufferExecutionRange
{
    uint32_t location;
    uint32_t length;
} _MTL_PACKED;

class IndirectCommandBufferDescriptor : public NS::Copying<IndirectCommandBufferDescriptor>
{
public:
    static IndirectCommandBufferDescriptor* alloc();

    IndirectCommandType                     commandTypes() const;

    bool                                    inheritBuffers() const;

    bool                                    inheritCullMode() const;

    bool                                    inheritDepthBias() const;

    bool                                    inheritDepthClipMode() const;

    bool                                    inheritDepthStencilState() const;

    bool                                    inheritFrontFacingWinding() const;

    bool                                    inheritPipelineState() const;

    bool                                    inheritTriangleFillMode() const;

    IndirectCommandBufferDescriptor*        init();

    NS::UInteger                            maxFragmentBufferBindCount() const;

    NS::UInteger                            maxKernelBufferBindCount() const;

    NS::UInteger                            maxKernelThreadgroupMemoryBindCount() const;

    NS::UInteger                            maxMeshBufferBindCount() const;

    NS::UInteger                            maxObjectBufferBindCount() const;

    NS::UInteger                            maxObjectThreadgroupMemoryBindCount() const;

    NS::UInteger                            maxVertexBufferBindCount() const;

    void                                    setCommandTypes(MTL::IndirectCommandType commandTypes);

    void                                    setInheritBuffers(bool inheritBuffers);

    void                                    setInheritCullMode(bool inheritCullMode);

    void                                    setInheritDepthBias(bool inheritDepthBias);

    void                                    setInheritDepthClipMode(bool inheritDepthClipMode);

    void                                    setInheritDepthStencilState(bool inheritDepthStencilState);

    void                                    setInheritFrontFacingWinding(bool inheritFrontFacingWinding);

    void                                    setInheritPipelineState(bool inheritPipelineState);

    void                                    setInheritTriangleFillMode(bool inheritTriangleFillMode);

    void                                    setMaxFragmentBufferBindCount(NS::UInteger maxFragmentBufferBindCount);

    void                                    setMaxKernelBufferBindCount(NS::UInteger maxKernelBufferBindCount);

    void                                    setMaxKernelThreadgroupMemoryBindCount(NS::UInteger maxKernelThreadgroupMemoryBindCount);

    void                                    setMaxMeshBufferBindCount(NS::UInteger maxMeshBufferBindCount);

    void                                    setMaxObjectBufferBindCount(NS::UInteger maxObjectBufferBindCount);

    void                                    setMaxObjectThreadgroupMemoryBindCount(NS::UInteger maxObjectThreadgroupMemoryBindCount);

    void                                    setMaxVertexBufferBindCount(NS::UInteger maxVertexBufferBindCount);

    void                                    setSupportColorAttachmentMapping(bool supportColorAttachmentMapping);

    void                                    setSupportDynamicAttributeStride(bool supportDynamicAttributeStride);

    void                                    setSupportRayTracing(bool supportRayTracing);

    bool                                    supportColorAttachmentMapping() const;

    bool                                    supportDynamicAttributeStride() const;

    bool                                    supportRayTracing() const;
};
class IndirectCommandBuffer : public NS::Referencing<IndirectCommandBuffer, Resource>
{
public:
    ResourceID              gpuResourceID() const;

    IndirectComputeCommand* indirectComputeCommand(NS::UInteger commandIndex);

    IndirectRenderCommand*  indirectRenderCommand(NS::UInteger commandIndex);

    void                    reset(NS::Range range);

    NS::UInteger            size() const;
};

}

/**
 * @brief Allocates a new IndirectCommandBufferDescriptor instance.
 *
 * The returned object is newly allocated and should be initialized (for example, by calling `init()`).
 *
 * @return MTL::IndirectCommandBufferDescriptor* Pointer to the newly allocated descriptor.
 */
_MTL_INLINE MTL::IndirectCommandBufferDescriptor* MTL::IndirectCommandBufferDescriptor::alloc()
{
    return NS::Object::alloc<MTL::IndirectCommandBufferDescriptor>(_MTL_PRIVATE_CLS(MTLIndirectCommandBufferDescriptor));
}

/**
 * @brief Get the set of indirect command types enabled by this descriptor.
 *
 * @return MTL::IndirectCommandType Bitmask containing one or more `IndirectCommandType` flags that indicate which indirect command types the descriptor supports.
 */
_MTL_INLINE MTL::IndirectCommandType MTL::IndirectCommandBufferDescriptor::commandTypes() const
{
    return Object::sendMessage<MTL::IndirectCommandType>(this, _MTL_PRIVATE_SEL(commandTypes));
}

/**
 * @brief Reports whether indirect commands inherit buffer bindings from their originating encoder.
 *
 * @return `true` if indirect commands inherit buffer bindings, `false` otherwise.
 */
_MTL_INLINE bool MTL::IndirectCommandBufferDescriptor::inheritBuffers() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(inheritBuffers));
}

/**
 * @brief Indicates whether indirect commands inherit the current cull mode.
 *
 * @return `true` if indirect commands inherit the descriptor's cull mode, `false` otherwise.
 */
_MTL_INLINE bool MTL::IndirectCommandBufferDescriptor::inheritCullMode() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(inheritCullMode));
}

/**
 * @brief Indicates whether indirect commands inherit the encoder's depth bias state.
 *
 * @return `true` if indirect commands inherit the encoder's depth bias, `false` otherwise.
 */
_MTL_INLINE bool MTL::IndirectCommandBufferDescriptor::inheritDepthBias() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(inheritDepthBias));
}

/**
 * @brief Indicates whether indirect commands inherit the depth clip mode.
 *
 * @return `true` if commands created from this descriptor inherit the encoder's depth clip mode, `false` otherwise.
 */
_MTL_INLINE bool MTL::IndirectCommandBufferDescriptor::inheritDepthClipMode() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(inheritDepthClipMode));
}

/**
 * @brief Indicates whether commands encoded into the indirect command buffer inherit the depth-stencil state.
 *
 * @return `true` if commands inherit the depth-stencil state, `false` otherwise.
 */
_MTL_INLINE bool MTL::IndirectCommandBufferDescriptor::inheritDepthStencilState() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(inheritDepthStencilState));
}

/**
 * @brief Indicates whether indirect commands inherit the front-facing winding.
 *
 * @return `true` if indirect commands inherit the front-facing winding state, `false` otherwise.
 */
_MTL_INLINE bool MTL::IndirectCommandBufferDescriptor::inheritFrontFacingWinding() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(inheritFrontFacingWinding));
}

/**
 * @brief Indicates whether indirect commands inherit the pipeline state.
 *
 * @return `true` if indirect commands inherit the pipeline state, `false` otherwise.
 */
_MTL_INLINE bool MTL::IndirectCommandBufferDescriptor::inheritPipelineState() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(inheritPipelineState));
}

/**
 * @brief Indicates whether indirect commands inherit the triangle fill mode from the encoder.
 *
 * @return `true` if commands inherit the triangle fill mode, `false` otherwise.
 */
_MTL_INLINE bool MTL::IndirectCommandBufferDescriptor::inheritTriangleFillMode() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(inheritTriangleFillMode));
}

/**
 * @brief Initialize an IndirectCommandBufferDescriptor instance.
 *
 * @return IndirectCommandBufferDescriptor* Pointer to the initialized descriptor instance.
 */
_MTL_INLINE MTL::IndirectCommandBufferDescriptor* MTL::IndirectCommandBufferDescriptor::init()
{
    return NS::Object::init<MTL::IndirectCommandBufferDescriptor>();
}

/**
 * @brief Retrieves the maximum number of fragment buffer bindings allowed by this descriptor.
 *
 * @return NS::UInteger The maximum number of fragment buffers that may be bound.
 */
_MTL_INLINE NS::UInteger MTL::IndirectCommandBufferDescriptor::maxFragmentBufferBindCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxFragmentBufferBindCount));
}

/**
 * @brief Report the maximum number of kernel buffers that may be bound for kernel commands encoded with this descriptor.
 *
 * @return NS::UInteger The maximum number of kernel buffer bindings allowed.
 */
_MTL_INLINE NS::UInteger MTL::IndirectCommandBufferDescriptor::maxKernelBufferBindCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxKernelBufferBindCount));
}

/**
 * @brief Returns the maximum number of kernel threadgroup memory bindings allowed.
 *
 * @return NS::UInteger The upper limit for how many kernel threadgroup memory bindings can be set.
 */
_MTL_INLINE NS::UInteger MTL::IndirectCommandBufferDescriptor::maxKernelThreadgroupMemoryBindCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxKernelThreadgroupMemoryBindCount));
}

/**
 * @brief Query the maximum number of mesh buffers that may be bound by commands described by this descriptor.
 *
 * @return NS::UInteger The maximum number of mesh buffers that can be bound per command.
 */
_MTL_INLINE NS::UInteger MTL::IndirectCommandBufferDescriptor::maxMeshBufferBindCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxMeshBufferBindCount));
}

/**
 * @brief Maximum number of object buffers that can be bound per indirect command.
 *
 * @return NS::UInteger The maximum number of object buffer bind slots available to indirect commands.
 */
_MTL_INLINE NS::UInteger MTL::IndirectCommandBufferDescriptor::maxObjectBufferBindCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxObjectBufferBindCount));
}

/**
 * @brief Maximum number of object threadgroup memory bindings allowed for indirect commands.
 *
 * @return NS::UInteger The maximum count of object threadgroup memory bindings that commands encoded into an indirect command buffer may bind.
 */
_MTL_INLINE NS::UInteger MTL::IndirectCommandBufferDescriptor::maxObjectThreadgroupMemoryBindCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxObjectThreadgroupMemoryBindCount));
}

/**
 * @brief Maximum number of vertex buffer bindings the descriptor allows.
 *
 * @return NS::UInteger The maximum number of vertex buffers that can be bound.
 */
_MTL_INLINE NS::UInteger MTL::IndirectCommandBufferDescriptor::maxVertexBufferBindCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxVertexBufferBindCount));
}

/**
 * @brief Configure which indirect command types are allowed by the descriptor.
 *
 * Sets the set of supported indirect command types (bitmask of IndirectCommandType flags)
 * that indirect command buffers created from this descriptor will accept.
 *
 * @param commandTypes Bitwise combination of IndirectCommandType flags specifying supported commands.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setCommandTypes(MTL::IndirectCommandType commandTypes)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCommandTypes_), commandTypes);
}

/**
 * @brief Enable or disable inheritance of buffer bindings by commands created from this descriptor.
 *
 * @param inheritBuffers `true` to have indirect commands inherit buffer bindings from the issuing encoder; `false` to require those bindings to be set explicitly for each command.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setInheritBuffers(bool inheritBuffers)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInheritBuffers_), inheritBuffers);
}

/**
 * @brief Sets whether indirect commands inherit the cull mode state.
 *
 * @param inheritCullMode `true` if indirect commands should inherit the current cull mode, `false` if they should not.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setInheritCullMode(bool inheritCullMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInheritCullMode_), inheritCullMode);
}

/**
 * @brief Controls whether commands encoded into the indirect command buffer inherit the depth bias state.
 *
 * @param inheritDepthBias `true` to have encoded commands inherit the current depth bias, `false` to require an explicit depth bias on each command.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setInheritDepthBias(bool inheritDepthBias)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInheritDepthBias_), inheritDepthBias);
}

/**
 * @brief Configure whether indirect commands inherit the depth clip mode from the encoder.
 *
 * @param inheritDepthClipMode `true` to have indirect commands inherit the encoder's depth clip mode, `false` to use their own depth clip mode.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setInheritDepthClipMode(bool inheritDepthClipMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInheritDepthClipMode_), inheritDepthClipMode);
}

/**
 * @brief Sets whether indirect commands inherit the depth-stencil state from the encoder.
 *
 * @param inheritDepthStencilState `true` to have commands inherit the encoder's depth-stencil state; `false` to require commands to provide their own.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setInheritDepthStencilState(bool inheritDepthStencilState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInheritDepthStencilState_), inheritDepthStencilState);
}

/**
 * @brief Configure whether indirect commands inherit the front-facing winding state.
 *
 * When enabled, indirect render commands created from this descriptor will inherit the front-facing
 * winding (clockwise or counterclockwise) from the render encoder that executes them.
 *
 * @param inheritFrontFacingWinding `true` to inherit the render encoder's front-facing winding, `false` to use the commands' own winding state.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setInheritFrontFacingWinding(bool inheritFrontFacingWinding)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInheritFrontFacingWinding_), inheritFrontFacingWinding);
}

/**
 * @brief Configure whether indirect commands inherit the encoder's pipeline state.
 *
 * When enabled, commands encoded into an indirect command buffer will use the current
 * render/compute pipeline state from the encoder instead of requiring an explicit
 * pipeline state to be set per command.
 *
 * @param inheritPipelineState True to enable inheritance of the encoder's pipeline state; false to require commands to set their own pipeline state.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setInheritPipelineState(bool inheritPipelineState)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInheritPipelineState_), inheritPipelineState);
}

/**
 * @brief Configure whether indirect commands inherit the triangle fill mode.
 *
 * @param inheritTriangleFillMode `true` to have indirect commands inherit the current triangle fill mode from their encoder/pipeline, `false` to disable inheritance.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setInheritTriangleFillMode(bool inheritTriangleFillMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInheritTriangleFillMode_), inheritTriangleFillMode);
}

/**
 * @brief Configure the maximum number of fragment buffers that indirect commands may bind.
 *
 * @param maxFragmentBufferBindCount The maximum count of fragment buffer bindings allowed.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setMaxFragmentBufferBindCount(NS::UInteger maxFragmentBufferBindCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxFragmentBufferBindCount_), maxFragmentBufferBindCount);
}

/**
 * @brief Sets the maximum number of kernel buffer bindings available to indirect commands.
 *
 * @param maxKernelBufferBindCount The upper limit of kernel buffer slots that indirect commands may bind.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setMaxKernelBufferBindCount(NS::UInteger maxKernelBufferBindCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxKernelBufferBindCount_), maxKernelBufferBindCount);
}

/**
 * @brief Set the maximum number of kernel threadgroup memory bindings the descriptor allows.
 *
 * @param maxKernelThreadgroupMemoryBindCount Maximum number of bindable kernel threadgroup memory slots.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setMaxKernelThreadgroupMemoryBindCount(NS::UInteger maxKernelThreadgroupMemoryBindCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxKernelThreadgroupMemoryBindCount_), maxKernelThreadgroupMemoryBindCount);
}

/**
 * @brief Set the maximum number of mesh buffer bindings allowed by the descriptor.
 *
 * @param maxMeshBufferBindCount Maximum count of mesh buffers that can be bound per mesh pipeline entry.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setMaxMeshBufferBindCount(NS::UInteger maxMeshBufferBindCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxMeshBufferBindCount_), maxMeshBufferBindCount);
}

/**
 * @brief Sets the maximum number of object buffers that may be bound by commands encoded into the indirect command buffer.
 *
 * @param maxObjectBufferBindCount Maximum number of object buffer binding slots available per indirect command.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setMaxObjectBufferBindCount(NS::UInteger maxObjectBufferBindCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxObjectBufferBindCount_), maxObjectBufferBindCount);
}

/**
 * @brief Set the maximum number of object threadgroup memory bindings available to commands encoded with this descriptor.
 *
 * @param maxObjectThreadgroupMemoryBindCount Maximum count of threadgroup memory bind points that indirect commands may use for object-level kernels.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setMaxObjectThreadgroupMemoryBindCount(NS::UInteger maxObjectThreadgroupMemoryBindCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxObjectThreadgroupMemoryBindCount_), maxObjectThreadgroupMemoryBindCount);
}

/**
 * @brief Sets the maximum number of vertex buffers that an indirect command may bind.
 *
 * @param maxVertexBufferBindCount Maximum number of vertex buffer bindings allowed per indirect command.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setMaxVertexBufferBindCount(NS::UInteger maxVertexBufferBindCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxVertexBufferBindCount_), maxVertexBufferBindCount);
}

/**
 * @brief Enable or disable color attachment mapping support for the descriptor.
 *
 * Sets whether indirect commands created from this descriptor will support mapping color
 * attachments.
 *
 * @param supportColorAttachmentMapping True to enable color attachment mapping support, false to disable.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setSupportColorAttachmentMapping(bool supportColorAttachmentMapping)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportColorAttachmentMapping_), supportColorAttachmentMapping);
}

/**
 * @brief Enable or disable support for dynamic attribute stride in indirect commands.
 *
 * When enabled, indirect commands created from this descriptor may specify per-attribute strides that can vary at draw/dispatch time.
 *
 * @param supportDynamicAttributeStride `true` to enable dynamic attribute stride support, `false` to disable it.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setSupportDynamicAttributeStride(bool supportDynamicAttributeStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportDynamicAttributeStride_), supportDynamicAttributeStride);
}

/**
 * @brief Configures whether indirect commands created from this descriptor support ray tracing.
 *
 * @param supportRayTracing `true` to enable ray tracing support, `false` to disable it.
 */
_MTL_INLINE void MTL::IndirectCommandBufferDescriptor::setSupportRayTracing(bool supportRayTracing)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportRayTracing_), supportRayTracing);
}

/**
 * @brief Indicates whether color attachment mapping is supported by this descriptor.
 *
 * @return `true` if color attachment mapping is supported, `false` otherwise.
 */
_MTL_INLINE bool MTL::IndirectCommandBufferDescriptor::supportColorAttachmentMapping() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportColorAttachmentMapping));
}

/**
 * @brief Indicates whether the descriptor supports dynamic attribute stride.
 *
 * @return `true` if dynamic attribute stride is supported, `false` otherwise.
 */
_MTL_INLINE bool MTL::IndirectCommandBufferDescriptor::supportDynamicAttributeStride() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportDynamicAttributeStride));
}

/**
 * @brief Reports whether the descriptor enables ray tracing support.
 *
 * @return `true` if ray tracing is supported, `false` otherwise.
 */
_MTL_INLINE bool MTL::IndirectCommandBufferDescriptor::supportRayTracing() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportRayTracing));
}

/**
 * @brief GPU resource identifier for this indirect command buffer.
 *
 * @return MTL::ResourceID The identifier of the underlying GPU resource.
 */
_MTL_INLINE MTL::ResourceID MTL::IndirectCommandBuffer::gpuResourceID() const
{
    return Object::sendMessage<MTL::ResourceID>(this, _MTL_PRIVATE_SEL(gpuResourceID));
}

/**
 * @brief Retrieve the indirect compute command at a given index in this buffer.
 *
 * @param commandIndex Index of the command within the indirect command buffer.
 * @return MTL::IndirectComputeCommand* Pointer to the indirect compute command at the specified index.
 */
_MTL_INLINE MTL::IndirectComputeCommand* MTL::IndirectCommandBuffer::indirectComputeCommand(NS::UInteger commandIndex)
{
    return Object::sendMessage<MTL::IndirectComputeCommand*>(this, _MTL_PRIVATE_SEL(indirectComputeCommandAtIndex_), commandIndex);
}

/**
 * @brief Retrieves the indirect render command at the specified index.
 *
 * @param commandIndex Index of the command within the indirect command buffer.
 * @return MTL::IndirectRenderCommand* Pointer to the indirect render command at the specified index.
 */
_MTL_INLINE MTL::IndirectRenderCommand* MTL::IndirectCommandBuffer::indirectRenderCommand(NS::UInteger commandIndex)
{
    return Object::sendMessage<MTL::IndirectRenderCommand*>(this, _MTL_PRIVATE_SEL(indirectRenderCommandAtIndex_), commandIndex);
}

/**
 * @brief Resets the commands within the specified range to their default state.
 *
 * @param range The range (location and length) of commands in the buffer to reset.
 */
_MTL_INLINE void MTL::IndirectCommandBuffer::reset(NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(resetWithRange_), range);
}

/**
 * @brief Retrieves the number of commands (capacity) contained in the indirect command buffer.
 *
 * @return NS::UInteger The number of commands in the buffer.
 */
_MTL_INLINE NS::UInteger MTL::IndirectCommandBuffer::size() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(size));
}