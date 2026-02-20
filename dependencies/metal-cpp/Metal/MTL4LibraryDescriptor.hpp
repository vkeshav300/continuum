//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4LibraryDescriptor.hpp
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
class LibraryDescriptor;
}

namespace MTL
{
class CompileOptions;
}

namespace MTL4
{
class LibraryDescriptor : public NS::Copying<LibraryDescriptor>
{
public:
    static LibraryDescriptor* alloc();

    LibraryDescriptor*        init();

    NS::String*               name() const;

    MTL::CompileOptions*      options() const;

    void                      setName(const NS::String* name);

    void                      setOptions(const MTL::CompileOptions* options);

    void                      setSource(const NS::String* source);
    NS::String*               source() const;
};

}
/**
 * @brief Allocates a new LibraryDescriptor instance.
 *
 * @return LibraryDescriptor* Pointer to a new LibraryDescriptor instance.
 */
_MTL_INLINE MTL4::LibraryDescriptor* MTL4::LibraryDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::LibraryDescriptor>(_MTL_PRIVATE_CLS(MTL4LibraryDescriptor));
}

/**
 * @brief Initializes a newly allocated LibraryDescriptor instance.
 *
 * @return LibraryDescriptor* Pointer to the initialized instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL4::LibraryDescriptor* MTL4::LibraryDescriptor::init()
{
    return NS::Object::init<MTL4::LibraryDescriptor>();
}

/**
 * @brief Retrieve the name of the library descriptor.
 *
 * @return NS::String* The descriptor's name, or nullptr if it has not been set.
 */
_MTL_INLINE NS::String* MTL4::LibraryDescriptor::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Retrieves the compile options associated with the library descriptor.
 *
 * @return MTL::CompileOptions* The compile options object associated with the descriptor, or `nullptr` if no options have been set.
 */
_MTL_INLINE MTL::CompileOptions* MTL4::LibraryDescriptor::options() const
{
    return Object::sendMessage<MTL::CompileOptions*>(this, _MTL_PRIVATE_SEL(options));
}

/**
 * @brief Set the library descriptor's name.
 *
 * @param name The name to assign to the library descriptor.
 */
_MTL_INLINE void MTL4::LibraryDescriptor::setName(const NS::String* name)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setName_), name);
}

/**
 * @brief Sets the compile options associated with this library descriptor.
 *
 * @param options The MTL::CompileOptions to use for compiling the library; may be nullptr to indicate no options.
 */
_MTL_INLINE void MTL4::LibraryDescriptor::setOptions(const MTL::CompileOptions* options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOptions_), options);
}

/**
 * @brief Set the source code for the library descriptor.
 *
 * @param source UTF-16 string containing the shader/library source text to associate with this descriptor.
 */
_MTL_INLINE void MTL4::LibraryDescriptor::setSource(const NS::String* source)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSource_), source);
}

/**
 * @brief Retrieves the library descriptor's source string.
 *
 * @return NS::String* The source code string associated with this descriptor, or `nullptr` if no source has been set.
 */
_MTL_INLINE NS::String* MTL4::LibraryDescriptor::source() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(source));
}