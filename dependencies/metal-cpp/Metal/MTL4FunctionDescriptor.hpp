//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal//MTL4FunctionDescriptor.hpp
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
class FunctionDescriptor;

class FunctionDescriptor : public NS::Copying<FunctionDescriptor>
{
public:
    static FunctionDescriptor* alloc();

    FunctionDescriptor*        init();
};

}
/**
 * @brief Allocate a new FunctionDescriptor instance from the private implementation class.
 *
 * @return MTL4::FunctionDescriptor* A newly allocated FunctionDescriptor instance, or `nullptr` if allocation fails.
 */
_MTL_INLINE MTL4::FunctionDescriptor* MTL4::FunctionDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::FunctionDescriptor>(_MTL_PRIVATE_CLS(MTL4FunctionDescriptor));
}

/**
 * @brief Initializes a newly allocated FunctionDescriptor instance.
 *
 * @return FunctionDescriptor* Pointer to the initialized FunctionDescriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL4::FunctionDescriptor* MTL4::FunctionDescriptor::init()
{
    return NS::Object::init<MTL4::FunctionDescriptor>();
}