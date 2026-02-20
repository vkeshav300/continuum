//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLCaptureManager.hpp
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

namespace MTL
{
class CaptureDescriptor;
class CaptureManager;
class CaptureScope;
class CommandQueue;
class Device;
}

namespace MTL4
{
class CommandQueue;
}

namespace MTL
{
_MTL_ENUM(NS::Integer, CaptureError) {
    CaptureErrorNotSupported = 1,
    CaptureErrorAlreadyCapturing = 2,
    CaptureErrorInvalidDescriptor = 3,
};

/**
 * @brief Capture output destination options.
 *
 * Enumerates where capture data may be written.
 */
 
/**
 * @brief Allocates a new CaptureDescriptor instance.
 *
 * @return CaptureDescriptor* A newly allocated, uninitialized descriptor.
 */
 
/**
 * @brief The object that will be captured.
 *
 * @return NS::Object* The object configured as the capture target, or `nullptr` if none.
 */
 
/**
 * @brief The configured capture destination.
 *
 * @return CaptureDestination The destination where capture data will be emitted.
 */
 
/**
 * @brief Initializes the CaptureDescriptor instance.
 *
 * @return CaptureDescriptor* The initialized descriptor, or `nullptr` on failure.
 */
 
/**
 * @brief The output URL for capture data.
 *
 * @return NS::URL* The URL where capture data will be written, or `nullptr` if not set.
 */
 
/**
 * @brief Sets the object to capture.
 *
 * @param captureObject The object to be captured; may be `nullptr` to clear.
 */
 
/**
 * @brief Sets the destination for capture output.
 *
 * @param destination The destination enum value indicating where to emit capture data.
 */
 
/**
 * @brief Sets the output URL for captured data.
 *
 * @param outputURL The URL to write capture data to; may be `nullptr` to clear.
 */
 
/**
 * @brief Allocates a new CaptureManager instance.
 *
 * @return CaptureManager* A newly allocated, uninitialized manager.
 */
 
/**
 * @brief The currently configured default capture scope.
 *
 * @return CaptureScope* The default capture scope, or `nullptr` if none is set.
 */
 
/**
 * @brief Initializes the CaptureManager instance.
 *
 * @return CaptureManager* The initialized manager, or `nullptr` on failure.
 */
 
/**
 * @brief Indicates whether a capture session is active.
 *
 * @return bool `true` if a capture is in progress, `false` otherwise.
 */
 
/**
 * @brief Creates a new capture scope for a device.
 *
 * @param device The device to scope the capture to.
 * @return CaptureScope* A new capture scope tied to `device`.
 */
 
/**
 * @brief Creates a new capture scope for a command queue.
 *
 * @param commandQueue The command queue to scope the capture to.
 * @return CaptureScope* A new capture scope tied to `commandQueue`.
 */
 
/**
 * @brief Creates a new capture scope for a Metal 4.x command queue.
 *
 * @param commandQueue The MTLCapture 4.x command queue to scope the capture to.
 * @return CaptureScope* A new capture scope tied to `commandQueue`.
 */
 
/**
 * @brief Sets the default capture scope used by the manager.
 *
 * @param defaultCaptureScope The capture scope to set as default; may be `nullptr` to clear.
 */
 
/**
 * @brief Returns the shared CaptureManager singleton.
 *
 * @return CaptureManager* The shared capture manager instance.
 */
 
/**
 * @brief Starts a capture using the provided descriptor.
 *
 * @param descriptor The capture descriptor that configures the session.
 * @param error If non-null and the call fails, populated with an NSError describing the failure.
 * @return bool `true` if the capture started successfully, `false` otherwise.
 */
 
/**
 * @brief Starts a capture scoped to a device.
 *
 * @param device The device to capture.
 */
 
/**
 * @brief Starts a capture scoped to a command queue.
 *
 * @param commandQueue The command queue to capture.
 */
 
/**
 * @brief Starts a capture using an explicit capture scope.
 *
 * @param captureScope The capture scope to start capturing.
 */
 
/**
 * @brief Stops any active capture session.
 */
 
/**
 * @brief Queries whether the manager supports a specific capture destination.
 *
 * @param destination The destination to test.
 * @return bool `true` if the destination is supported, `false` otherwise.
 */
_MTL_ENUM(NS::Integer, CaptureDestination) {
    CaptureDestinationDeveloperTools = 1,
    CaptureDestinationGPUTraceDocument = 2,
};

class CaptureDescriptor : public NS::Copying<CaptureDescriptor>
{
public:
    static CaptureDescriptor* alloc();

    NS::Object*               captureObject() const;

    CaptureDestination        destination() const;

    CaptureDescriptor*        init();

    NS::URL*                  outputURL() const;

    void                      setCaptureObject(NS::Object* captureObject);

    void                      setDestination(MTL::CaptureDestination destination);

    void                      setOutputURL(const NS::URL* outputURL);
};
class CaptureManager : public NS::Referencing<CaptureManager>
{
public:
    static CaptureManager* alloc();

    CaptureScope*          defaultCaptureScope() const;

    CaptureManager*        init();

    bool                   isCapturing() const;

    CaptureScope*          newCaptureScope(const MTL::Device* device);
    CaptureScope*          newCaptureScope(const MTL::CommandQueue* commandQueue);
    CaptureScope*          newCaptureScope(const MTL4::CommandQueue* commandQueue);

    void                   setDefaultCaptureScope(const MTL::CaptureScope* defaultCaptureScope);

    static CaptureManager* sharedCaptureManager();

    bool                   startCapture(const MTL::CaptureDescriptor* descriptor, NS::Error** error);
    void                   startCapture(const MTL::Device* device);
    void                   startCapture(const MTL::CommandQueue* commandQueue);
    void                   startCapture(const MTL::CaptureScope* captureScope);

    void                   stopCapture();

    bool                   supportsDestination(MTL::CaptureDestination destination);
};

}
/**
 * @brief Allocates a new CaptureDescriptor.
 *
 * @return MTL::CaptureDescriptor* Allocated CaptureDescriptor instance.
 */
_MTL_INLINE MTL::CaptureDescriptor* MTL::CaptureDescriptor::alloc()
{
    return NS::Object::alloc<MTL::CaptureDescriptor>(_MTL_PRIVATE_CLS(MTLCaptureDescriptor));
}

/**
 * @brief Gets the object configured as the capture target.
 *
 * @return NS::Object* The object used as the capture target, or `nullptr` if no capture object is set.
 */
_MTL_INLINE NS::Object* MTL::CaptureDescriptor::captureObject() const
{
    return Object::sendMessage<NS::Object*>(this, _MTL_PRIVATE_SEL(captureObject));
}

/**
 * @brief Retrieves the configured destination for this capture descriptor.
 *
 * @return MTL::CaptureDestination The destination where capture data will be written.
 */
_MTL_INLINE MTL::CaptureDestination MTL::CaptureDescriptor::destination() const
{
    return Object::sendMessage<MTL::CaptureDestination>(this, _MTL_PRIVATE_SEL(destination));
}

/**
 * @brief Initialize a newly allocated CaptureDescriptor instance.
 *
 * @return MTL::CaptureDescriptor* Pointer to the initialized CaptureDescriptor instance, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::CaptureDescriptor* MTL::CaptureDescriptor::init()
{
    return NS::Object::init<MTL::CaptureDescriptor>();
}

/**
 * @brief Gets the output URL configured for the capture descriptor.
 *
 * @return NS::URL* The output URL where capture data will be written, or `nullptr` if no URL is set.
 */
_MTL_INLINE NS::URL* MTL::CaptureDescriptor::outputURL() const
{
    return Object::sendMessage<NS::URL*>(this, _MTL_PRIVATE_SEL(outputURL));
}

/**
 * @brief Sets the object that the capture descriptor will target.
 *
 * @param captureObject The Objective‑C object to capture — typically an MTL device, command queue, or capture scope wrapped as an NS::Object.
 */
_MTL_INLINE void MTL::CaptureDescriptor::setCaptureObject(NS::Object* captureObject)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCaptureObject_), captureObject);
}

/**
 * @brief Set the destination where capture data will be written.
 *
 * Selects the capture output destination used for subsequent capture operations.
 *
 * @param destination The capture destination to use (one of `MTL::CaptureDestination`).
 */
_MTL_INLINE void MTL::CaptureDescriptor::setDestination(MTL::CaptureDestination destination)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDestination_), destination);
}

/**
 * @brief Sets the file URL where capture output will be written.
 *
 * @param outputURL The destination URL for the capture data.
 */
_MTL_INLINE void MTL::CaptureDescriptor::setOutputURL(const NS::URL* outputURL)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOutputURL_), outputURL);
}

/**
 * @brief Allocates a new CaptureManager instance.
 *
 * @return MTL::CaptureManager* A newly allocated, uninitialized CaptureManager instance.
 */
_MTL_INLINE MTL::CaptureManager* MTL::CaptureManager::alloc()
{
    return NS::Object::alloc<MTL::CaptureManager>(_MTL_PRIVATE_CLS(MTLCaptureManager));
}

/**
 * @brief Retrieves the manager's default capture scope.
 *
 * @return MTL::CaptureScope* The current default CaptureScope, or `nullptr` if no default is set.
 */
_MTL_INLINE MTL::CaptureScope* MTL::CaptureManager::defaultCaptureScope() const
{
    return Object::sendMessage<MTL::CaptureScope*>(this, _MTL_PRIVATE_SEL(defaultCaptureScope));
}

/**
 * @brief Initializes a CaptureManager instance.
 *
 * @return MTL::CaptureManager* Initialized CaptureManager instance, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::CaptureManager* MTL::CaptureManager::init()
{
    return NS::Object::init<MTL::CaptureManager>();
}

/**
 * @brief Indicates whether a capture session is currently active.
 *
 * @return `true` if a capture is in progress, `false` otherwise.
 */
_MTL_INLINE bool MTL::CaptureManager::isCapturing() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isCapturing));
}

/**
 * @brief Creates a new capture scope for a specific Metal device.
 *
 * @param device Device to associate with the new capture scope.
 * @return MTL::CaptureScope* Pointer to the newly created capture scope for the given device.
 */
_MTL_INLINE MTL::CaptureScope* MTL::CaptureManager::newCaptureScope(const MTL::Device* device)
{
    return Object::sendMessage<MTL::CaptureScope*>(this, _MTL_PRIVATE_SEL(newCaptureScopeWithDevice_), device);
}

/**
 * @brief Creates a capture scope configured for the given command queue.
 *
 * @param commandQueue The command queue to restrict the capture to.
 * @return MTL::CaptureScope* A CaptureScope instance associated with the specified command queue.
 */
_MTL_INLINE MTL::CaptureScope* MTL::CaptureManager::newCaptureScope(const MTL::CommandQueue* commandQueue)
{
    return Object::sendMessage<MTL::CaptureScope*>(this, _MTL_PRIVATE_SEL(newCaptureScopeWithCommandQueue_), commandQueue);
}

/**
 * @brief Creates a capture scope associated with the given MTL4 command queue.
 *
 * @param commandQueue The MTL4::CommandQueue used to create the capture scope.
 * @return MTL::CaptureScope* A newly created CaptureScope for the provided command queue.
 */
_MTL_INLINE MTL::CaptureScope* MTL::CaptureManager::newCaptureScope(const MTL4::CommandQueue* commandQueue)
{
    return Object::sendMessage<MTL::CaptureScope*>(this, _MTL_PRIVATE_SEL(newCaptureScopeWithMTL4CommandQueue_), commandQueue);
}

/**
 * @brief Sets the manager's default capture scope.
 *
 * The provided capture scope will be used as the default target for subsequent capture operations
 * that rely on the manager's default scope.
 *
 * @param defaultCaptureScope CaptureScope to set as the manager's default. May be nullptr to clear the default.
 */
_MTL_INLINE void MTL::CaptureManager::setDefaultCaptureScope(const MTL::CaptureScope* defaultCaptureScope)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDefaultCaptureScope_), defaultCaptureScope);
}

/**
 * @brief Accesses the global shared CaptureManager singleton.
 *
 * @return MTL::CaptureManager* Pointer to the shared CaptureManager instance.
 */
_MTL_INLINE MTL::CaptureManager* MTL::CaptureManager::sharedCaptureManager()
{
    return Object::sendMessage<MTL::CaptureManager*>(_MTL_PRIVATE_CLS(MTLCaptureManager), _MTL_PRIVATE_SEL(sharedCaptureManager));
}

/**
 * @brief Starts a capture using the provided capture descriptor.
 *
 * Attempts to begin a capture configured by `descriptor`. If the operation fails
 * and `error` is non-null, an NSError describing the failure will be stored
 * into `*error`.
 *
 * @param descriptor Capture descriptor that configures the capture.
 * @param error Optional out parameter that, on failure, will be set to an NSError describing the error.
 * @return `true` if the capture was started successfully, `false` otherwise.
 */
_MTL_INLINE bool MTL::CaptureManager::startCapture(const MTL::CaptureDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(startCaptureWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Start a capture session scoped to the specified device.
 *
 * @param device The device whose GPU work will be captured.
_MTL_INLINE void MTL::CaptureManager::startCapture(const MTL::Device* device)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(startCaptureWithDevice_), device);
}

/**
 * @brief Begins a GPU capture for the specified command queue.
 *
 * Initiates capture operations scoped to the provided `commandQueue`, causing GPU work submitted
 * to that queue to be recorded according to the current capture configuration.
 *
 * @param commandQueue The command queue whose submitted work will be captured.
 */
_MTL_INLINE void MTL::CaptureManager::startCapture(const MTL::CommandQueue* commandQueue)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(startCaptureWithCommandQueue_), commandQueue);
}

/**
 * @brief Starts a capture session for the given capture scope.
 *
 * Initiates GPU capture using the specified CaptureScope; the active capture will be associated with and limited to that scope.
 *
 * @param captureScope The CaptureScope to start capturing for; must be a valid scope object.
 */
_MTL_INLINE void MTL::CaptureManager::startCapture(const MTL::CaptureScope* captureScope)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(startCaptureWithScope_), captureScope);
}

/**
 * @brief Stops any active Metal capture session.
 *
 * If no capture is in progress, this call has no effect.
 */
_MTL_INLINE void MTL::CaptureManager::stopCapture()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(stopCapture));
}

/**
 * @brief Checks whether the capture manager supports the specified capture destination.
 *
 * @param destination The capture destination to query.
 * @return `true` if the capture destination is supported, `false` otherwise.
 */
_MTL_INLINE bool MTL::CaptureManager::supportsDestination(MTL::CaptureDestination destination)
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportsDestination_), destination);
}