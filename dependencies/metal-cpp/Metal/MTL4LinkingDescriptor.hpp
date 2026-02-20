//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4LinkingDescriptor.hpp
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
class PipelineStageDynamicLinkingDescriptor;
class RenderPipelineDynamicLinkingDescriptor;
class StaticLinkingDescriptor;

class StaticLinkingDescriptor : public NS::Copying<StaticLinkingDescriptor>
{
public:
    static StaticLinkingDescriptor* alloc();

    NS::Array*                      functionDescriptors() const;

    NS::Dictionary*                 groups() const;

    StaticLinkingDescriptor*        init();

    NS::Array*                      privateFunctionDescriptors() const;

    void                            setFunctionDescriptors(const NS::Array* functionDescriptors);

    void                            setGroups(const NS::Dictionary* groups);

    void                            setPrivateFunctionDescriptors(const NS::Array* privateFunctionDescriptors);
};
class PipelineStageDynamicLinkingDescriptor : public NS::Copying<PipelineStageDynamicLinkingDescriptor>
{
public:
    static PipelineStageDynamicLinkingDescriptor* alloc();

    NS::Array*                                    binaryLinkedFunctions() const;

    PipelineStageDynamicLinkingDescriptor*        init();

    NS::UInteger                                  maxCallStackDepth() const;

    NS::Array*                                    preloadedLibraries() const;

    void                                          setBinaryLinkedFunctions(const NS::Array* binaryLinkedFunctions);

    void                                          setMaxCallStackDepth(NS::UInteger maxCallStackDepth);

    void                                          setPreloadedLibraries(const NS::Array* preloadedLibraries);
};
class RenderPipelineDynamicLinkingDescriptor : public NS::Copying<RenderPipelineDynamicLinkingDescriptor>
{
public:
    static RenderPipelineDynamicLinkingDescriptor* alloc();

    PipelineStageDynamicLinkingDescriptor*         fragmentLinkingDescriptor() const;

    RenderPipelineDynamicLinkingDescriptor*        init();

    PipelineStageDynamicLinkingDescriptor*         meshLinkingDescriptor() const;

    PipelineStageDynamicLinkingDescriptor*         objectLinkingDescriptor() const;

    PipelineStageDynamicLinkingDescriptor*         tileLinkingDescriptor() const;

    PipelineStageDynamicLinkingDescriptor*         vertexLinkingDescriptor() const;
};

}
/**
 * @brief Allocate a new StaticLinkingDescriptor instance.
 *
 * @return MTL4::StaticLinkingDescriptor* Pointer to a newly allocated StaticLinkingDescriptor; the object is uninitialized and should be initialized (for example by calling `init()`) before use.
 */
_MTL_INLINE MTL4::StaticLinkingDescriptor* MTL4::StaticLinkingDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::StaticLinkingDescriptor>(_MTL_PRIVATE_CLS(MTL4StaticLinkingDescriptor));
}

/**
 * @brief Provides the collection of function descriptors used for static linking.
 *
 * @return NS::Array* Array of function descriptor objects used by this descriptor for static linking.
 */
_MTL_INLINE NS::Array* MTL4::StaticLinkingDescriptor::functionDescriptors() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(functionDescriptors));
}

/**
 * @brief Returns the dictionary of groups associated with this static linking descriptor.
 *
 * @return NS::Dictionary* Dictionary containing the descriptor's groups (may be null).
 */
_MTL_INLINE NS::Dictionary* MTL4::StaticLinkingDescriptor::groups() const
{
    return Object::sendMessage<NS::Dictionary*>(this, _MTL_PRIVATE_SEL(groups));
}

/**
 * @brief Initializes the StaticLinkingDescriptor instance.
 *
 * @return StaticLinkingDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL4::StaticLinkingDescriptor* MTL4::StaticLinkingDescriptor::init()
{
    return NS::Object::init<MTL4::StaticLinkingDescriptor>();
}

/**
 * @brief Accesses the array of private function descriptors associated with this descriptor.
 *
 * @return NS::Array* Array containing the private function descriptors, or `nullptr` if none are set.
 */
_MTL_INLINE NS::Array* MTL4::StaticLinkingDescriptor::privateFunctionDescriptors() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(privateFunctionDescriptors));
}

/**
 * @brief Assigns the list of function descriptors used for static linking.
 *
 * @param functionDescriptors Array whose elements are function descriptor objects to associate with this StaticLinkingDescriptor; pass `nullptr` to clear the list.
 */
_MTL_INLINE void MTL4::StaticLinkingDescriptor::setFunctionDescriptors(const NS::Array* functionDescriptors)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFunctionDescriptors_), functionDescriptors);
}

/**
 * @brief Assigns the groups mapping for this static linking descriptor.
 *
 * @param groups Dictionary of groups to associate with the descriptor.
 */
_MTL_INLINE void MTL4::StaticLinkingDescriptor::setGroups(const NS::Dictionary* groups)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setGroups_), groups);
}

/**
 * @brief Set the descriptor's private function descriptors.
 *
 * Assigns the provided array as this StaticLinkingDescriptor's private function descriptors used during linking.
 *
 * @param privateFunctionDescriptors Array of function descriptor objects to use as the descriptor's private functions.
 */
_MTL_INLINE void MTL4::StaticLinkingDescriptor::setPrivateFunctionDescriptors(const NS::Array* privateFunctionDescriptors)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPrivateFunctionDescriptors_), privateFunctionDescriptors);
}

/**
 * @brief Allocate a new PipelineStageDynamicLinkingDescriptor instance.
 *
 * @return PipelineStageDynamicLinkingDescriptor* A newly allocated descriptor instance (requires `init()` before use).
 */
_MTL_INLINE MTL4::PipelineStageDynamicLinkingDescriptor* MTL4::PipelineStageDynamicLinkingDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::PipelineStageDynamicLinkingDescriptor>(_MTL_PRIVATE_CLS(MTL4PipelineStageDynamicLinkingDescriptor));
}

/**
 * @brief Accesses the list of binary-linked functions for this pipeline stage.
 *
 * @return NS::Array* containing the binary-linked function objects for this pipeline stage; may be `nil`.
 */
_MTL_INLINE NS::Array* MTL4::PipelineStageDynamicLinkingDescriptor::binaryLinkedFunctions() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(binaryLinkedFunctions));
}

/**
 * @brief Initializes the pipeline-stage dynamic linking descriptor.
 *
 * @return PipelineStageDynamicLinkingDescriptor* The initialized descriptor instance.
 */
_MTL_INLINE MTL4::PipelineStageDynamicLinkingDescriptor* MTL4::PipelineStageDynamicLinkingDescriptor::init()
{
    return NS::Object::init<MTL4::PipelineStageDynamicLinkingDescriptor>();
}

/**
 * @brief Retrieves the maximum permitted call stack depth for functions in this pipeline stage.
 *
 * @return NS::UInteger The maximum call stack depth (number of nested function calls) allowed for the pipeline stage.
 */
_MTL_INLINE NS::UInteger MTL4::PipelineStageDynamicLinkingDescriptor::maxCallStackDepth() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxCallStackDepth));
}

/**
 * @brief Array of libraries to be preloaded for this pipeline stage's dynamic linking.
 *
 * @return NS::Array* Array of library objects to preload for dynamic linking.
 */
_MTL_INLINE NS::Array* MTL4::PipelineStageDynamicLinkingDescriptor::preloadedLibraries() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(preloadedLibraries));
}

/**
 * @brief Set the array of binary-linked functions for this pipeline stage descriptor.
 *
 * @param binaryLinkedFunctions Array of function objects to be used for binary linking for this stage.
 */
_MTL_INLINE void MTL4::PipelineStageDynamicLinkingDescriptor::setBinaryLinkedFunctions(const NS::Array* binaryLinkedFunctions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBinaryLinkedFunctions_), binaryLinkedFunctions);
}

/**
 * @brief Set the maximum allowed call stack depth for this pipeline stage's dynamic linking.
 *
 * @param maxCallStackDepth Maximum number of nested function calls permitted when linking dynamically for the pipeline stage.
 */
_MTL_INLINE void MTL4::PipelineStageDynamicLinkingDescriptor::setMaxCallStackDepth(NS::UInteger maxCallStackDepth)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxCallStackDepth_), maxCallStackDepth);
}

/**
 * @brief Configure the list of libraries to preload for dynamic linking of this pipeline stage.
 *
 * @param preloadedLibraries Array of library objects (e.g., MTLDynamicLibrary) to be preloaded before linking.
 */
_MTL_INLINE void MTL4::PipelineStageDynamicLinkingDescriptor::setPreloadedLibraries(const NS::Array* preloadedLibraries)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPreloadedLibraries_), preloadedLibraries);
}

/**
 * @brief Allocate a new RenderPipelineDynamicLinkingDescriptor instance.
 *
 * The returned object is freshly allocated and follows the Objective-C-style
 * alloc/init pattern; call `init()` before using the instance.
 *
 * @return RenderPipelineDynamicLinkingDescriptor* Pointer to the newly allocated descriptor.
 */
_MTL_INLINE MTL4::RenderPipelineDynamicLinkingDescriptor* MTL4::RenderPipelineDynamicLinkingDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::RenderPipelineDynamicLinkingDescriptor>(_MTL_PRIVATE_CLS(MTL4RenderPipelineDynamicLinkingDescriptor));
}

/**
 * @brief Accesses the fragment-stage dynamic linking descriptor.
 *
 * @return PipelineStageDynamicLinkingDescriptor* Pointer to the descriptor for the fragment stage, or `nullptr` if none is set.
 */
_MTL_INLINE MTL4::PipelineStageDynamicLinkingDescriptor* MTL4::RenderPipelineDynamicLinkingDescriptor::fragmentLinkingDescriptor() const
{
    return Object::sendMessage<MTL4::PipelineStageDynamicLinkingDescriptor*>(this, _MTL_PRIVATE_SEL(fragmentLinkingDescriptor));
}

/**
 * @brief Initialize the RenderPipelineDynamicLinkingDescriptor instance.
 *
 * @return RenderPipelineDynamicLinkingDescriptor* Pointer to the initialized instance.
 */
_MTL_INLINE MTL4::RenderPipelineDynamicLinkingDescriptor* MTL4::RenderPipelineDynamicLinkingDescriptor::init()
{
    return NS::Object::init<MTL4::RenderPipelineDynamicLinkingDescriptor>();
}

/**
 * @brief Accesses the mesh stage's dynamic linking descriptor.
 *
 * @return PipelineStageDynamicLinkingDescriptor* Descriptor for mesh-stage dynamic linking, or `nullptr` if no descriptor is set.
 */
_MTL_INLINE MTL4::PipelineStageDynamicLinkingDescriptor* MTL4::RenderPipelineDynamicLinkingDescriptor::meshLinkingDescriptor() const
{
    return Object::sendMessage<MTL4::PipelineStageDynamicLinkingDescriptor*>(this, _MTL_PRIVATE_SEL(meshLinkingDescriptor));
}

/**
 * @brief Retrieves the pipeline-stage dynamic linking descriptor for the object stage.
 *
 * @return MTL4::PipelineStageDynamicLinkingDescriptor* Pointer to the descriptor for the object stage, or `nullptr` if none is set.
 */
_MTL_INLINE MTL4::PipelineStageDynamicLinkingDescriptor* MTL4::RenderPipelineDynamicLinkingDescriptor::objectLinkingDescriptor() const
{
    return Object::sendMessage<MTL4::PipelineStageDynamicLinkingDescriptor*>(this, _MTL_PRIVATE_SEL(objectLinkingDescriptor));
}

/**
 * @brief Retrieves the dynamic linking descriptor for the tile pipeline stage.
 *
 * @return MTL4::PipelineStageDynamicLinkingDescriptor* The descriptor for the tile stage, or `nullptr` if no descriptor is set.
 */
_MTL_INLINE MTL4::PipelineStageDynamicLinkingDescriptor* MTL4::RenderPipelineDynamicLinkingDescriptor::tileLinkingDescriptor() const
{
    return Object::sendMessage<MTL4::PipelineStageDynamicLinkingDescriptor*>(this, _MTL_PRIVATE_SEL(tileLinkingDescriptor));
}

/**
 * @brief Accesses the vertex-stage dynamic linking descriptor.
 *
 * @return PipelineStageDynamicLinkingDescriptor* Pointer to the descriptor for the vertex stage, or `nullptr` if none is set.
 */
_MTL_INLINE MTL4::PipelineStageDynamicLinkingDescriptor* MTL4::RenderPipelineDynamicLinkingDescriptor::vertexLinkingDescriptor() const
{
    return Object::sendMessage<MTL4::PipelineStageDynamicLinkingDescriptor*>(this, _MTL_PRIVATE_SEL(vertexLinkingDescriptor));
}