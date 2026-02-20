//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4PipelineState.hpp
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
#include "MTLPipeline.hpp"
#include "MTLPrivate.hpp"

namespace MTL4
{
class PipelineDescriptor;
class PipelineOptions;
_MTL_ENUM(NS::Integer, AlphaToOneState) {
    AlphaToOneStateDisabled = 0,
    AlphaToOneStateEnabled = 1,
};

_MTL_ENUM(NS::Integer, AlphaToCoverageState) {
    AlphaToCoverageStateDisabled = 0,
    AlphaToCoverageStateEnabled = 1,
};

_MTL_ENUM(NS::Integer, BlendState) {
    BlendStateDisabled = 0,
    BlendStateEnabled = 1,
    BlendStateUnspecialized = 2,
};

_MTL_ENUM(NS::Integer, IndirectCommandBufferSupportState) {
    IndirectCommandBufferSupportStateDisabled = 0,
    IndirectCommandBufferSupportStateEnabled = 1,
};

/**
 * @brief Bitmask options controlling what shader reflection data to generate.
 *
 * Specifies which categories of shader reflection information should be produced.
 */
 
/**
 * @brief Represents configurable compilation/runtime options for pipeline creation.
 *
 * Holds settings that influence pipeline behavior such as which shader reflection
 * data to generate and shader validation level.
 */
 
/**
 * @brief Allocate a new PipelineOptions instance.
 *
 * @return PipelineOptions* A newly allocated, uninitialized PipelineOptions object.
 */
 
/**
 * @brief Initialize a PipelineOptions instance.
 *
 * @return PipelineOptions* The initialized PipelineOptions object.
 */
 
/**
 * @brief Set which shader reflection data should be generated for pipelines using these options.
 *
 * @param shaderReflection Bitmask of ShaderReflection flags indicating which reflection categories to enable.
 */
 
/**
 * @brief Set the shader validation policy to apply when compiling or validating shaders.
 *
 * @param shaderValidation The shader validation level to use.
 */
 
/**
 * @brief Query which shader reflection categories are enabled on these options.
 *
 * @return ShaderReflection The currently configured ShaderReflection bitmask.
 */
 
/**
 * @brief Get the configured shader validation policy.
 *
 * @return MTL::ShaderValidation The current shader validation setting.
 */
 
/**
 * @brief Represents a descriptor used to configure pipeline creation parameters.
 *
 * Contains user-facing metadata (like a label) and associated PipelineOptions.
 */
 
/**
 * @brief Allocate a new PipelineDescriptor instance.
 *
 * @return PipelineDescriptor* A newly allocated, uninitialized PipelineDescriptor object.
 */
 
/**
 * @brief Initialize a PipelineDescriptor instance.
 *
 * @return PipelineDescriptor* The initialized PipelineDescriptor object.
 */
 
/**
 * @brief Retrieve the human-readable label associated with this descriptor.
 *
 * @return NS::String* The descriptor's label string, or nullptr if none is set.
 */
 
/**
 * @brief Retrieve the PipelineOptions associated with this descriptor.
 *
 * @return PipelineOptions* Pointer to the descriptor's PipelineOptions, or nullptr if none is set.
 */
 
/**
 * @brief Set a human-readable label for this descriptor.
 *
 * @param label The label string to assign to the descriptor.
 */
 
/**
 * @brief Associate PipelineOptions with this descriptor.
 *
 * @param options Pointer to the PipelineOptions to attach to the descriptor.
 */
_MTL_OPTIONS(NS::UInteger, ShaderReflection) {
    ShaderReflectionNone = 0,
    ShaderReflectionBindingInfo = 1,
    ShaderReflectionBufferTypeInfo = 1 << 1,
};

class PipelineOptions : public NS::Copying<PipelineOptions>
{
public:
    static PipelineOptions* alloc();

    PipelineOptions*        init();

    void                    setShaderReflection(MTL4::ShaderReflection shaderReflection);

    void                    setShaderValidation(MTL::ShaderValidation shaderValidation);

    ShaderReflection        shaderReflection() const;

    MTL::ShaderValidation   shaderValidation() const;
};
class PipelineDescriptor : public NS::Copying<PipelineDescriptor>
{
public:
    static PipelineDescriptor* alloc();

    PipelineDescriptor*        init();

    NS::String*                label() const;

    PipelineOptions*           options() const;

    void                       setLabel(const NS::String* label);

    void                       setOptions(const MTL4::PipelineOptions* options);
};

}
/**
 * @brief Allocate a new PipelineOptions instance.
 *
 * @return MTL4::PipelineOptions* Pointer to an uninitialized PipelineOptions object; call init() before use.
 */
_MTL_INLINE MTL4::PipelineOptions* MTL4::PipelineOptions::alloc()
{
    return NS::Object::alloc<MTL4::PipelineOptions>(_MTL_PRIVATE_CLS(MTL4PipelineOptions));
}

/**
 * @brief Initializes a newly allocated PipelineOptions instance.
 *
 * @return MTL4::PipelineOptions* Pointer to the initialized PipelineOptions instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL4::PipelineOptions* MTL4::PipelineOptions::init()
{
    return NS::Object::init<MTL4::PipelineOptions>();
}

/**
 * @brief Configure which shader reflection data the pipeline should provide.
 *
 * Sets the shader reflection options that control which reflection information
 * (for example, binding info or buffer type info) is retained for this pipeline.
 *
 * @param shaderReflection Bitmask of `MTL4::ShaderReflection` flags specifying which reflection details to enable.
 */
_MTL_INLINE void MTL4::PipelineOptions::setShaderReflection(MTL4::ShaderReflection shaderReflection)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setShaderReflection_), shaderReflection);
}

/**
 * @brief Set the shader validation mode for these pipeline options.
 *
 * @param shaderValidation Validation mode to apply to shaders used by pipelines configured with these options.
 */
_MTL_INLINE void MTL4::PipelineOptions::setShaderValidation(MTL::ShaderValidation shaderValidation)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setShaderValidation_), shaderValidation);
}

/**
 * @brief Retrieve the shader reflection options configured on this PipelineOptions.
 *
 * @return MTL4::ShaderReflection Bitmask describing which shader reflection features are enabled.
 */
_MTL_INLINE MTL4::ShaderReflection MTL4::PipelineOptions::shaderReflection() const
{
    return Object::sendMessage<MTL4::ShaderReflection>(this, _MTL_PRIVATE_SEL(shaderReflection));
}

/**
 * @brief Retrieves the shader validation mode configured for these pipeline options.
 *
 * @return MTL::ShaderValidation The configured shader validation mode.
 */
_MTL_INLINE MTL::ShaderValidation MTL4::PipelineOptions::shaderValidation() const
{
    return Object::sendMessage<MTL::ShaderValidation>(this, _MTL_PRIVATE_SEL(shaderValidation));
}

/**
 * @brief Allocate a new PipelineDescriptor instance.
 *
 * @return MTL4::PipelineDescriptor* A newly allocated PipelineDescriptor instance; call init() before using it.
 */
_MTL_INLINE MTL4::PipelineDescriptor* MTL4::PipelineDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::PipelineDescriptor>(_MTL_PRIVATE_CLS(MTL4PipelineDescriptor));
}

/**
 * @brief Initializes a newly allocated PipelineDescriptor instance.
 *
 * @return MTL4::PipelineDescriptor* Pointer to the initialized PipelineDescriptor, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL4::PipelineDescriptor* MTL4::PipelineDescriptor::init()
{
    return NS::Object::init<MTL4::PipelineDescriptor>();
}

/**
 * @brief Retrieves the pipeline descriptor's label.
 *
 * @return NS::String* The label string, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL4::PipelineDescriptor::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Retrieves the pipeline options associated with this descriptor.
 *
 * @return MTL4::PipelineOptions* Pointer to the PipelineOptions for this descriptor, or `nullptr` if no options are set.
 */
_MTL_INLINE MTL4::PipelineOptions* MTL4::PipelineDescriptor::options() const
{
    return Object::sendMessage<MTL4::PipelineOptions*>(this, _MTL_PRIVATE_SEL(options));
}

/**
 * @brief Set the descriptor's user-visible label.
 *
 * Assigns a human-readable label to the pipeline descriptor for identification.
 *
 * @param label The label string to assign to the descriptor; pass `nullptr` to clear any existing label.
 */
_MTL_INLINE void MTL4::PipelineDescriptor::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Assigns the pipeline options for this descriptor.
 *
 * @param options The PipelineOptions instance to associate with the descriptor.
 */
_MTL_INLINE void MTL4::PipelineDescriptor::setOptions(const MTL4::PipelineOptions* options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOptions_), options);
}