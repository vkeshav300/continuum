//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLLibrary.hpp
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
#include "MTLDataType.hpp"
#include "MTLDefines.hpp"
#include "MTLFunctionDescriptor.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLTypes.hpp"

namespace MTL
{
class Argument;
class ArgumentEncoder;
class Attribute;
class CompileOptions;
class Device;
class Function;
class FunctionConstant;
class FunctionConstantValues;
class FunctionDescriptor;
class FunctionReflection;
class IntersectionFunctionDescriptor;
class VertexAttribute;
_MTL_ENUM(NS::UInteger, PatchType) {
    PatchTypeNone = 0,
    PatchTypeTriangle = 1,
    PatchTypeQuad = 2,
};

_MTL_ENUM(NS::UInteger, FunctionType) {
    FunctionTypeVertex = 1,
    FunctionTypeFragment = 2,
    FunctionTypeKernel = 3,
    FunctionTypeVisible = 5,
    FunctionTypeIntersection = 6,
    FunctionTypeMesh = 7,
    FunctionTypeObject = 8,
};

_MTL_ENUM(NS::UInteger, LanguageVersion) {
    LanguageVersion1_0 = 65536,
    LanguageVersion1_1 = 65537,
    LanguageVersion1_2 = 65538,
    LanguageVersion2_0 = 131072,
    LanguageVersion2_1 = 131073,
    LanguageVersion2_2 = 131074,
    LanguageVersion2_3 = 131075,
    LanguageVersion2_4 = 131076,
    LanguageVersion3_0 = 196608,
    LanguageVersion3_1 = 196609,
    LanguageVersion3_2 = 196610,
    LanguageVersion4_0 = 262144,
};

_MTL_ENUM(NS::Integer, LibraryType) {
    LibraryTypeExecutable = 0,
    LibraryTypeDynamic = 1,
};

_MTL_ENUM(NS::Integer, LibraryOptimizationLevel) {
    LibraryOptimizationLevelDefault = 0,
    LibraryOptimizationLevelSize = 1,
};

_MTL_ENUM(NS::Integer, CompileSymbolVisibility) {
    CompileSymbolVisibilityDefault = 0,
    CompileSymbolVisibilityHidden = 1,
};

_MTL_ENUM(NS::Integer, MathMode) {
    MathModeSafe = 0,
    MathModeRelaxed = 1,
    MathModeFast = 2,
};

_MTL_ENUM(NS::Integer, MathFloatingPointFunctions) {
    MathFloatingPointFunctionsFast = 0,
    MathFloatingPointFunctionsPrecise = 1,
};

/**
 * @brief Library error codes returned by library operations.
 */

/**
 * @brief Alias for an autoreleased argument pointer.
 */

/**
 * @brief Alias for a function completion handler type that receives a Function and an NSError.
 *
 * @param pFunction The created Function or nullptr on failure.
 * @param pError An NSError describing failure, or nullptr on success.
 */

/**
 * @brief Returns whether the vertex attribute was active in the compiled function.
 *
 * @return bool `true` if the attribute is active, `false` otherwise.
 */

/**
 * @brief Allocate a new VertexAttribute instance.
 *
 * @return VertexAttribute* A newly allocated, uninitialized VertexAttribute.
 */

/**
 * @brief Index of the vertex attribute within its argument table.
 *
 * @return NS::UInteger The attribute index.
 */

/**
 * @brief Data type of the vertex attribute.
 *
 * @return DataType The attribute's MTL data type.
 */

/**
 * @brief Initialize a VertexAttribute instance.
 *
 * @return VertexAttribute* The initialized VertexAttribute.
 */

/**
 * @brief Indicates whether the vertex attribute is active.
 *
 * @return bool `true` if active, `false` otherwise.
 */

/**
 * @brief Indicates if the attribute represents per-patch control point data.
 *
 * @return bool `true` if it represents patch control point data, `false` otherwise.
 */

/**
 * @brief Indicates if the attribute represents per-patch data.
 *
 * @return bool `true` if it represents patch data, `false` otherwise.
 */

/**
 * @brief Human-readable name of the vertex attribute.
 *
 * @return NS::String* The attribute name, or nullptr if unnamed.
 */

/**
 * @brief Deprecated alias for isPatchControlPointData().
 *
 * @return bool `true` if it represents patch control point data, `false` otherwise.
 */

/**
 * @brief Deprecated alias for isPatchData().
 *
 * @return bool `true` if it represents patch data, `false` otherwise.
 */

/**
 * @brief Returns whether the attribute was active in the compiled function.
 *
 * @return bool `true` if the attribute is active, `false` otherwise.
 */

/**
 * @brief Allocate a new Attribute instance.
 *
 * @return Attribute* A newly allocated, uninitialized Attribute.
 */

/**
 * @brief Index of the attribute within its argument table.
 *
 * @return NS::UInteger The attribute index.
 */

/**
 * @brief Data type of the attribute.
 *
 * @return DataType The attribute's MTL data type.
 */

/**
 * @brief Initialize an Attribute instance.
 *
 * @return Attribute* The initialized Attribute.
 */

/**
 * @brief Indicates whether the attribute is active.
 *
 * @return bool `true` if active, `false` otherwise.
 */

/**
 * @brief Indicates if the attribute represents per-patch control point data.
 *
 * @return bool `true` if it represents patch control point data, `false` otherwise.
 */

/**
 * @brief Indicates if the attribute represents per-patch data.
 *
 * @return bool `true` if it represents patch data, `false` otherwise.
 */

/**
 * @brief Human-readable name of the attribute.
 *
 * @return NS::String* The attribute name, or nullptr if unnamed.
 */

/**
 * @brief Deprecated alias for isPatchControlPointData().
 *
 * @return bool `true` if it represents patch control point data, `false` otherwise.
 */

/**
 * @brief Deprecated alias for isPatchData().
 *
 * @return bool `true` if it represents patch data, `false` otherwise.
 */

/**
 * @brief Allocate a new FunctionConstant instance.
 *
 * @return FunctionConstant* A newly allocated, uninitialized FunctionConstant.
 */

/**
 * @brief Index of the function constant.
 *
 * @return NS::UInteger The constant index.
 */

/**
 * @brief Initialize a FunctionConstant instance.
 *
 * @return FunctionConstant* The initialized FunctionConstant.
 */

/**
 * @brief Human-readable name of the function constant.
 *
 * @return NS::String* The constant name.
 */

/**
 * @brief Whether the function constant is required for function specialization.
 *
 * @return bool `true` if required, `false` otherwise.
 */

/**
 * @brief Data type of the function constant.
 *
 * @return DataType The constant's MTL data type.
 */

/**
 * @brief Device that created or owns the function.
 *
 * @return Device* The associated device.
 */

/**
 * @brief Dictionary describing the function's compile-time constants.
 *
 * @return NS::Dictionary* A mapping of function constant descriptors.
 */

/**
 * @brief Type of the function (vertex, fragment, kernel, etc.).
 *
 * @return FunctionType The function's classification.
 */

/**
 * @brief User-facing label for the function.
 *
 * @return NS::String* The label string, or nullptr if not set.
 */

/**
 * @brief Name of the function within the library.
 *
 * @return NS::String* The function name.
 */

/**
 * @brief Create an ArgumentEncoder for the specified buffer index.
 *
 * @param bufferIndex Buffer index for which to create the encoder.
 * @return ArgumentEncoder* The encoder for the given buffer index.
 */

/**
 * @brief Create an ArgumentEncoder for the specified buffer index using reflection.
 *
 * @param bufferIndex Buffer index for which to create the encoder.
 * @param reflection Reflection information (an AutoreleasedArgument) to guide encoder creation.
 * @return ArgumentEncoder* The encoder configured with the provided reflection.
 */

/**
 * @brief Options associated with the function (runtime/compile options).
 *
 * @return FunctionOptions The function's options.
 */

/**
 * @brief Number of patch control points for tessellated functions.
 *
 * @return NS::Integer The patch control point count.
 */

/**
 * @brief Patch type used for tessellation by this function.
 *
 * @return PatchType The patch type.
 */

/**
 * @brief Set a user-facing label on the function.
 *
 * @param label The label string to assign.
 */

/**
 * @brief Input attributes provided by the stage (stage-specific inputs).
 *
 * @return NS::Array* An array of stage input attribute descriptors.
 */

/**
 * @brief Vertex attributes consumed by the function.
 *
 * @return NS::Array* An array of vertex attribute descriptors.
 */

/**
 * @brief Allocate a new CompileOptions instance.
 *
 * @return CompileOptions* A newly allocated CompileOptions.
 */

/**
 * @brief Whether the compiler may reference undefined symbols when compiling.
 *
 * @return bool `true` if referencing undefined symbols is allowed, `false` otherwise.
 */

/**
 * @brief Visibility setting for symbols produced by compilation.
 *
 * @return CompileSymbolVisibility The configured symbol visibility.
 */

/**
 * @brief Whether the compiler should enable additional logging.
 *
 * @return bool `true` if logging is enabled, `false` otherwise.
 */

/**
 * @brief Whether fast-math optimizations are enabled.
 *
 * @return bool `true` if fast-math is enabled, `false` otherwise.
 */

/**
 * @brief Initialize a CompileOptions instance.
 *
 * @return CompileOptions* The initialized CompileOptions.
 */

/**
 * @brief Install name to embed in a compiled library.
 *
 * @return NS::String* The install name, or nullptr if not set.
 */

/**
 * @brief Language version used to interpret shader source.
 *
 * @return LanguageVersion The configured language version.
 */

/**
 * @brief Libraries to link against during compilation.
 *
 * @return NS::Array* An array of library references.
 */

/**
 * @brief Target library type for compilation.
 *
 * @return LibraryType The configured library type.
 */

/**
 * @brief Floating-point function behavior selection.
 *
 * @return MathFloatingPointFunctions The chosen floating-point function behavior.
 */

/**
 * @brief Math mode controlling precision/safety tradeoffs.
 *
 * @return MathMode The configured math mode.
 */

/**
 * @brief Maximum total threads allowed per threadgroup.
 *
 * @return NS::UInteger The maximum thread count.
 */

/**
 * @brief Optimization level used for library compilation.
 *
 * @return LibraryOptimizationLevel The optimization level.
 */

/**
 * @brief Preprocessor macros applied during compilation.
 *
 * @return NS::Dictionary* Dictionary of macro name/value pairs.
 */

/**
 * @brief Whether invariance is preserved during compilation.
 *
 * @return bool `true` if invariance is preserved, `false` otherwise.
 */

/**
 * @brief Required threads-per-threadgroup size hint for the compiled library.
 *
 * @return Size The required threads-per-threadgroup size.
 */

/**
 * @brief Allow or disallow referencing undefined symbols during compilation.
 *
 * @param allowReferencingUndefinedSymbols `true` to allow, `false` to disallow.
 */

/**
 * @brief Set the visibility for symbols produced by compilation.
 *
 * @param compileSymbolVisibility The desired symbol visibility.
 */

/**
 * @brief Enable or disable compiler logging.
 *
 * @param enableLogging `true` to enable logging, `false` to disable.
 */

/**
 * @brief Enable or disable fast-math optimizations.
 *
 * @param fastMathEnabled `true` to enable fast-math, `false` to disable.
 */

/**
 * @brief Set the install name to embed in the compiled library.
 *
 * @param installName The install name string.
 */

/**
 * @brief Set the language version used to interpret shader source.
 *
 * @param languageVersion The language version to use.
 */

/**
 * @brief Set libraries to link against during compilation.
 *
 * @param libraries An array of library references.
 */

/**
 * @brief Set the target library type for compilation.
 *
 * @param libraryType The desired library type.
 */

/**
 * @brief Set the floating-point function behavior selection.
 *
 * @param mathFloatingPointFunctions The chosen floating-point function behavior.
 */

/**
 * @brief Set the math mode controlling precision/safety tradeoffs.
 *
 * @param mathMode The desired math mode.
 */

/**
 * @brief Set the maximum total threads allowed per threadgroup.
 *
 * @param maxTotalThreadsPerThreadgroup The maximum thread count.
 */

/**
 * @brief Set the optimization level for library compilation.
 *
 * @param optimizationLevel The desired optimization level.
 */

/**
 * @brief Set preprocessor macros to apply during compilation.
 *
 * @param preprocessorMacros Dictionary of macro name/value pairs.
 */

/**
 * @brief Set whether invariance should be preserved during compilation.
 *
 * @param preserveInvariance `true` to preserve invariance, `false` otherwise.
 */

/**
 * @brief Set the required threads-per-threadgroup size hint for the compiled library.
 *
 * @param requiredThreadsPerThreadgroup The required threads-per-threadgroup size.
 */

/**
 * @brief Allocate a new FunctionReflection instance.
 *
 * @return FunctionReflection* A newly allocated FunctionReflection.
 */

/**
 * @brief Array of binding descriptors describing resources used by the function.
 *
 * @return NS::Array* An array of binding descriptors.
 */

/**
 * @brief Initialize a FunctionReflection instance.
 *
 * @return FunctionReflection* The initialized FunctionReflection.
 */

/**
 * @brief Device associated with the library.
 *
 * @return Device* The device that created the library.
 */

/**
 * @brief Names of functions contained in the library.
 *
 * @return NS::Array* An array of function name strings.
 */

/**
 * @brief Install name of the library, if present.
 *
 * @return NS::String* The library install name, or nullptr if not set.
 */

/**
 * @brief User-facing label for the library.
 *
 * @return NS::String* The label string, or nullptr if not set.
 */

/**
 * @brief Create a Function by name from the library.
 *
 * @param functionName Name of the function to create.
 * @return Function* The created Function, or nullptr if not found.
 */

/**
 * @brief Create a specialized Function by name using provided constant values.
 *
 * @param name Name of the function to create.
 * @param constantValues FunctionConstantValues used to specialize the function.
 * @param error Out parameter set to an NSError on failure.
 * @return Function* The created Function, or nullptr on failure.
 */

/**
 * @brief Asynchronously create a specialized Function by name using provided constant values.
 *
 * @param name Name of the function to create.
 * @param constantValues FunctionConstantValues used to specialize the function.
 * @param completionHandler Block invoked with the created Function or an NSError on failure.
 */

/**
 * @brief Asynchronously create a Function using a FunctionDescriptor.
 *
 * @param descriptor Descriptor describing function creation parameters.
 * @param completionHandler Block invoked with the created Function or an NSError on failure.
 */

/**
 * @brief Create a Function synchronously using a FunctionDescriptor.
 *
 * @param descriptor Descriptor describing function creation parameters.
 * @param error Out parameter set to an NSError on failure.
 * @return Function* The created Function, or nullptr on failure.
 */

/**
 * @brief Create a specialized Function by name using provided constant values with a std::function completion callback.
 *
 * @param pFunctionName Name of the function to create.
 * @param pConstantValues FunctionConstantValues used to specialize the function.
 * @param completionHandler Function invoked with the created Function or an NSError on failure.
 */

/**
 * @brief Asynchronously create a Function using a FunctionDescriptor with a std::function completion callback.
 *
 * @param pDescriptor Descriptor describing function creation parameters.
 * @param completionHandler Function invoked with the created Function or an NSError on failure.
 */

/**
 * @brief Asynchronously create an intersection function using a descriptor.
 *
 * @param descriptor Descriptor describing the intersection function.
 * @param completionHandler Block invoked with the created Function or an NSError on failure.
 */

/**
 * @brief Create an intersection function synchronously using a descriptor.
 *
 * @param descriptor Descriptor describing the intersection function.
 * @param error Out parameter set to an NSError on failure.
 * @return Function* The created intersection Function, or nullptr on failure.
 */

/**
 * @brief Asynchronously create an intersection function using a descriptor with a std::function completion callback.
 *
 * @param pDescriptor Descriptor describing the intersection function.
 * @param completionHandler Function invoked with the created Function or an NSError on failure.
 */

/**
 * @brief Retrieve reflection information for a named function in the library.
 *
 * @param functionName Name of the function to reflect.
 * @return FunctionReflection* Reflection data for the function, or nullptr if not available.
 */

/**
 * @brief Set a user-facing label on the library.
 *
 * @param label The label string to assign.
 */

/**
 * @brief Type of the library (executable, dynamic, etc.).
 *
 * @return LibraryType The library's type.
 */
_MTL_ENUM(NS::UInteger, LibraryError) {
    LibraryErrorUnsupported = 1,
    LibraryErrorInternal = 2,
    LibraryErrorCompileFailure = 3,
    LibraryErrorCompileWarning = 4,
    LibraryErrorFunctionNotFound = 5,
    LibraryErrorFileNotFound = 6,
};

using AutoreleasedArgument = MTL::Argument*;
using FunctionCompletionHandlerFunction = std::function<void(MTL::Function* pFunction, NS::Error* pError)>;

class VertexAttribute : public NS::Referencing<VertexAttribute>
{
public:
    [[deprecated("please use isActive instead")]]
    bool                    active() const;

    static VertexAttribute* alloc();

    NS::UInteger            attributeIndex() const;

    DataType                attributeType() const;

    VertexAttribute*        init();

    bool                    isActive() const;

    bool                    isPatchControlPointData() const;

    bool                    isPatchData() const;

    NS::String*             name() const;

    [[deprecated("please use isPatchControlPointData instead")]]
    bool patchControlPointData() const;

    [[deprecated("please use isPatchData instead")]]
    bool patchData() const;
};
class Attribute : public NS::Referencing<Attribute>
{
public:
    [[deprecated("please use isActive instead")]]
    bool              active() const;

    static Attribute* alloc();

    NS::UInteger      attributeIndex() const;

    DataType          attributeType() const;

    Attribute*        init();

    bool              isActive() const;

    bool              isPatchControlPointData() const;

    bool              isPatchData() const;

    NS::String*       name() const;

    [[deprecated("please use isPatchControlPointData instead")]]
    bool patchControlPointData() const;

    [[deprecated("please use isPatchData instead")]]
    bool patchData() const;
};
class FunctionConstant : public NS::Referencing<FunctionConstant>
{
public:
    static FunctionConstant* alloc();

    NS::UInteger             index() const;

    FunctionConstant*        init();

    NS::String*              name() const;

    bool                     required() const;

    DataType                 type() const;
};
class Function : public NS::Referencing<Function>
{
public:
    Device*          device() const;

    NS::Dictionary*  functionConstantsDictionary() const;

    FunctionType     functionType() const;

    NS::String*      label() const;

    NS::String*      name() const;

    ArgumentEncoder* newArgumentEncoder(NS::UInteger bufferIndex);
    ArgumentEncoder* newArgumentEncoder(NS::UInteger bufferIndex, const MTL::AutoreleasedArgument* reflection);

    FunctionOptions  options() const;

    NS::Integer      patchControlPointCount() const;

    PatchType        patchType() const;

    void             setLabel(const NS::String* label);

    NS::Array*       stageInputAttributes() const;

    NS::Array*       vertexAttributes() const;
};
class CompileOptions : public NS::Copying<CompileOptions>
{
public:
    static CompileOptions*     alloc();

    bool                       allowReferencingUndefinedSymbols() const;

    CompileSymbolVisibility    compileSymbolVisibility() const;

    bool                       enableLogging() const;

    bool                       fastMathEnabled() const;

    CompileOptions*            init();

    NS::String*                installName() const;

    LanguageVersion            languageVersion() const;

    NS::Array*                 libraries() const;

    LibraryType                libraryType() const;

    MathFloatingPointFunctions mathFloatingPointFunctions() const;

    MathMode                   mathMode() const;

    NS::UInteger               maxTotalThreadsPerThreadgroup() const;

    LibraryOptimizationLevel   optimizationLevel() const;

    NS::Dictionary*            preprocessorMacros() const;

    bool                       preserveInvariance() const;

    Size                       requiredThreadsPerThreadgroup() const;

    void                       setAllowReferencingUndefinedSymbols(bool allowReferencingUndefinedSymbols);

    void                       setCompileSymbolVisibility(MTL::CompileSymbolVisibility compileSymbolVisibility);

    void                       setEnableLogging(bool enableLogging);

    void                       setFastMathEnabled(bool fastMathEnabled);

    void                       setInstallName(const NS::String* installName);

    void                       setLanguageVersion(MTL::LanguageVersion languageVersion);

    void                       setLibraries(const NS::Array* libraries);

    void                       setLibraryType(MTL::LibraryType libraryType);

    void                       setMathFloatingPointFunctions(MTL::MathFloatingPointFunctions mathFloatingPointFunctions);

    void                       setMathMode(MTL::MathMode mathMode);

    void                       setMaxTotalThreadsPerThreadgroup(NS::UInteger maxTotalThreadsPerThreadgroup);

    void                       setOptimizationLevel(MTL::LibraryOptimizationLevel optimizationLevel);

    void                       setPreprocessorMacros(const NS::Dictionary* preprocessorMacros);

    void                       setPreserveInvariance(bool preserveInvariance);

    void                       setRequiredThreadsPerThreadgroup(MTL::Size requiredThreadsPerThreadgroup);
};
class FunctionReflection : public NS::Referencing<FunctionReflection>
{
public:
    static FunctionReflection* alloc();

    NS::Array*                 bindings() const;

    FunctionReflection*        init();
};
class Library : public NS::Referencing<Library>
{
public:
    Device*             device() const;

    NS::Array*          functionNames() const;

    NS::String*         installName() const;

    NS::String*         label() const;

    Function*           newFunction(const NS::String* functionName);
    Function*           newFunction(const NS::String* name, const MTL::FunctionConstantValues* constantValues, NS::Error** error);
    void                newFunction(const NS::String* name, const MTL::FunctionConstantValues* constantValues, void (^completionHandler)(MTL::Function*, NS::Error*));
    void                newFunction(const MTL::FunctionDescriptor* descriptor, void (^completionHandler)(MTL::Function*, NS::Error*));
    Function*           newFunction(const MTL::FunctionDescriptor* descriptor, NS::Error** error);
    void                newFunction(const NS::String* pFunctionName, const MTL::FunctionConstantValues* pConstantValues, const MTL::FunctionCompletionHandlerFunction& completionHandler);
    void                newFunction(const MTL::FunctionDescriptor* pDescriptor, const MTL::FunctionCompletionHandlerFunction& completionHandler);

    void                newIntersectionFunction(const MTL::IntersectionFunctionDescriptor* descriptor, void (^completionHandler)(MTL::Function*, NS::Error*));
    Function*           newIntersectionFunction(const MTL::IntersectionFunctionDescriptor* descriptor, NS::Error** error);
    void                newIntersectionFunction(const MTL::IntersectionFunctionDescriptor* pDescriptor, const MTL::FunctionCompletionHandlerFunction& completionHandler);

    FunctionReflection* reflectionForFunction(const NS::String* functionName);

    void                setLabel(const NS::String* label);

    LibraryType         type() const;
};

}
/**
 * @brief Query whether the vertex attribute is active.
 *
 * @return `true` if the vertex attribute is active, `false` otherwise.
 */
_MTL_INLINE bool MTL::VertexAttribute::active() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isActive));
}

/**
 * @brief Allocates a new VertexAttribute instance.
 *
 * @return MTL::VertexAttribute* A newly allocated VertexAttribute object; call init() before use.
 */
_MTL_INLINE MTL::VertexAttribute* MTL::VertexAttribute::alloc()
{
    return NS::Object::alloc<MTL::VertexAttribute>(_MTL_PRIVATE_CLS(MTLVertexAttribute));
}

/**
 * @brief Retrieves the index of this vertex attribute.
 *
 * @return NS::UInteger The attribute's index within its vertex descriptor.
 */
_MTL_INLINE NS::UInteger MTL::VertexAttribute::attributeIndex() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(attributeIndex));
}

/**
 * @brief Gets the data type of the vertex attribute.
 *
 * @return MTL::DataType The data type of this vertex attribute.
 */
_MTL_INLINE MTL::DataType MTL::VertexAttribute::attributeType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(attributeType));
}

/**
 * @brief Initialize a newly allocated VertexAttribute instance.
 *
 * @return MTL::VertexAttribute* Pointer to the initialized instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::VertexAttribute* MTL::VertexAttribute::init()
{
    return NS::Object::init<MTL::VertexAttribute>();
}

/**
 * @brief Indicates whether the vertex attribute is active.
 *
 * @return `true` if the attribute is active, `false` otherwise.
 */
_MTL_INLINE bool MTL::VertexAttribute::isActive() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isActive));
}

/**
 * @brief Indicates whether the attribute represents per-patch control point data.
 *
 * @return `true` if the vertex attribute is patch control point data, `false` otherwise.
 */
_MTL_INLINE bool MTL::VertexAttribute::isPatchControlPointData() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isPatchControlPointData));
}

/**
 * @brief Indicates whether this vertex attribute represents patch data.
 *
 * @return `true` if the attribute represents patch data (tessellation patch-level data), `false` otherwise.
 */
_MTL_INLINE bool MTL::VertexAttribute::isPatchData() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isPatchData));
}

/**
 * @brief Retrieves the vertex attribute's name.
 *
 * @return NS::String* The attribute's name.
 */
_MTL_INLINE NS::String* MTL::VertexAttribute::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Indicates whether the attribute contains per-patch control point data.
 *
 * @return `true` if the attribute represents patch control point data, `false` otherwise.
 */
_MTL_INLINE bool MTL::VertexAttribute::patchControlPointData() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isPatchControlPointData));
}

/**
 * @brief Indicates whether the vertex attribute represents patch data.
 *
 * @deprecated Use isPatchData() instead.
 * @return `true` if the attribute represents patch data, `false` otherwise.
 */
_MTL_INLINE bool MTL::VertexAttribute::patchData() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isPatchData));
}

/**
 * @brief Indicates whether the attribute is active.
 *
 * @return `true` if the attribute is active, `false` otherwise.
 */
_MTL_INLINE bool MTL::Attribute::active() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isActive));
}

/**
 * @brief Allocate a new Attribute object.
 *
 * Allocates memory for an Attribute instance; the returned object must be initialized (call init()) before use.
 *
 * @return MTL::Attribute* A newly allocated Attribute instance.
 */
_MTL_INLINE MTL::Attribute* MTL::Attribute::alloc()
{
    return NS::Object::alloc<MTL::Attribute>(_MTL_PRIVATE_CLS(MTLAttribute));
}

/**
 * @brief Gets the attribute's index within its owning function or argument list.
 *
 * @return NS::UInteger The attribute's index.
 */
_MTL_INLINE NS::UInteger MTL::Attribute::attributeIndex() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(attributeIndex));
}

/**
 * @brief Retrieves the attribute's data type.
 *
 * @return MTL::DataType The attribute's data type.
 */
_MTL_INLINE MTL::DataType MTL::Attribute::attributeType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(attributeType));
}

/**
 * @brief Initialize a newly allocated Attribute instance.
 *
 * @return MTL::Attribute* An initialized Attribute instance.
 */
_MTL_INLINE MTL::Attribute* MTL::Attribute::init()
{
    return NS::Object::init<MTL::Attribute>();
}

/**
 * @brief Indicates whether this attribute is active in the function interface.
 *
 * @return `true` if the attribute is active, `false` otherwise.
 */
_MTL_INLINE bool MTL::Attribute::isActive() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isActive));
}

/**
 * @brief Reports whether the attribute contains patch control point data.
 *
 * @return `true` if the attribute represents patch control point data, `false` otherwise.
 */
_MTL_INLINE bool MTL::Attribute::isPatchControlPointData() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isPatchControlPointData));
}

/**
 * @brief Indicates whether the attribute contains per-patch data rather than per-vertex data.
 *
 * @return `true` if the attribute represents patch data, `false` otherwise.
 */
_MTL_INLINE bool MTL::Attribute::isPatchData() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isPatchData));
}

/**
 * @brief Retrieve the attribute's name.
 *
 * @return NS::String* The attribute's name, or `nullptr` if no name is set.
 */
_MTL_INLINE NS::String* MTL::Attribute::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Checks whether the attribute represents patch control point data.
 *
 * @deprecated This accessor is deprecated; prefer the clearer `isPatchControlPointData` API.
 * @return `true` if the attribute represents patch control point data, `false` otherwise.
 */
_MTL_INLINE bool MTL::Attribute::patchControlPointData() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isPatchControlPointData));
}

/**
 * @brief Deprecated. Indicates whether the attribute represents per-patch data.
 *
 * @deprecated Use `isPatchData()` instead.
 * @return `true` if the attribute stores per-patch data, `false` otherwise.
 */
_MTL_INLINE bool MTL::Attribute::patchData() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isPatchData));
}

/**
 * @brief Allocates a new FunctionConstant object.
 *
 * Allocates memory for a FunctionConstant instance; the returned object must be initialized before use (for example, by calling `init()`).
 *
 * @return MTL::FunctionConstant* Pointer to the newly allocated FunctionConstant.
 */
_MTL_INLINE MTL::FunctionConstant* MTL::FunctionConstant::alloc()
{
    return NS::Object::alloc<MTL::FunctionConstant>(_MTL_PRIVATE_CLS(MTLFunctionConstant));
}

/**
 * @brief Gets the index of this function constant.
 *
 * @return NS::UInteger The function constant's index within its function.
 */
_MTL_INLINE NS::UInteger MTL::FunctionConstant::index() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(index));
}

/**
 * @brief Initializes a FunctionConstant instance.
 *
 * Performs object initialization and returns the initialized instance.
 *
 * @return MTL::FunctionConstant* Pointer to the initialized FunctionConstant, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::FunctionConstant* MTL::FunctionConstant::init()
{
    return NS::Object::init<MTL::FunctionConstant>();
}

/**
 * @brief Gets the function constant's name.
 *
 * @return NS::String* The name of the function constant.
 */
_MTL_INLINE NS::String* MTL::FunctionConstant::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Indicates whether the function constant is required.
 *
 * @return `true` if the function constant must be provided, `false` otherwise.
 */
_MTL_INLINE bool MTL::FunctionConstant::required() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(required));
}

/**
 * @brief Retrieve the function constant's data type.
 *
 * @return MTL::DataType describing the function constant's data representation.
 */
_MTL_INLINE MTL::DataType MTL::FunctionConstant::type() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(type));
}

/**
 * @brief Gets the Metal device associated with this function.
 *
 * @return MTL::Device* The device object that created or owns this function.
 */
_MTL_INLINE MTL::Device* MTL::Function::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Retrieve the dictionary of function-constant descriptors for this function.
 *
 * @return NS::Dictionary* A dictionary mapping function constant names (NSString) to
 *         MTL::FunctionConstant objects describing each compile-time constant. 
 */
_MTL_INLINE NS::Dictionary* MTL::Function::functionConstantsDictionary() const
{
    return Object::sendMessage<NS::Dictionary*>(this, _MTL_PRIVATE_SEL(functionConstantsDictionary));
}

/**
 * @brief Reports the kind of shader function.
 *
 * @return MTL::FunctionType The function's type (one of `Vertex`, `Fragment`, `Kernel`, `Visible`, `Intersection`, `Mesh`, or `Object`).
 */
_MTL_INLINE MTL::FunctionType MTL::Function::functionType() const
{
    return Object::sendMessage<MTL::FunctionType>(this, _MTL_PRIVATE_SEL(functionType));
}

/**
 * @brief The user-facing label for this function.
 *
 * @return NS::String* The function's label, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::Function::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Retrieves the human-readable name of the function.
 *
 * @return NS::String* The function's name.
 */
_MTL_INLINE NS::String* MTL::Function::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Creates an argument encoder for the function's argument buffer at the specified index.
 *
 * @param bufferIndex Index of the argument buffer within the function's argument table.
 * @return MTL::ArgumentEncoder* An encoder configured to encode the function's arguments for the specified buffer index.
 */
_MTL_INLINE MTL::ArgumentEncoder* MTL::Function::newArgumentEncoder(NS::UInteger bufferIndex)
{
    return Object::sendMessage<MTL::ArgumentEncoder*>(this, _MTL_PRIVATE_SEL(newArgumentEncoderWithBufferIndex_), bufferIndex);
}

/**
 * @brief Create an argument encoder for a specific buffer index, optionally using reflection data.
 *
 * @param bufferIndex The buffer index whose argument layout the encoder will target.
 * @param reflection Optional reflection information describing the argument layout; may be `nullptr`.
 * @return MTL::ArgumentEncoder* An argument encoder configured for encoding arguments at the specified buffer index, or `nullptr` if creation fails.
 */
_MTL_INLINE MTL::ArgumentEncoder* MTL::Function::newArgumentEncoder(NS::UInteger bufferIndex, const MTL::AutoreleasedArgument* reflection)
{
    return Object::sendMessage<MTL::ArgumentEncoder*>(this, _MTL_PRIVATE_SEL(newArgumentEncoderWithBufferIndex_reflection_), bufferIndex, reflection);
}

/**
 * @brief Returns the options configured for this shader function.
 *
 * @return MTL::FunctionOptions Bitmask describing the function's compilation and runtime options (flags).
 */
_MTL_INLINE MTL::FunctionOptions MTL::Function::options() const
{
    return Object::sendMessage<MTL::FunctionOptions>(this, _MTL_PRIVATE_SEL(options));
}

/**
 * @brief Returns the number of patch control points associated with this function's tessellation patch.
 *
 * @return NS::Integer Number of patch control points; 0 if the function does not use patch-based tessellation.
 */
_MTL_INLINE NS::Integer MTL::Function::patchControlPointCount() const
{
    return Object::sendMessage<NS::Integer>(this, _MTL_PRIVATE_SEL(patchControlPointCount));
}

/**
 * @brief Retrieve the tessellation patch type for this function.
 *
 * @return MTL::PatchType The function's patch type: PatchType::None, PatchType::Triangle, or PatchType::Quad.
 */
_MTL_INLINE MTL::PatchType MTL::Function::patchType() const
{
    return Object::sendMessage<MTL::PatchType>(this, _MTL_PRIVATE_SEL(patchType));
}

/**
 * @brief Assigns a human-readable label to the function.
 *
 * @param label The string to set as the function's label; passing `nullptr` clears the label.
 */
_MTL_INLINE void MTL::Function::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/ **
 * @brief Retrieves the function's stage input attributes.
 *
 * @return NS::Array* An array of `MTL::VertexAttribute` objects describing the function's stage input attributes, or `nullptr` if there are no stage input attributes.
 */
_MTL_INLINE NS::Array* MTL::Function::stageInputAttributes() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(stageInputAttributes));
}

/**
 * @brief Retrieves the vertex attribute descriptors associated with this function.
 *
 * @return NS::Array* An array of MTL::VertexAttribute objects describing the function's vertex attributes; may be empty if the function has no vertex attributes.
 */
_MTL_INLINE NS::Array* MTL::Function::vertexAttributes() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(vertexAttributes));
}

/**
 * @brief Allocate a new CompileOptions instance.
 *
 * @return CompileOptions* A newly allocated CompileOptions instance.
 */
_MTL_INLINE MTL::CompileOptions* MTL::CompileOptions::alloc()
{
    return NS::Object::alloc<MTL::CompileOptions>(_MTL_PRIVATE_CLS(MTLCompileOptions));
}

/**
 * @brief Indicates whether referencing undefined symbols is allowed during compilation.
 *
 * @return `true` if referencing undefined symbols is allowed during compilation, `false` otherwise.
 */
_MTL_INLINE bool MTL::CompileOptions::allowReferencingUndefinedSymbols() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(allowReferencingUndefinedSymbols));
}

/**
 * @brief Returns the symbol visibility setting used when compiling a library.
 *
 * @return MTL::CompileSymbolVisibility The visibility policy that will be applied to symbols during compilation.
 */
_MTL_INLINE MTL::CompileSymbolVisibility MTL::CompileOptions::compileSymbolVisibility() const
{
    return Object::sendMessage<MTL::CompileSymbolVisibility>(this, _MTL_PRIVATE_SEL(compileSymbolVisibility));
}

/**
 * @brief Indicates whether compiler logging is enabled for these compile options.
 *
 * @return `true` if logging is enabled during library compilation, `false` otherwise.
 */
_MTL_INLINE bool MTL::CompileOptions::enableLogging() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(enableLogging));
}

/**
 * @brief Indicates whether fast-math optimizations are enabled for these compile options.
 *
 * @return `true` if fast-math optimizations are enabled, `false` otherwise.
 */
_MTL_INLINE bool MTL::CompileOptions::fastMathEnabled() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(fastMathEnabled));
}

/**
 * @brief Initializes a newly allocated CompileOptions instance.
 *
 * Initializes the object and returns the initialized CompileOptions pointer.
 *
 * @return MTL::CompileOptions* Pointer to the initialized CompileOptions instance.
 */
_MTL_INLINE MTL::CompileOptions* MTL::CompileOptions::init()
{
    return NS::Object::init<MTL::CompileOptions>();
}

/**
 * @brief The install name that will be embedded in or used for a compiled library.
 *
 * @return NS::String* The install name string, or `nullptr` if no install name is set.
 */
_MTL_INLINE NS::String* MTL::CompileOptions::installName() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(installName));
}

/**
 * @brief Query the shading language version configured for these compile options.
 *
 * @return MTL::LanguageVersion The LanguageVersion used to interpret and compile shader source.
 */
_MTL_INLINE MTL::LanguageVersion MTL::CompileOptions::languageVersion() const
{
    return Object::sendMessage<MTL::LanguageVersion>(this, _MTL_PRIVATE_SEL(languageVersion));
}

/**
 * @brief Get the list of libraries to link against during compilation.
 *
 * The array contains references to MTL::Library objects that will be linked
 * when the compile options are used.
 *
 * @return NS::Array* An array of `MTL::Library*` references; may be empty or null.
 */
_MTL_INLINE NS::Array* MTL::CompileOptions::libraries() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(libraries));
}

/**
 * @brief Indicates the target type used when compiling the library.
 *
 * @return LibraryType The compilation target: `LibraryType::Executable` for an executable library or `LibraryType::Dynamic` for a dynamic library.
 */
_MTL_INLINE MTL::LibraryType MTL::CompileOptions::libraryType() const
{
    return Object::sendMessage<MTL::LibraryType>(this, _MTL_PRIVATE_SEL(libraryType));
}

/**
 * @brief Retrieves the floating-point function behavior selection used during compilation.
 *
 * @return MTL::MathFloatingPointFunctions Enum value indicating which floating-point function behavior is selected (e.g., `Fast` or `Precise`).
 */
_MTL_INLINE MTL::MathFloatingPointFunctions MTL::CompileOptions::mathFloatingPointFunctions() const
{
    return Object::sendMessage<MTL::MathFloatingPointFunctions>(this, _MTL_PRIVATE_SEL(mathFloatingPointFunctions));
}

/**
 * @brief The math mode used for shader math operations.
 *
 * @return MTL::MathMode The current math mode governing operation safety and precision.
 */
_MTL_INLINE MTL::MathMode MTL::CompileOptions::mathMode() const
{
    return Object::sendMessage<MTL::MathMode>(this, _MTL_PRIVATE_SEL(mathMode));
}

/**
 * @brief Queries the maximum total number of threads allowed per threadgroup.
 *
 * @return NS::UInteger Maximum number of threads that can be launched in a single threadgroup.
 */
_MTL_INLINE NS::UInteger MTL::CompileOptions::maxTotalThreadsPerThreadgroup() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxTotalThreadsPerThreadgroup));
}

/**
 * @brief Gets the optimization level used for library compilation.
 *
 * @return The optimization level applied when compiling the library.
 */
_MTL_INLINE MTL::LibraryOptimizationLevel MTL::CompileOptions::optimizationLevel() const
{
    return Object::sendMessage<MTL::LibraryOptimizationLevel>(this, _MTL_PRIVATE_SEL(optimizationLevel));
}

/**
 * @brief Returns the preprocessor macros configured for this compile options object.
 *
 * The dictionary maps preprocessor macro names to their corresponding values used during library compilation.
 *
 * @return NS::Dictionary* A dictionary of macro name -> value entries (empty if no macros are set).
 */
_MTL_INLINE NS::Dictionary* MTL::CompileOptions::preprocessorMacros() const
{
    return Object::sendMessage<NS::Dictionary*>(this, _MTL_PRIVATE_SEL(preprocessorMacros));
}

/**
 * @brief Indicates whether invariance is preserved during compilation.
 *
 * @return `true` if invariance is preserved during compilation, `false` otherwise.
 */
_MTL_INLINE bool MTL::CompileOptions::preserveInvariance() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(preserveInvariance));
}

/**
 * @brief Retrieve the required number of threads per threadgroup for compiled kernels.
 *
 * @return MTL::Size The threadgroup dimensions (width, height, depth) required per threadgroup.
 */
_MTL_INLINE MTL::Size MTL::CompileOptions::requiredThreadsPerThreadgroup() const
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(requiredThreadsPerThreadgroup));
}

/**
 * @brief Configure whether the compiler permits references to undefined symbols.
 *
 * @param allowReferencingUndefinedSymbols If `true`, allow references to symbols that are not defined during compilation; if `false`, disallow such references.
 */
_MTL_INLINE void MTL::CompileOptions::setAllowReferencingUndefinedSymbols(bool allowReferencingUndefinedSymbols)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAllowReferencingUndefinedSymbols_), allowReferencingUndefinedSymbols);
}

/**
 * @brief Set the visibility used for symbols produced by compilation.
 *
 * Configures whether symbols emitted when building a library are exposed or hidden for this CompileOptions instance.
 *
 * @param compileSymbolVisibility Visibility to apply to compiled symbols.
 */
_MTL_INLINE void MTL::CompileOptions::setCompileSymbolVisibility(MTL::CompileSymbolVisibility compileSymbolVisibility)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCompileSymbolVisibility_), compileSymbolVisibility);
}

/**
 * @brief Enable or disable logging for library compilation.
 *
 * @param enableLogging `true` to enable logging during compilation, `false` to disable it.
 */
_MTL_INLINE void MTL::CompileOptions::setEnableLogging(bool enableLogging)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setEnableLogging_), enableLogging);
}

/**
 * @brief Enable or disable fast-math optimizations for library compilation.
 *
 * When enabled, the compiler may apply less strict floating-point optimizations to improve performance.
 *
 * @param fastMathEnabled `true` to enable fast-math optimizations, `false` to require stricter IEEE-compliant math.
 */
_MTL_INLINE void MTL::CompileOptions::setFastMathEnabled(bool fastMathEnabled)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFastMathEnabled_), fastMathEnabled);
}

/**
 * @brief Set the install name used when producing a compiled library.
 *
 * The install name is recorded in the compiled library and used by the dynamic
 * loader when resolving the library at runtime.
 *
 * @param installName The install name (typically a path or identifier) to embed in the library.
 */
_MTL_INLINE void MTL::CompileOptions::setInstallName(const NS::String* installName)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInstallName_), installName);
}

/**
 * @brief Set the shading language version used when compiling the library.
 *
 * @param languageVersion The LanguageVersion to apply to subsequent compilations.
 */
_MTL_INLINE void MTL::CompileOptions::setLanguageVersion(MTL::LanguageVersion languageVersion)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLanguageVersion_), languageVersion);
}

/**
 * @brief Set the libraries to be linked into the compiled library.
 *
 * @param libraries An NSArray of library objects to link against during compilation.
 */
_MTL_INLINE void MTL::CompileOptions::setLibraries(const NS::Array* libraries)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLibraries_), libraries);
}

/**
 * @brief Set the target library type used when compiling the library.
 *
 * @param libraryType The LibraryType value specifying the kind of library to produce (e.g., executable or dynamic).
 */
_MTL_INLINE void MTL::CompileOptions::setLibraryType(MTL::LibraryType libraryType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLibraryType_), libraryType);
}

/**
 * @brief Set the floating-point function behavior for shader compilation.
 *
 * Controls how floating-point math functions are handled by the compiler (for example selecting fast approximations or precise implementations).
 *
 * @param mathFloatingPointFunctions The MathFloatingPointFunctions mode to apply.
 */
_MTL_INLINE void MTL::CompileOptions::setMathFloatingPointFunctions(MTL::MathFloatingPointFunctions mathFloatingPointFunctions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMathFloatingPointFunctions_), mathFloatingPointFunctions);
}

/**
 * @brief Sets the math mode that controls safety and precision of math operations.
 *
 * @param mathMode The desired MathMode determining how the compiler and runtime treat floating-point
 *                 math (e.g., safe, relaxed, or fast).
 */
_MTL_INLINE void MTL::CompileOptions::setMathMode(MTL::MathMode mathMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMathMode_), mathMode);
}

/**
 * @brief Sets the maximum total number of threads allowed per threadgroup for shader compilation.
 *
 * This value constrains the combined X×Y×Z thread count that may be used when allocating threadgroups.
 *
 * @param maxTotalThreadsPerThreadgroup Maximum total threads per threadgroup (X × Y × Z).
 */
_MTL_INLINE void MTL::CompileOptions::setMaxTotalThreadsPerThreadgroup(NS::UInteger maxTotalThreadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxTotalThreadsPerThreadgroup_), maxTotalThreadsPerThreadgroup);
}

/**
 * @brief Set the optimization level to use when compiling the library.
 *
 * @param optimizationLevel The desired optimization strategy for the compiled library (e.g., `LibraryOptimizationLevel::Default` or `LibraryOptimizationLevel::Size`).
 */
_MTL_INLINE void MTL::CompileOptions::setOptimizationLevel(MTL::LibraryOptimizationLevel optimizationLevel)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOptimizationLevel_), optimizationLevel);
}

/**
 * @brief Set the preprocessor macros to apply when compiling a library.
 *
 * @param preprocessorMacros Dictionary mapping macro names to replacement values used by the preprocessor (commonly NSString keys to NSString/NSNumber values).
 */
_MTL_INLINE void MTL::CompileOptions::setPreprocessorMacros(const NS::Dictionary* preprocessorMacros)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPreprocessorMacros_), preprocessorMacros);
}

/**
 * @brief Configure whether the compiler must preserve floating-point invariance.
 *
 * When set to `true`, the compiler will avoid optimizations that can change the
 * exact floating-point results (preserving IEEE/algorithmic invariants). When
 * `false`, the compiler may perform optimizations that can reorder or alter
 * floating-point operations for performance.
 *
 * @param preserveInvariance `true` to preserve floating-point invariance, `false` to allow optimizations that may change results.
 */
_MTL_INLINE void MTL::CompileOptions::setPreserveInvariance(bool preserveInvariance)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPreserveInvariance_), preserveInvariance);
}

/**
 * @brief Set the required number of threads per threadgroup for compiled compute functions.
 *
 * @param requiredThreadsPerThreadgroup Size specifying the required threads per threadgroup (width, height, depth).
 */
_MTL_INLINE void MTL::CompileOptions::setRequiredThreadsPerThreadgroup(MTL::Size requiredThreadsPerThreadgroup)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRequiredThreadsPerThreadgroup_), requiredThreadsPerThreadgroup);
}

/**
 * @brief Allocate a new FunctionReflection object.
 *
 * @return MTL::FunctionReflection* A newly allocated FunctionReflection instance; call `init()` on the returned object before use.
 */
_MTL_INLINE MTL::FunctionReflection* MTL::FunctionReflection::alloc()
{
    return NS::Object::alloc<MTL::FunctionReflection>(_MTL_PRIVATE_CLS(MTLFunctionReflection));
}

/**
 * @brief Retrieves the collection of binding descriptors for the function.
 *
 * @return NS::Array* An array of binding descriptors (arguments/bindings) describing the function's resource and argument bindings.
 */
_MTL_INLINE NS::Array* MTL::FunctionReflection::bindings() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(bindings));
}

/**
 * @brief Initializes a FunctionReflection instance.
 *
 * @return MTL::FunctionReflection* Pointer to the initialized FunctionReflection object.
 */
_MTL_INLINE MTL::FunctionReflection* MTL::FunctionReflection::init()
{
    return NS::Object::init<MTL::FunctionReflection>();
}

/**
 * @brief Retrieves the device associated with this library.
 *
 * @return MTL::Device* The MTL device that created or owns the library, or `nullptr` if unavailable.
 */
_MTL_INLINE MTL::Device* MTL::Library::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Retrieve the names of all shader functions contained in the library.
 *
 * @return NS::Array* Array of `NS::String*` objects representing the function names in this library.
 */
_MTL_INLINE NS::Array* MTL::Library::functionNames() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(functionNames));
}

/**
 * @brief Retrieves the library's install name.
 *
 * @return NS::String* The install name of the library.
 */
_MTL_INLINE NS::String* MTL::Library::installName() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(installName));
}

/**
 * @brief Returns the user-facing label assigned to the library.
 *
 * @return NS::String* The library's label string, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::Library::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Create a shader Function object from this library by its name.
 *
 * @param functionName The name of the function to retrieve from the library.
 * @return MTL::Function* Pointer to the Function with the given name, or `nullptr` if the function does not exist in the library.
 */
_MTL_INLINE MTL::Function* MTL::Library::newFunction(const NS::String* functionName)
{
    return Object::sendMessage<MTL::Function*>(this, _MTL_PRIVATE_SEL(newFunctionWithName_), functionName);
}

/**
 * @brief Create a Function from the library with optional specialization constants.
 *
 * Creates a new Function object identified by `name`, applying the provided
 * `constantValues` to specialize function constants for compilation or lookup.
 *
 * @param name The name of the function to create.
 * @param constantValues FunctionConstantValues used to specialize function constants; may be `nullptr` to use defaults.
 * @param error If non-null and creation fails, set to an NSError describing the failure; may be `nullptr`.
 * @return MTL::Function* The created Function instance, or `nullptr` if creation failed.
 */
_MTL_INLINE MTL::Function* MTL::Library::newFunction(const NS::String* name, const MTL::FunctionConstantValues* constantValues, NS::Error** error)
{
    return Object::sendMessage<MTL::Function*>(this, _MTL_PRIVATE_SEL(newFunctionWithName_constantValues_error_), name, constantValues, error);
}

/**
 * Creates a Function from this Library using the provided function constant values and delivers the result via the completion handler.
 *
 * @param name The name of the function to create.
 * @param constantValues FunctionConstantValues used to specialize the function's constants.
 * @param completionHandler Block invoked when creation completes; receives the created `MTL::Function*` (or `nullptr` on failure) and an `NS::Error*` describing any error.
 */
_MTL_INLINE void MTL::Library::newFunction(const NS::String* name, const MTL::FunctionConstantValues* constantValues, void (^completionHandler)(MTL::Function*, NS::Error*))
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(newFunctionWithName_constantValues_completionHandler_), name, constantValues, completionHandler);
}

/**
 * @brief Creates a Function from the given descriptor and invokes the completion handler with the result.
 *
 * @param descriptor Descriptor that specifies the function to create.
 * @param completionHandler Block invoked when creation finishes. On success the block receives the newly created `MTL::Function*` and a null `NS::Error*`; on failure the function pointer is null and the error describes the failure.
 */
_MTL_INLINE void MTL::Library::newFunction(const MTL::FunctionDescriptor* descriptor, void (^completionHandler)(MTL::Function*, NS::Error*))
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(newFunctionWithDescriptor_completionHandler_), descriptor, completionHandler);
}

/**
 * @brief Create a Function from a FunctionDescriptor within this library.
 *
 * @param descriptor Descriptor describing the function to create.
 * @param error If non-null and creation fails, set to an NS::Error describing the failure.
 * @return MTL::Function* Pointer to the newly created Function, or `nullptr` if creation failed.
 */
_MTL_INLINE MTL::Function* MTL::Library::newFunction(const MTL::FunctionDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<MTL::Function*>(this, _MTL_PRIVATE_SEL(newFunctionWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Asynchronously creates a Function with the given name and constant values, invoking the handler when finished.
 *
 * If creation succeeds the handler is called with the created `MTL::Function*`; on failure the handler is called with `nullptr` and an `NS::Error*` describing the failure.
 *
 * @param pFunctionName Name of the function to create.
 * @param pConstantValues Optional function constant values to specialize the function; may be `nullptr`.
 * @param completionHandler Called when creation completes with the resulting `MTL::Function*` or an `NS::Error*` on failure.
 */
_MTL_INLINE void MTL::Library::newFunction(const NS::String* pFunctionName, const MTL::FunctionConstantValues* pConstantValues, const MTL::FunctionCompletionHandlerFunction& completionHandler)
{
    __block MTL::FunctionCompletionHandlerFunction blockCompletionHandler = completionHandler;
    newFunction(pFunctionName, pConstantValues, ^(MTL::Function* pFunction, NS::Error* pError) { blockCompletionHandler(pFunction, pError); });
}

/**
 * @brief Asynchronously creates a new Function from a FunctionDescriptor.
 *
 * The provided completion handler is invoked once creation finishes. On success
 * the handler receives a non-null `MTL::Function*` and a null `NS::Error*`; on
 * failure the function pointer will be null and `NS::Error*` describes the error.
 *
 * @param pDescriptor Descriptor that describes the function to create.
 * @param completionHandler Callback invoked with the created `MTL::Function*` and an `NS::Error*` describing any failure.
 */
_MTL_INLINE void MTL::Library::newFunction(const MTL::FunctionDescriptor* pDescriptor, const MTL::FunctionCompletionHandlerFunction& completionHandler)
{
    __block MTL::FunctionCompletionHandlerFunction blockCompletionHandler = completionHandler;
    newFunction(pDescriptor, ^(MTL::Function* pFunction, NS::Error* pError) { blockCompletionHandler(pFunction, pError); });
}

/**
 * @brief Requests creation of an intersection function from the given descriptor and reports the result via callback.
 *
 * The provided completion handler is invoked when function creation finishes. On success the handler receives the created `MTL::Function*` and a null `NS::Error*`; on failure the function pointer is null and the error describes the failure.
 *
 * @param descriptor Descriptor that describes the intersection function to create.
 * @param completionHandler Block called with the created `MTL::Function*` and an `NS::Error*` describing any error.
 */
_MTL_INLINE void MTL::Library::newIntersectionFunction(const MTL::IntersectionFunctionDescriptor* descriptor, void (^completionHandler)(MTL::Function*, NS::Error*))
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(newIntersectionFunctionWithDescriptor_completionHandler_), descriptor, completionHandler);
}

/**
 * @brief Creates a new intersection function from the given descriptor.
 *
 * @param descriptor Descriptor describing the intersection function to create.
 * @param error On failure, populated with an NSError describing the error; pass `nullptr` to ignore.
 * @return MTL::Function* The newly created intersection function, or `nullptr` if creation failed.
 */
_MTL_INLINE MTL::Function* MTL::Library::newIntersectionFunction(const MTL::IntersectionFunctionDescriptor* descriptor, NS::Error** error)
{
    return Object::sendMessage<MTL::Function*>(this, _MTL_PRIVATE_SEL(newIntersectionFunctionWithDescriptor_error_), descriptor, error);
}

/**
 * @brief Creates an intersection function from the provided descriptor and invokes the completion handler when creation finishes.
 *
 * @param pDescriptor Descriptor describing the intersection function to create.
 * @param completionHandler Callback invoked with the created `MTL::Function*` on success or an `NS::Error*` on failure.
 */
_MTL_INLINE void MTL::Library::newIntersectionFunction(const MTL::IntersectionFunctionDescriptor* pDescriptor, const MTL::FunctionCompletionHandlerFunction& completionHandler)
{
    __block MTL::FunctionCompletionHandlerFunction blockCompletionHandler = completionHandler;
    newIntersectionFunction(pDescriptor, ^(MTL::Function* pFunction, NS::Error* pError) { blockCompletionHandler(pFunction, pError); });
}

/**
 * @brief Obtain reflection data for a named function in the library.
 *
 * @param functionName Name of the function to reflect.
 * @return MTL::FunctionReflection* Reflection information for the specified function; `nullptr` if the function is not present in the library.
 */
_MTL_INLINE MTL::FunctionReflection* MTL::Library::reflectionForFunction(const NS::String* functionName)
{
    return Object::sendMessage<MTL::FunctionReflection*>(this, _MTL_PRIVATE_SEL(reflectionForFunctionWithName_), functionName);
}

/**
 * @brief Set the user-visible label for the library.
 *
 * The label is a human-readable identifier used for debugging, profiling, and tooling.
 *
 * @param label The string to assign as the library's label.
 */
_MTL_INLINE void MTL::Library::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Query the library's type to determine whether it is executable or dynamic.
 *
 * @return MTL::LibraryType Value indicating the library kind: `LibraryType::Executable` for executable libraries or `LibraryType::Dynamic` for dynamic libraries.
 */
_MTL_INLINE MTL::LibraryType MTL::Library::type() const
{
    return Object::sendMessage<MTL::LibraryType>(this, _MTL_PRIVATE_SEL(type));
}