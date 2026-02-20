//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLComputePipeline.hpp
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
#include "MTLAllocation.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPipeline.hpp"
#include "MTLPrivate.hpp"
#include "MTLTypes.hpp"

namespace MTL
{
class ComputePipelineDescriptor;
class ComputePipelineReflection;
class ComputePipelineState;
class Device;
class Function;
class FunctionHandle;
class IntersectionFunctionTable;
class IntersectionFunctionTableDescriptor;
class LinkedFunctions;
class PipelineBufferDescriptorArray;
class StageInputOutputDescriptor;
class VisibleFunctionTable;
class VisibleFunctionTableDescriptor;

}
namespace MTL4
{
class BinaryFunction;

}
namespace MTL
{
class ComputePipelineReflection : public NS::Referencing<ComputePipelineReflection>
{
public:
    static ComputePipelineReflection* alloc();

    NS::Array*                        arguments() const;

    NS::Array*                        bindings() const;

    ComputePipelineReflection*        init();
};
class ComputePipelineDescriptor : public NS::Copying<ComputePipelineDescriptor>
{
public:
    static ComputePipelineDescriptor* alloc();

    NS::Array*                        binaryArchives() const;

    PipelineBufferDescriptorArray*    buffers() const;

    Function*                         computeFunction() const;

    ComputePipelineDescriptor*        init();

    NS::Array*                        insertLibraries() const;

    NS::String*                       label() const;

    LinkedFunctions*                  linkedFunctions() const;

    NS::UInteger                      maxCallStackDepth() const;

    NS::UInteger                      maxTotalThreadsPerThreadgroup() const;

    NS::Array*                        preloadedLibraries() const;

    Size                              requiredThreadsPerThreadgroup() const;

    void                              reset();

    void                              setBinaryArchives(const NS::Array* binaryArchives);

    void                              setComputeFunction(const MTL::Function* computeFunction);

    void                              setInsertLibraries(const NS::Array* insertLibraries);

    void                              setLabel(const NS::String* label);

    void                              setLinkedFunctions(const MTL::LinkedFunctions* linkedFunctions);

    void                              setMaxCallStackDepth(NS::UInteger maxCallStackDepth);

    void                              setMaxTotalThreadsPerThreadgroup(NS::UInteger maxTotalThreadsPerThreadgroup);

    void                              setPreloadedLibraries(const NS::Array* preloadedLibraries);

    void                              setRequiredThreadsPerThreadgroup(MTL::Size requiredThreadsPerThreadgroup);

    void                              setShaderValidation(MTL::ShaderValidation shaderValidation);

    void                              setStageInputDescriptor(const MTL::StageInputOutputDescriptor* stageInputDescriptor);

    void                              setSupportAddingBinaryFunctions(bool supportAddingBinaryFunctions);

    void                              setSupportIndirectCommandBuffers(bool supportIndirectCommandBuffers);

    void                              setThreadGroupSizeIsMultipleOfThreadExecutionWidth(bool threadGroupSizeIsMultipleOfThreadExecutionWidth);

    ShaderValidation                  shaderValidation() const;

    StageInputOutputDescriptor*       stageInputDescriptor() const;

    bool                              supportAddingBinaryFunctions() const;

    bool                              supportIndirectCommandBuffers() const;

    bool                              threadGroupSizeIsMultipleOfThreadExecutionWidth() const;
};
class ComputePipelineState : public NS::Referencing<ComputePipelineState, Allocation>
{
public:
    Device*                    device() const;

    FunctionHandle*            functionHandle(const NS::String* name);
    FunctionHandle*            functionHandle(const MTL4::BinaryFunction* function);
    FunctionHandle*            functionHandle(const MTL::Function* function);

    ResourceID                 gpuResourceID() const;

    NS::UInteger               imageblockMemoryLength(MTL::Size imageblockDimensions);

    NS::String*                label() const;

    NS::UInteger               maxTotalThreadsPerThreadgroup() const;

    ComputePipelineState*      newComputePipelineStateWithBinaryFunctions(const NS::Array* additionalBinaryFunctions, NS::Error** error);
    ComputePipelineState*      newComputePipelineState(const NS::Array* functions, NS::Error** error);

    IntersectionFunctionTable* newIntersectionFunctionTable(const MTL::IntersectionFunctionTableDescriptor* descriptor);

    VisibleFunctionTable*      newVisibleFunctionTable(const MTL::VisibleFunctionTableDescriptor* descriptor);

    ComputePipelineReflection* reflection() const;

    Size                       requiredThreadsPerThreadgroup() const;

    ShaderValidation           shaderValidation() const;

    NS::UInteger               staticThreadgroupMemoryLength() const;

    bool                       supportIndirectCommandBuffers() const;

    NS::UInteger               threadExecutionWidth() const;
};

}
/**
 * @brief Allocates a new ComputePipelineReflection instance.
 *
 * @return MTL::ComputePipelineReflection* A pointer to the allocated ComputePipelineReflection object;
 * the object is allocated but not initialized (call init() before use).
 */
_MTL_INLINE MTL::ComputePipelineReflection* MTL::ComputePipelineReflection::alloc()
{
    return NS::Object::alloc<MTL::ComputePipelineReflection>(_MTL_PRIVATE_CLS(MTLComputePipelineReflection));
}

/**
 * @brief Retrieve argument metadata for the reflected compute pipeline.
 *
 * @return NS::Array* An array of argument descriptors for the reflected compute function; each element describes a single argument (buffer, texture, sampler, threadgroup memory, etc.).
 */
_MTL_INLINE NS::Array* MTL::ComputePipelineReflection::arguments() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(arguments));
}

/**
 * @brief Retrieves binding metadata associated with this compute pipeline reflection.
 *
 * @return NS::Array* An array of binding descriptor objects describing the pipeline's resource bindings.
 */
_MTL_INLINE NS::Array* MTL::ComputePipelineReflection::bindings() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(bindings));
}

/**
 * @brief Initialize the ComputePipelineReflection instance.
 *
 * Performs the Objective-C init step for a ComputePipelineReflection object.
 *
 * @return ComputePipelineReflection* The initialized instance, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::ComputePipelineReflection* MTL::ComputePipelineReflection::init()
{
    return NS::Object::init<MTL::ComputePipelineReflection>();
}

/**
 * @brief Allocates a new ComputePipelineDescriptor instance.
 *
 * @return MTL::ComputePipelineDescriptor* Allocated, uninitialized compute pipeline descriptor.
 */
_MTL_INLINE MTL::ComputePipelineDescriptor* MTL::ComputePipelineDescriptor::alloc()
{
    return NS::Object::alloc<MTL::ComputePipelineDescriptor>(_MTL_PRIVATE_CLS(MTLComputePipelineDescriptor));
}

/**
 * @brief Binary archives associated with the descriptor.
 *
 * @return NS::Array* An array of binary archive objects previously set on the descriptor, or `nullptr` if none.
 */
_MTL_INLINE NS::Array* MTL::ComputePipelineDescriptor::binaryArchives() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(binaryArchives));
}

/**
 * @brief Retrieve the array of pipeline buffer descriptors configured on this compute pipeline descriptor.
 *
 * @return MTL::PipelineBufferDescriptorArray* Array of pipeline buffer descriptors associated with the descriptor.
 */
_MTL_INLINE MTL::PipelineBufferDescriptorArray* MTL::ComputePipelineDescriptor::buffers() const
{
    return Object::sendMessage<MTL::PipelineBufferDescriptorArray*>(this, _MTL_PRIVATE_SEL(buffers));
}

/**
 * @brief Gets the compute function associated with this descriptor.
 *
 * @return MTL::Function* The compute `Function` set on the descriptor, or `nullptr` if no function is assigned.
 */
_MTL_INLINE MTL::Function* MTL::ComputePipelineDescriptor::computeFunction() const
{
    return Object::sendMessage<MTL::Function*>(this, _MTL_PRIVATE_SEL(computeFunction));
}

/**
 * @brief Initializes the compute pipeline descriptor instance.
 *
 * @return MTL::ComputePipelineDescriptor* Pointer to the initialized descriptor instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::ComputePipelineDescriptor* MTL::ComputePipelineDescriptor::init()
{
    return NS::Object::init<MTL::ComputePipelineDescriptor>();
}

/**
 * @brief Retrieves the list of libraries to insert into the compute pipeline descriptor.
 *
 * @return NS::Array* An array of library objects to be inserted, or `nullptr` if no libraries are set.
 */
_MTL_INLINE NS::Array* MTL::ComputePipelineDescriptor::insertLibraries() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(insertLibraries));
}

/**
 * @brief Gets the human-readable label for the compute pipeline descriptor.
 *
 * @return NS::String* The label string, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::ComputePipelineDescriptor::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Retrieve the LinkedFunctions descriptor associated with this compute pipeline descriptor.
 *
 * @return MTL::LinkedFunctions* The linked functions descriptor, or nullptr if no linked functions are set.
 */
_MTL_INLINE MTL::LinkedFunctions* MTL::ComputePipelineDescriptor::linkedFunctions() const
{
    return Object::sendMessage<MTL::LinkedFunctions*>(this, _MTL_PRIVATE_SEL(linkedFunctions));
}

/**
 * @brief Query the maximum call stack depth configured for this compute pipeline descriptor.
 *
 * @return NS::UInteger The maximum permitted call stack depth for threads executing the pipeline.
 */
_MTL_INLINE NS::UInteger MTL::ComputePipelineDescriptor::maxCallStackDepth() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxCallStackDepth));
}

/**
 * @brief Retrieves the maximum total number of threads allowed per threadgroup for this descriptor.
 *
 * @return NS::UInteger The maximum total threads per threadgroup configured on the descriptor.
 */
_MTL_INLINE NS::UInteger MTL::ComputePipelineDescriptor::maxTotalThreadsPerThreadgroup() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxTotalThreadsPerThreadgroup));
}

/**
 * @brief Returns the array of preloaded libraries configured on the descriptor.
 *
 * The returned array contains the library objects that will be preloaded for the compute pipeline.
 *
 * @return NS::Array* Array of preloaded libraries; may be empty if none are set.
 */
_MTL_INLINE NS::Array* MTL::ComputePipelineDescriptor::preloadedLibraries() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(preloadedLibraries));
}

/**
 * @brief Retrieves the required number of threads per threadgroup for this descriptor.
 *
 * Returns the required threads-per-threadgroup as an MTL::Size struct (width, height, depth).
 *
 * @return MTL::Size The required threads per threadgroup for the compute pipeline descriptor.
 */
_MTL_INLINE MTL::Size MTL::ComputePipelineDescriptor::requiredThreadsPerThreadgroup() const
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(requiredThreadsPerThreadgroup));
}

/**
 * @brief Resets the descriptor to its default, empty state.
 *
 * Clears all configuration set on this compute pipeline descriptor so it
 * matches a newly initialized descriptor.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

/**
 * @brief Set the binary archives to associate with this compute pipeline descriptor.
 *
 * Associates the provided array of binary archives with the descriptor so they are
 * considered when creating or linking the compute pipeline state.
 *
 * @param binaryArchives Array of binary archive objects to use for linking the pipeline.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setBinaryArchives(const NS::Array* binaryArchives)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBinaryArchives_), binaryArchives);
}

/**
 * @brief Set the compute shader function associated with this descriptor.
 *
 * @param computeFunction The Function to use for the compute stage of the pipeline.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setComputeFunction(const MTL::Function* computeFunction)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setComputeFunction_), computeFunction);
}

/**
 * @brief Set the array of additional libraries to insert into the compute pipeline descriptor.
 *
 * @param insertLibraries An NS::Array containing library objects to be inserted into the descriptor.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setInsertLibraries(const NS::Array* insertLibraries)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInsertLibraries_), insertLibraries);
}

/**
 * @brief Sets a human-readable label for the compute pipeline descriptor.
 *
 * @param label A user-visible string to identify the descriptor (may be null to clear).
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Set the linked functions descriptor for this compute pipeline descriptor.
 *
 * Associates a LinkedFunctions descriptor that specifies additional functions and linkage
 * information to include when creating the compute pipeline. Passing `nullptr` clears any
 * previously set linked functions.
 *
 * @param linkedFunctions Descriptor describing linked functions to use, or `nullptr` to clear.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setLinkedFunctions(const MTL::LinkedFunctions* linkedFunctions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLinkedFunctions_), linkedFunctions);
}

/**
 * @brief Set the maximum call stack depth used by the compute pipeline.
 *
 * Configures the maximum number of nested function calls allowed during kernel execution.
 *
 * @param maxCallStackDepth Maximum permitted call stack depth (number of nested calls).
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setMaxCallStackDepth(NS::UInteger maxCallStackDepth)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxCallStackDepth_), maxCallStackDepth);
}

/**
 * @brief Sets the maximum number of threads allowed in a single threadgroup.
 *
 * @param maxTotalThreadsPerThreadgroup The maximum total threads per threadgroup.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setMaxTotalThreadsPerThreadgroup(NS::UInteger maxTotalThreadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxTotalThreadsPerThreadgroup_), maxTotalThreadsPerThreadgroup);
}

/**
 * @brief Set the list of libraries to preload when creating the compute pipeline.
 *
 * @param preloadedLibraries An NS::Array containing library objects to be preloaded into the pipeline before compilation or state creation.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setPreloadedLibraries(const NS::Array* preloadedLibraries)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPreloadedLibraries_), preloadedLibraries);
}

/**
 * @brief Specifies the required number of threads in each threadgroup for the compute pipeline.
 *
 * @param requiredThreadsPerThreadgroup Threadgroup dimensions (width, height, depth) that the pipeline requires.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setRequiredThreadsPerThreadgroup(MTL::Size requiredThreadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRequiredThreadsPerThreadgroup_), requiredThreadsPerThreadgroup);
}

/**
 * @brief Set the shader validation policy for the compute pipeline descriptor.
 *
 * @param shaderValidation The ShaderValidation mode to apply to this descriptor.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setShaderValidation(MTL::ShaderValidation shaderValidation)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setShaderValidation_), shaderValidation);
}

/**
 * @brief Associates a stage input/output descriptor with this compute pipeline descriptor.
 *
 * @param stageInputDescriptor Descriptor that specifies stage input and output layout for the compute pipeline.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setStageInputDescriptor(const MTL::StageInputOutputDescriptor* stageInputDescriptor)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStageInputDescriptor_), stageInputDescriptor);
}

/**
 * @brief Enable or disable support for adding binary functions to the descriptor.
 *
 * @param supportAddingBinaryFunctions `true` to allow adding binary functions to the compute pipeline, `false` to disallow it.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setSupportAddingBinaryFunctions(bool supportAddingBinaryFunctions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportAddingBinaryFunctions_), supportAddingBinaryFunctions);
}

/**
 * @brief Sets whether the compute pipeline supports indirect command buffers.
 *
 * Updates the descriptor to enable or disable support for encoding indirect command buffers
 * when creating the compute pipeline state.
 *
 * @param supportIndirectCommandBuffers `true` to allow indirect command buffers, `false` to disallow them.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setSupportIndirectCommandBuffers(bool supportIndirectCommandBuffers)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSupportIndirectCommandBuffers_), supportIndirectCommandBuffers);
}

/**
 * @brief Configure whether the compute threadgroup size must be a multiple of the thread execution width.
 *
 * @param threadGroupSizeIsMultipleOfThreadExecutionWidth `true` to require threadgroup sizes to be multiples of the thread execution width, `false` to allow other sizes.
 */
_MTL_INLINE void MTL::ComputePipelineDescriptor::setThreadGroupSizeIsMultipleOfThreadExecutionWidth(bool threadGroupSizeIsMultipleOfThreadExecutionWidth)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setThreadGroupSizeIsMultipleOfThreadExecutionWidth_), threadGroupSizeIsMultipleOfThreadExecutionWidth);
}

/**
 * @brief Retrieve the shader validation policy configured for the descriptor.
 *
 * @return MTL::ShaderValidation The current shader validation setting.
 */
_MTL_INLINE MTL::ShaderValidation MTL::ComputePipelineDescriptor::shaderValidation() const
{
    return Object::sendMessage<MTL::ShaderValidation>(this, _MTL_PRIVATE_SEL(shaderValidation));
}

/**
 * @brief Retrieves the stage input/output descriptor configured on this compute pipeline descriptor.
 *
 * @return MTL::StageInputOutputDescriptor* Pointer to the configured stage input/output descriptor, or `nullptr` if none is set.
 */
_MTL_INLINE MTL::StageInputOutputDescriptor* MTL::ComputePipelineDescriptor::stageInputDescriptor() const
{
    return Object::sendMessage<MTL::StageInputOutputDescriptor*>(this, _MTL_PRIVATE_SEL(stageInputDescriptor));
}

/**
 * @brief Reports whether the descriptor permits adding binary functions.
 *
 * @returns `true` if adding binary functions is supported, `false` otherwise.
 */
_MTL_INLINE bool MTL::ComputePipelineDescriptor::supportAddingBinaryFunctions() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportAddingBinaryFunctions));
}

/**
 * @brief Indicates whether indirect command buffers are supported by this descriptor.
 *
 * @return `true` if indirect command buffers are supported, `false` otherwise.
 */
_MTL_INLINE bool MTL::ComputePipelineDescriptor::supportIndirectCommandBuffers() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportIndirectCommandBuffers));
}

/**
 * @brief Indicates whether the pipeline requires the threadgroup size to be a multiple of the thread execution width.
 *
 * @return `true` if the threadgroup size must be a multiple of the thread execution width, `false` otherwise.
 */
_MTL_INLINE bool MTL::ComputePipelineDescriptor::threadGroupSizeIsMultipleOfThreadExecutionWidth() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(threadGroupSizeIsMultipleOfThreadExecutionWidth));
}

/**
 * @brief Returns the Metal device associated with this compute pipeline state.
 *
 * @return MTL::Device* The device that created or owns the compute pipeline state.
 */
_MTL_INLINE MTL::Device* MTL::ComputePipelineState::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Retrieves a function handle for a compute function by name.
 *
 * @param name The name of the function to retrieve a handle for.
 * @return MTL::FunctionHandle* A pointer to the function handle for the named function, or `nullptr` if no function with that name exists.
 */
_MTL_INLINE MTL::FunctionHandle* MTL::ComputePipelineState::functionHandle(const NS::String* name)
{
    return Object::sendMessage<MTL::FunctionHandle*>(this, _MTL_PRIVATE_SEL(functionHandleWithName_), name);
}

/**
 * @brief Retrieve the function handle for the specified binary function.
 *
 * @param function The binary function to look up.
 * @return MTL::FunctionHandle* The function handle associated with `function`, or `nullptr` if no handle is available.
 */
_MTL_INLINE MTL::FunctionHandle* MTL::ComputePipelineState::functionHandle(const MTL4::BinaryFunction* function)
{
    return Object::sendMessage<MTL::FunctionHandle*>(this, _MTL_PRIVATE_SEL(functionHandleWithBinaryFunction_), function);
}

/**
 * @brief Obtain the function handle corresponding to a given compute `Function`.
 *
 * @param function The `Function` whose handle is requested.
 * @return MTL::FunctionHandle* The handle for `function`, or `nullptr` if no handle is available.
 */
_MTL_INLINE MTL::FunctionHandle* MTL::ComputePipelineState::functionHandle(const MTL::Function* function)
{
    return Object::sendMessage<MTL::FunctionHandle*>(this, _MTL_PRIVATE_SEL(functionHandleWithFunction_), function);
}

/**
 * @brief GPU resource identifier associated with this compute pipeline state.
 *
 * @return MTL::ResourceID Identifier that represents the GPU resource used by this pipeline state.
 */
_MTL_INLINE MTL::ResourceID MTL::ComputePipelineState::gpuResourceID() const
{
    return Object::sendMessage<MTL::ResourceID>(this, _MTL_PRIVATE_SEL(gpuResourceID));
}

/**
 * @brief Compute the memory length required for an imageblock with the given dimensions.
 *
 * @param imageblockDimensions Dimensions of the imageblock (width, height, depth).
 * @return NS::UInteger Memory length in bytes required to store the imageblock.
 */
_MTL_INLINE NS::UInteger MTL::ComputePipelineState::imageblockMemoryLength(MTL::Size imageblockDimensions)
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(imageblockMemoryLengthForDimensions_), imageblockDimensions);
}

/**
 * @brief The label associated with this compute pipeline state.
 *
 * @return NS::String* The label string for the pipeline state, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::ComputePipelineState::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Query the maximum total number of threads allowed in a threadgroup.
 *
 * @return NS::UInteger Maximum number of threads that can be dispatched in a single threadgroup.
 */
_MTL_INLINE NS::UInteger MTL::ComputePipelineState::maxTotalThreadsPerThreadgroup() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxTotalThreadsPerThreadgroup));
}

/**
 * @brief Create a new compute pipeline state that includes the provided binary functions.
 *
 * @param additionalBinaryFunctions An NS::Array of MTL4::BinaryFunction objects to include in the created pipeline state.
 * @param error On failure, receives an NS::Error describing the creation error; may be set to nullptr if caller does not want error information.
 * @return MTL::ComputePipelineState* Pointer to the newly created compute pipeline state, or `nullptr` if creation failed.
 */
_MTL_INLINE MTL::ComputePipelineState* MTL::ComputePipelineState::newComputePipelineStateWithBinaryFunctions(const NS::Array* additionalBinaryFunctions, NS::Error** error)
{
    return Object::sendMessage<MTL::ComputePipelineState*>(this, _MTL_PRIVATE_SEL(newComputePipelineStateWithBinaryFunctions_error_), additionalBinaryFunctions, error);
}

/**
 * @brief Create a new compute pipeline state that includes the provided additional binary functions.
 *
 * @param functions An NS::Array containing additional binary functions to include in the created pipeline state.
 * @param error If non-null and pipeline creation fails, set to an NSError describing the failure.
 * @return MTL::ComputePipelineState* A pointer to the newly created compute pipeline state on success, or `nullptr` on failure.
 */
_MTL_INLINE MTL::ComputePipelineState* MTL::ComputePipelineState::newComputePipelineState(const NS::Array* functions, NS::Error** error)
{
    return Object::sendMessage<MTL::ComputePipelineState*>(this, _MTL_PRIVATE_SEL(newComputePipelineStateWithAdditionalBinaryFunctions_error_), functions, error);
}

/**
 * @brief Creates a new intersection function table configured by the given descriptor.
 *
 * @param descriptor Descriptor that specifies the layout and function assignments for the intersection function table.
 * @return MTL::IntersectionFunctionTable* Pointer to the newly created intersection function table, or `nullptr` if creation fails.
 */
_MTL_INLINE MTL::IntersectionFunctionTable* MTL::ComputePipelineState::newIntersectionFunctionTable(const MTL::IntersectionFunctionTableDescriptor* descriptor)
{
    return Object::sendMessage<MTL::IntersectionFunctionTable*>(this, _MTL_PRIVATE_SEL(newIntersectionFunctionTableWithDescriptor_), descriptor);
}

/**
 * @brief Creates a new visible function table configured by the given descriptor.
 *
 * @param descriptor Descriptor that specifies the layout and options for the visible function table.
 * @return MTL::VisibleFunctionTable* A newly created visible function table configured according to `descriptor`, or `nullptr` on failure.
 */
_MTL_INLINE MTL::VisibleFunctionTable* MTL::ComputePipelineState::newVisibleFunctionTable(const MTL::VisibleFunctionTableDescriptor* descriptor)
{
    return Object::sendMessage<MTL::VisibleFunctionTable*>(this, _MTL_PRIVATE_SEL(newVisibleFunctionTableWithDescriptor_), descriptor);
}

/**
 * @brief Provides reflection information for this compute pipeline state.
 *
 * @return MTL::ComputePipelineReflection* Reflection object containing argument metadata and binding descriptions for the compute pipeline.
 */
_MTL_INLINE MTL::ComputePipelineReflection* MTL::ComputePipelineState::reflection() const
{
    return Object::sendMessage<MTL::ComputePipelineReflection*>(this, _MTL_PRIVATE_SEL(reflection));
}

/**
 * @brief Reports the required threads per threadgroup for this compute pipeline state.
 *
 * @return MTL::Size A Size value containing the required number of threads per threadgroup in each dimension (width, height, depth).
 */
_MTL_INLINE MTL::Size MTL::ComputePipelineState::requiredThreadsPerThreadgroup() const
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(requiredThreadsPerThreadgroup));
}

/**
 * @brief Retrieves the shader validation mode configured for this compute pipeline state.
 *
 * @return `MTL::ShaderValidation` value indicating the shader validation policy currently applied to the pipeline state.
 */
_MTL_INLINE MTL::ShaderValidation MTL::ComputePipelineState::shaderValidation() const
{
    return Object::sendMessage<MTL::ShaderValidation>(this, _MTL_PRIVATE_SEL(shaderValidation));
}

/**
 * @brief Retrieves the size, in bytes, of static threadgroup memory required by the compute pipeline state.
 *
 * @return NS::UInteger Size in bytes of static threadgroup memory required by this pipeline state.
 */
_MTL_INLINE NS::UInteger MTL::ComputePipelineState::staticThreadgroupMemoryLength() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(staticThreadgroupMemoryLength));
}

/**
 * @brief Indicates whether the compute pipeline supports indirect command buffers.
 *
 * @return `true` if indirect command buffers are supported, `false` otherwise.
 */
_MTL_INLINE bool MTL::ComputePipelineState::supportIndirectCommandBuffers() const
{
    return Object::sendMessageSafe<bool>(this, _MTL_PRIVATE_SEL(supportIndirectCommandBuffers));
}

/**
 * @brief Query the thread execution width for this compute pipeline state.
 *
 * @return NS::UInteger Number of threads that execute concurrently in a single thread execution width (the device's SIMD/warp size) for this pipeline.
 */
_MTL_INLINE NS::UInteger MTL::ComputePipelineState::threadExecutionWidth() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(threadExecutionWidth));
}