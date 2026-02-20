//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLParallelRenderCommandEncoder.hpp
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
#include "MTLCommandEncoder.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLRenderPass.hpp"

namespace MTL
{
class RenderCommandEncoder;

class ParallelRenderCommandEncoder : public NS::Referencing<ParallelRenderCommandEncoder, CommandEncoder>
{
public:
    RenderCommandEncoder* renderCommandEncoder();

    void                  setColorStoreAction(MTL::StoreAction storeAction, NS::UInteger colorAttachmentIndex);
    void                  setColorStoreActionOptions(MTL::StoreActionOptions storeActionOptions, NS::UInteger colorAttachmentIndex);

    void                  setDepthStoreAction(MTL::StoreAction storeAction);
    void                  setDepthStoreActionOptions(MTL::StoreActionOptions storeActionOptions);

    void                  setStencilStoreAction(MTL::StoreAction storeAction);
    void                  setStencilStoreActionOptions(MTL::StoreActionOptions storeActionOptions);
};

}
/**
 * @brief Retrieves the RenderCommandEncoder associated with this ParallelRenderCommandEncoder.
 *
 * @return The associated RenderCommandEncoder pointer, or `nullptr` if no render encoder is available.
 */
_MTL_INLINE MTL::RenderCommandEncoder* MTL::ParallelRenderCommandEncoder::renderCommandEncoder()
{
    return Object::sendMessage<MTL::RenderCommandEncoder*>(this, _MTL_PRIVATE_SEL(renderCommandEncoder));
}

/**
 * @brief Set the store action for a specific color attachment.
 *
 * @param storeAction The action to perform when storing the attachment's rendering results.
 * @param colorAttachmentIndex Zero-based index of the color attachment to modify.
 */
_MTL_INLINE void MTL::ParallelRenderCommandEncoder::setColorStoreAction(MTL::StoreAction storeAction, NS::UInteger colorAttachmentIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setColorStoreAction_atIndex_), storeAction, colorAttachmentIndex);
}

/**
 * @brief Set the store action options for a specific color attachment.
 *
 * @param storeActionOptions Store action options to apply to the color attachment.
 * @param colorAttachmentIndex Index of the color attachment to configure.
 */
_MTL_INLINE void MTL::ParallelRenderCommandEncoder::setColorStoreActionOptions(MTL::StoreActionOptions storeActionOptions, NS::UInteger colorAttachmentIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setColorStoreActionOptions_atIndex_), storeActionOptions, colorAttachmentIndex);
}

/**
 * @brief Configure the store action for the depth attachment when the render pass completes.
 *
 * @param storeAction The store action to apply to the depth attachment.
 */
_MTL_INLINE void MTL::ParallelRenderCommandEncoder::setDepthStoreAction(MTL::StoreAction storeAction)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthStoreAction_), storeAction);
}

/**
 * @brief Sets the store action options used for the depth attachment.
 *
 * @param storeActionOptions Options that modify how the depth attachment is stored (e.g., transient, memory-backed behaviors).
 */
_MTL_INLINE void MTL::ParallelRenderCommandEncoder::setDepthStoreActionOptions(MTL::StoreActionOptions storeActionOptions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDepthStoreActionOptions_), storeActionOptions);
}

/**
 * @brief Sets the store action for the stencil attachment.
 *
 * Specifies how the stencil attachment's contents are stored when the render pass completes.
 *
 * @param storeAction The store action to apply to the stencil attachment.
 */
_MTL_INLINE void MTL::ParallelRenderCommandEncoder::setStencilStoreAction(MTL::StoreAction storeAction)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStencilStoreAction_), storeAction);
}

/**
 * @brief Sets the store action options for the render target's stencil attachment.
 *
 * Adjusts how the stencil attachment's contents are stored after a render pass for this parallel encoder.
 *
 * @param storeActionOptions Options specifying stencil store behavior (combination of `MTL::StoreActionOptions` flags).
 */
_MTL_INLINE void MTL::ParallelRenderCommandEncoder::setStencilStoreActionOptions(MTL::StoreActionOptions storeActionOptions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStencilStoreActionOptions_), storeActionOptions);
}