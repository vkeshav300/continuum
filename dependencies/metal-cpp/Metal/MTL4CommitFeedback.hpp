//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4CommitFeedback.hpp
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

#include <functional>

namespace MTL4
{
class CommitFeedback;

using CommitFeedbackHandler = void (^)(MTL4::CommitFeedback*);
using CommitFeedbackHandlerFunction = std::function<void(MTL4::CommitFeedback*)>;

class CommitFeedback : public NS::Referencing<CommitFeedback>
{
public:
    CFTimeInterval GPUEndTime() const;

    CFTimeInterval GPUStartTime() const;

    NS::Error*     error() const;
};

}
/**
 * @brief Retrieves the GPU end timestamp for this commit.
 *
 * @return CFTimeInterval The GPU end time for the commit, in seconds. 
 */
_MTL_INLINE CFTimeInterval MTL4::CommitFeedback::GPUEndTime() const
{
    return Object::sendMessage<CFTimeInterval>(this, _MTL_PRIVATE_SEL(GPUEndTime));
}

/**
 * @brief Retrieve the GPU start time for the commit.
 *
 * @return CFTimeInterval The GPU start time for the associated commit, in seconds.
 */
_MTL_INLINE CFTimeInterval MTL4::CommitFeedback::GPUStartTime() const
{
    return Object::sendMessage<CFTimeInterval>(this, _MTL_PRIVATE_SEL(GPUStartTime));
}

/**
 * @brief Retrieves the error associated with the commit, if any.
 *
 * Returns the error object produced by this commit operation when a failure occurred.
 *
 * @return NS::Error* The error object for the commit, or `nullptr` if no error occurred.
 */
_MTL_INLINE NS::Error* MTL4::CommitFeedback::error() const
{
    return Object::sendMessage<NS::Error*>(this, _MTL_PRIVATE_SEL(error));
}