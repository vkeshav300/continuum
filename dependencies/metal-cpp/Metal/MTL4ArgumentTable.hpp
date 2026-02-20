//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4ArgumentTable.hpp
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
#include "MTLTypes.hpp"

namespace MTL
{
class Device;
}

namespace MTL4
{
class ArgumentTableDescriptor : public NS::Copying<ArgumentTableDescriptor>
{
public:
    static ArgumentTableDescriptor* alloc();

    ArgumentTableDescriptor*        init();
    bool                            initializeBindings() const;

    NS::String*                     label() const;

    NS::UInteger                    maxBufferBindCount() const;

    NS::UInteger                    maxSamplerStateBindCount() const;

    NS::UInteger                    maxTextureBindCount() const;

    void                            setInitializeBindings(bool initializeBindings);

    void                            setLabel(const NS::String* label);

    void                            setMaxBufferBindCount(NS::UInteger maxBufferBindCount);

    void                            setMaxSamplerStateBindCount(NS::UInteger maxSamplerStateBindCount);

    void                            setMaxTextureBindCount(NS::UInteger maxTextureBindCount);

    void                            setSupportAttributeStrides(bool supportAttributeStrides);
    bool                            supportAttributeStrides() const;
};
class ArgumentTable : public NS::Referencing<ArgumentTable>
{
public:
    MTL::Device* device() const;

    NS::String*  label() const;

    void         setAddress(MTL::GPUAddress gpuAddress, NS::UInteger bindingIndex);
    void         setAddress(MTL::GPUAddress gpuAddress, NS::UInteger stride, NS::UInteger bindingIndex);

    void         setResource(MTL::ResourceID resourceID, NS::UInteger bindingIndex);

    void         setSamplerState(MTL::ResourceID resourceID, NS::UInteger bindingIndex);

    void         setTexture(MTL::ResourceID resourceID, NS::UInteger bindingIndex);
};

}
/**
 * @brief Allocates a new ArgumentTableDescriptor instance.
 *
 * The returned object is newly allocated and must be initialized (for example by calling `init()`).
 *
 * @return MTL4::ArgumentTableDescriptor* Newly allocated ArgumentTableDescriptor instance.
 */
_MTL_INLINE MTL4::ArgumentTableDescriptor* MTL4::ArgumentTableDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::ArgumentTableDescriptor>(_MTL_PRIVATE_CLS(MTL4ArgumentTableDescriptor));
}

/**
 * @brief Initializes a newly allocated ArgumentTableDescriptor instance.
 *
 * @return MTL4::ArgumentTableDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL4::ArgumentTableDescriptor* MTL4::ArgumentTableDescriptor::init()
{
    return NS::Object::init<MTL4::ArgumentTableDescriptor>();
}

/**
 * @brief Indicates whether the descriptor requests bindings to be initialized.
 *
 * @return `true` if bindings should be initialized, `false` otherwise.
 */
_MTL_INLINE bool MTL4::ArgumentTableDescriptor::initializeBindings() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(initializeBindings));
}

/**
 * @brief The descriptor's user-visible label.
 *
 * @return NS::String* The label string, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL4::ArgumentTableDescriptor::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Query the maximum number of buffer bindings allowed by this descriptor.
 *
 * @return NS::UInteger The maximum number of buffer bindings this descriptor permits.
 */
_MTL_INLINE NS::UInteger MTL4::ArgumentTableDescriptor::maxBufferBindCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxBufferBindCount));
}

/**
 * @brief Maximum number of sampler state bindings allowed by this descriptor.
 *
 * @return NS::UInteger Maximum number of sampler state binding slots.
 */
_MTL_INLINE NS::UInteger MTL4::ArgumentTableDescriptor::maxSamplerStateBindCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxSamplerStateBindCount));
}

/**
 * @brief Retrieve the maximum number of texture bindings allowed by the descriptor.
 *
 * @return NS::UInteger The maximum number of texture bindings.
 */
_MTL_INLINE NS::UInteger MTL4::ArgumentTableDescriptor::maxTextureBindCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxTextureBindCount));
}

/**
 * @brief Set whether bindings should be initialized.
 *
 * @param initializeBindings `true` to initialize bindings, `false` to leave them uninitialized.
 */
_MTL_INLINE void MTL4::ArgumentTableDescriptor::setInitializeBindings(bool initializeBindings)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInitializeBindings_), initializeBindings);
}

/**
 * @brief Sets the human-readable label for the argument table descriptor.
 *
 * @param label UTF-8 string used as the descriptor's label; may be nullptr to clear the label.
 */
_MTL_INLINE void MTL4::ArgumentTableDescriptor::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Set the maximum number of buffer bindings allowed by the descriptor.
 *
 * @param maxBufferBindCount Maximum number of buffer binding slots.
 */
_MTL_INLINE void MTL4::ArgumentTableDescriptor::setMaxBufferBindCount(NS::UInteger maxBufferBindCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxBufferBindCount_), maxBufferBindCount);
}

/**
 * @brief Set the maximum number of sampler state bindings allowed by the descriptor.
 *
 * @param maxSamplerStateBindCount Maximum number of sampler state bindings that can be configured.
 */
_MTL_INLINE void MTL4::ArgumentTableDescriptor::setMaxSamplerStateBindCount(NS::UInteger maxSamplerStateBindCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxSamplerStateBindCount_), maxSamplerStateBindCount);
}

/**
 * @brief Set the maximum number of texture bindings for this descriptor.
 *
 * @param maxTextureBindCount Maximum number of texture bindings allowed.
 */
_MTL_INLINE void MTL4::ArgumentTableDescriptor::setMaxTextureBindCount(NS::UInteger maxTextureBindCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxTextureBindCount_), maxTextureBindCount);
}

/**
 * @brief Sets whether the descriptor indicates support for attribute strides.
 *
 * @param supportAttributeStrides `true` to enable attribute stride support, `false` to disable it.
 */
_MTL_INLINE void MTL4::ArgumentTableDescriptor::setSupportAttributeStrides(bool supportAttributeStrides)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportAttributeStrides_), supportAttributeStrides);
}

/**
 * @brief Indicates whether attribute strides are supported.
 *
 * @return true if the descriptor supports attribute strides, false otherwise.
 */
_MTL_INLINE bool MTL4::ArgumentTableDescriptor::supportAttributeStrides() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportAttributeStrides));
}

/**
 * @brief Retrieve the device associated with this argument table.
 *
 * @return MTL::Device* The device associated with this argument table.
 */
_MTL_INLINE MTL::Device* MTL4::ArgumentTable::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Retrieves the label of the argument table.
 *
 * @return NS::String* The label string for the table, or nullptr if no label is set.
 */
_MTL_INLINE NS::String* MTL4::ArgumentTable::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Set the GPU virtual address for a buffer binding in the argument table.
 *
 * @param gpuAddress GPU virtual address to bind at the given index.
 * @param bindingIndex Binding index within the argument table to receive the address.
 */
_MTL_INLINE void MTL4::ArgumentTable::setAddress(MTL::GPUAddress gpuAddress, NS::UInteger bindingIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAddress_atIndex_), gpuAddress, bindingIndex);
}

/**
 * @brief Set the GPU address and attribute stride for a specific binding in the argument table.
 *
 * @param gpuAddress GPU virtual address to assign to the binding.
 * @param stride Attribute stride (in bytes) associated with the binding's address.
 * @param bindingIndex Index of the binding to update.
 */
_MTL_INLINE void MTL4::ArgumentTable::setAddress(MTL::GPUAddress gpuAddress, NS::UInteger stride, NS::UInteger bindingIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAddress_attributeStride_atIndex_), gpuAddress, stride, bindingIndex);
}

/**
 * @brief Bind a resource identifier to a buffer binding slot in the argument table.
 *
 * @param resourceID The resource identifier to bind.
 * @param bindingIndex The buffer binding index to assign the resource to.
 */
_MTL_INLINE void MTL4::ArgumentTable::setResource(MTL::ResourceID resourceID, NS::UInteger bindingIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setResource_atBufferIndex_), resourceID, bindingIndex);
}

/**
 * @brief Bind a sampler-state resource to a specific argument-table binding index.
 *
 * Associates the sampler-state identified by `resourceID` with the argument table binding at `bindingIndex`.
 *
 * @param resourceID Identifier of the sampler-state resource to bind.
 * @param bindingIndex Binding slot index within the argument table.
 */
_MTL_INLINE void MTL4::ArgumentTable::setSamplerState(MTL::ResourceID resourceID, NS::UInteger bindingIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSamplerState_atIndex_), resourceID, bindingIndex);
}

/**
 * @brief Bind a texture resource to the argument table at a specific texture binding index.
 *
 * Associates the given resource identifier with the texture slot identified by bindingIndex in this argument table.
 *
 * @param resourceID Identifier of the texture resource to bind.
 * @param bindingIndex Index of the texture binding slot to assign the resource to.
 */
_MTL_INLINE void MTL4::ArgumentTable::setTexture(MTL::ResourceID resourceID, NS::UInteger bindingIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTexture_atIndex_), resourceID, bindingIndex);
}