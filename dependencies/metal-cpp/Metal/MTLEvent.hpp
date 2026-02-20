//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLEvent.hpp
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
#include <cstdint>
#include <dispatch/dispatch.h>

#include <cstdint>
#include <functional>

namespace MTL
{
class Device;
class SharedEvent;
class SharedEventHandle;
class SharedEventListener;

using SharedEventNotificationBlock = void (^)(SharedEvent* pEvent, std::uint64_t value);
using SharedEventNotificationFunction = std::function<void(SharedEvent* pEvent, std::uint64_t value)>;

class Event : public NS::Referencing<Event>
{
public:
    Device*     device() const;

    NS::String* label() const;
    void        setLabel(const NS::String* label);
};
class SharedEventListener : public NS::Referencing<SharedEventListener>
{
public:
    static SharedEventListener* alloc();

    dispatch_queue_t            dispatchQueue() const;

    SharedEventListener*        init();
    SharedEventListener*        init(const dispatch_queue_t dispatchQueue);

    static SharedEventListener* sharedListener();
};
class SharedEvent : public NS::Referencing<SharedEvent, Event>
{
public:
    SharedEventHandle* newSharedEventHandle();

    void               notifyListener(const MTL::SharedEventListener* listener, uint64_t value, const MTL::SharedEventNotificationBlock block);
    void               notifyListener(const MTL::SharedEventListener* listener, uint64_t value, const MTL::SharedEventNotificationFunction& function);

    void               setSignaledValue(uint64_t signaledValue);
    uint64_t           signaledValue() const;
    bool               waitUntilSignaledValue(uint64_t value, uint64_t milliseconds);
};
class SharedEventHandle : public NS::SecureCoding<SharedEventHandle>
{
public:
    static SharedEventHandle* alloc();

    SharedEventHandle*        init();

    NS::String*               label() const;
};

}
/**
 * @brief Retrieve the device associated with this Event.
 *
 * @return MTL::Device* Pointer to the device that created or owns this Event, or `nullptr` if no device is associated.
 */
_MTL_INLINE MTL::Device* MTL::Event::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Retrieves the label assigned to the event.
 *
 * @return NS::String* The event's label string, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::Event::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Set the human-readable label associated with the event.
 *
 * Associates the provided string with the event for identification or debugging.
 *
 * @param label The label to assign to the event; may be `nullptr` to clear any existing label.
 */
_MTL_INLINE void MTL::Event::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Allocates a new SharedEventListener instance.
 *
 * @return MTL::SharedEventListener* Pointer to a newly allocated, uninitialized SharedEventListener object; may be nullptr on allocation failure.
 */
_MTL_INLINE MTL::SharedEventListener* MTL::SharedEventListener::alloc()
{
    return NS::Object::alloc<MTL::SharedEventListener>(_MTL_PRIVATE_CLS(MTLSharedEventListener));
}

/**
 * @brief Retrieve the dispatch queue associated with this shared event listener.
 *
 * @return dispatch_queue_t The dispatch queue used by the listener (may be NULL).
 */
_MTL_INLINE dispatch_queue_t MTL::SharedEventListener::dispatchQueue() const
{
    return Object::sendMessage<dispatch_queue_t>(this, _MTL_PRIVATE_SEL(dispatchQueue));
}

/**
 * @brief Initializes and returns this SharedEventListener instance.
 *
 * @return SharedEventListener* The initialized listener instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::SharedEventListener* MTL::SharedEventListener::init()
{
    return NS::Object::init<MTL::SharedEventListener>();
}

/**
 * @brief Initializes the listener with a specific dispatch queue for event callbacks.
 *
 * @param dispatchQueue The Grand Central Dispatch queue on which the listener will schedule notifications; may be `nullptr` to use a default queue.
 * @return SharedEventListener* The initialized listener (`this`) on success, or `nullptr` on failure.
 */
_MTL_INLINE MTL::SharedEventListener* MTL::SharedEventListener::init(const dispatch_queue_t dispatchQueue)
{
    return Object::sendMessage<MTL::SharedEventListener*>(this, _MTL_PRIVATE_SEL(initWithDispatchQueue_), dispatchQueue);
}

/**
 * @brief Accesses the shared MTL::SharedEventListener singleton.
 *
 * @return SharedEventListener* Pointer to the shared listener instance.
 */
_MTL_INLINE MTL::SharedEventListener* MTL::SharedEventListener::sharedListener()
{
    return Object::sendMessage<MTL::SharedEventListener*>(_MTL_PRIVATE_CLS(MTLSharedEventListener), _MTL_PRIVATE_SEL(sharedListener));
}

/**
 * @brief Create a handle that references this shared event.
 *
 * @return MTL::SharedEventHandle* A newly created SharedEventHandle referencing this SharedEvent.
 */
_MTL_INLINE MTL::SharedEventHandle* MTL::SharedEvent::newSharedEventHandle()
{
    return Object::sendMessage<MTL::SharedEventHandle*>(this, _MTL_PRIVATE_SEL(newSharedEventHandle));
}

/**
 * @brief Registers a notification that invokes a callback when the shared event reaches a specific value.
 *
 * Registers a notification associated with the specified listener that will call `block` with this
 * SharedEvent and the reached value when the event's signaled value becomes equal to or greater than `value`.
 *
 * @param listener The listener that receives the notification; determines the dispatch context for the callback.
 * @param value The signaled value at or above which the notification will trigger.
 * @param block A block invoked as `block(SharedEvent* event, uint64_t value)` when the notification fires.
 */
_MTL_INLINE void MTL::SharedEvent::notifyListener(const MTL::SharedEventListener* listener, uint64_t value, const MTL::SharedEventNotificationBlock block)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(notifyListener_atValue_block_), listener, value, block);
}

/**
 * @brief Registers a C++ callback to be invoked when the shared event reaches the specified value for the given listener.
 *
 * The callback is invoked with the signaled SharedEvent pointer and the observed value.
 *
 * @param listener The listener to notify.
 * @param value The value that triggers the notification.
 * @param function The C++ function to call when the notification fires; invoked as `function(SharedEvent*, uint64_t)`.
 */
_MTL_INLINE void MTL::SharedEvent::notifyListener(const MTL::SharedEventListener* listener, uint64_t value, const MTL::SharedEventNotificationFunction& function)
{
    __block MTL::SharedEventNotificationFunction callback = function;
    notifyListener(listener, value, ^void(SharedEvent* pEvent, std::uint64_t innerValue) { callback(pEvent, innerValue); });
}

/**
 * @brief Set the event's current signaled value.
 *
 * Updates the shared event's signaled value used for comparisons and for triggering registered listeners or waiters.
 *
 * @param signaledValue New signaled value to store in the shared event.
 */
_MTL_INLINE void MTL::SharedEvent::setSignaledValue(uint64_t signaledValue)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSignaledValue_), signaledValue);
}

/**
 * @brief Retrieve the current signaled value of the shared event.
 *
 * @return uint64_t The current signaled value.
 */
_MTL_INLINE uint64_t MTL::SharedEvent::signaledValue() const
{
    return Object::sendMessage<uint64_t>(this, _MTL_PRIVATE_SEL(signaledValue));
}

/**
 * @brief Blocks until the shared event's signaled value reaches or exceeds the specified value or the timeout elapses.
 *
 * Waits up to `milliseconds` milliseconds for the event's signaled value to become greater than or equal to `value`.
 *
 * @param value Target signaled value to wait for.
 * @param milliseconds Maximum time to wait in milliseconds.
 * @return true if the signaled value reached or exceeded `value` before the timeout, false if the timeout elapsed first.
 */
_MTL_INLINE bool MTL::SharedEvent::waitUntilSignaledValue(uint64_t value, uint64_t milliseconds)
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(waitUntilSignaledValue_timeoutMS_), value, milliseconds);
}

/**
 * @brief Allocates a new MTL::SharedEventHandle object.
 *
 * The returned object is allocated but not initialized; call init() on the result before use.
 *
 * @return MTL::SharedEventHandle* Pointer to the newly allocated SharedEventHandle.
 */
_MTL_INLINE MTL::SharedEventHandle* MTL::SharedEventHandle::alloc()
{
    return NS::Object::alloc<MTL::SharedEventHandle>(_MTL_PRIVATE_CLS(MTLSharedEventHandle));
}

/**
 * @brief Initializes a newly allocated SharedEventHandle instance.
 *
 * Performs object initialization and returns the initialized handle.
 *
 * @return MTL::SharedEventHandle* The initialized instance, or nullptr if initialization failed.
 */
_MTL_INLINE MTL::SharedEventHandle* MTL::SharedEventHandle::init()
{
    return NS::Object::init<MTL::SharedEventHandle>();
}

/**
 * @brief Retrieve the label assigned to the shared event handle.
 *
 * @return NS::String* The label for the shared event handle, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::SharedEventHandle::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}