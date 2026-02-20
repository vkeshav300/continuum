//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4CompilerTask.hpp
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

namespace MTL4
{
class Compiler;
/**
 * @brief Status codes for a compiler task.
 *
 * Enumerates the lifecycle states a CompilerTask can be in.
 *
 * - CompilerTaskStatusNone: Task has no status / not initialized.
 * - CompilerTaskStatusScheduled: Task is scheduled to run.
 * - CompilerTaskStatusCompiling: Task is currently compiling.
 * - CompilerTaskStatusFinished: Task has finished.
 */
 
/**
 * @brief Represents a compiler task with accessors and control methods.
 *
 * Instances provide access to the associated Compiler, the task's current
 * status, and the ability to wait for task completion.
 */
 
/**
 * @brief Returns the Compiler associated with this task.
 *
 * @return Compiler* Pointer to the associated Compiler instance.
 */
 
/**
 * @brief Returns the current status of the compiler task.
 *
 * @return CompilerTaskStatus The task's current CompilerTaskStatus value.
 */
 
/**
 * @brief Blocks until the compiler task has completed.
 *
 * Waits for the task to reach a finished state before returning.
 */
_MTL_ENUM(NS::Integer, CompilerTaskStatus) {
    CompilerTaskStatusNone = 0,
    CompilerTaskStatusScheduled = 1,
    CompilerTaskStatusCompiling = 2,
    CompilerTaskStatusFinished = 3,
};

class CompilerTask : public NS::Referencing<CompilerTask>
{
public:
    Compiler*          compiler() const;

    CompilerTaskStatus status() const;

    void               waitUntilCompleted();
};

}

/**
 * @brief Retrieves the Compiler associated with this task.
 *
 * @return MTL4::Compiler* Pointer to the associated Compiler instance, or nullptr if no compiler is associated.
 */
_MTL_INLINE MTL4::Compiler* MTL4::CompilerTask::compiler() const
{
    return Object::sendMessage<MTL4::Compiler*>(this, _MTL_PRIVATE_SEL(compiler));
}

/**
 * @brief Retrieves the current status of the compiler task.
 *
 * @return MTL4::CompilerTaskStatus The task's current status: `CompilerTaskStatusNone`, `CompilerTaskStatusScheduled`,
 * `CompilerTaskStatusCompiling`, or `CompilerTaskStatusFinished`.
 */
_MTL_INLINE MTL4::CompilerTaskStatus MTL4::CompilerTask::status() const
{
    return Object::sendMessage<MTL4::CompilerTaskStatus>(this, _MTL_PRIVATE_SEL(status));
}

/**
 * @brief Block the current thread until the compiler task finishes.
 *
 * This call returns when the task's status becomes MTL4::CompilerTaskStatusFinished.
 */
_MTL_INLINE void MTL4::CompilerTask::waitUntilCompleted()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(waitUntilCompleted));
}