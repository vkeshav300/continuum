//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLFunctionLog.hpp
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
class Function;
class FunctionLogDebugLocation;
/**
 * @brief Returns the source URL associated with the debug location.
 *
 * @return NS::URL* URL of the source file for the debug location, or `nullptr` if unavailable.
 */
/**
 * @brief Returns the column number within the source file for the debug location.
 *
 * @return NS::UInteger Column number (1-based) of the debug location.
 */
/**
 * @brief Returns the function name associated with the debug location.
 *
 * @return NS::String* The function name, or `nullptr` if unavailable.
 */
/**
 * @brief Returns the line number within the source file for the debug location.
 *
 * @return NS::UInteger Line number (1-based) of the debug location.
 */
/**
 * @brief Returns the debug location information for this function log.
 *
 * @return FunctionLogDebugLocation* Debug location object, or `nullptr` if not provided.
 */
/**
 * @brief Returns the label of the encoder that produced this log entry.
 *
 * @return NS::String* Encoder label string, or `nullptr` if not available.
 */
/**
 * @brief Returns the function associated with this log entry.
 *
 * @return Function* The function referenced by the log, or `nullptr` if not set.
 */
/**
 * @brief Returns the type classification of this function log.
 *
 * @return FunctionLogType The log's type (e.g., FunctionLogTypeValidation).
 */
_MTL_ENUM(NS::UInteger, FunctionLogType) {
    FunctionLogTypeValidation = 0,
};

class LogContainer : public NS::Referencing<LogContainer, NS::FastEnumeration>
{
};
class FunctionLogDebugLocation : public NS::Referencing<FunctionLogDebugLocation>
{
public:
    NS::URL*     URL() const;

    NS::UInteger column() const;

    NS::String*  functionName() const;

    NS::UInteger line() const;
};
class FunctionLog : public NS::Referencing<FunctionLog>
{
public:
    FunctionLogDebugLocation* debugLocation() const;

    NS::String*               encoderLabel() const;

    Function*                 function() const;

    FunctionLogType           type() const;
};

}
/**
 * @brief Retrieve the URL associated with this debug location.
 *
 * @return NS::URL* The URL pointing to the source file for the debug location, or `nullptr` if none is available.
 */
_MTL_INLINE NS::URL* MTL::FunctionLogDebugLocation::URL() const
{
    return Object::sendMessage<NS::URL*>(this, _MTL_PRIVATE_SEL(URL));
}

/**
 * @brief Column number within the source file for this debug location.
 *
 * @return NS::UInteger Column number in the source file for the debug location.
 */
_MTL_INLINE NS::UInteger MTL::FunctionLogDebugLocation::column() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(column));
}

/**
 * @brief Retrieves the source function name associated with this debug location.
 *
 * @return NS::String* The function name as an `NS::String*`, or `nullptr` if no name is available.
 */
_MTL_INLINE NS::String* MTL::FunctionLogDebugLocation::functionName() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(functionName));
}

/**
 * @brief Retrieve the source line number for this debug location.
 *
 * @return NS::UInteger The line number within the source file.
 */
_MTL_INLINE NS::UInteger MTL::FunctionLogDebugLocation::line() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(line));
}

/**
 * @brief Retrieve the debug location associated with this function log.
 *
 * @return MTL::FunctionLogDebugLocation* Pointer to the debug location for this function log, or `nullptr` if no debug location is available.
 */
_MTL_INLINE MTL::FunctionLogDebugLocation* MTL::FunctionLog::debugLocation() const
{
    return Object::sendMessage<MTL::FunctionLogDebugLocation*>(this, _MTL_PRIVATE_SEL(debugLocation));
}

/**
 * @brief Retrieve the label of the encoder that produced this function log.
 *
 * @return NS::String* The encoder's label, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::FunctionLog::encoderLabel() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(encoderLabel));
}

/**
 * @brief Retrieves the Function associated with this FunctionLog.
 *
 * @return MTL::Function* The associated Function object.
 */
_MTL_INLINE MTL::Function* MTL::FunctionLog::function() const
{
    return Object::sendMessage<MTL::Function*>(this, _MTL_PRIVATE_SEL(function));
}

/**
 * @brief Retrieves the function log's type.
 *
 * @return MTL::FunctionLogType The category of this function log.
 */
_MTL_INLINE MTL::FunctionLogType MTL::FunctionLog::type() const
{
    return Object::sendMessage<MTL::FunctionLogType>(this, _MTL_PRIVATE_SEL(type));
}