//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLLogState.hpp
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
class LogStateDescriptor;
_MTL_ENUM(NS::Integer, LogLevel) {
    LogLevelUndefined = 0,
    LogLevelDebug = 1,
    LogLevelInfo = 2,
    LogLevelNotice = 3,
    LogLevelError = 4,
    LogLevelFault = 5,
};

/**
 * @brief Log state error codes.
 *
 * Values representing specific validation errors for log state configuration.
 */

/**
 * @brief Log handler function type.
 *
 * A callable invoked for each log event.
 *
 * @param subsystem The subsystem identifier associated with the log event.
 * @param category The category associated with the log event.
 * @param logLevel The log level of the event.
 * @param message The log message.
 */

/**
 * @brief Error domain for LogState-related errors.
 *
 * An NSError domain used for errors produced by log state validation or configuration.
 */

/**
 * @brief Registers a block to receive log events.
 *
 * The provided block is invoked for each log message with the subsystem, category,
 * log level, and formatted message.
 *
 * @param block A block that will be called for each log event.
 */

/**
 * @brief Registers a C++ function to receive log events.
 *
 * The provided handler is invoked for each log message with the subsystem, category,
 * log level, and formatted message.
 *
 * @param handler A callable that will be called for each log event.
 */

/**
 * @brief Allocate a new LogStateDescriptor instance.
 *
 * @return LogStateDescriptor* A newly allocated descriptor instance.
 */

/**
 * @brief Returns the configured buffer size for the descriptor.
 *
 * @return NS::Integer The buffer size in bytes.
 */

/**
 * @brief Initializes the descriptor instance.
 *
 * @return LogStateDescriptor* The initialized descriptor, or nullptr on failure.
 */

/**
 * @brief Returns the configured log level for the descriptor.
 *
 * @return LogLevel The log level set on the descriptor.
 */

/**
 * @brief Set the descriptor's buffer size.
 *
 * @param bufferSize The buffer size in bytes to use for log storage.
 */

/**
 * @brief Set the descriptor's log level.
 *
 * @param level The minimum log level to record.
 */
_MTL_ENUM(NS::UInteger, LogStateError) {
    LogStateErrorInvalidSize = 1,
    LogStateErrorInvalid = 2,
};

using LogHandlerFunction = std::function<void(NS::String* subsystem, NS::String* category, MTL::LogLevel logLevel, NS::String* message)>;

_MTL_CONST(NS::ErrorDomain, LogStateErrorDomain);
class LogState : public NS::Referencing<LogState>
{
public:
    void addLogHandler(void (^block)(NS::String*, NS::String*, MTL::LogLevel, NS::String*));
    void addLogHandler(const MTL::LogHandlerFunction& handler);
};
class LogStateDescriptor : public NS::Copying<LogStateDescriptor>
{
public:
    static LogStateDescriptor* alloc();

    NS::Integer                bufferSize() const;

    LogStateDescriptor*        init();

    LogLevel                   level() const;

    void                       setBufferSize(NS::Integer bufferSize);

    void                       setLevel(MTL::LogLevel level);
};

}
_MTL_PRIVATE_DEF_CONST(NS::ErrorDomain, LogStateErrorDomain);
_MTL_INLINE void MTL::LogState::addLogHandler(void (^block)(NS::String*, NS::String*, MTL::LogLevel, NS::String*))
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(addLogHandler_), block);
}

/**
 * @brief Registers a C++ log handler to receive Metal log events.
 *
 * The provided handler will be invoked for each log event with the originating
 * subsystem, category, log level, and message.
 *
 * @param handler Function called on log events with parameters:
 *                - `NS::String* subsystem`: the subsystem generating the log.
 *                - `NS::String* category`: the category of the log entry.
 *                - `MTL::LogLevel logLevel`: the severity level of the log.
 *                - `NS::String* message`: the log message text.
 */
_MTL_INLINE void MTL::LogState::addLogHandler(const MTL::LogHandlerFunction& handler)
{
    __block LogHandlerFunction function = handler;
    addLogHandler(^void(NS::String* subsystem, NS::String* category, MTL::LogLevel logLevel, NS::String* message) { function(subsystem, category, logLevel, message); });
}

/**
 * @brief Allocate a new LogStateDescriptor instance.
 *
 * @return MTL::LogStateDescriptor* Newly allocated LogStateDescriptor instance.
 */
_MTL_INLINE MTL::LogStateDescriptor* MTL::LogStateDescriptor::alloc()
{
    return NS::Object::alloc<MTL::LogStateDescriptor>(_MTL_PRIVATE_CLS(MTLLogStateDescriptor));
}

/**
 * @brief Retrieves the configured log buffer size in bytes.
 *
 * @return NS::Integer The buffer size, in bytes.
 */
_MTL_INLINE NS::Integer MTL::LogStateDescriptor::bufferSize() const
{
    return Object::sendMessage<NS::Integer>(this, _MTL_PRIVATE_SEL(bufferSize));
}

/**
 * @brief Initializes the log state descriptor and returns the initialized instance.
 *
 * @return LogStateDescriptor* The initialized descriptor instance, or nullptr on failure.
 */
_MTL_INLINE MTL::LogStateDescriptor* MTL::LogStateDescriptor::init()
{
    return NS::Object::init<MTL::LogStateDescriptor>();
}

/**
 * @brief Gets the configured log level for this descriptor.
 *
 * @return MTL::LogLevel The descriptor's current log level.
 */
_MTL_INLINE MTL::LogLevel MTL::LogStateDescriptor::level() const
{
    return Object::sendMessage<MTL::LogLevel>(this, _MTL_PRIVATE_SEL(level));
}

/**
 * @brief Sets the size of the log buffer on the descriptor.
 *
 * @param bufferSize Size of the descriptor's log buffer in bytes.
 */
_MTL_INLINE void MTL::LogStateDescriptor::setBufferSize(NS::Integer bufferSize)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBufferSize_), bufferSize);
}

/**
 * @brief Configures the log level for this descriptor.
 *
 * @param level The log level to apply; controls which messages are captured or reported by log state configured with this descriptor.
 */
_MTL_INLINE void MTL::LogStateDescriptor::setLevel(MTL::LogLevel level)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLevel_), level);
}