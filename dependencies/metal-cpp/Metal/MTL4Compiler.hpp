//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4Compiler.hpp
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
#include "MTLDevice.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"

#include <functional>

namespace MTL4
{
class BinaryFunction;
class BinaryFunctionDescriptor;
class CompilerDescriptor;
class CompilerTask;
class CompilerTaskOptions;
class ComputePipelineDescriptor;
class LibraryDescriptor;
class MachineLearningPipelineDescriptor;
class MachineLearningPipelineState;
class PipelineDataSetSerializer;
class PipelineDescriptor;
class PipelineStageDynamicLinkingDescriptor;
class RenderPipelineDynamicLinkingDescriptor;
}

namespace MTL
{
class ComputePipelineState;
class Device;
class DynamicLibrary;
class Library;
class RenderPipelineState;

using NewDynamicLibraryCompletionHandler = void (^)(MTL::DynamicLibrary*, NS::Error*);
using NewDynamicLibraryCompletionHandlerFunction = std::function<void(MTL::DynamicLibrary*, NS::Error*)>;
}

namespace MTL4
{
using NewComputePipelineStateCompletionHandler = void (^)(MTL::ComputePipelineState*, NS::Error*);
using NewComputePipelineStateCompletionHandlerFunction = std::function<void(MTL::ComputePipelineState*, NS::Error*)>;
using NewRenderPipelineStateCompletionHandler = void (^)(MTL::RenderPipelineState*, NS::Error*);
using NewRenderPipelineStateCompletionHandlerFunction = std::function<void(MTL::RenderPipelineState*, NS::Error*)>;
using NewBinaryFunctionCompletionHandler = void (^)(MTL4::BinaryFunction*, NS::Error*);
using NewBinaryFunctionCompletionHandlerFunction = std::function<void(MTL4::BinaryFunction*, NS::Error*)>;
using NewMachineLearningPipelineStateCompletionHandler = void (^)(MTL4::MachineLearningPipelineState*, NS::Error*);
using NewMachineLearningPipelineStateCompletionHandlerFunction = std::function<void(MTL4::MachineLearningPipelineState*, NS::Error*)>;

class CompilerDescriptor : public NS::Copying<CompilerDescriptor>
{
public:
    static CompilerDescriptor* alloc();

    CompilerDescriptor*        init();

    NS::String*                label() const;

    PipelineDataSetSerializer* pipelineDataSetSerializer() const;

    void                       setLabel(const NS::String* label);

    void                       setPipelineDataSetSerializer(const MTL4::PipelineDataSetSerializer* pipelineDataSetSerializer);
};
class CompilerTaskOptions : public NS::Copying<CompilerTaskOptions>
{
public:
    static CompilerTaskOptions* alloc();

    CompilerTaskOptions*        init();

    NS::Array*                  lookupArchives() const;
    void                        setLookupArchives(const NS::Array* lookupArchives);
};
class Compiler : public NS::Referencing<Compiler>
{
public:
    MTL::Device*                  device() const;

    NS::String*                   label() const;

    BinaryFunction*               newBinaryFunction(const MTL4::BinaryFunctionDescriptor* descriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, NS::Error** error);
    CompilerTask*                 newBinaryFunction(const MTL4::BinaryFunctionDescriptor* descriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, const MTL4::NewBinaryFunctionCompletionHandler completionHandler);

    MTL::ComputePipelineState*    newComputePipelineState(const MTL4::ComputePipelineDescriptor* descriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, NS::Error** error);
    MTL::ComputePipelineState*    newComputePipelineState(const MTL4::ComputePipelineDescriptor* descriptor, const MTL4::PipelineStageDynamicLinkingDescriptor* dynamicLinkingDescriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, NS::Error** error);
    CompilerTask*                 newComputePipelineState(const MTL4::ComputePipelineDescriptor* descriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, const MTL::NewComputePipelineStateCompletionHandler completionHandler);
    CompilerTask*                 newComputePipelineState(const MTL4::ComputePipelineDescriptor* descriptor, const MTL4::PipelineStageDynamicLinkingDescriptor* dynamicLinkingDescriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, const MTL::NewComputePipelineStateCompletionHandler completionHandler);
    CompilerTask*                 newComputePipelineState(const MTL4::ComputePipelineDescriptor* pDescriptor, const MTL4::CompilerTaskOptions* options, const MTL4::NewComputePipelineStateCompletionHandlerFunction& function);

    MTL::DynamicLibrary*          newDynamicLibrary(const MTL::Library* library, NS::Error** error);
    MTL::DynamicLibrary*          newDynamicLibrary(const NS::URL* url, NS::Error** error);
    CompilerTask*                 newDynamicLibrary(const MTL::Library* library, const MTL::NewDynamicLibraryCompletionHandler completionHandler);
    CompilerTask*                 newDynamicLibrary(const NS::URL* url, const MTL::NewDynamicLibraryCompletionHandler completionHandler);
    CompilerTask*                 newDynamicLibrary(const MTL::Library* pLibrary, const MTL::NewDynamicLibraryCompletionHandlerFunction& function);
    CompilerTask*                 newDynamicLibrary(const NS::URL* pURL, const MTL::NewDynamicLibraryCompletionHandlerFunction& function);

    MTL::Library*                 newLibrary(const MTL4::LibraryDescriptor* descriptor, NS::Error** error);
    CompilerTask*                 newLibrary(const MTL4::LibraryDescriptor* descriptor, const MTL::NewLibraryCompletionHandler completionHandler);
    CompilerTask*                 newLibrary(const MTL4::LibraryDescriptor* pDescriptor, const MTL::NewLibraryCompletionHandlerFunction& function);

    MachineLearningPipelineState* newMachineLearningPipelineState(const MTL4::MachineLearningPipelineDescriptor* descriptor, NS::Error** error);
    CompilerTask*                 newMachineLearningPipelineState(const MTL4::MachineLearningPipelineDescriptor* descriptor, const MTL4::NewMachineLearningPipelineStateCompletionHandler completionHandler);
    CompilerTask*                 newMachineLearningPipelineState(const MTL4::MachineLearningPipelineDescriptor* pDescriptor, const MTL4::NewMachineLearningPipelineStateCompletionHandlerFunction& function);

    MTL::RenderPipelineState*     newRenderPipelineState(const MTL4::PipelineDescriptor* descriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, NS::Error** error);
    MTL::RenderPipelineState*     newRenderPipelineState(const MTL4::PipelineDescriptor* descriptor, const MTL4::RenderPipelineDynamicLinkingDescriptor* dynamicLinkingDescriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, NS::Error** error);
    CompilerTask*                 newRenderPipelineState(const MTL4::PipelineDescriptor* descriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, const MTL::NewRenderPipelineStateCompletionHandler completionHandler);
    CompilerTask*                 newRenderPipelineState(const MTL4::PipelineDescriptor* descriptor, const MTL4::RenderPipelineDynamicLinkingDescriptor* dynamicLinkingDescriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, const MTL::NewRenderPipelineStateCompletionHandler completionHandler);
    CompilerTask*                 newRenderPipelineState(const MTL4::PipelineDescriptor* pDescriptor, const MTL4::CompilerTaskOptions* options, const MTL4::NewRenderPipelineStateCompletionHandlerFunction& function);
    MTL::RenderPipelineState*     newRenderPipelineStateBySpecialization(const MTL4::PipelineDescriptor* descriptor, const MTL::RenderPipelineState* pipeline, NS::Error** error);
    CompilerTask*                 newRenderPipelineStateBySpecialization(const MTL4::PipelineDescriptor* descriptor, const MTL::RenderPipelineState* pipeline, const MTL::NewRenderPipelineStateCompletionHandler completionHandler);
    CompilerTask*                 newRenderPipelineStateBySpecialization(const MTL4::PipelineDescriptor* pDescriptor, const MTL::RenderPipelineState* pPipeline, const MTL4::NewRenderPipelineStateCompletionHandlerFunction& function);

    PipelineDataSetSerializer*    pipelineDataSetSerializer() const;
};

}
/**
 * @brief Allocates a new, uninitialized CompilerDescriptor instance.
 *
 * @return MTL4::CompilerDescriptor* A newly allocated, uninitialized CompilerDescriptor object.
 */
_MTL_INLINE MTL4::CompilerDescriptor* MTL4::CompilerDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::CompilerDescriptor>(_MTL_PRIVATE_CLS(MTL4CompilerDescriptor));
}

/**
 * @brief Initializes a newly allocated CompilerDescriptor instance.
 *
 * @return MTL4::CompilerDescriptor* Pointer to the initialized CompilerDescriptor, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL4::CompilerDescriptor* MTL4::CompilerDescriptor::init()
{
    return NS::Object::init<MTL4::CompilerDescriptor>();
}

/**
 * @brief Returns the human-readable label for the compiler descriptor.
 *
 * @return NS::String* The label string, or `nullptr` if no label has been set.
 */
_MTL_INLINE NS::String* MTL4::CompilerDescriptor::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Retrieves the pipeline data set serializer associated with this compiler descriptor.
 *
 * @return MTL4::PipelineDataSetSerializer* The serializer used for pipeline data sets, or `nullptr` if no serializer has been set.
 */
_MTL_INLINE MTL4::PipelineDataSetSerializer* MTL4::CompilerDescriptor::pipelineDataSetSerializer() const
{
    return Object::sendMessage<MTL4::PipelineDataSetSerializer*>(this, _MTL_PRIVATE_SEL(pipelineDataSetSerializer));
}

/**
 * @brief Set the human-readable label for the compiler descriptor.
 *
 * @param label Human-readable label for the descriptor.
 */
_MTL_INLINE void MTL4::CompilerDescriptor::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Set the pipeline data set serializer for this compiler descriptor.
 *
 * @param pipelineDataSetSerializer The PipelineDataSetSerializer to associate with the descriptor.
 */
_MTL_INLINE void MTL4::CompilerDescriptor::setPipelineDataSetSerializer(const MTL4::PipelineDataSetSerializer* pipelineDataSetSerializer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPipelineDataSetSerializer_), pipelineDataSetSerializer);
}

/**
 * @brief Allocate a new, uninitialized CompilerTaskOptions instance.
 *
 * @return MTL4::CompilerTaskOptions* Pointer to a newly allocated, uninitialized CompilerTaskOptions object.
 */
_MTL_INLINE MTL4::CompilerTaskOptions* MTL4::CompilerTaskOptions::alloc()
{
    return NS::Object::alloc<MTL4::CompilerTaskOptions>(_MTL_PRIVATE_CLS(MTL4CompilerTaskOptions));
}

/**
 * @brief Initializes a newly allocated CompilerTaskOptions instance.
 *
 * Performs object initialization and returns the initialized instance.
 *
 * @return MTL4::CompilerTaskOptions* Pointer to the initialized object, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL4::CompilerTaskOptions* MTL4::CompilerTaskOptions::init()
{
    return NS::Object::init<MTL4::CompilerTaskOptions>();
}

/**
 * @brief Retrieves the list of archives that will be searched during compilation tasks.
 *
 * @return NS::Array* Array of archive objects to look up; may be `nullptr` if no archives are configured.
 */
_MTL_INLINE NS::Array* MTL4::CompilerTaskOptions::lookupArchives() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(lookupArchives));
}

/**
 * @brief Set the archives that the compiler should consult when resolving references.
 *
 * @param lookupArchives An NSArray of archive objects to be searched during compiler tasks.
 */
_MTL_INLINE void MTL4::CompilerTaskOptions::setLookupArchives(const NS::Array* lookupArchives)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLookupArchives_), lookupArchives);
}

/**
 * @brief Retrieve the Metal device associated with this compiler.
 *
 * @return MTL::Device* The device associated with this compiler.
 */
_MTL_INLINE MTL::Device* MTL4::Compiler::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Retrieve the compiler's user-visible label.
 *
 * @return NS::String* The label associated with this compiler, or nullptr if no label is set.
 */
_MTL_INLINE NS::String* MTL4::Compiler::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Creates a new BinaryFunction configured by the given descriptor and task options.
 *
 * @param descriptor Descriptor that specifies the binary function to create.
 * @param compilerTaskOptions Optional compilation options that influence lookup/linking; may be `nullptr`.
 * @param error If non-null and creation fails, set to an `NSError*` describing the failure; may be `nullptr`.
 * @return MTL4::BinaryFunction* The created `BinaryFunction` on success, or `nullptr` on failure (see `error`).
 */
_MTL_INLINE MTL4::BinaryFunction* MTL4::Compiler::newBinaryFunction(const MTL4::BinaryFunctionDescriptor* descriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, NS::Error** error)
{
    return Object::sendMessage<MTL4::BinaryFunction*>(this, _MTL_PRIVATE_SEL(newBinaryFunctionWithDescriptor_compilerTaskOptions_error_), descriptor, compilerTaskOptions, error);
}

/**
 * @brief Asynchronously creates a binary function from the provided descriptor.
 *
 * @param descriptor Descriptor that describes the binary function to create.
 * @param compilerTaskOptions Optional compilation options that influence the task (for example, lookup archives).
 * @param completionHandler Block invoked when the compilation task completes; receives the resulting compiler task and any error encountered.
 * @return MTL4::CompilerTask* The compiler task representing the asynchronous compilation operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newBinaryFunction(const MTL4::BinaryFunctionDescriptor* descriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, const MTL4::NewBinaryFunctionCompletionHandler completionHandler)
{
    return Object::sendMessage<MTL4::CompilerTask*>(this, _MTL_PRIVATE_SEL(newBinaryFunctionWithDescriptor_compilerTaskOptions_completionHandler_), descriptor, compilerTaskOptions, completionHandler);
}

/**
 * @brief Creates a compute pipeline state configured by the given descriptor.
 *
 * Builds and returns a compute pipeline state using the provided descriptor and task options.
 *
 * @param descriptor Descriptor that specifies the compute pipeline configuration.
 * @param compilerTaskOptions Optional compilation options; may be `nullptr`.
 * @param error Out parameter that, on failure, is set to an `NS::Error*` describing the problem; may be `nullptr`.
 * @return MTL::ComputePipelineState* The created compute pipeline state, or `nullptr` if creation failed (see `error`).
 */
_MTL_INLINE MTL::ComputePipelineState* MTL4::Compiler::newComputePipelineState(const MTL4::ComputePipelineDescriptor* descriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, NS::Error** error)
{
    return Object::sendMessage<MTL::ComputePipelineState*>(this, _MTL_PRIVATE_SEL(newComputePipelineStateWithDescriptor_compilerTaskOptions_error_), descriptor, compilerTaskOptions, error);
}

/**
 * Create a compute pipeline state configured by a compute pipeline descriptor,
 * with optional dynamic linking configuration and compiler task options.
 *
 * @param descriptor Descriptor that specifies the compute pipeline configuration.
 * @param dynamicLinkingDescriptor Optional dynamic linking configuration for pipeline stages; may be `nullptr`.
 * @param compilerTaskOptions Optional compilation options (for example, archives to look up); may be `nullptr`.
 * @param error Out parameter set to an `NS::Error*` describing the failure when creation fails; may be `nullptr` if the caller does not require error details.
 * @return MTL::ComputePipelineState* The created compute pipeline state, or `nullptr` if creation failed (in which case `*error` may be set).
 */
_MTL_INLINE MTL::ComputePipelineState* MTL4::Compiler::newComputePipelineState(const MTL4::ComputePipelineDescriptor* descriptor, const MTL4::PipelineStageDynamicLinkingDescriptor* dynamicLinkingDescriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, NS::Error** error)
{
    return Object::sendMessage<MTL::ComputePipelineState*>(this, _MTL_PRIVATE_SEL(newComputePipelineStateWithDescriptor_dynamicLinkingDescriptor_compilerTaskOptions_error_), descriptor, dynamicLinkingDescriptor, compilerTaskOptions, error);
}

/**
 * @brief Begins asynchronous creation of a compute pipeline state using the given descriptor.
 *
 * Starts a compiler task that compiles the provided compute pipeline descriptor and invokes the
 * completion handler when the operation finishes.
 *
 * @param descriptor Descriptor describing the compute pipeline to compile.
 * @param compilerTaskOptions Options that influence the compiler task (for example, archives to look up).
 * @param completionHandler Block invoked on completion with the resulting compute pipeline state or an error.
 * @return MTL4::CompilerTask* A task object representing the asynchronous compilation operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newComputePipelineState(const MTL4::ComputePipelineDescriptor* descriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, const MTL::NewComputePipelineStateCompletionHandler completionHandler)
{
    return Object::sendMessage<MTL4::CompilerTask*>(this, _MTL_PRIVATE_SEL(newComputePipelineStateWithDescriptor_compilerTaskOptions_completionHandler_), descriptor, compilerTaskOptions, completionHandler);
}

/**
 * @brief Starts asynchronous compilation of a compute pipeline state from the provided descriptor.
 *
 * @param descriptor Descriptor that describes the compute pipeline to compile.
 * @param dynamicLinkingDescriptor Dynamic linking options used during pipeline compilation; may be null if not applicable.
 * @param compilerTaskOptions Additional options that influence the compile task (for example, archives to consult); may be null.
 * @param completionHandler Handler invoked when compilation completes; receives the resulting `MTL4::ComputePipelineState*` (or `nullptr`) and an `NS::Error*` if an error occurred.
 * @return MTL4::CompilerTask* A task object representing the asynchronous compilation operation; the provided completion handler will be invoked when the task finishes.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newComputePipelineState(const MTL4::ComputePipelineDescriptor* descriptor, const MTL4::PipelineStageDynamicLinkingDescriptor* dynamicLinkingDescriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, const MTL::NewComputePipelineStateCompletionHandler completionHandler)
{
    return Object::sendMessage<MTL4::CompilerTask*>(this, _MTL_PRIVATE_SEL(newComputePipelineStateWithDescriptor_dynamicLinkingDescriptor_compilerTaskOptions_completionHandler_), descriptor, dynamicLinkingDescriptor, compilerTaskOptions, completionHandler);
}

/**
 * Create a compute pipeline state asynchronously using a function-style completion handler.
 *
 * Wraps the provided function into the block-based completion form and begins an asynchronous
 * compilation task.
 *
 * @param pDescriptor Descriptor that describes the compute pipeline to create.
 * @param options Compiler task options that influence compilation (may be null).
 * @param function Completion function invoked when compilation finishes; called with the created
 *                 `MTL::ComputePipelineState*` (or `nullptr` on failure) and an `NS::Error*`
 *                 describing the failure (or `nullptr` on success).
 * @return MTL4::CompilerTask* A task object representing the asynchronous compilation operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newComputePipelineState(const MTL4::ComputePipelineDescriptor* pDescriptor, const MTL4::CompilerTaskOptions* options, const MTL4::NewComputePipelineStateCompletionHandlerFunction& function)
{
    __block MTL4::NewComputePipelineStateCompletionHandlerFunction blockFunction = function;
    return newComputePipelineState(pDescriptor, options, ^(MTL::ComputePipelineState* pPipeline, NS::Error* pError) { blockFunction(pPipeline, pError); });
}

/**
 * @brief Creates a dynamic library from an existing Library.
 *
 * @param library The source Library to build the dynamic library from.
 * @param error On failure, set to an NS::Error describing the failure; may be `nullptr`.
 * @return MTL::DynamicLibrary* The created dynamic library, or `nullptr` if creation failed.
 */
_MTL_INLINE MTL::DynamicLibrary* MTL4::Compiler::newDynamicLibrary(const MTL::Library* library, NS::Error** error)
{
    return Object::sendMessage<MTL::DynamicLibrary*>(this, _MTL_PRIVATE_SEL(newDynamicLibrary_error_), library, error);
}

/**
 * @brief Builds a dynamic library from the file at the given URL.
 *
 * @param url Location of the library input to build.
 * @param error Out parameter set to an `NS::Error` describing failure, if any.
 * @return MTL::DynamicLibrary* Pointer to the created dynamic library, or `nullptr` if creation failed.
 */
_MTL_INLINE MTL::DynamicLibrary* MTL4::Compiler::newDynamicLibrary(const NS::URL* url, NS::Error** error)
{
    return Object::sendMessage<MTL::DynamicLibrary*>(this, _MTL_PRIVATE_SEL(newDynamicLibraryWithURL_error_), url, error);
}

/**
 * @brief Asynchronously builds a dynamic library from an existing library.
 *
 * Initiates an asynchronous compilation/link step that produces a dynamic library based
 * on the provided `library` and invokes `completionHandler` when the operation completes.
 *
 * @param library The source `MTL::Library` to build the dynamic library from.
 * @param completionHandler Block invoked on completion with the resulting dynamic library and an `NS::Error` if one occurred.
 * @return MTL4::CompilerTask* A task object representing the in-flight compilation operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newDynamicLibrary(const MTL::Library* library, const MTL::NewDynamicLibraryCompletionHandler completionHandler)
{
    return Object::sendMessage<MTL4::CompilerTask*>(this, _MTL_PRIVATE_SEL(newDynamicLibrary_completionHandler_), library, completionHandler);
}

/**
 * @brief Starts an asynchronous build of a dynamic library from the given file URL.
 *
 * @param url Filesystem URL pointing to the library input (e.g., an existing compiled library or source bundle) to build into a dynamic library.
 * @param completionHandler Block invoked when the build completes; called with the resulting `MTL::DynamicLibrary*` on success or an `NS::Error*` describing the failure.
 * @return MTL4::CompilerTask* Task object representing the asynchronous compilation/build operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newDynamicLibrary(const NS::URL* url, const MTL::NewDynamicLibraryCompletionHandler completionHandler)
{
    return Object::sendMessage<MTL4::CompilerTask*>(this, _MTL_PRIVATE_SEL(newDynamicLibraryWithURL_completionHandler_), url, completionHandler);
}

/**
 * @brief Asynchronously creates a dynamic library from an existing Library and invokes a function-style completion handler when finished.
 *
 * The provided completion function is called with the resulting `MTL::DynamicLibrary*` and an `NS::Error*` if one occurred.
 *
 * @param pLibrary Source `MTL::Library` to build the dynamic library from.
 * @param function Completion callback invoked as `function(dynamicLibrary, error)`.
 * @return MTL4::CompilerTask* Task object representing the asynchronous compilation/build operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newDynamicLibrary(const MTL::Library* pLibrary, const MTL::NewDynamicLibraryCompletionHandlerFunction& function)
{
    __block MTL::NewDynamicLibraryCompletionHandlerFunction blockFunction = function;
    return newDynamicLibrary(pLibrary, ^(MTL::DynamicLibrary* pLibraryRef, NS::Error* pError) { blockFunction(pLibraryRef, pError); });
}

/**
 * @brief Create a dynamic library from the given URL and invoke the provided callback on completion.
 *
 * @param pURL URL of the library to build.
 * @param function Callback function invoked with the resulting `MTL::DynamicLibrary*` and an `NS::Error*` describing any failure.
 * @return MTL4::CompilerTask* A task object representing the compilation operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newDynamicLibrary(const NS::URL* pURL, const MTL::NewDynamicLibraryCompletionHandlerFunction& function)
{
    __block MTL::NewDynamicLibraryCompletionHandlerFunction blockFunction = function;
    return newDynamicLibrary(pURL, ^(MTL::DynamicLibrary* pLibrary, NS::Error* pError) { blockFunction(pLibrary, pError); });
}

/**
 * @brief Creates a library from the provided descriptor.
 *
 * @param descriptor Descriptor that describes the library to create.
 * @param error Output parameter that, on failure, is set to an NSError describing the error (may be set to nullptr if the caller is uninterested).
 * @return MTL::Library* Pointer to the created library on success, `nullptr` on failure.
 */
_MTL_INLINE MTL::Library* MTL4::Compiler::newLibrary(const MTL4::LibraryDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<MTL::Library*>(this, _MTL_PRIVATE_SEL(newLibraryWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Begins creating a Library from the provided descriptor and schedules the given completion handler to be called when the operation completes.
 *
 * @param descriptor Descriptor that describes the library to create.
 * @param completionHandler Block invoked when library creation finishes; called with the resulting `MTL::Library*` (or `nullptr` on failure) and an `NS::Error*` describing any error.
 * @return MTL4::CompilerTask* A task object representing the in-progress library creation operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newLibrary(const MTL4::LibraryDescriptor* descriptor, const MTL::NewLibraryCompletionHandler completionHandler)
{
    return Object::sendMessage<MTL4::CompilerTask*>(this, _MTL_PRIVATE_SEL(newLibraryWithDescriptor_completionHandler_), descriptor, completionHandler);
}

/**
 * @brief Create a library asynchronously from a descriptor and notify via a function callback.
 *
 * Initiates asynchronous compilation/creation of a library described by @p pDescriptor and invokes
 * the provided completion @p function with the resulting `MTL::Library*` and any `NS::Error*`.
 *
 * @param pDescriptor Descriptor that specifies the library to create.
 * @param function Completion callback invoked as `function(library, error)` when the operation finishes.
 * @return MTL4::CompilerTask* Task object representing the in-progress asynchronous library creation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newLibrary(const MTL4::LibraryDescriptor* pDescriptor, const MTL::NewLibraryCompletionHandlerFunction& function)
{
    __block MTL::NewLibraryCompletionHandlerFunction blockFunction = function;
    return newLibrary(pDescriptor, ^(MTL::Library* pLibrary, NS::Error* pError) { blockFunction(pLibrary, pError); });
}

/**
 * @brief Create a machine learning pipeline state from the given descriptor.
 *
 * @param descriptor Descriptor describing the machine learning pipeline to create.
 * @param error On error, set to an `NS::Error*` describing the failure; pass `nullptr` to ignore error details.
 * @return MTL4::MachineLearningPipelineState* Compiled pipeline state, or `nullptr` if creation failed. If `nullptr`, `error` may be populated with details.
 */
_MTL_INLINE MTL4::MachineLearningPipelineState* MTL4::Compiler::newMachineLearningPipelineState(const MTL4::MachineLearningPipelineDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<MTL4::MachineLearningPipelineState*>(this, _MTL_PRIVATE_SEL(newMachineLearningPipelineStateWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Begins asynchronous creation of a machine learning pipeline state from a descriptor.
 *
 * Starts a compiler task that compiles or constructs a MachineLearningPipelineState using the
 * provided descriptor and invokes the given completion handler when finished.
 *
 * @param descriptor Descriptor that configures the machine learning pipeline state to create.
 * @param completionHandler Called when the operation completes. Receives the resulting
 *        `MTL4::MachineLearningPipelineState*` (or `nullptr` on failure) and an `NS::Error*`
 *        describing any error (or `nullptr` on success).
 * @return MTL4::CompilerTask* A task object representing the asynchronous compilation operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newMachineLearningPipelineState(const MTL4::MachineLearningPipelineDescriptor* descriptor, const MTL4::NewMachineLearningPipelineStateCompletionHandler completionHandler)
{
    return Object::sendMessage<MTL4::CompilerTask*>(this, _MTL_PRIVATE_SEL(newMachineLearningPipelineStateWithDescriptor_completionHandler_), descriptor, completionHandler);
}

/**
 * @brief Creates a machine learning pipeline state asynchronously using a std::function completion callback.
 *
 * @param pDescriptor Descriptor that configures the machine learning pipeline to create.
 * @param function Completion callback invoked with the created `MTL4::MachineLearningPipelineState*` or an `NS::Error*` on failure.
 * @return MTL4::CompilerTask* A task object that represents and tracks the asynchronous compilation operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newMachineLearningPipelineState(const MTL4::MachineLearningPipelineDescriptor* pDescriptor, const MTL4::NewMachineLearningPipelineStateCompletionHandlerFunction& function)
{
    __block MTL4::NewMachineLearningPipelineStateCompletionHandlerFunction blockFunction = function;
    return newMachineLearningPipelineState(pDescriptor, ^(MTL4::MachineLearningPipelineState* pPipeline, NS::Error* pError) { blockFunction(pPipeline, pError); });
}

/**
 * @brief Create a render pipeline state from the given pipeline descriptor.
 *
 * Compiles and returns a render pipeline state configured by `descriptor`, optionally influenced
 * by `compilerTaskOptions`.
 *
 * @param descriptor Pipeline descriptor that describes the render pipeline to create.
 * @param compilerTaskOptions Optional compiler task options that modify compilation/linking behavior; may be `nullptr`.
 * @param error On failure, set to an `NS::Error*` describing the error; on success may remain unchanged. May be `nullptr` if the caller does not need error details.
 * @return MTL::RenderPipelineState* A new render pipeline state on success, `nullptr` on failure (in which case `error` may be populated).
 */
_MTL_INLINE MTL::RenderPipelineState* MTL4::Compiler::newRenderPipelineState(const MTL4::PipelineDescriptor* descriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, NS::Error** error)
{
    return Object::sendMessage<MTL::RenderPipelineState*>(this, _MTL_PRIVATE_SEL(newRenderPipelineStateWithDescriptor_compilerTaskOptions_error_), descriptor, compilerTaskOptions, error);
}

/**
 * @brief Creates a render pipeline state from a pipeline descriptor with optional dynamic linking and task options.
 *
 * @param descriptor Pipeline descriptor describing the render pipeline to create.
 * @param dynamicLinkingDescriptor Optional descriptor that configures dynamic linking behavior; may be `nullptr`.
 * @param compilerTaskOptions Optional compiler task options (for example, archives to consult); may be `nullptr`.
 * @param error Out parameter set to an `NSError` describing the failure if creation fails; may be `nullptr`.
 * @return MTL::RenderPipelineState* A new render pipeline state on success, `nullptr` on failure.
 */
_MTL_INLINE MTL::RenderPipelineState* MTL4::Compiler::newRenderPipelineState(const MTL4::PipelineDescriptor* descriptor, const MTL4::RenderPipelineDynamicLinkingDescriptor* dynamicLinkingDescriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, NS::Error** error)
{
    return Object::sendMessage<MTL::RenderPipelineState*>(this, _MTL_PRIVATE_SEL(newRenderPipelineStateWithDescriptor_dynamicLinkingDescriptor_compilerTaskOptions_error_), descriptor, dynamicLinkingDescriptor, compilerTaskOptions, error);
}

/**
 * @brief Asynchronously creates a render pipeline state from the given pipeline descriptor.
 *
 * @param descriptor Pipeline descriptor describing the render pipeline to create.
 * @param compilerTaskOptions Options that influence compilation and linking for the task (may be null).
 * @param completionHandler Block invoked when compilation completes; receives the created `MTL::RenderPipelineState*` (or null) and an `NS::Error*` describing any failure.
 * @return MTL4::CompilerTask* Task object representing the asynchronous compilation operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newRenderPipelineState(const MTL4::PipelineDescriptor* descriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, const MTL::NewRenderPipelineStateCompletionHandler completionHandler)
{
    return Object::sendMessage<MTL4::CompilerTask*>(this, _MTL_PRIVATE_SEL(newRenderPipelineStateWithDescriptor_compilerTaskOptions_completionHandler_), descriptor, compilerTaskOptions, completionHandler);
}

/**
 * @brief Creates a render pipeline state using the provided pipeline and dynamic-linking descriptors and compiler options, invoking a completion handler when finished.
 *
 * @param descriptor Pipeline descriptor that describes the render pipeline to create.
 * @param dynamicLinkingDescriptor Dynamic linking configuration to use during pipeline creation (may be null).
 * @param compilerTaskOptions Options that influence the compilation task (e.g., archives to look up).
 * @param completionHandler Called when the operation completes; receives the created `MTL::RenderPipelineState*` (or `nullptr` on failure) and an `NS::Error*` if an error occurred.
 * @return MTL4::CompilerTask* A task object representing the asynchronous compile/link operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newRenderPipelineState(const MTL4::PipelineDescriptor* descriptor, const MTL4::RenderPipelineDynamicLinkingDescriptor* dynamicLinkingDescriptor, const MTL4::CompilerTaskOptions* compilerTaskOptions, const MTL::NewRenderPipelineStateCompletionHandler completionHandler)
{
    return Object::sendMessage<MTL4::CompilerTask*>(this, _MTL_PRIVATE_SEL(newRenderPipelineStateWithDescriptor_dynamicLinkingDescriptor_compilerTaskOptions_completionHandler_), descriptor, dynamicLinkingDescriptor, compilerTaskOptions, completionHandler);
}

/**
 * @brief Initiates asynchronous creation of a render pipeline state and invokes the provided callback when complete.
 *
 * @param pDescriptor Descriptor describing the render pipeline to create.
 * @param options Options that influence the compilation task (may be null).
 * @param function Callback invoked on completion with the created `MTL::RenderPipelineState*` and an `NS::Error*` if one occurred.
 * @return MTL4::CompilerTask* A task object representing the asynchronous compilation operation.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newRenderPipelineState(const MTL4::PipelineDescriptor* pDescriptor, const MTL4::CompilerTaskOptions* options, const MTL4::NewRenderPipelineStateCompletionHandlerFunction& function)
{
    __block MTL4::NewRenderPipelineStateCompletionHandlerFunction blockFunction = function;
    return newRenderPipelineState(pDescriptor, options, ^(MTL::RenderPipelineState* pPipeline, NS::Error* pError) { blockFunction(pPipeline, pError); });
}

/**
 * @brief Create a render pipeline state specialized from an existing pipeline using the provided descriptor.
 *
 * @param descriptor Pipeline descriptor that defines specialization parameters.
 * @param pipeline Existing render pipeline state to specialize.
 * @param error Pointer to an NSError* that will be set if creation fails; may be null.
 * @return MTL::RenderPipelineState* Specialized render pipeline state on success, `nullptr` on failure and `*error` set. 
 */
_MTL_INLINE MTL::RenderPipelineState* MTL4::Compiler::newRenderPipelineStateBySpecialization(const MTL4::PipelineDescriptor* descriptor, const MTL::RenderPipelineState* pipeline, NS::Error** error)
{
    return Object::sendMessage<MTL::RenderPipelineState*>(this, _MTL_PRIVATE_SEL(newRenderPipelineStateBySpecializationWithDescriptor_pipeline_error_), descriptor, pipeline, error);
}

/**
 * @brief Requests specialization of a render pipeline state using a pipeline descriptor and an existing pipeline.
 *
 * @param descriptor Descriptor describing the specialized pipeline to produce.
 * @param pipeline Existing render pipeline state used as the specialization base.
 * @param completionHandler Block invoked when the specialization finishes; receives the resulting `MTL::RenderPipelineState*` (or `nullptr`) and an `NS::Error*` (or `nullptr`).
 * @return MTL4::CompilerTask* Compiler task that performs the specialization and invokes `completionHandler` upon completion.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newRenderPipelineStateBySpecialization(const MTL4::PipelineDescriptor* descriptor, const MTL::RenderPipelineState* pipeline, const MTL::NewRenderPipelineStateCompletionHandler completionHandler)
{
    return Object::sendMessage<MTL4::CompilerTask*>(this, _MTL_PRIVATE_SEL(newRenderPipelineStateBySpecializationWithDescriptor_pipeline_completionHandler_), descriptor, pipeline, completionHandler);
}

/**
 * @brief Creates a specialization task that produces a render pipeline state from an existing pipeline and a pipeline descriptor.
 *
 * Initiates a render-pipeline specialization operation using the provided pipeline descriptor and existing render pipeline, and invokes the given completion function with the resulting pipeline state or an error.
 *
 * @param pDescriptor Descriptor that describes the specialization to apply.
 * @param pPipeline Existing render pipeline state to specialize.
 * @param function Completion callback invoked with the resulting `MTL::RenderPipelineState*` and an `NS::Error*` if one occurred.
 * @return MTL4::CompilerTask* A compiler task representing the specialization operation; the provided completion function will be called when the task completes.
 */
_MTL_INLINE MTL4::CompilerTask* MTL4::Compiler::newRenderPipelineStateBySpecialization(const MTL4::PipelineDescriptor* pDescriptor, const MTL::RenderPipelineState* pPipeline, const MTL4::NewRenderPipelineStateCompletionHandlerFunction& function)
{
    __block MTL4::NewRenderPipelineStateCompletionHandlerFunction blockFunction = function;
    return newRenderPipelineStateBySpecialization(pDescriptor, pPipeline, ^(MTL::RenderPipelineState* pPipelineRef, NS::Error* pError) { blockFunction(pPipelineRef, pError); });
}

/**
 * Retrieves the PipelineDataSetSerializer associated with this compiler.
 *
 * @return MTL4::PipelineDataSetSerializer* The serializer associated with the compiler, or `nullptr` if none is set.
 */
_MTL_INLINE MTL4::PipelineDataSetSerializer* MTL4::Compiler::pipelineDataSetSerializer() const
{
    return Object::sendMessage<MTL4::PipelineDataSetSerializer*>(this, _MTL_PRIVATE_SEL(pipelineDataSetSerializer));
}