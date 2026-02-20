//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLDepthStencil.hpp
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
#include "MTLTypes.hpp"
#include <cstdint>

namespace MTL
{
class DepthStencilDescriptor;
class Device;
class StencilDescriptor;
_MTL_ENUM(NS::UInteger, CompareFunction) {
    CompareFunctionNever = 0,
    CompareFunctionLess = 1,
    CompareFunctionEqual = 2,
    CompareFunctionLessEqual = 3,
    CompareFunctionGreater = 4,
    CompareFunctionNotEqual = 5,
    CompareFunctionGreaterEqual = 6,
    CompareFunctionAlways = 7,
};

/**
 * @brief Allocate a new StencilDescriptor instance.
 *
 * @return StencilDescriptor* A newly allocated, uninitialized descriptor.
 */
/**
 * @brief Get the stencil operation to perform when a fragment fails the depth test.
 *
 * @return StencilOperation The stencil operation used on depth-test failure.
 */
/**
 * @brief Get the stencil operation to perform when both the depth and stencil tests pass.
 *
 * @return StencilOperation The stencil operation used when depth and stencil tests pass.
 */
/**
 * @brief Initialize a newly allocated StencilDescriptor.
 *
 * @return StencilDescriptor* The initialized descriptor instance.
 */
/**
 * @brief Retrieve the stencil read mask.
 *
 * @return uint32_t The mask applied to stencil values for reading.
 */
/**
 * @brief Set the stencil operation to perform when a fragment fails the depth test.
 *
 * @param depthFailureOperation The stencil operation to use on depth-test failure.
 */
/**
 * @brief Set the stencil operation to perform when both the depth and stencil tests pass.
 *
 * @param depthStencilPassOperation The stencil operation to use when depth and stencil tests pass.
 */
/**
 * @brief Set the stencil read mask.
 *
 * @param readMask The mask to apply to stencil values for reading.
 */
/**
 * @brief Set the stencil comparison function used by this descriptor.
 *
 * @param stencilCompareFunction The comparison function to use for stencil tests.
 */
/**
 * @brief Set the stencil operation to perform when the stencil test fails.
 *
 * @param stencilFailureOperation The stencil operation to use on stencil-test failure.
 */
/**
 * @brief Set the stencil write mask.
 *
 * @param writeMask The mask to apply to stencil values for writing.
 */
/**
 * @brief Get the stencil comparison function used by this descriptor.
 *
 * @return CompareFunction The comparison function used for stencil tests.
 */
/**
 * @brief Get the stencil operation to perform when the stencil test fails.
 *
 * @return StencilOperation The stencil operation used on stencil-test failure.
 */
/**
 * @brief Retrieve the stencil write mask.
 *
 * @return uint32_t The mask applied to stencil values for writing.
 */
/**
 * @brief Allocate a new DepthStencilDescriptor instance.
 *
 * @return DepthStencilDescriptor* A newly allocated, uninitialized descriptor.
 */
/**
 * @brief Get the descriptor used for back-face stencil operations.
 *
 * @return StencilDescriptor* The back-face stencil descriptor, or nullptr if not set.
 */
/**
 * @brief Get the depth comparison function used by this descriptor.
 *
 * @return CompareFunction The comparison function used for depth tests.
 */
/**
 * @brief Get whether depth writes are enabled.
 *
 * @return bool `true` if depth writes are enabled, `false` otherwise.
 */
/**
 * @brief Get the descriptor used for front-face stencil operations.
 *
 * @return StencilDescriptor* The front-face stencil descriptor, or nullptr if not set.
 */
/**
 * @brief Initialize a newly allocated DepthStencilDescriptor.
 *
 * @return DepthStencilDescriptor* The initialized descriptor instance.
 */
/**
 * @brief Determine whether depth writes are enabled.
 *
 * @return bool `true` if depth writes are enabled, `false` otherwise.
 */
/**
 * @brief Get the label assigned to this descriptor.
 *
 * @return NS::String* The descriptor label, or nullptr if none is set.
 */
/**
 * @brief Set the descriptor used for back-face stencil operations.
 *
 * @param backFaceStencil The back-face stencil descriptor to assign.
 */
/**
 * @brief Set the depth comparison function for this descriptor.
 *
 * @param depthCompareFunction The comparison function to use for depth tests.
 */
/**
 * @brief Enable or disable depth writes for this descriptor.
 *
 * @param depthWriteEnabled `true` to enable depth writes, `false` to disable them.
 */
/**
 * @brief Set the descriptor used for front-face stencil operations.
 *
 * @param frontFaceStencil The front-face stencil descriptor to assign.
 */
/**
 * @brief Assign a human-readable label to this descriptor.
 *
 * @param label The label string to set.
 */
/**
 * @brief Get the device associated with this depth-stencil state.
 *
 * @return Device* The owning Device, or nullptr if none is associated.
 */
/**
 * @brief Get the GPU resource identifier for this depth-stencil state.
 *
 * @return ResourceID The GPU resource ID.
 */
/**
 * @brief Get the label assigned to this depth-stencil state.
 *
 * @return NS::String* The state label, or nullptr if none is set.
 */
_MTL_ENUM(NS::UInteger, StencilOperation) {
    StencilOperationKeep = 0,
    StencilOperationZero = 1,
    StencilOperationReplace = 2,
    StencilOperationIncrementClamp = 3,
    StencilOperationDecrementClamp = 4,
    StencilOperationInvert = 5,
    StencilOperationIncrementWrap = 6,
    StencilOperationDecrementWrap = 7,
};

class StencilDescriptor : public NS::Copying<StencilDescriptor>
{
public:
    static StencilDescriptor* alloc();

    StencilOperation          depthFailureOperation() const;

    StencilOperation          depthStencilPassOperation() const;

    StencilDescriptor*        init();

    uint32_t                  readMask() const;

    void                      setDepthFailureOperation(MTL::StencilOperation depthFailureOperation);

    void                      setDepthStencilPassOperation(MTL::StencilOperation depthStencilPassOperation);

    void                      setReadMask(uint32_t readMask);

    void                      setStencilCompareFunction(MTL::CompareFunction stencilCompareFunction);

    void                      setStencilFailureOperation(MTL::StencilOperation stencilFailureOperation);

    void                      setWriteMask(uint32_t writeMask);

    CompareFunction           stencilCompareFunction() const;

    StencilOperation          stencilFailureOperation() const;

    uint32_t                  writeMask() const;
};
class DepthStencilDescriptor : public NS::Copying<DepthStencilDescriptor>
{
public:
    static DepthStencilDescriptor* alloc();

    StencilDescriptor*             backFaceStencil() const;

    CompareFunction                depthCompareFunction() const;

    [[deprecated("please use isDepthWriteEnabled instead")]]
    bool                    depthWriteEnabled() const;

    StencilDescriptor*      frontFaceStencil() const;

    DepthStencilDescriptor* init();

    bool                    isDepthWriteEnabled() const;

    NS::String*             label() const;

    void                    setBackFaceStencil(const MTL::StencilDescriptor* backFaceStencil);

    void                    setDepthCompareFunction(MTL::CompareFunction depthCompareFunction);

    void                    setDepthWriteEnabled(bool depthWriteEnabled);

    void                    setFrontFaceStencil(const MTL::StencilDescriptor* frontFaceStencil);

    void                    setLabel(const NS::String* label);
};
class DepthStencilState : public NS::Referencing<DepthStencilState>
{
public:
    Device*     device() const;

    ResourceID  gpuResourceID() const;

    NS::String* label() const;
};

}
/**
 * @brief Allocates a new StencilDescriptor object.
 *
 * @return StencilDescriptor* A newly allocated StencilDescriptor object; call `init()` to initialize before use.
 */
_MTL_INLINE MTL::StencilDescriptor* MTL::StencilDescriptor::alloc()
{
    return NS::Object::alloc<MTL::StencilDescriptor>(_MTL_PRIVATE_CLS(MTLStencilDescriptor));
}

/**
 * @brief Retrieves the stencil operation applied when a depth test fails.
 *
 * @return MTL::StencilOperation The operation performed on the stencil buffer when a depth test fails.
 */
_MTL_INLINE MTL::StencilOperation MTL::StencilDescriptor::depthFailureOperation() const
{
    return Object::sendMessage<MTL::StencilOperation>(this, _MTL_PRIVATE_SEL(depthFailureOperation));
}

/**
 * @brief Stencil operation performed when both the depth test and stencil test pass.
 *
 * @return MTL::StencilOperation The operation applied to the stencil buffer when both the depth and stencil tests pass.
 */
_MTL_INLINE MTL::StencilOperation MTL::StencilDescriptor::depthStencilPassOperation() const
{
    return Object::sendMessage<MTL::StencilOperation>(this, _MTL_PRIVATE_SEL(depthStencilPassOperation));
}

/**
 * @brief Initializes a newly allocated StencilDescriptor instance.
 *
 * @return StencilDescriptor* Initialized descriptor instance.
 */
_MTL_INLINE MTL::StencilDescriptor* MTL::StencilDescriptor::init()
{
    return NS::Object::init<MTL::StencilDescriptor>();
}

/**
 * @brief Retrieves the stencil read mask used for stencil comparisons.
 *
 * @return uint32_t The mask applied to stencil values when reading for stencil tests.
 */
_MTL_INLINE uint32_t MTL::StencilDescriptor::readMask() const
{
    return Object::sendMessage<uint32_t>(this, _MTL_PRIVATE_SEL(readMask));
}

/**
 * @brief Set the stencil operation to perform when the depth test fails.
 *
 * @param depthFailureOperation The stencil operation to apply when a fragment fails the depth test.
 */
_MTL_INLINE void MTL::StencilDescriptor::setDepthFailureOperation(MTL::StencilOperation depthFailureOperation)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthFailureOperation_), depthFailureOperation);
}

/**
 * @brief Sets the stencil operation to perform when both the depth test and stencil test pass.
 *
 * @param depthStencilPassOperation The stencil operation to apply when a fragment passes both depth and stencil tests.
 */
_MTL_INLINE void MTL::StencilDescriptor::setDepthStencilPassOperation(MTL::StencilOperation depthStencilPassOperation)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthStencilPassOperation_), depthStencilPassOperation);
}

/**
 * @brief Sets the stencil read mask used for stencil comparisons.
 *
 * The mask is applied to stencil values read from the buffer before compare operations.
 *
 * @param readMask Bitmask to apply to stencil values when reading for comparisons.
 */
_MTL_INLINE void MTL::StencilDescriptor::setReadMask(uint32_t readMask)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setReadMask_), readMask);
}

/**
 * @brief Sets the stencil compare function used for stencil testing.
 *
 * @param stencilCompareFunction The compare function to use when comparing stencil values during rendering.
 */
_MTL_INLINE void MTL::StencilDescriptor::setStencilCompareFunction(MTL::CompareFunction stencilCompareFunction)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStencilCompareFunction_), stencilCompareFunction);
}

/**
 * @brief Sets the stencil operation to perform when the stencil test fails.
 *
 * @param stencilFailureOperation The stencil operation to apply on stencil-test failure.
 */
_MTL_INLINE void MTL::StencilDescriptor::setStencilFailureOperation(MTL::StencilOperation stencilFailureOperation)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStencilFailureOperation_), stencilFailureOperation);
}

/**
 * @brief Sets the stencil write mask.
 *
 * Controls which bits of the stencil buffer may be modified during stencil write operations.
 *
 * @param writeMask Bitmask (lower 32 bits) specifying which stencil bits can be written.
 */
_MTL_INLINE void MTL::StencilDescriptor::setWriteMask(uint32_t writeMask)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setWriteMask_), writeMask);
}

/**
 * @brief Gets the compare function used for stencil testing.
 *
 * @return The compare function used for stencil comparisons.
 */
_MTL_INLINE MTL::CompareFunction MTL::StencilDescriptor::stencilCompareFunction() const
{
    return Object::sendMessage<MTL::CompareFunction>(this, _MTL_PRIVATE_SEL(stencilCompareFunction));
}

/**
 * @brief Retrieve the stencil operation used when the stencil test fails.
 *
 * @return MTL::StencilOperation The operation performed when the stencil test fails.
 */
_MTL_INLINE MTL::StencilOperation MTL::StencilDescriptor::stencilFailureOperation() const
{
    return Object::sendMessage<MTL::StencilOperation>(this, _MTL_PRIVATE_SEL(stencilFailureOperation));
}

/**
 * @brief Retrieve the stencil write mask.
 *
 * @return uint32_t The 32-bit mask specifying which stencil bits may be written.
 */
_MTL_INLINE uint32_t MTL::StencilDescriptor::writeMask() const
{
    return Object::sendMessage<uint32_t>(this, _MTL_PRIVATE_SEL(writeMask));
}

/**
 * @brief Allocate a new DepthStencilDescriptor instance.
 *
 * Allocates and returns a newly created DepthStencilDescriptor object.
 * The returned object is allocated but not initialized; call init() before use.
 *
 * @return DepthStencilDescriptor* Pointer to the newly allocated descriptor.
 */
_MTL_INLINE MTL::DepthStencilDescriptor* MTL::DepthStencilDescriptor::alloc()
{
    return NS::Object::alloc<MTL::DepthStencilDescriptor>(_MTL_PRIVATE_CLS(MTLDepthStencilDescriptor));
}

/**
 * @brief Stencil descriptor used for back-face stencil testing.
 *
 * @return MTL::StencilDescriptor* Pointer to the back-face stencil descriptor, or `nullptr` if no back-face descriptor is set.
 */
_MTL_INLINE MTL::StencilDescriptor* MTL::DepthStencilDescriptor::backFaceStencil() const
{
    return Object::sendMessage<MTL::StencilDescriptor*>(this, _MTL_PRIVATE_SEL(backFaceStencil));
}

/**
 * @brief Gets the depth comparison function used for depth testing.
 *
 * The compare function determines how incoming fragment depth values are compared
 * against existing values in the depth buffer when this descriptor is applied.
 *
 * @return MTL::CompareFunction The depth compare function (e.g., Less, GreaterEqual).
 */
_MTL_INLINE MTL::CompareFunction MTL::DepthStencilDescriptor::depthCompareFunction() const
{
    return Object::sendMessage<MTL::CompareFunction>(this, _MTL_PRIVATE_SEL(depthCompareFunction));
}

/**
 * @brief Indicates whether depth writes are enabled for the descriptor.
 *
 * @deprecated Use isDepthWriteEnabled() instead.
 * @return `true` if depth writing is enabled, `false` otherwise.
 */
_MTL_INLINE bool MTL::DepthStencilDescriptor::depthWriteEnabled() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isDepthWriteEnabled));
}

/**
 * @brief Retrieve the front-face stencil descriptor for this depth-stencil descriptor.
 *
 * @return MTL::StencilDescriptor* Pointer to the front-face stencil descriptor, or `nullptr` if none is set.
 */
_MTL_INLINE MTL::StencilDescriptor* MTL::DepthStencilDescriptor::frontFaceStencil() const
{
    return Object::sendMessage<MTL::StencilDescriptor*>(this, _MTL_PRIVATE_SEL(frontFaceStencil));
}

/**
 * @brief Initializes this DepthStencilDescriptor instance.
 *
 * @return DepthStencilDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::DepthStencilDescriptor* MTL::DepthStencilDescriptor::init()
{
    return NS::Object::init<MTL::DepthStencilDescriptor>();
}

/**
 * @brief Indicates whether depth writing is enabled for this depth-stencil descriptor.
 *
 * @return `true` if depth writing is enabled, `false` otherwise.
 */
_MTL_INLINE bool MTL::DepthStencilDescriptor::isDepthWriteEnabled() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isDepthWriteEnabled));
}

/**
 * @brief Gets the descriptor's label.
 *
 * @return NS::String* The label assigned to the descriptor, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::DepthStencilDescriptor::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Sets the stencil descriptor used for back-face stencil operations.
 *
 * @param backFaceStencil Descriptor that configures stencil behavior for back-facing polygons; may be `nullptr` to remove the back-face descriptor.
 */
_MTL_INLINE void MTL::DepthStencilDescriptor::setBackFaceStencil(const MTL::StencilDescriptor* backFaceStencil)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBackFaceStencil_), backFaceStencil);
}

/**
 * @brief Sets the comparison function used for depth testing.
 *
 * @param depthCompareFunction The depth comparison function to apply when comparing fragment depth values.
 */
_MTL_INLINE void MTL::DepthStencilDescriptor::setDepthCompareFunction(MTL::CompareFunction depthCompareFunction)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthCompareFunction_), depthCompareFunction);
}

/**
 * @brief Enables or disables writing to the depth buffer for the descriptor.
 *
 * @param depthWriteEnabled If `true`, depth writes are enabled; if `false`, depth writes are disabled.
 */
_MTL_INLINE void MTL::DepthStencilDescriptor::setDepthWriteEnabled(bool depthWriteEnabled)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthWriteEnabled_), depthWriteEnabled);
}

/**
 * @brief Set the stencil descriptor used for front-face stencil operations.
 *
 * @param frontFaceStencil Pointer to a `StencilDescriptor` that specifies the front-face stencil operations and masks.
 */
_MTL_INLINE void MTL::DepthStencilDescriptor::setFrontFaceStencil(const MTL::StencilDescriptor* frontFaceStencil)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFrontFaceStencil_), frontFaceStencil);
}

/**
 * @brief Sets a human-readable label for the descriptor.
 *
 * @param label The label string to assign to the descriptor. Pass `nullptr` to clear any existing label.
 */
_MTL_INLINE void MTL::DepthStencilDescriptor::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Retrieves the device that created this depth-stencil state.
 *
 * @return MTL::Device* Pointer to the Device associated with this depth-stencil state.
 */
_MTL_INLINE MTL::Device* MTL::DepthStencilState::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Gets the GPU resource identifier associated with this depth-stencil state.
 *
 * @return MTL::ResourceID GPU resource identifier for this depth-stencil state.
 */
_MTL_INLINE MTL::ResourceID MTL::DepthStencilState::gpuResourceID() const
{
    return Object::sendMessage<MTL::ResourceID>(this, _MTL_PRIVATE_SEL(gpuResourceID));
}

/**
 * @brief Label of the depth-stencil state.
 *
 * @return NS::String* The label string associated with this DepthStencilState, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::DepthStencilState::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}