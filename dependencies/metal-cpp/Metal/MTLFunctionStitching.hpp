//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLFunctionStitching.hpp
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
class FunctionStitchingAttributeAlwaysInline;
class FunctionStitchingFunctionNode;
class FunctionStitchingGraph;
class FunctionStitchingInputNode;
class StitchedLibraryDescriptor;

/**
 * @brief Options controlling stitched library behavior.
 *
 * Bitmask values used to configure stitched library creation and handling.
 */

/**
 * @brief Represents a generic attribute for function stitching graphs.
 */

/**
 * @brief Attribute indicating a function should always be inlined.
 *
 * Use when a function in a stitching graph must be marked to prefer inline expansion.
 */

/**
 * @brief Allocate a new `FunctionStitchingAttributeAlwaysInline` instance.
 *
 * @return FunctionStitchingAttributeAlwaysInline* Newly allocated attribute instance.
 */

/**
 * @brief Initialize a `FunctionStitchingAttributeAlwaysInline` instance.
 *
 * @return FunctionStitchingAttributeAlwaysInline* Initialized instance or `nullptr` on failure.
 */

/**
 * @brief Base type for nodes used in function stitching graphs.
 */

/**
 * @brief Represents an input node in a function stitching graph.
 */

/**
 * @brief Allocate a new `FunctionStitchingInputNode` instance.
 *
 * @return FunctionStitchingInputNode* Newly allocated input node.
 */

/**
 * @brief Retrieve the argument index associated with this input node.
 *
 * @return NS::UInteger The zero-based argument index for this input node.
 */

/**
 * @brief Initialize a default `FunctionStitchingInputNode`.
 *
 * @return FunctionStitchingInputNode* Initialized instance or `nullptr` on failure.
 */

/**
 * @brief Initialize a `FunctionStitchingInputNode` with a specific argument index.
 *
 * @param argument The zero-based argument index to associate with the node.
 * @return FunctionStitchingInputNode* Initialized instance or `nullptr` on failure.
 */

/**
 * @brief Set the argument index for this input node.
 *
 * @param argumentIndex The zero-based argument index to assign to the node.
 */

/**
 * @brief Represents a function node within a stitching graph.
 */

/**
 * @brief Allocate a new `FunctionStitchingFunctionNode` instance.
 *
 * @return FunctionStitchingFunctionNode* Newly allocated function node.
 */

/**
 * @brief Retrieve the node's argument list.
 *
 * @return NS::Array* An array of argument descriptors for the function node.
 */

/**
 * @brief Retrieve the node's control dependencies.
 *
 * @return NS::Array* An array describing control-dependent nodes for this function node.
 */

/**
 * @brief Initialize a default `FunctionStitchingFunctionNode`.
 *
 * @return FunctionStitchingFunctionNode* Initialized instance or `nullptr` on failure.
 */

/**
 * @brief Initialize a `FunctionStitchingFunctionNode` with name, arguments, and control dependencies.
 *
 * @param name The function node's name.
 * @param arguments An array of argument descriptors.
 * @param controlDependencies An array of control dependency descriptors.
 * @return FunctionStitchingFunctionNode* Initialized instance or `nullptr` on failure.
 */

/**
 * @brief Retrieve the function node's name.
 *
 * @return NS::String* The name associated with the function node.
 */

/**
 * @brief Replace the node's arguments.
 *
 * @param arguments An array of argument descriptors to assign to the node.
 */

/**
 * @brief Replace the node's control dependencies.
 *
 * @param controlDependencies An array of control dependency descriptors to assign to the node.
 */

/**
 * @brief Set the function node's name.
 *
 * @param name The name to assign to the function node.
 */

/**
 * @brief Represents an entire function stitching graph.
 */

/**
 * @brief Allocate a new `FunctionStitchingGraph` instance.
 *
 * @return FunctionStitchingGraph* Newly allocated stitching graph.
 */

/**
 * @brief Retrieve the graph's attributes.
 *
 * @return NS::Array* An array of attributes associated with the graph.
 */

/**
 * @brief Retrieve the name of the stitched function represented by this graph.
 *
 * @return NS::String* The stitched function's name.
 */

/**
 * @brief Initialize a default `FunctionStitchingGraph`.
 *
 * @return FunctionStitchingGraph* Initialized instance or `nullptr` on failure.
 */

/**
 * @brief Initialize a `FunctionStitchingGraph` with function name, nodes, output node, and attributes.
 *
 * @param functionName The name of the stitched function.
 * @param nodes An array of nodes that comprise the graph.
 * @param outputNode The function node designated as the graph's output.
 * @param attributes An array of attributes applied to the graph.
 * @return FunctionStitchingGraph* Initialized instance or `nullptr` on failure.
 */

/**
 * @brief Retrieve the graph's nodes.
 *
 * @return NS::Array* An array containing the graph's nodes.
 */

/**
 * @brief Retrieve the graph's output node.
 *
 * @return FunctionStitchingFunctionNode* The node designated as the graph's output, or `nullptr` if none.
 */

/**
 * @brief Replace the graph's attributes.
 *
 * @param attributes An array of attributes to assign to the graph.
 */

/**
 * @brief Set the stitched function name for the graph.
 *
 * @param functionName The name to assign to the graph.
 */

/**
 * @brief Replace the graph's nodes.
 *
 * @param nodes An array of nodes to assign to the graph.
 */

/**
 * @brief Set the graph's output node.
 *
 * @param outputNode The function node to designate as the graph's output.
 */

/**
 * @brief Describes a stitched library configuration including sources, graphs, and options.
 */

/**
 * @brief Allocate a new `StitchedLibraryDescriptor` instance.
 *
 * @return StitchedLibraryDescriptor* Newly allocated descriptor.
 */

/**
 * @brief Retrieve the descriptor's binary archives.
 *
 * @return NS::Array* An array of binary archive descriptors.
 */

/**
 * @brief Retrieve the function graphs described by the descriptor.
 *
 * @return NS::Array* An array of `FunctionStitchingGraph` instances.
 */

/**
 * @brief Retrieve the list of functions included in the stitched library.
 *
 * @return NS::Array* An array of function descriptors or names included in the library.
 */

/**
 * @brief Initialize a default `StitchedLibraryDescriptor`.
 *
 * @return StitchedLibraryDescriptor* Initialized instance or `nullptr` on failure.
 */

/**
 * @brief Retrieve the descriptor's configuration options.
 *
 * @return StitchedLibraryOptions The bitmask of options currently set on the descriptor.
 */

/**
 * @brief Set the descriptor's binary archives.
 *
 * @param binaryArchives An array of binary archive descriptors to associate with the descriptor.
 */

/**
 * @brief Set the function graphs for the stitched library.
 *
 * @param functionGraphs An array of `FunctionStitchingGraph` instances to include in the descriptor.
 */

/**
 * @brief Set the functions included in the stitched library.
 *
 * @param functions An array of function descriptors or names to include.
 */

/**
 * @brief Set the stitched library options.
 *
 * @param options Bitmask of `StitchedLibraryOptions` to apply to the descriptor.
 */
_MTL_OPTIONS(NS::UInteger, StitchedLibraryOptions) {
    StitchedLibraryOptionNone = 0,
    StitchedLibraryOptionFailOnBinaryArchiveMiss = 1,
    StitchedLibraryOptionStoreLibraryInMetalPipelinesScript = 1 << 1,
};

class FunctionStitchingAttribute : public NS::Referencing<FunctionStitchingAttribute>
{
};
class FunctionStitchingAttributeAlwaysInline : public NS::Referencing<FunctionStitchingAttributeAlwaysInline, FunctionStitchingAttribute>
{
public:
    static FunctionStitchingAttributeAlwaysInline* alloc();

    FunctionStitchingAttributeAlwaysInline*        init();
};
class FunctionStitchingNode : public NS::Copying<FunctionStitchingNode>
{
};
class FunctionStitchingInputNode : public NS::Referencing<FunctionStitchingInputNode, FunctionStitchingNode>
{
public:
    static FunctionStitchingInputNode* alloc();

    NS::UInteger                       argumentIndex() const;

    FunctionStitchingInputNode*        init();
    FunctionStitchingInputNode*        init(NS::UInteger argument);

    void                               setArgumentIndex(NS::UInteger argumentIndex);
};
class FunctionStitchingFunctionNode : public NS::Referencing<FunctionStitchingFunctionNode, FunctionStitchingNode>
{
public:
    static FunctionStitchingFunctionNode* alloc();

    NS::Array*                            arguments() const;

    NS::Array*                            controlDependencies() const;

    FunctionStitchingFunctionNode*        init();
    FunctionStitchingFunctionNode*        init(const NS::String* name, const NS::Array* arguments, const NS::Array* controlDependencies);

    NS::String*                           name() const;

    void                                  setArguments(const NS::Array* arguments);

    void                                  setControlDependencies(const NS::Array* controlDependencies);

    void                                  setName(const NS::String* name);
};
class FunctionStitchingGraph : public NS::Copying<FunctionStitchingGraph>
{
public:
    static FunctionStitchingGraph* alloc();

    NS::Array*                     attributes() const;

    NS::String*                    functionName() const;

    FunctionStitchingGraph*        init();
    FunctionStitchingGraph*        init(const NS::String* functionName, const NS::Array* nodes, const MTL::FunctionStitchingFunctionNode* outputNode, const NS::Array* attributes);

    NS::Array*                     nodes() const;

    FunctionStitchingFunctionNode* outputNode() const;

    void                           setAttributes(const NS::Array* attributes);

    void                           setFunctionName(const NS::String* functionName);

    void                           setNodes(const NS::Array* nodes);

    void                           setOutputNode(const MTL::FunctionStitchingFunctionNode* outputNode);
};
class StitchedLibraryDescriptor : public NS::Copying<StitchedLibraryDescriptor>
{
public:
    static StitchedLibraryDescriptor* alloc();

    NS::Array*                        binaryArchives() const;

    NS::Array*                        functionGraphs() const;

    NS::Array*                        functions() const;

    StitchedLibraryDescriptor*        init();

    StitchedLibraryOptions            options() const;

    void                              setBinaryArchives(const NS::Array* binaryArchives);

    void                              setFunctionGraphs(const NS::Array* functionGraphs);

    void                              setFunctions(const NS::Array* functions);

    void                              setOptions(MTL::StitchedLibraryOptions options);
};

}
/**
 * @brief Allocate a new FunctionStitchingAttributeAlwaysInline instance.
 *
 * @return MTL::FunctionStitchingAttributeAlwaysInline* A newly allocated instance; call `init()` before using.
 */
_MTL_INLINE MTL::FunctionStitchingAttributeAlwaysInline* MTL::FunctionStitchingAttributeAlwaysInline::alloc()
{
    return NS::Object::alloc<MTL::FunctionStitchingAttributeAlwaysInline>(_MTL_PRIVATE_CLS(MTLFunctionStitchingAttributeAlwaysInline));
}

/**
 * @brief Initialize an attribute that marks a stitched function as always inline.
 *
 * @return MTL::FunctionStitchingAttributeAlwaysInline* Initialized instance, or `nullptr` on failure.
 */
_MTL_INLINE MTL::FunctionStitchingAttributeAlwaysInline* MTL::FunctionStitchingAttributeAlwaysInline::init()
{
    return NS::Object::init<MTL::FunctionStitchingAttributeAlwaysInline>();
}

/**
 * @brief Allocate a new FunctionStitchingInputNode instance.
 *
 * @return FunctionStitchingInputNode* A newly allocated `FunctionStitchingInputNode` instance.
 */
_MTL_INLINE MTL::FunctionStitchingInputNode* MTL::FunctionStitchingInputNode::alloc()
{
    return NS::Object::alloc<MTL::FunctionStitchingInputNode>(_MTL_PRIVATE_CLS(MTLFunctionStitchingInputNode));
}

/**
 * @brief Retrieves the argument position associated with this input node.
 *
 * @return NS::UInteger The zero-based index of the function argument represented by this node.
 */
_MTL_INLINE NS::UInteger MTL::FunctionStitchingInputNode::argumentIndex() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(argumentIndex));
}

/**
 * @brief Initialize a FunctionStitchingInputNode with default state.
 *
 * @return FunctionStitchingInputNode* Initialized instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::FunctionStitchingInputNode* MTL::FunctionStitchingInputNode::init()
{
    return NS::Object::init<MTL::FunctionStitchingInputNode>();
}

/**
 * @brief Initialize the input node with a specific argument index.
 *
 * @param argument The zero-based argument index that this input node represents.
 * @return MTL::FunctionStitchingInputNode* Pointer to the initialized input node, or `nullptr` on failure.
 */
_MTL_INLINE MTL::FunctionStitchingInputNode* MTL::FunctionStitchingInputNode::init(NS::UInteger argument)
{
    return Object::sendMessage<MTL::FunctionStitchingInputNode*>(this, _MTL_PRIVATE_SEL(initWithArgumentIndex_), argument);
}

/**
 * @brief Set the input node's argument index.
 *
 * Assigns which function argument position this input node represents.
 *
 * @param argumentIndex The zero-based index of the function argument.
 */
_MTL_INLINE void MTL::FunctionStitchingInputNode::setArgumentIndex(NS::UInteger argumentIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setArgumentIndex_), argumentIndex);
}

/**
 * @brief Allocate a new FunctionStitchingFunctionNode instance.
 *
 * @return FunctionStitchingFunctionNode* A newly allocated instance (uninitialized).
 */
_MTL_INLINE MTL::FunctionStitchingFunctionNode* MTL::FunctionStitchingFunctionNode::alloc()
{
    return NS::Object::alloc<MTL::FunctionStitchingFunctionNode>(_MTL_PRIVATE_CLS(MTLFunctionStitchingFunctionNode));
}

/**
 * @brief Retrieve the function node's list of arguments.
 *
 * @return NS::Array* An array of nodes representing the function's arguments.
 */
_MTL_INLINE NS::Array* MTL::FunctionStitchingFunctionNode::arguments() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(arguments));
}

/**
 * @brief Retrieve the node's control dependency nodes.
 *
 * @return NS::Array* An array of control dependency nodes; each element is a
 * FunctionStitchingFunctionNode* representing a node that must execute before this node.
 */
_MTL_INLINE NS::Array* MTL::FunctionStitchingFunctionNode::controlDependencies() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(controlDependencies));
}

/**
 * @brief Initializes a FunctionStitchingFunctionNode instance.
 *
 * @return FunctionStitchingFunctionNode* Pointer to the initialized instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::FunctionStitchingFunctionNode* MTL::FunctionStitchingFunctionNode::init()
{
    return NS::Object::init<MTL::FunctionStitchingFunctionNode>();
}

/**
 * @brief Initialize the function node with a name, its argument list, and control dependencies.
 *
 * @param name The function node's name.
 * @param arguments An array of argument descriptors for the function node.
 * @param controlDependencies An array of nodes that this function node depends on for control flow.
 * @return FunctionStitchingFunctionNode* The initialized function node instance, or `nullptr` on failure.
 */
_MTL_INLINE MTL::FunctionStitchingFunctionNode* MTL::FunctionStitchingFunctionNode::init(const NS::String* name, const NS::Array* arguments, const NS::Array* controlDependencies)
{
    return Object::sendMessage<MTL::FunctionStitchingFunctionNode*>(this, _MTL_PRIVATE_SEL(initWithName_arguments_controlDependencies_), name, arguments, controlDependencies);
}

/**
 * @brief Retrieves the function node's name.
 *
 * @return NS::String* The name of the function node, or `nullptr` if no name is set.
 */
_MTL_INLINE NS::String* MTL::FunctionStitchingFunctionNode::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Set the function node's arguments.
 *
 * @param arguments An NSArray containing the argument nodes for this function node.
 */
_MTL_INLINE void MTL::FunctionStitchingFunctionNode::setArguments(const NS::Array* arguments)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setArguments_), arguments);
}

/**
 * @brief Set the control dependency nodes for this function node.
 *
 * @param controlDependencies Array of nodes that this function node has control dependencies on.
 */
_MTL_INLINE void MTL::FunctionStitchingFunctionNode::setControlDependencies(const NS::Array* controlDependencies)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setControlDependencies_), controlDependencies);
}

/**
 * @brief Set the function node's name.
 *
 * @param name The new name for the function node.
 */
_MTL_INLINE void MTL::FunctionStitchingFunctionNode::setName(const NS::String* name)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setName_), name);
}

/**
 * @brief Allocate a new FunctionStitchingGraph instance.
 *
 * @return MTL::FunctionStitchingGraph* Pointer to a newly allocated FunctionStitchingGraph instance.
 */
_MTL_INLINE MTL::FunctionStitchingGraph* MTL::FunctionStitchingGraph::alloc()
{
    return NS::Object::alloc<MTL::FunctionStitchingGraph>(_MTL_PRIVATE_CLS(MTLFunctionStitchingGraph));
}

/**
 * @brief Retrieves the attributes associated with this function stitching graph.
 *
 * @return NS::Array* An array of FunctionStitchingAttribute instances describing attributes applied to the graph.
 */
_MTL_INLINE NS::Array* MTL::FunctionStitchingGraph::attributes() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(attributes));
}

/**
 * @brief Function name associated with this stitching graph.
 *
 * @return NS::String* The function name, or nullptr if no name is set.
 */
_MTL_INLINE NS::String* MTL::FunctionStitchingGraph::functionName() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(functionName));
}

/**
 * @brief Initialize a FunctionStitchingGraph to its default state.
 *
 * @return FunctionStitchingGraph* Pointer to the initialized instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::FunctionStitchingGraph* MTL::FunctionStitchingGraph::init()
{
    return NS::Object::init<MTL::FunctionStitchingGraph>();
}

/**
 * @brief Initialize a FunctionStitchingGraph with a function name, nodes, an output node, and attributes.
 *
 * @param functionName Name of the stitched function represented by the graph.
 * @param nodes Array of nodes that form the graph.
 * @param outputNode The function node that serves as the graph's output.
 * @param attributes Array of graph-level attributes.
 * @return MTL::FunctionStitchingGraph* The initialized FunctionStitchingGraph instance.
 */
_MTL_INLINE MTL::FunctionStitchingGraph* MTL::FunctionStitchingGraph::init(const NS::String* functionName, const NS::Array* nodes, const MTL::FunctionStitchingFunctionNode* outputNode, const NS::Array* attributes)
{
    return Object::sendMessage<MTL::FunctionStitchingGraph*>(this, _MTL_PRIVATE_SEL(initWithFunctionName_nodes_outputNode_attributes_), functionName, nodes, outputNode, attributes);
}

/**
 * @brief Retrieves the nodes that make up the function stitching graph.
 *
 * @return NS::Array* An array of `MTL::FunctionStitchingFunctionNode*` objects representing the graph's nodes.
 */
_MTL_INLINE NS::Array* MTL::FunctionStitchingGraph::nodes() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(nodes));
}

/**
 * @brief Retrieve the graph's designated output node.
 *
 * @return FunctionStitchingFunctionNode* Pointer to the graph's output node, or `nullptr` if no output node is set.
 */
_MTL_INLINE MTL::FunctionStitchingFunctionNode* MTL::FunctionStitchingGraph::outputNode() const
{
    return Object::sendMessage<MTL::FunctionStitchingFunctionNode*>(this, _MTL_PRIVATE_SEL(outputNode));
}

/**
 * @brief Sets the function stitching graph's attributes.
 *
 * Replaces the graph's current attributes with the provided array of attribute objects.
 *
 * @param attributes Array of FunctionStitchingAttribute instances describing graph-level attributes; may be nullptr to clear existing attributes.
 */
_MTL_INLINE void MTL::FunctionStitchingGraph::setAttributes(const NS::Array* attributes)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAttributes_), attributes);
}

/**
 * @brief Set the name of the function represented by this stitching graph.
 *
 * @param functionName The new function name for the graph.
 */
_MTL_INLINE void MTL::FunctionStitchingGraph::setFunctionName(const NS::String* functionName)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFunctionName_), functionName);
}

/**
 * @brief Set the nodes contained in the function stitching graph.
 *
 * @param nodes Array of node objects to assign as the graph's nodes (expected to contain
 *              FunctionStitchingNode / subclasses).
 */
_MTL_INLINE void MTL::FunctionStitchingGraph::setNodes(const NS::Array* nodes)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setNodes_), nodes);
}

/**
 * @brief Set the graph's output node.
 *
 * @param outputNode The function node to use as the graph's output; pass `nullptr` to clear the output node.
 */
_MTL_INLINE void MTL::FunctionStitchingGraph::setOutputNode(const MTL::FunctionStitchingFunctionNode* outputNode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOutputNode_), outputNode);
}

/**
 * @brief Allocate a new StitchedLibraryDescriptor instance.
 *
 * @return StitchedLibraryDescriptor* A pointer to an allocated descriptor; call `init()` on the result before use.
 */
_MTL_INLINE MTL::StitchedLibraryDescriptor* MTL::StitchedLibraryDescriptor::alloc()
{
    return NS::Object::alloc<MTL::StitchedLibraryDescriptor>(_MTL_PRIVATE_CLS(MTLStitchedLibraryDescriptor));
}

/**
 * @brief Retrieve the binary archives associated with this descriptor.
 *
 * @return NS::Array* The array of binary archives associated with this descriptor.
 */
_MTL_INLINE NS::Array* MTL::StitchedLibraryDescriptor::binaryArchives() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(binaryArchives));
}

/**
 * @brief Retrieves the array of function stitching graphs associated with this descriptor.
 *
 * @return NS::Array* An array of MTL::FunctionStitchingGraph objects describing each function graph.
 */
_MTL_INLINE NS::Array* MTL::StitchedLibraryDescriptor::functionGraphs() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(functionGraphs));
}

/**
 * @brief Retrieves the functions described by this stitched library descriptor.
 *
 * @return NS::Array* An array containing the function descriptors for the stitched library.
 */
_MTL_INLINE NS::Array* MTL::StitchedLibraryDescriptor::functions() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(functions));
}

/**
 * @brief Initializes a StitchedLibraryDescriptor with default empty configuration.
 *
 * @return StitchedLibraryDescriptor* Pointer to the initialized descriptor, or nullptr if initialization failed.
 */
_MTL_INLINE MTL::StitchedLibraryDescriptor* MTL::StitchedLibraryDescriptor::init()
{
    return NS::Object::init<MTL::StitchedLibraryDescriptor>();
}

/**
 * @brief Retrieve the stitched library options bitmask for this descriptor.
 *
 * @return MTL::StitchedLibraryOptions Bitmask containing the descriptor's options.
 *         Individual flags may include `StitchedLibraryOptionFailOnBinaryArchiveMiss`
 *         and `StitchedLibraryOptionStoreLibraryInMetalPipelinesScript`.
 */
_MTL_INLINE MTL::StitchedLibraryOptions MTL::StitchedLibraryDescriptor::options() const
{
    return Object::sendMessage<MTL::StitchedLibraryOptions>(this, _MTL_PRIVATE_SEL(options));
}

/**
 * @brief Set the collection of binary archives associated with this stitched library descriptor.
 *
 * @param binaryArchives An NSArray of binary archive objects to be included in the descriptor.
 */
_MTL_INLINE void MTL::StitchedLibraryDescriptor::setBinaryArchives(const NS::Array* binaryArchives)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBinaryArchives_), binaryArchives);
}

/**
 * @brief Set the function graphs for this stitched library descriptor.
 *
 * @param functionGraphs Array of `FunctionStitchingGraph` objects to assign as the descriptor's function graphs.
 */
_MTL_INLINE void MTL::StitchedLibraryDescriptor::setFunctionGraphs(const NS::Array* functionGraphs)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFunctionGraphs_), functionGraphs);
}

/**
 * @brief Set the functions that belong to this stitched library descriptor.
 *
 * @param functions Array of functions to include in the stitched library descriptor.
 */
_MTL_INLINE void MTL::StitchedLibraryDescriptor::setFunctions(const NS::Array* functions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setFunctions_), functions);
}

/**
 * @brief Configure runtime options for the stitched library descriptor.
 *
 * @param options Bitwise combination of MTL::StitchedLibraryOptions flags that control stitched-library behavior
 *                (for example: fail on missing binary archives or store the library in the Metal pipelines script).
 */
_MTL_INLINE void MTL::StitchedLibraryDescriptor::setOptions(MTL::StitchedLibraryOptions options)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOptions_), options);
}