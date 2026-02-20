//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLDrawable.hpp
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
#include <CoreFoundation/CoreFoundation.h>

#include <CoreFoundation/CoreFoundation.h>
#include <functional>

namespace MTL
{
class Drawable;

using DrawablePresentedHandler = void (^)(MTL::Drawable*);
using DrawablePresentedHandlerFunction = std::function<void(MTL::Drawable*)>;

class Drawable : public NS::Referencing<Drawable>
{
public:
    void           addPresentedHandler(const MTL::DrawablePresentedHandler block);
    void           addPresentedHandler(const MTL::DrawablePresentedHandlerFunction& function);

    NS::UInteger   drawableID() const;

    void           present();
    void           presentAfterMinimumDuration(CFTimeInterval duration);

    void           presentAtTime(CFTimeInterval presentationTime);

    CFTimeInterval presentedTime() const;
};

}
/**
 * @brief Registers a handler block that will be invoked when the drawable is presented.
 *
 * @param block A block invoked with the presented `MTL::Drawable*` when the drawable has been presented.
 */
_MTL_INLINE void MTL::Drawable::addPresentedHandler(const MTL::DrawablePresentedHandler block)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(addPresentedHandler_), block);
}

/**
 * @brief Registers a C++ callable to be invoked when this drawable is presented.
 *
 * The provided callable will be called with this drawable as its sole argument
 * when the drawable is presented by the system.
 *
 * @param function Callable invoked on presentation; signature must be
 * `void(MTL::Drawable*)`. The callable is copied/stored for later invocation.
 */
_MTL_INLINE void MTL::Drawable::addPresentedHandler(const MTL::DrawablePresentedHandlerFunction& function)
{
    __block DrawablePresentedHandlerFunction blockFunction = function;
    addPresentedHandler(^(Drawable* pDrawable) { blockFunction(pDrawable); });
}

/**
 * @brief Retrieves the unique identifier for this drawable.
 *
 * @return NS::UInteger The drawable's identifier.
 */
_MTL_INLINE NS::UInteger MTL::Drawable::drawableID() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(drawableID));
}

/**
 * @brief Schedules the drawable to be presented to the display at the next appropriate time.
 *
 * This enqueues the drawable for presentation; the actual presentation time is determined by the system.
 */
_MTL_INLINE void MTL::Drawable::present()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(present));
}

/**
 * @brief Schedules the drawable to be presented after at least the specified time interval.
 *
 * @param duration Time interval in seconds to wait before the drawable is eligible for presentation.
 */
_MTL_INLINE void MTL::Drawable::presentAfterMinimumDuration(CFTimeInterval duration)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(presentAfterMinimumDuration_), duration);
}

/**
 * @brief Schedules the drawable to be presented at a specific system presentation time.
 *
 * @param presentationTime The absolute host time (in seconds) at which the drawable should be presented.
 */
_MTL_INLINE void MTL::Drawable::presentAtTime(CFTimeInterval presentationTime)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(presentAtTime_), presentationTime);
}

/**
 * @brief Returns the system timestamp when the drawable was presented.
 *
 * @return CFTimeInterval The presentation time, in seconds, at which the drawable was presented.
 */
_MTL_INLINE CFTimeInterval MTL::Drawable::presentedTime() const
{
    return Object::sendMessage<CFTimeInterval>(this, _MTL_PRIVATE_SEL(presentedTime));
}