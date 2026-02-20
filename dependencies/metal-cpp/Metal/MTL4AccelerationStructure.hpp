//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4AccelerationStructure.hpp
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
#include "MTLAccelerationStructure.hpp"
#include "MTLAccelerationStructureTypes.hpp"
#include "MTLArgument.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLStageInputOutputDescriptor.hpp"

namespace MTL4
{
class AccelerationStructureBoundingBoxGeometryDescriptor;
class AccelerationStructureCurveGeometryDescriptor;
class AccelerationStructureDescriptor;
class AccelerationStructureGeometryDescriptor;
class AccelerationStructureMotionBoundingBoxGeometryDescriptor;
class AccelerationStructureMotionCurveGeometryDescriptor;
class AccelerationStructureMotionTriangleGeometryDescriptor;
class AccelerationStructureTriangleGeometryDescriptor;
class IndirectInstanceAccelerationStructureDescriptor;
class InstanceAccelerationStructureDescriptor;
class PrimitiveAccelerationStructureDescriptor;

class AccelerationStructureDescriptor : public NS::Copying<AccelerationStructureDescriptor, MTL::AccelerationStructureDescriptor>
{
public:
    static AccelerationStructureDescriptor* alloc();

    AccelerationStructureDescriptor*        init();
};
class AccelerationStructureGeometryDescriptor : public NS::Copying<AccelerationStructureGeometryDescriptor>
{
public:
    static AccelerationStructureGeometryDescriptor* alloc();

    bool                                            allowDuplicateIntersectionFunctionInvocation() const;

    AccelerationStructureGeometryDescriptor*        init();

    NS::UInteger                                    intersectionFunctionTableOffset() const;

    NS::String*                                     label() const;

    bool                                            opaque() const;

    BufferRange                                     primitiveDataBuffer() const;

    NS::UInteger                                    primitiveDataElementSize() const;

    NS::UInteger                                    primitiveDataStride() const;

    void                                            setAllowDuplicateIntersectionFunctionInvocation(bool allowDuplicateIntersectionFunctionInvocation);

    void                                            setIntersectionFunctionTableOffset(NS::UInteger intersectionFunctionTableOffset);

    void                                            setLabel(const NS::String* label);

    void                                            setOpaque(bool opaque);

    void                                            setPrimitiveDataBuffer(const MTL4::BufferRange primitiveDataBuffer);

    void                                            setPrimitiveDataElementSize(NS::UInteger primitiveDataElementSize);

    void                                            setPrimitiveDataStride(NS::UInteger primitiveDataStride);
};
class PrimitiveAccelerationStructureDescriptor : public NS::Copying<PrimitiveAccelerationStructureDescriptor, AccelerationStructureDescriptor>
{
public:
    static PrimitiveAccelerationStructureDescriptor* alloc();

    NS::Array*                                       geometryDescriptors() const;

    PrimitiveAccelerationStructureDescriptor*        init();

    MTL::MotionBorderMode                            motionEndBorderMode() const;

    float                                            motionEndTime() const;

    NS::UInteger                                     motionKeyframeCount() const;

    MTL::MotionBorderMode                            motionStartBorderMode() const;

    float                                            motionStartTime() const;

    void                                             setGeometryDescriptors(const NS::Array* geometryDescriptors);

    void                                             setMotionEndBorderMode(MTL::MotionBorderMode motionEndBorderMode);

    void                                             setMotionEndTime(float motionEndTime);

    void                                             setMotionKeyframeCount(NS::UInteger motionKeyframeCount);

    void                                             setMotionStartBorderMode(MTL::MotionBorderMode motionStartBorderMode);

    void                                             setMotionStartTime(float motionStartTime);
};
class AccelerationStructureTriangleGeometryDescriptor : public NS::Copying<AccelerationStructureTriangleGeometryDescriptor, AccelerationStructureGeometryDescriptor>
{
public:
    static AccelerationStructureTriangleGeometryDescriptor* alloc();

    BufferRange                                             indexBuffer() const;

    MTL::IndexType                                          indexType() const;

    AccelerationStructureTriangleGeometryDescriptor*        init();

    void                                                    setIndexBuffer(const MTL4::BufferRange indexBuffer);

    void                                                    setIndexType(MTL::IndexType indexType);

    void                                                    setTransformationMatrixBuffer(const MTL4::BufferRange transformationMatrixBuffer);

    void                                                    setTransformationMatrixLayout(MTL::MatrixLayout transformationMatrixLayout);

    void                                                    setTriangleCount(NS::UInteger triangleCount);

    void                                                    setVertexBuffer(const MTL4::BufferRange vertexBuffer);

    void                                                    setVertexFormat(MTL::AttributeFormat vertexFormat);

    void                                                    setVertexStride(NS::UInteger vertexStride);

    BufferRange                                             transformationMatrixBuffer() const;

    MTL::MatrixLayout                                       transformationMatrixLayout() const;

    NS::UInteger                                            triangleCount() const;

    BufferRange                                             vertexBuffer() const;

    MTL::AttributeFormat                                    vertexFormat() const;

    NS::UInteger                                            vertexStride() const;
};
class AccelerationStructureBoundingBoxGeometryDescriptor : public NS::Copying<AccelerationStructureBoundingBoxGeometryDescriptor, AccelerationStructureGeometryDescriptor>
{
public:
    static AccelerationStructureBoundingBoxGeometryDescriptor* alloc();

    BufferRange                                                boundingBoxBuffer() const;

    NS::UInteger                                               boundingBoxCount() const;

    NS::UInteger                                               boundingBoxStride() const;

    AccelerationStructureBoundingBoxGeometryDescriptor*        init();

    void                                                       setBoundingBoxBuffer(const MTL4::BufferRange boundingBoxBuffer);

    void                                                       setBoundingBoxCount(NS::UInteger boundingBoxCount);

    void                                                       setBoundingBoxStride(NS::UInteger boundingBoxStride);
};
class AccelerationStructureMotionTriangleGeometryDescriptor : public NS::Copying<AccelerationStructureMotionTriangleGeometryDescriptor, AccelerationStructureGeometryDescriptor>
{
public:
    static AccelerationStructureMotionTriangleGeometryDescriptor* alloc();

    BufferRange                                                   indexBuffer() const;

    MTL::IndexType                                                indexType() const;

    AccelerationStructureMotionTriangleGeometryDescriptor*        init();

    void                                                          setIndexBuffer(const MTL4::BufferRange indexBuffer);

    void                                                          setIndexType(MTL::IndexType indexType);

    void                                                          setTransformationMatrixBuffer(const MTL4::BufferRange transformationMatrixBuffer);

    void                                                          setTransformationMatrixLayout(MTL::MatrixLayout transformationMatrixLayout);

    void                                                          setTriangleCount(NS::UInteger triangleCount);

    void                                                          setVertexBuffers(const MTL4::BufferRange vertexBuffers);

    void                                                          setVertexFormat(MTL::AttributeFormat vertexFormat);

    void                                                          setVertexStride(NS::UInteger vertexStride);

    BufferRange                                                   transformationMatrixBuffer() const;

    MTL::MatrixLayout                                             transformationMatrixLayout() const;

    NS::UInteger                                                  triangleCount() const;

    BufferRange                                                   vertexBuffers() const;

    MTL::AttributeFormat                                          vertexFormat() const;

    NS::UInteger                                                  vertexStride() const;
};
class AccelerationStructureMotionBoundingBoxGeometryDescriptor : public NS::Copying<AccelerationStructureMotionBoundingBoxGeometryDescriptor, AccelerationStructureGeometryDescriptor>
{
public:
    static AccelerationStructureMotionBoundingBoxGeometryDescriptor* alloc();

    BufferRange                                                      boundingBoxBuffers() const;

    NS::UInteger                                                     boundingBoxCount() const;

    NS::UInteger                                                     boundingBoxStride() const;

    AccelerationStructureMotionBoundingBoxGeometryDescriptor*        init();

    void                                                             setBoundingBoxBuffers(const MTL4::BufferRange boundingBoxBuffers);

    void                                                             setBoundingBoxCount(NS::UInteger boundingBoxCount);

    void                                                             setBoundingBoxStride(NS::UInteger boundingBoxStride);
};
class AccelerationStructureCurveGeometryDescriptor : public NS::Copying<AccelerationStructureCurveGeometryDescriptor, AccelerationStructureGeometryDescriptor>
{
public:
    static AccelerationStructureCurveGeometryDescriptor* alloc();

    BufferRange                                          controlPointBuffer() const;

    NS::UInteger                                         controlPointCount() const;

    MTL::AttributeFormat                                 controlPointFormat() const;

    NS::UInteger                                         controlPointStride() const;

    MTL::CurveBasis                                      curveBasis() const;

    MTL::CurveEndCaps                                    curveEndCaps() const;

    MTL::CurveType                                       curveType() const;

    BufferRange                                          indexBuffer() const;

    MTL::IndexType                                       indexType() const;

    AccelerationStructureCurveGeometryDescriptor*        init();

    BufferRange                                          radiusBuffer() const;

    MTL::AttributeFormat                                 radiusFormat() const;

    NS::UInteger                                         radiusStride() const;

    NS::UInteger                                         segmentControlPointCount() const;

    NS::UInteger                                         segmentCount() const;

    void                                                 setControlPointBuffer(const MTL4::BufferRange controlPointBuffer);

    void                                                 setControlPointCount(NS::UInteger controlPointCount);

    void                                                 setControlPointFormat(MTL::AttributeFormat controlPointFormat);

    void                                                 setControlPointStride(NS::UInteger controlPointStride);

    void                                                 setCurveBasis(MTL::CurveBasis curveBasis);

    void                                                 setCurveEndCaps(MTL::CurveEndCaps curveEndCaps);

    void                                                 setCurveType(MTL::CurveType curveType);

    void                                                 setIndexBuffer(const MTL4::BufferRange indexBuffer);

    void                                                 setIndexType(MTL::IndexType indexType);

    void                                                 setRadiusBuffer(const MTL4::BufferRange radiusBuffer);

    void                                                 setRadiusFormat(MTL::AttributeFormat radiusFormat);

    void                                                 setRadiusStride(NS::UInteger radiusStride);

    void                                                 setSegmentControlPointCount(NS::UInteger segmentControlPointCount);

    void                                                 setSegmentCount(NS::UInteger segmentCount);
};
class AccelerationStructureMotionCurveGeometryDescriptor : public NS::Copying<AccelerationStructureMotionCurveGeometryDescriptor, AccelerationStructureGeometryDescriptor>
{
public:
    static AccelerationStructureMotionCurveGeometryDescriptor* alloc();

    BufferRange                                                controlPointBuffers() const;

    NS::UInteger                                               controlPointCount() const;

    MTL::AttributeFormat                                       controlPointFormat() const;

    NS::UInteger                                               controlPointStride() const;

    MTL::CurveBasis                                            curveBasis() const;

    MTL::CurveEndCaps                                          curveEndCaps() const;

    MTL::CurveType                                             curveType() const;

    BufferRange                                                indexBuffer() const;

    MTL::IndexType                                             indexType() const;

    AccelerationStructureMotionCurveGeometryDescriptor*        init();

    BufferRange                                                radiusBuffers() const;

    MTL::AttributeFormat                                       radiusFormat() const;

    NS::UInteger                                               radiusStride() const;

    NS::UInteger                                               segmentControlPointCount() const;

    NS::UInteger                                               segmentCount() const;

    void                                                       setControlPointBuffers(const MTL4::BufferRange controlPointBuffers);

    void                                                       setControlPointCount(NS::UInteger controlPointCount);

    void                                                       setControlPointFormat(MTL::AttributeFormat controlPointFormat);

    void                                                       setControlPointStride(NS::UInteger controlPointStride);

    void                                                       setCurveBasis(MTL::CurveBasis curveBasis);

    void                                                       setCurveEndCaps(MTL::CurveEndCaps curveEndCaps);

    void                                                       setCurveType(MTL::CurveType curveType);

    void                                                       setIndexBuffer(const MTL4::BufferRange indexBuffer);

    void                                                       setIndexType(MTL::IndexType indexType);

    void                                                       setRadiusBuffers(const MTL4::BufferRange radiusBuffers);

    void                                                       setRadiusFormat(MTL::AttributeFormat radiusFormat);

    void                                                       setRadiusStride(NS::UInteger radiusStride);

    void                                                       setSegmentControlPointCount(NS::UInteger segmentControlPointCount);

    void                                                       setSegmentCount(NS::UInteger segmentCount);
};
class InstanceAccelerationStructureDescriptor : public NS::Copying<InstanceAccelerationStructureDescriptor, AccelerationStructureDescriptor>
{
public:
    static InstanceAccelerationStructureDescriptor*  alloc();

    InstanceAccelerationStructureDescriptor*         init();

    NS::UInteger                                     instanceCount() const;

    BufferRange                                      instanceDescriptorBuffer() const;

    NS::UInteger                                     instanceDescriptorStride() const;

    MTL::AccelerationStructureInstanceDescriptorType instanceDescriptorType() const;

    MTL::MatrixLayout                                instanceTransformationMatrixLayout() const;

    BufferRange                                      motionTransformBuffer() const;

    NS::UInteger                                     motionTransformCount() const;

    NS::UInteger                                     motionTransformStride() const;

    MTL::TransformType                               motionTransformType() const;

    void                                             setInstanceCount(NS::UInteger instanceCount);

    void                                             setInstanceDescriptorBuffer(const MTL4::BufferRange instanceDescriptorBuffer);

    void                                             setInstanceDescriptorStride(NS::UInteger instanceDescriptorStride);

    void                                             setInstanceDescriptorType(MTL::AccelerationStructureInstanceDescriptorType instanceDescriptorType);

    void                                             setInstanceTransformationMatrixLayout(MTL::MatrixLayout instanceTransformationMatrixLayout);

    void                                             setMotionTransformBuffer(const MTL4::BufferRange motionTransformBuffer);

    void                                             setMotionTransformCount(NS::UInteger motionTransformCount);

    void                                             setMotionTransformStride(NS::UInteger motionTransformStride);

    void                                             setMotionTransformType(MTL::TransformType motionTransformType);
};
class IndirectInstanceAccelerationStructureDescriptor : public NS::Copying<IndirectInstanceAccelerationStructureDescriptor, AccelerationStructureDescriptor>
{
public:
    static IndirectInstanceAccelerationStructureDescriptor* alloc();

    IndirectInstanceAccelerationStructureDescriptor*        init();

    BufferRange                                             instanceCountBuffer() const;

    BufferRange                                             instanceDescriptorBuffer() const;

    NS::UInteger                                            instanceDescriptorStride() const;

    MTL::AccelerationStructureInstanceDescriptorType        instanceDescriptorType() const;

    MTL::MatrixLayout                                       instanceTransformationMatrixLayout() const;

    NS::UInteger                                            maxInstanceCount() const;

    NS::UInteger                                            maxMotionTransformCount() const;

    BufferRange                                             motionTransformBuffer() const;

    BufferRange                                             motionTransformCountBuffer() const;

    NS::UInteger                                            motionTransformStride() const;

    MTL::TransformType                                      motionTransformType() const;

    void                                                    setInstanceCountBuffer(const MTL4::BufferRange instanceCountBuffer);

    void                                                    setInstanceDescriptorBuffer(const MTL4::BufferRange instanceDescriptorBuffer);

    void                                                    setInstanceDescriptorStride(NS::UInteger instanceDescriptorStride);

    void                                                    setInstanceDescriptorType(MTL::AccelerationStructureInstanceDescriptorType instanceDescriptorType);

    void                                                    setInstanceTransformationMatrixLayout(MTL::MatrixLayout instanceTransformationMatrixLayout);

    void                                                    setMaxInstanceCount(NS::UInteger maxInstanceCount);

    void                                                    setMaxMotionTransformCount(NS::UInteger maxMotionTransformCount);

    void                                                    setMotionTransformBuffer(const MTL4::BufferRange motionTransformBuffer);

    void                                                    setMotionTransformCountBuffer(const MTL4::BufferRange motionTransformCountBuffer);

    void                                                    setMotionTransformStride(NS::UInteger motionTransformStride);

    void                                                    setMotionTransformType(MTL::TransformType motionTransformType);
};

}
/**
 * @brief Allocates a new AccelerationStructureDescriptor object.
 *
 * The returned object is allocated but not initialized; call init() on the result before use.
 *
 * @return MTL4::AccelerationStructureDescriptor* Pointer to the allocated descriptor instance.
 */
_MTL_INLINE MTL4::AccelerationStructureDescriptor* MTL4::AccelerationStructureDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::AccelerationStructureDescriptor>(_MTL_PRIVATE_CLS(MTL4AccelerationStructureDescriptor));
}

/**
 * @brief Initializes the acceleration structure descriptor instance.
 *
 * @return MTL4::AccelerationStructureDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL4::AccelerationStructureDescriptor* MTL4::AccelerationStructureDescriptor::init()
{
    return NS::Object::init<MTL4::AccelerationStructureDescriptor>();
}

/**
 * @brief Allocate a new AccelerationStructureGeometryDescriptor instance.
 *
 * @return MTL4::AccelerationStructureGeometryDescriptor* A newly allocated, uninitialized descriptor object.
 */
_MTL_INLINE MTL4::AccelerationStructureGeometryDescriptor* MTL4::AccelerationStructureGeometryDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::AccelerationStructureGeometryDescriptor>(_MTL_PRIVATE_CLS(MTL4AccelerationStructureGeometryDescriptor));
}

/**
 * @brief Indicates whether duplicate intersection function invocations are allowed for this geometry descriptor.
 *
 * @return `true` if duplicate intersection function invocations are allowed, `false` otherwise.
 */
_MTL_INLINE bool MTL4::AccelerationStructureGeometryDescriptor::allowDuplicateIntersectionFunctionInvocation() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(allowDuplicateIntersectionFunctionInvocation));
}

/**
 * @brief Initializes the geometry descriptor.
 *
 * Performs initialization for this AccelerationStructureGeometryDescriptor instance and returns the initialized object.
 *
 * @return MTL4::AccelerationStructureGeometryDescriptor* The initialized descriptor instance.
 */
_MTL_INLINE MTL4::AccelerationStructureGeometryDescriptor* MTL4::AccelerationStructureGeometryDescriptor::init()
{
    return NS::Object::init<MTL4::AccelerationStructureGeometryDescriptor>();
}

/**
 * @brief Gets the offset into the intersection function table used by this geometry descriptor.
 *
 * @return NS::UInteger The offset (in function-table entries) where this geometry's intersection functions begin.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureGeometryDescriptor::intersectionFunctionTableOffset() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(intersectionFunctionTableOffset));
}

/**
 * @brief The optional user-facing label for this geometry descriptor.
 *
 * @return NS::String* The label string if one has been set, `nullptr` otherwise.
 */
_MTL_INLINE NS::String* MTL4::AccelerationStructureGeometryDescriptor::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Queries whether the geometry is marked as opaque.
 *
 * @return `true` if the geometry is opaque, `false` otherwise.
 */
_MTL_INLINE bool MTL4::AccelerationStructureGeometryDescriptor::opaque() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(opaque));
}

/**
 * @brief Accesses the buffer range that contains per-primitive data for the geometry descriptor.
 *
 * @return MTL4::BufferRange The buffer range (buffer, offset, length) used for primitive data.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureGeometryDescriptor::primitiveDataBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(primitiveDataBuffer));
}

/**
 * @brief Retrieves the size, in bytes, of each primitive data element for this geometry descriptor.
 *
 * @return NS::UInteger Size in bytes of a single primitive data element.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureGeometryDescriptor::primitiveDataElementSize() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(primitiveDataElementSize));
}

/**
 * @brief Gets the byte stride between consecutive primitive data elements.
 *
 * @return NS::UInteger The byte stride (in bytes) separating each primitive data element.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureGeometryDescriptor::primitiveDataStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(primitiveDataStride));
}

/**
 * @brief Set whether duplicate intersection function invocations are allowed for this geometry.
 *
 * @param allowDuplicateIntersectionFunctionInvocation `true` to allow duplicate intersection function invocations, `false` otherwise.
 */
_MTL_INLINE void MTL4::AccelerationStructureGeometryDescriptor::setAllowDuplicateIntersectionFunctionInvocation(bool allowDuplicateIntersectionFunctionInvocation)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAllowDuplicateIntersectionFunctionInvocation_), allowDuplicateIntersectionFunctionInvocation);
}

/**
 * @brief Set the offset into the intersection function table for this geometry.
 *
 * @param intersectionFunctionTableOffset Offset into the intersection function table to associate with the geometry.
 */
_MTL_INLINE void MTL4::AccelerationStructureGeometryDescriptor::setIntersectionFunctionTableOffset(NS::UInteger intersectionFunctionTableOffset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIntersectionFunctionTableOffset_), intersectionFunctionTableOffset);
}

/**
 * @brief Assigns a human-readable label to the geometry descriptor.
 *
 * @param label The label to assign; pass nullptr to clear the label.
 */
_MTL_INLINE void MTL4::AccelerationStructureGeometryDescriptor::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Set whether this geometry is treated as opaque for ray intersections.
 *
 * Marks the geometry descriptor as opaque when true, or as non-opaque when false.
 *
 * @param opaque true to mark the geometry as opaque, false to mark it non-opaque.
 */
_MTL_INLINE void MTL4::AccelerationStructureGeometryDescriptor::setOpaque(bool opaque)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setOpaque_), opaque);
}

/**
 * @brief Set the GPU buffer range containing per-primitive data for this geometry descriptor.
 *
 * @param primitiveDataBuffer BufferRange describing the GPU buffer region that holds per-primitive data for the geometry.
 */
_MTL_INLINE void MTL4::AccelerationStructureGeometryDescriptor::setPrimitiveDataBuffer(const MTL4::BufferRange primitiveDataBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPrimitiveDataBuffer_), primitiveDataBuffer);
}

/**
 * @brief Set the size, in bytes, of each element in the primitive data for this geometry descriptor.
 *
 * @param primitiveDataElementSize Size of a single primitive data element, in bytes.
 */
_MTL_INLINE void MTL4::AccelerationStructureGeometryDescriptor::setPrimitiveDataElementSize(NS::UInteger primitiveDataElementSize)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPrimitiveDataElementSize_), primitiveDataElementSize);
}

/**
 * @brief Sets the byte stride between consecutive primitive data entries for the geometry.
 *
 * @param primitiveDataStride The stride in bytes between each primitive's data entry.
 */
_MTL_INLINE void MTL4::AccelerationStructureGeometryDescriptor::setPrimitiveDataStride(NS::UInteger primitiveDataStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setPrimitiveDataStride_), primitiveDataStride);
}

/**
 * @brief Allocate a new PrimitiveAccelerationStructureDescriptor.
 *
 * Allocates and returns a newly created PrimitiveAccelerationStructureDescriptor instance.
 *
 * @return MTL4::PrimitiveAccelerationStructureDescriptor* Pointer to the allocated descriptor.
 */
_MTL_INLINE MTL4::PrimitiveAccelerationStructureDescriptor* MTL4::PrimitiveAccelerationStructureDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::PrimitiveAccelerationStructureDescriptor>(_MTL_PRIVATE_CLS(MTL4PrimitiveAccelerationStructureDescriptor));
}

/**
 * @brief Retrieve the geometry descriptors assigned to this primitive acceleration structure.
 *
 * @return NS::Array* An array containing MTL4::AccelerationStructureGeometryDescriptor objects representing each geometry in the primitive acceleration structure, or `nullptr` if no descriptors are set.
 */
_MTL_INLINE NS::Array* MTL4::PrimitiveAccelerationStructureDescriptor::geometryDescriptors() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(geometryDescriptors));
}

/**
 * @brief Initializes a PrimitiveAccelerationStructureDescriptor instance.
 *
 * @return Pointer to the initialized PrimitiveAccelerationStructureDescriptor.
 */
_MTL_INLINE MTL4::PrimitiveAccelerationStructureDescriptor* MTL4::PrimitiveAccelerationStructureDescriptor::init()
{
    return NS::Object::init<MTL4::PrimitiveAccelerationStructureDescriptor>();
}

/**
 * @brief Retrieves the motion end border mode for the primitive acceleration structure descriptor.
 *
 * Indicates how motion samples that lie beyond the descriptor's configured motion end time are handled.
 *
 * @return MTL::MotionBorderMode The motion end border mode. 
 */
_MTL_INLINE MTL::MotionBorderMode MTL4::PrimitiveAccelerationStructureDescriptor::motionEndBorderMode() const
{
    return Object::sendMessage<MTL::MotionBorderMode>(this, _MTL_PRIVATE_SEL(motionEndBorderMode));
}

/**
 * @brief Retrieves the end time of the motion range for the primitive acceleration structure.
 *
 * @return float The motion end time in seconds.
 */
_MTL_INLINE float MTL4::PrimitiveAccelerationStructureDescriptor::motionEndTime() const
{
    return Object::sendMessage<float>(this, _MTL_PRIVATE_SEL(motionEndTime));
}

/**
 * @brief Gets the number of motion keyframes for the primitive acceleration structure.
 *
 * @return NS::UInteger The number of motion keyframes configured for this descriptor.
 */
_MTL_INLINE NS::UInteger MTL4::PrimitiveAccelerationStructureDescriptor::motionKeyframeCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(motionKeyframeCount));
}

/**
 * @brief Gets the motion border mode used at the start of the descriptor's motion range.
 *
 * This mode specifies how primitives are treated at the start time when motion is applied to the
 * primitive acceleration structure.
 *
 * @return MTL::MotionBorderMode The border mode used at the start of the motion range.
 */
_MTL_INLINE MTL::MotionBorderMode MTL4::PrimitiveAccelerationStructureDescriptor::motionStartBorderMode() const
{
    return Object::sendMessage<MTL::MotionBorderMode>(this, _MTL_PRIVATE_SEL(motionStartBorderMode));
}

/**
 * The start time used for motion sampling in the primitive acceleration structure.
 *
 * @return float The start time value for motion sampling.
 */
_MTL_INLINE float MTL4::PrimitiveAccelerationStructureDescriptor::motionStartTime() const
{
    return Object::sendMessage<float>(this, _MTL_PRIVATE_SEL(motionStartTime));
}

/**
 * @brief Assigns the list of geometry descriptors used by this primitive acceleration structure.
 *
 * @param geometryDescriptors An NSArray of geometry descriptor objects describing the primitives (e.g., triangle, curve, bounding box) that compose the acceleration structure.
 */
_MTL_INLINE void MTL4::PrimitiveAccelerationStructureDescriptor::setGeometryDescriptors(const NS::Array* geometryDescriptors)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setGeometryDescriptors_), geometryDescriptors);
}

/**
 * @brief Sets the motion end border mode used when sampling motion transforms.
 *
 * @param motionEndBorderMode The motion border mode to apply at the end of the motion interval.
 */
_MTL_INLINE void MTL4::PrimitiveAccelerationStructureDescriptor::setMotionEndBorderMode(MTL::MotionBorderMode motionEndBorderMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionEndBorderMode_), motionEndBorderMode);
}

/**
 * @brief Sets the end time of the motion window for this primitive acceleration structure.
 *
 * @param motionEndTime End time for motion sampling (in the same time units used by the descriptor).
 */
_MTL_INLINE void MTL4::PrimitiveAccelerationStructureDescriptor::setMotionEndTime(float motionEndTime)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionEndTime_), motionEndTime);
}

/**
 * @brief Sets the number of motion keyframes for this primitive acceleration structure.
 *
 * @param motionKeyframeCount The number of motion keyframes to use for motion blur sampling; must be a non-zero count when motion is enabled.
 */
_MTL_INLINE void MTL4::PrimitiveAccelerationStructureDescriptor::setMotionKeyframeCount(NS::UInteger motionKeyframeCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionKeyframeCount_), motionKeyframeCount);
}

/**
 * @brief Set the motion start border mode for this primitive acceleration structure.
 *
 * Controls how primitives are treated outside the start motion keyframe when the structure contains motion data.
 *
 * @param motionStartBorderMode The mode that determines border behavior at the start of motion.
 */
_MTL_INLINE void MTL4::PrimitiveAccelerationStructureDescriptor::setMotionStartBorderMode(MTL::MotionBorderMode motionStartBorderMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionStartBorderMode_), motionStartBorderMode);
}

/**
 * @brief Sets the start time for motion sampling on the primitive acceleration structure.
 *
 * @param motionStartTime Start time of the motion range, in seconds.
 */
_MTL_INLINE void MTL4::PrimitiveAccelerationStructureDescriptor::setMotionStartTime(float motionStartTime)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionStartTime_), motionStartTime);
}

/**
 * @brief Allocates a new AccelerationStructureTriangleGeometryDescriptor.
 *
 * @return MTL4::AccelerationStructureTriangleGeometryDescriptor*
 * A newly allocated descriptor instance that must be initialized (call init()) before use.
 */
_MTL_INLINE MTL4::AccelerationStructureTriangleGeometryDescriptor* MTL4::AccelerationStructureTriangleGeometryDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::AccelerationStructureTriangleGeometryDescriptor>(_MTL_PRIVATE_CLS(MTL4AccelerationStructureTriangleGeometryDescriptor));
}

/**
 * @brief Returns the buffer range containing triangle index data for the descriptor.
 *
 * The buffer range identifies the GPU buffer and its offset/length that store indices
 * for the triangle geometry described by this object.
 *
 * @return MTL4::BufferRange The index buffer range (or an empty range if no index buffer is set).
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureTriangleGeometryDescriptor::indexBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(indexBuffer));
}

/**
 * @brief Gets the index type used by this triangle geometry descriptor.
 *
 * @return MTL::IndexType The index format for triangle indices (for example `MTL::IndexTypeUInt16` or `MTL::IndexTypeUInt32`).
 */
_MTL_INLINE MTL::IndexType MTL4::AccelerationStructureTriangleGeometryDescriptor::indexType() const
{
    return Object::sendMessage<MTL::IndexType>(this, _MTL_PRIVATE_SEL(indexType));
}

/**
 * @brief Initializes a triangle geometry descriptor.
 *
 * @return MTL4::AccelerationStructureTriangleGeometryDescriptor* Initialized descriptor instance.
 */
_MTL_INLINE MTL4::AccelerationStructureTriangleGeometryDescriptor* MTL4::AccelerationStructureTriangleGeometryDescriptor::init()
{
    return NS::Object::init<MTL4::AccelerationStructureTriangleGeometryDescriptor>();
}

/**
 * @brief Set the index buffer range used for triangle indices in the geometry descriptor.
 *
 * @param indexBuffer BufferRange describing the buffer and range that contains triangle index data.
 */
_MTL_INLINE void MTL4::AccelerationStructureTriangleGeometryDescriptor::setIndexBuffer(const MTL4::BufferRange indexBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIndexBuffer_), indexBuffer);
}

/**
 * @brief Set the index data type used by the triangle geometry.
 *
 * Configures the index element type that the descriptor's index buffer contains.
 *
 * @param indexType The index element format to use for triangle indexing.
 */
_MTL_INLINE void MTL4::AccelerationStructureTriangleGeometryDescriptor::setIndexType(MTL::IndexType indexType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIndexType_), indexType);
}

/**
 * @brief Sets the buffer range that contains transformation matrices for the geometry.
 *
 * @param transformationMatrixBuffer BufferRange referencing the transformation-matrix data used for per-geometry transforms.
 */
_MTL_INLINE void MTL4::AccelerationStructureTriangleGeometryDescriptor::setTransformationMatrixBuffer(const MTL4::BufferRange transformationMatrixBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTransformationMatrixBuffer_), transformationMatrixBuffer);
}

/**
 * @brief Configure the layout used for per-primitive transformation matrices.
 *
 * @param transformationMatrixLayout The matrix memory layout that describes how transformation matrices are stored for this triangle geometry.
 */
_MTL_INLINE void MTL4::AccelerationStructureTriangleGeometryDescriptor::setTransformationMatrixLayout(MTL::MatrixLayout transformationMatrixLayout)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTransformationMatrixLayout_), transformationMatrixLayout);
}

/**
 * @brief Set the number of triangles represented by this triangle-geometry descriptor.
 *
 * @param triangleCount The total number of triangles for the geometry.
 */
_MTL_INLINE void MTL4::AccelerationStructureTriangleGeometryDescriptor::setTriangleCount(NS::UInteger triangleCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTriangleCount_), triangleCount);
}

/**
 * @brief Sets the vertex buffer range to be used by this triangle geometry descriptor.
 *
 * Specifies the buffer and range that contain vertex position data (and any per-vertex attributes)
 * for triangles referenced by this descriptor.
 *
 * @param vertexBuffer BufferRange describing the buffer and byte range that hold the vertex data.
 */
_MTL_INLINE void MTL4::AccelerationStructureTriangleGeometryDescriptor::setVertexBuffer(const MTL4::BufferRange vertexBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexBuffer_), vertexBuffer);
}

/**
 * @brief Sets the vertex attribute format used for triangle vertices in this descriptor.
 *
 * @param vertexFormat The attribute format to apply to vertex data.
 */
_MTL_INLINE void MTL4::AccelerationStructureTriangleGeometryDescriptor::setVertexFormat(MTL::AttributeFormat vertexFormat)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexFormat_), vertexFormat);
}

/**
 * @brief Set the byte stride between consecutive vertices in the vertex buffer.
 *
 * @param vertexStride Number of bytes between the start of one vertex and the start of the next.
 */
_MTL_INLINE void MTL4::AccelerationStructureTriangleGeometryDescriptor::setVertexStride(NS::UInteger vertexStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexStride_), vertexStride);
}

/**
 * @brief Retrieves the buffer range that contains transformation matrices for this triangle geometry.
 *
 * @return MTL4::BufferRange The buffer range describing where per-geometry transformation matrices are stored,
 *         or an empty/default BufferRange if no transformation matrix buffer has been assigned.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureTriangleGeometryDescriptor::transformationMatrixBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(transformationMatrixBuffer));
}

/**
 * @brief Retrieves the layout used for transformation matrices in the triangle geometry.
 *
 * @return MTL::MatrixLayout The layout of the transformation matrix buffer for this geometry descriptor.
 */
_MTL_INLINE MTL::MatrixLayout MTL4::AccelerationStructureTriangleGeometryDescriptor::transformationMatrixLayout() const
{
    return Object::sendMessage<MTL::MatrixLayout>(this, _MTL_PRIVATE_SEL(transformationMatrixLayout));
}

/**
 * @brief Retrieves the number of triangles described by this geometry descriptor.
 *
 * @return NS::UInteger The number of triangles contained in the descriptor.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureTriangleGeometryDescriptor::triangleCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(triangleCount));
}

/**
 * @brief Gets the buffer range containing vertex data for this triangle geometry descriptor.
 *
 * @return MTL4::BufferRange The buffer range that supplies vertex data (positions/attributes) for the descriptor.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureTriangleGeometryDescriptor::vertexBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(vertexBuffer));
}

/**
 * @brief Get the vertex attribute format used for triangle geometry.
 *
 * @return MTL::AttributeFormat The attribute format of the vertex data.
 */
_MTL_INLINE MTL::AttributeFormat MTL4::AccelerationStructureTriangleGeometryDescriptor::vertexFormat() const
{
    return Object::sendMessage<MTL::AttributeFormat>(this, _MTL_PRIVATE_SEL(vertexFormat));
}

/**
 * @brief Retrieves the byte stride between consecutive vertex elements.
 *
 * @return NS::UInteger The stride, in bytes, between successive vertices in the vertex buffer.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureTriangleGeometryDescriptor::vertexStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(vertexStride));
}

/**
 * @brief Allocate a new AccelerationStructureBoundingBoxGeometryDescriptor.
 *
 * @return MTL4::AccelerationStructureBoundingBoxGeometryDescriptor* Pointer to the newly allocated descriptor.
 */
_MTL_INLINE MTL4::AccelerationStructureBoundingBoxGeometryDescriptor* MTL4::AccelerationStructureBoundingBoxGeometryDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::AccelerationStructureBoundingBoxGeometryDescriptor>(_MTL_PRIVATE_CLS(MTL4AccelerationStructureBoundingBoxGeometryDescriptor));
}

/**
 * @brief Gets the buffer range that provides axis-aligned bounding box data for this geometry descriptor.
 *
 * @return MTL4::BufferRange The buffer range containing the descriptor's bounding box data.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureBoundingBoxGeometryDescriptor::boundingBoxBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(boundingBoxBuffer));
}

/**
 * @brief Gets the number of axis-aligned bounding boxes described by this geometry descriptor.
 *
 * @return NS::UInteger The number of bounding boxes.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureBoundingBoxGeometryDescriptor::boundingBoxCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(boundingBoxCount));
}

/**
 * @brief Get the byte stride between consecutive bounding box entries.
 *
 * @return NS::UInteger The stride in bytes between bounding box entries.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureBoundingBoxGeometryDescriptor::boundingBoxStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(boundingBoxStride));
}

/**
 * @brief Initializes the acceleration-structure bounding box geometry descriptor.
 *
 * @return AccelerationStructureBoundingBoxGeometryDescriptor* The initialized descriptor instance.
 */
_MTL_INLINE MTL4::AccelerationStructureBoundingBoxGeometryDescriptor* MTL4::AccelerationStructureBoundingBoxGeometryDescriptor::init()
{
    return NS::Object::init<MTL4::AccelerationStructureBoundingBoxGeometryDescriptor>();
}

/**
 * @brief Sets the buffer range that contains axis-aligned bounding box data for this geometry descriptor.
 *
 * @param boundingBoxBuffer BufferRange specifying the buffer and byte range where bounding box entries are stored.
 */
_MTL_INLINE void MTL4::AccelerationStructureBoundingBoxGeometryDescriptor::setBoundingBoxBuffer(const MTL4::BufferRange boundingBoxBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBoundingBoxBuffer_), boundingBoxBuffer);
}

/**
 * @brief Set the number of axis-aligned bounding boxes referenced by this descriptor.
 *
 * @param boundingBoxCount The number of bounding boxes stored in the bounding box buffer.
 */
_MTL_INLINE void MTL4::AccelerationStructureBoundingBoxGeometryDescriptor::setBoundingBoxCount(NS::UInteger boundingBoxCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBoundingBoxCount_), boundingBoxCount);
}

/**
 * @brief Set the byte stride between consecutive axis-aligned bounding box entries.
 *
 * @param boundingBoxStride Number of bytes between the start of one bounding box and the next in the bounding box buffer.
 */
_MTL_INLINE void MTL4::AccelerationStructureBoundingBoxGeometryDescriptor::setBoundingBoxStride(NS::UInteger boundingBoxStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBoundingBoxStride_), boundingBoxStride);
}

/**
 * @brief Allocate a new AccelerationStructureMotionTriangleGeometryDescriptor instance.
 *
 * @return MTL4::AccelerationStructureMotionTriangleGeometryDescriptor* Newly allocated descriptor object.
 */
_MTL_INLINE MTL4::AccelerationStructureMotionTriangleGeometryDescriptor* MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::AccelerationStructureMotionTriangleGeometryDescriptor>(_MTL_PRIVATE_CLS(MTL4AccelerationStructureMotionTriangleGeometryDescriptor));
}

/**
 * @brief Returns the buffer range containing triangle indices for this motion-enabled triangle geometry descriptor.
 *
 * @return MTL4::BufferRange BufferRange describing the index buffer (buffer, offset, and length) used by the descriptor.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::indexBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(indexBuffer));
}

/**
 * @brief Retrieves the index type used for triangle indices in this motion triangle geometry descriptor.
 *
 * @return MTL::IndexType The index type used for the geometry (for example, 16-bit or 32-bit indices).
 */
_MTL_INLINE MTL::IndexType MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::indexType() const
{
    return Object::sendMessage<MTL::IndexType>(this, _MTL_PRIVATE_SEL(indexType));
}

/**
 * @brief Initialize a motion-enabled triangle geometry descriptor.
 *
 * @return MTL4::AccelerationStructureMotionTriangleGeometryDescriptor* Initialized descriptor instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL4::AccelerationStructureMotionTriangleGeometryDescriptor* MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::init()
{
    return NS::Object::init<MTL4::AccelerationStructureMotionTriangleGeometryDescriptor>();
}

/**
 * @brief Set the index buffer for the motion-enabled triangle geometry descriptor.
 *
 * @param indexBuffer BufferRange specifying the buffer and range that contain triangle indices.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::setIndexBuffer(const MTL4::BufferRange indexBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIndexBuffer_), indexBuffer);
}

/**
 * @brief Set the index type used for triangle indices in this motion triangle geometry descriptor.
 *
 * @param indexType The index format to use for vertex indices (for example `MTL::IndexType::UInt16` or `MTL::IndexType::UInt32`).
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::setIndexType(MTL::IndexType indexType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIndexType_), indexType);
}

/**
 * @brief Sets the buffer that provides transformation matrices for motion triangle geometry.
 *
 * Specifies the BufferRange that contains per-geometry transformation matrices used to apply motion transforms
 * to the triangle geometry.
 *
 * @param transformationMatrixBuffer BufferRange specifying the buffer, offset and length for transformation matrices.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::setTransformationMatrixBuffer(const MTL4::BufferRange transformationMatrixBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTransformationMatrixBuffer_), transformationMatrixBuffer);
}

/**
 * @brief Set the layout used for transformation matrices on motion-enabled triangle geometry.
 *
 * @param transformationMatrixLayout The matrix layout to use for the transformation matrix buffer.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::setTransformationMatrixLayout(MTL::MatrixLayout transformationMatrixLayout)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTransformationMatrixLayout_), transformationMatrixLayout);
}

/**
 * @brief Sets the number of triangles contained in the motion triangle geometry.
 *
 * @param triangleCount The number of triangles in the geometry.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::setTriangleCount(NS::UInteger triangleCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setTriangleCount_), triangleCount);
}

/**
 * @brief Set the vertex buffer range(s) used by this motion-enabled triangle geometry descriptor.
 *
 * @param vertexBuffers BufferRange describing one or more buffers that contain vertex data for the geometry's motion keyframes.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::setVertexBuffers(const MTL4::BufferRange vertexBuffers)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexBuffers_), vertexBuffers);
}

/**
 * @brief Set the vertex attribute format used for vertex data in the motion triangle geometry descriptor.
 *
 * @param vertexFormat The attribute format that describes the layout of each vertex (position, normal, etc.).
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::setVertexFormat(MTL::AttributeFormat vertexFormat)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexFormat_), vertexFormat);
}

/**
 * @brief Set the byte stride between consecutive vertex elements in the vertex buffer(s).
 *
 * @param vertexStride Number of bytes between the start of one vertex and the start of the next.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::setVertexStride(NS::UInteger vertexStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setVertexStride_), vertexStride);
}

/**
 * @brief Returns the buffer range containing per-geometry transformation matrices for motion-enabled triangle geometry.
 *
 * @return MTL4::BufferRange The buffer range that holds transformation matrices used by this motion triangle geometry descriptor.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::transformationMatrixBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(transformationMatrixBuffer));
}

/**
 * @brief Query the layout used for transformation matrices referenced by this descriptor.
 *
 * @return MTL::MatrixLayout The layout of the transformation matrix buffer. 
 */
_MTL_INLINE MTL::MatrixLayout MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::transformationMatrixLayout() const
{
    return Object::sendMessage<MTL::MatrixLayout>(this, _MTL_PRIVATE_SEL(transformationMatrixLayout));
}

/**
 * @brief Gets the number of triangles in this motion triangle geometry descriptor.
 *
 * @return NS::UInteger The number of triangles described by the descriptor.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::triangleCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(triangleCount));
}

/**
 * @brief Vertex buffers range for motion-enabled triangle geometry.
 *
 * @return MTL4::BufferRange The buffer range containing vertex buffers used by the motion triangle geometry.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::vertexBuffers() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(vertexBuffers));
}

/**
 * @brief Returns the vertex attribute format used by the motion triangle geometry.
 *
 * @return MTL::AttributeFormat The attribute format describing how vertex data is laid out.
 */
_MTL_INLINE MTL::AttributeFormat MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::vertexFormat() const
{
    return Object::sendMessage<MTL::AttributeFormat>(this, _MTL_PRIVATE_SEL(vertexFormat));
}

/**
 * @brief Retrieve the byte stride between consecutive vertex elements.
 *
 * @return NS::UInteger The vertex stride, in bytes.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureMotionTriangleGeometryDescriptor::vertexStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(vertexStride));
}

/**
 * @brief Allocate a new AccelerationStructureMotionBoundingBoxGeometryDescriptor instance.
 *
 * @return MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor* Pointer to a newly allocated (but not initialized) descriptor.
 */
_MTL_INLINE MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor* MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor>(_MTL_PRIVATE_CLS(MTL4AccelerationStructureMotionBoundingBoxGeometryDescriptor));
}

/**
 * @brief Retrieve the buffer range(s) that contain motion-enabled axis-aligned bounding box data.
 *
 * @return MTL4::BufferRange The buffer range describing the bounding box buffers used for motion geometry.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor::boundingBoxBuffers() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(boundingBoxBuffers));
}

/**
 * @brief Returns the number of axis-aligned bounding boxes described by this motion bounding-box geometry.
 *
 * @return NS::UInteger The number of bounding boxes in the descriptor.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor::boundingBoxCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(boundingBoxCount));
}

/**
 * @brief Byte stride between consecutive bounding boxes in the bounding box buffers.
 *
 * @return NS::UInteger The stride in bytes between each bounding box entry.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor::boundingBoxStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(boundingBoxStride));
}

/**
 * @brief Initializes an AccelerationStructureMotionBoundingBoxGeometryDescriptor instance.
 *
 * @return Pointer to the initialized MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor.
 */
_MTL_INLINE MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor* MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor::init()
{
    return NS::Object::init<MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor>();
}

/**
 * @brief Sets the per-geometry bounding box buffers for a motion-enabled bounding box geometry descriptor.
 *
 * @param boundingBoxBuffers A BufferRange describing one or more buffers that contain axis-aligned bounding box data for the geometry's motion keyframes.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor::setBoundingBoxBuffers(const MTL4::BufferRange boundingBoxBuffers)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBoundingBoxBuffers_), boundingBoxBuffers);
}

/**
 * @brief Set the number of axis-aligned bounding boxes referenced by this geometry descriptor.
 *
 * @param boundingBoxCount The number of bounding boxes to use for the descriptor.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor::setBoundingBoxCount(NS::UInteger boundingBoxCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBoundingBoxCount_), boundingBoxCount);
}

/**
 * @brief Sets the byte stride between consecutive bounding box entries.
 *
 * The stride is the number of bytes from the start of one bounding box record to the start of the next.
 *
 * @param boundingBoxStride Number of bytes between consecutive bounding box entries.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionBoundingBoxGeometryDescriptor::setBoundingBoxStride(NS::UInteger boundingBoxStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBoundingBoxStride_), boundingBoxStride);
}

/**
 * @brief Allocates a new AccelerationStructureCurveGeometryDescriptor.
 *
 * @return MTL4::AccelerationStructureCurveGeometryDescriptor* Pointer to the newly allocated descriptor.
 */
_MTL_INLINE MTL4::AccelerationStructureCurveGeometryDescriptor* MTL4::AccelerationStructureCurveGeometryDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::AccelerationStructureCurveGeometryDescriptor>(_MTL_PRIVATE_CLS(MTL4AccelerationStructureCurveGeometryDescriptor));
}

/**
 * @brief The buffer range that holds control point data for this curve geometry descriptor.
 *
 * @return MTL4::BufferRange Buffer range referencing the control point data used by the descriptor.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureCurveGeometryDescriptor::controlPointBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(controlPointBuffer));
}

/**
 * @brief Retrieve the number of control points for the curve geometry.
 *
 * @return NS::UInteger The number of control points in the geometry.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureCurveGeometryDescriptor::controlPointCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(controlPointCount));
}

/**
 * @brief Returns the attribute format used for control points in the curve geometry.
 *
 * @return MTL::AttributeFormat The format describing each control point's attribute layout.
 */
_MTL_INLINE MTL::AttributeFormat MTL4::AccelerationStructureCurveGeometryDescriptor::controlPointFormat() const
{
    return Object::sendMessage<MTL::AttributeFormat>(this, _MTL_PRIVATE_SEL(controlPointFormat));
}

/**
 * @brief Gets the byte stride between consecutive control points.
 *
 * @return NS::UInteger The stride in bytes between consecutive control points.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureCurveGeometryDescriptor::controlPointStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(controlPointStride));
}

/**
 * The curve basis used by this curve geometry descriptor.
 *
 * @return MTL::CurveBasis The curve basis enum value that describes how curve control points are interpreted.
 */
_MTL_INLINE MTL::CurveBasis MTL4::AccelerationStructureCurveGeometryDescriptor::curveBasis() const
{
    return Object::sendMessage<MTL::CurveBasis>(this, _MTL_PRIVATE_SEL(curveBasis));
}

/**
 * @brief Query the curve end-cap style used by the geometry descriptor.
 *
 * @return MTL::CurveEndCaps The end-cap style applied to the curve geometry.
 */
_MTL_INLINE MTL::CurveEndCaps MTL4::AccelerationStructureCurveGeometryDescriptor::curveEndCaps() const
{
    return Object::sendMessage<MTL::CurveEndCaps>(this, _MTL_PRIVATE_SEL(curveEndCaps));
}

/**
 * @brief Gets the curve type for this curve geometry descriptor.
 *
 * @return MTL::CurveType The curve representation used by the descriptor.
 */
_MTL_INLINE MTL::CurveType MTL4::AccelerationStructureCurveGeometryDescriptor::curveType() const
{
    return Object::sendMessage<MTL::CurveType>(this, _MTL_PRIVATE_SEL(curveType));
}

/**
 * @brief Get the buffer range that holds index data for this curve geometry.
 *
 * The index buffer contains indices that reference control points or segment elements used to define curve primitives.
 *
 * @return MTL4::BufferRange The buffer range describing the index buffer; an empty range if no index buffer is set.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureCurveGeometryDescriptor::indexBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(indexBuffer));
}

/**
 * @brief Retrieve the index type used to reference control points in the curve geometry descriptor.
 *
 * @return MTL::IndexType The index type used for indices referencing control points.
 */
_MTL_INLINE MTL::IndexType MTL4::AccelerationStructureCurveGeometryDescriptor::indexType() const
{
    return Object::sendMessage<MTL::IndexType>(this, _MTL_PRIVATE_SEL(indexType));
}

/**
 * @brief Initializes the acceleration-structure curve geometry descriptor.
 *
 * Performs object initialization and returns the initialized descriptor.
 *
 * @return A pointer to the initialized AccelerationStructureCurveGeometryDescriptor, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL4::AccelerationStructureCurveGeometryDescriptor* MTL4::AccelerationStructureCurveGeometryDescriptor::init()
{
    return NS::Object::init<MTL4::AccelerationStructureCurveGeometryDescriptor>();
}

/**
 * @brief Gets the buffer range containing radius data for the curve geometry.
 *
 * @return MTL4::BufferRange The buffer range that holds per-curve radius values.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureCurveGeometryDescriptor::radiusBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(radiusBuffer));
}

/**
 * @brief Returns the attribute format used for curve radius data.
 *
 * @return MTL::AttributeFormat The format of the per-curve radius attribute.
 */
_MTL_INLINE MTL::AttributeFormat MTL4::AccelerationStructureCurveGeometryDescriptor::radiusFormat() const
{
    return Object::sendMessage<MTL::AttributeFormat>(this, _MTL_PRIVATE_SEL(radiusFormat));
}

/**
 * @brief Byte stride between consecutive radius entries in the radius buffer.
 *
 * @return NS::UInteger The number of bytes between the start of one radius element and the start of the next in the radius buffer.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureCurveGeometryDescriptor::radiusStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(radiusStride));
}

/**
 * @brief Query the number of control points per curve segment.
 *
 * @return NS::UInteger The number of control points for each segment in the curve geometry.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureCurveGeometryDescriptor::segmentControlPointCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(segmentControlPointCount));
}

/**
 * @brief Number of segments used to represent each curve in this geometry descriptor.
 *
 * @return NS::UInteger The segment count for the curve geometry.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureCurveGeometryDescriptor::segmentCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(segmentCount));
}

/**
 * @brief Sets the buffer range that provides control point data for the curve geometry.
 *
 * The provided BufferRange specifies the buffer and byte range containing control points used
 * by this curve geometry descriptor.
 *
 * @param controlPointBuffer BufferRange describing the buffer and byte range that holds control point data.
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setControlPointBuffer(const MTL4::BufferRange controlPointBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setControlPointBuffer_), controlPointBuffer);
}

/**
 * @brief Sets the number of control points used by the curve geometry.
 *
 * @param controlPointCount The number of control points for the curve geometry.
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setControlPointCount(NS::UInteger controlPointCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setControlPointCount_), controlPointCount);
}

/**
 * @brief Set the attribute format used for control point data in the curve geometry descriptor.
 *
 * @param controlPointFormat The attribute format that describes the layout of each control point.
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setControlPointFormat(MTL::AttributeFormat controlPointFormat)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setControlPointFormat_), controlPointFormat);
}

/**
 * @brief Set the byte stride between consecutive control points in the control point buffer.
 *
 * @param controlPointStride The stride, in bytes, between adjacent control points.
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setControlPointStride(NS::UInteger controlPointStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setControlPointStride_), controlPointStride);
}

/**
 * @brief Sets the curve basis used by this curve geometry descriptor.
 *
 * @param curveBasis The curve basis to use for curve tessellation and evaluation.
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setCurveBasis(MTL::CurveBasis curveBasis)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCurveBasis_), curveBasis);
}

/**
 * @brief Sets the end cap style used for curve geometry.
 *
 * @param curveEndCaps The curve end-cap mode to apply to the descriptor.
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setCurveEndCaps(MTL::CurveEndCaps curveEndCaps)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCurveEndCaps_), curveEndCaps);
}

/**
 * @brief Set the curve type used by this curve-geometry descriptor.
 *
 * @param curveType The curve representation to use (one of `MTL::CurveType`).
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setCurveType(MTL::CurveType curveType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCurveType_), curveType);
}

/**
 * @brief Set the buffer range that holds index data for the curve geometry.
 *
 * @param indexBuffer BufferRange describing the buffer, offset and size containing index values used by this curve geometry descriptor.
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setIndexBuffer(const MTL4::BufferRange indexBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIndexBuffer_), indexBuffer);
}

/**
 * @brief Sets the index type used to interpret the curve's index buffer.
 *
 * @param indexType Index format describing how curve indices are encoded (for example 16-bit or 32-bit).
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setIndexType(MTL::IndexType indexType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIndexType_), indexType);
}

/**
 * @brief Set the buffer range containing radius values for the curve geometry.
 *
 * @param radiusBuffer BufferRange specifying the GPU buffer, offset, and length that hold per-control-point radius values used by the curve geometry.
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setRadiusBuffer(const MTL4::BufferRange radiusBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRadiusBuffer_), radiusBuffer);
}

/**
 * @brief Sets the attribute format used for per-primitive radius values.
 *
 * @param radiusFormat Attribute format that describes how radius values are stored in the radius buffer.
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setRadiusFormat(MTL::AttributeFormat radiusFormat)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRadiusFormat_), radiusFormat);
}

/**
 * @brief Set the byte stride between consecutive radius elements for curve geometry.
 *
 * @param radiusStride Byte stride, in bytes, between successive radius entries in the radius buffer.
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setRadiusStride(NS::UInteger radiusStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRadiusStride_), radiusStride);
}

/**
 * @brief Set the number of control points used per curve segment.
 *
 * @param segmentControlPointCount Number of control points in each segment of the curve.
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setSegmentControlPointCount(NS::UInteger segmentControlPointCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSegmentControlPointCount_), segmentControlPointCount);
}

/**
 * @brief Set the number of curve segments for this geometry descriptor.
 *
 * @param segmentCount The number of segments per curve used by the descriptor.
 */
_MTL_INLINE void MTL4::AccelerationStructureCurveGeometryDescriptor::setSegmentCount(NS::UInteger segmentCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSegmentCount_), segmentCount);
}

/**
 * @brief Allocates a new AccelerationStructureMotionCurveGeometryDescriptor instance.
 *
 * @return MTL4::AccelerationStructureMotionCurveGeometryDescriptor* Newly allocated descriptor object.
 */
_MTL_INLINE MTL4::AccelerationStructureMotionCurveGeometryDescriptor* MTL4::AccelerationStructureMotionCurveGeometryDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::AccelerationStructureMotionCurveGeometryDescriptor>(_MTL_PRIVATE_CLS(MTL4AccelerationStructureMotionCurveGeometryDescriptor));
}

/**
 * @brief Control point buffers for the motion-enabled curve geometry descriptor.
 *
 * The returned BufferRange references the buffers that contain curve control points for the descriptor's motion keyframes.
 *
 * @return MTL4::BufferRange Buffer range referencing control point buffers for the descriptor's motion keyframes.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureMotionCurveGeometryDescriptor::controlPointBuffers() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(controlPointBuffers));
}

/**
 * @brief Query the number of control points per curve in this motion curve geometry descriptor.
 *
 * @return NS::UInteger The number of control points per curve.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureMotionCurveGeometryDescriptor::controlPointCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(controlPointCount));
}

/**
 * @brief Attribute format used for control points in the motion curve geometry descriptor.
 *
 * @return MTL::AttributeFormat The format of each control point.
 */
_MTL_INLINE MTL::AttributeFormat MTL4::AccelerationStructureMotionCurveGeometryDescriptor::controlPointFormat() const
{
    return Object::sendMessage<MTL::AttributeFormat>(this, _MTL_PRIVATE_SEL(controlPointFormat));
}

/**
 * @brief Byte stride, in bytes, between consecutive control points in the control-point buffer for motion curve geometry.
 *
 * @return NS::UInteger The stride in bytes between consecutive control points.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureMotionCurveGeometryDescriptor::controlPointStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(controlPointStride));
}

/**
 * @brief Gets the curve basis used by this motion curve geometry descriptor.
 *
 * @return MTL::CurveBasis The curve basis used to evaluate the descriptor's curves.
 */
_MTL_INLINE MTL::CurveBasis MTL4::AccelerationStructureMotionCurveGeometryDescriptor::curveBasis() const
{
    return Object::sendMessage<MTL::CurveBasis>(this, _MTL_PRIVATE_SEL(curveBasis));
}

/**
 * @brief Gets the end-cap style used for curve segments in this motion curve geometry descriptor.
 *
 * @return MTL::CurveEndCaps The end-cap mode applied to the descriptor's curves.
 */
_MTL_INLINE MTL::CurveEndCaps MTL4::AccelerationStructureMotionCurveGeometryDescriptor::curveEndCaps() const
{
    return Object::sendMessage<MTL::CurveEndCaps>(this, _MTL_PRIVATE_SEL(curveEndCaps));
}

/**
 * @brief Retrieve the curve type for this motion curve geometry descriptor.
 *
 * @return MTL::CurveType indicating the curve representation used by the descriptor.
 */
_MTL_INLINE MTL::CurveType MTL4::AccelerationStructureMotionCurveGeometryDescriptor::curveType() const
{
    return Object::sendMessage<MTL::CurveType>(this, _MTL_PRIVATE_SEL(curveType));
}

/**
 * @brief Buffer range for the index buffer used by the curve geometry.
 *
 * @return MTL4::BufferRange The buffer range referencing the index buffer for the curve geometry.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureMotionCurveGeometryDescriptor::indexBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(indexBuffer));
}

/**
 * @brief Retrieves the index type used by the motion curve geometry.
 *
 * @return MTL::IndexType The index type for index buffer elements in this motion curve geometry descriptor.
 */
_MTL_INLINE MTL::IndexType MTL4::AccelerationStructureMotionCurveGeometryDescriptor::indexType() const
{
    return Object::sendMessage<MTL::IndexType>(this, _MTL_PRIVATE_SEL(indexType));
}

/**
 * @brief Initializes the motion-curve geometry descriptor.
 *
 * @return MTL4::AccelerationStructureMotionCurveGeometryDescriptor* Initialized descriptor instance.
 */
_MTL_INLINE MTL4::AccelerationStructureMotionCurveGeometryDescriptor* MTL4::AccelerationStructureMotionCurveGeometryDescriptor::init()
{
    return NS::Object::init<MTL4::AccelerationStructureMotionCurveGeometryDescriptor>();
}

/**
 * @brief Accesses the radius buffer range for motion-enabled curve geometry.
 *
 * @return MTL4::BufferRange The buffer range that contains radius data for the curve geometry across motion keyframes.
 */
_MTL_INLINE MTL4::BufferRange MTL4::AccelerationStructureMotionCurveGeometryDescriptor::radiusBuffers() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(radiusBuffers));
}

/**
 * @brief Attribute format used for per-control-point radius data in this motion curve geometry descriptor.
 *
 * @return MTL::AttributeFormat The attribute format of the radius data.
 */
_MTL_INLINE MTL::AttributeFormat MTL4::AccelerationStructureMotionCurveGeometryDescriptor::radiusFormat() const
{
    return Object::sendMessage<MTL::AttributeFormat>(this, _MTL_PRIVATE_SEL(radiusFormat));
}

/**
 * @brief Query the byte stride between consecutive radius elements in the radius buffer.
 *
 * @return NS::UInteger Number of bytes between consecutive radius elements in the radius buffer.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureMotionCurveGeometryDescriptor::radiusStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(radiusStride));
}

/**
 * @brief Retrieves the number of control points per curve segment for this motion curve geometry descriptor.
 *
 * @return NS::UInteger Number of control points in each segment.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureMotionCurveGeometryDescriptor::segmentControlPointCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(segmentControlPointCount));
}

/**
 * @brief Query the number of curve segments in this motion curve geometry descriptor.
 *
 * @return NS::UInteger The number of segments that make up the curve.
 */
_MTL_INLINE NS::UInteger MTL4::AccelerationStructureMotionCurveGeometryDescriptor::segmentCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(segmentCount));
}

/**
 * @brief Set the buffer range(s) containing control point data for motion curve geometry.
 *
 * @param controlPointBuffers BufferRange that specifies one or more GPU buffers (and offsets/sizes) holding control points for each motion keyframe used by the curve geometry.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setControlPointBuffers(const MTL4::BufferRange controlPointBuffers)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setControlPointBuffers_), controlPointBuffers);
}

/**
 * @brief Sets the number of control points used by the curve geometry descriptor.
 *
 * @param controlPointCount The number of control points.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setControlPointCount(NS::UInteger controlPointCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setControlPointCount_), controlPointCount);
}

/**
 * @brief Sets the attribute format used for control points in the motion curve geometry descriptor.
 *
 * @param controlPointFormat The attribute format to apply to each control point.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setControlPointFormat(MTL::AttributeFormat controlPointFormat)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setControlPointFormat_), controlPointFormat);
}

/**
 * @brief Set the byte stride between consecutive control points.
 *
 * @param controlPointStride Number of bytes from the start of one control point to the start of the next.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setControlPointStride(NS::UInteger controlPointStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setControlPointStride_), controlPointStride);
}

/**
 * @brief Set the curve basis used by this motion curve geometry descriptor.
 *
 * Specifies the mathematical basis (e.g., Bezier, BSpline) that defines how curve control points are interpreted for motion curve geometry.
 *
 * @param curveBasis The curve basis to apply to the descriptor.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setCurveBasis(MTL::CurveBasis curveBasis)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCurveBasis_), curveBasis);
}

/**
 * @brief Set the end-cap style used for curve segments in this geometry descriptor.
 *
 * @param curveEndCaps The end-cap mode to apply to curve segments.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setCurveEndCaps(MTL::CurveEndCaps curveEndCaps)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCurveEndCaps_), curveEndCaps);
}

/**
 * @brief Set the curve type used by this motion curve geometry descriptor.
 *
 * @param curveType The curve type to apply to the descriptor's curve primitives.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setCurveType(MTL::CurveType curveType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCurveType_), curveType);
}

/**
 * @brief Set the index buffer range used by the motion curve geometry.
 *
 * Associates a buffer range containing indices for the curve geometry with this descriptor.
 *
 * @param indexBuffer BufferRange specifying the buffer, offset and length of the index data.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setIndexBuffer(const MTL4::BufferRange indexBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIndexBuffer_), indexBuffer);
}

/**
 * @brief Set the index type used to interpret the descriptor's index buffer for curve geometry.
 *
 * @param indexType The index format to use (for example `MTL::IndexType::UInt16` or `MTL::IndexType::UInt32`).
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setIndexType(MTL::IndexType indexType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setIndexType_), indexType);
}

/**
 * @brief Set the radius buffers used by the motion curve geometry descriptor.
 *
 * Specifies one or more buffers containing per-control-point radius data for the curve across motion keyframes.
 *
 * @param radiusBuffers BufferRange describing the buffer(s) that hold radius values for the curve's control points.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setRadiusBuffers(const MTL4::BufferRange radiusBuffers)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRadiusBuffers_), radiusBuffers);
}

/**
 * @brief Sets the attribute format used for radius data on motion curve geometry.
 *
 * @param radiusFormat The attribute format to apply to the radius buffer.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setRadiusFormat(MTL::AttributeFormat radiusFormat)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRadiusFormat_), radiusFormat);
}

/**
 * @brief Sets the byte stride between successive radius elements for the radius buffer(s) of this motion curve geometry descriptor.
 *
 * @param radiusStride Byte stride, in bytes, between consecutive radius entries.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setRadiusStride(NS::UInteger radiusStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setRadiusStride_), radiusStride);
}

/**
 * @brief Sets the number of control points per curve segment for a motion curve geometry descriptor.
 *
 * @param segmentControlPointCount Number of control points in each curve segment.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setSegmentControlPointCount(NS::UInteger segmentControlPointCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSegmentControlPointCount_), segmentControlPointCount);
}

/**
 * @brief Set the number of segments for curve primitives in this motion curve geometry descriptor.
 *
 * @param segmentCount The total number of segments per curve to be used by the descriptor.
 */
_MTL_INLINE void MTL4::AccelerationStructureMotionCurveGeometryDescriptor::setSegmentCount(NS::UInteger segmentCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSegmentCount_), segmentCount);
}

/**
 * @brief Allocate a new InstanceAccelerationStructureDescriptor.
 *
 * @return MTL4::InstanceAccelerationStructureDescriptor* A newly allocated, uninitialized descriptor instance.
 */
_MTL_INLINE MTL4::InstanceAccelerationStructureDescriptor* MTL4::InstanceAccelerationStructureDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::InstanceAccelerationStructureDescriptor>(_MTL_PRIVATE_CLS(MTL4InstanceAccelerationStructureDescriptor));
}

/**
 * @brief Initializes the instance acceleration structure descriptor.
 *
 * Initializes the receiver and returns the initialized descriptor object.
 *
 * @return InstanceAccelerationStructureDescriptor* Pointer to the initialized descriptor.
 */
_MTL_INLINE MTL4::InstanceAccelerationStructureDescriptor* MTL4::InstanceAccelerationStructureDescriptor::init()
{
    return NS::Object::init<MTL4::InstanceAccelerationStructureDescriptor>();
}

/**
 * @brief Retrieves the number of instances configured for this instance acceleration structure descriptor.
 *
 * @return Number of instances contained in the descriptor.
 */
_MTL_INLINE NS::UInteger MTL4::InstanceAccelerationStructureDescriptor::instanceCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(instanceCount));
}

/**
 * @brief Provides the buffer range that contains the instance descriptors for this acceleration structure.
 *
 * @return MTL4::BufferRange The buffer range referencing the instance descriptor data.
 */
_MTL_INLINE MTL4::BufferRange MTL4::InstanceAccelerationStructureDescriptor::instanceDescriptorBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(instanceDescriptorBuffer));
}

/**
 * @brief Returns the byte stride used for each instance descriptor.
 *
 * @return The stride of the instance descriptor, in bytes.
 */
_MTL_INLINE NS::UInteger MTL4::InstanceAccelerationStructureDescriptor::instanceDescriptorStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(instanceDescriptorStride));
}

/**
 * @brief Obtains the instance descriptor layout used by this acceleration structure descriptor.
 *
 * @return MTL::AccelerationStructureInstanceDescriptorType The instance descriptor type. 
 */
_MTL_INLINE MTL::AccelerationStructureInstanceDescriptorType MTL4::InstanceAccelerationStructureDescriptor::instanceDescriptorType() const
{
    return Object::sendMessage<MTL::AccelerationStructureInstanceDescriptorType>(this, _MTL_PRIVATE_SEL(instanceDescriptorType));
}

/**
 * @brief Gets the layout used for instance transformation matrices.
 *
 * @return MTL::MatrixLayout The matrix layout used to interpret instance transformation matrices.
 */
_MTL_INLINE MTL::MatrixLayout MTL4::InstanceAccelerationStructureDescriptor::instanceTransformationMatrixLayout() const
{
    return Object::sendMessage<MTL::MatrixLayout>(this, _MTL_PRIVATE_SEL(instanceTransformationMatrixLayout));
}

/**
 * @brief Retrieves the buffer range containing per-instance motion transforms.
 *
 * The buffer range references the GPU memory that stores motion transform data used for instance-level motion in the acceleration structure.
 *
 * @return MTL4::BufferRange The buffer range for motion transforms, or an empty range if no buffer is set.
 */
_MTL_INLINE MTL4::BufferRange MTL4::InstanceAccelerationStructureDescriptor::motionTransformBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(motionTransformBuffer));
}

/**
 * @brief Retrieves the number of motion transforms configured for this instance acceleration structure descriptor.
 *
 * @return NS::UInteger The number of motion transforms set on the descriptor.
 */
_MTL_INLINE NS::UInteger MTL4::InstanceAccelerationStructureDescriptor::motionTransformCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(motionTransformCount));
}

/**
 * @brief Retrieves the byte stride between consecutive motion transform entries in the motion transform buffer.
 *
 * @return NS::UInteger The stride in bytes between successive motion transform entries.
 */
_MTL_INLINE NS::UInteger MTL4::InstanceAccelerationStructureDescriptor::motionTransformStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(motionTransformStride));
}

/**
 * @brief Retrieves the transform type used for per-instance motion transforms.
 *
 * @return MTL::TransformType The current transform type applied to instance motion transforms.
 */
_MTL_INLINE MTL::TransformType MTL4::InstanceAccelerationStructureDescriptor::motionTransformType() const
{
    return Object::sendMessage<MTL::TransformType>(this, _MTL_PRIVATE_SEL(motionTransformType));
}

/**
 * @brief Set the number of instances described by this instance acceleration structure descriptor.
 *
 * @param instanceCount The number of instances contained in the descriptor.
 */
_MTL_INLINE void MTL4::InstanceAccelerationStructureDescriptor::setInstanceCount(NS::UInteger instanceCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInstanceCount_), instanceCount);
}

/**
 * @brief Set the buffer range that contains instance descriptors for this descriptor.
 *
 * @param instanceDescriptorBuffer BufferRange describing the GPU buffer and range that holds instance descriptor entries used by the instance acceleration structure.
 */
_MTL_INLINE void MTL4::InstanceAccelerationStructureDescriptor::setInstanceDescriptorBuffer(const MTL4::BufferRange instanceDescriptorBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInstanceDescriptorBuffer_), instanceDescriptorBuffer);
}

/**
 * @brief Set the byte stride between consecutive instance descriptors.
 *
 * @param instanceDescriptorStride Number of bytes between the start of adjacent instance descriptors in the instance descriptor buffer.
 */
_MTL_INLINE void MTL4::InstanceAccelerationStructureDescriptor::setInstanceDescriptorStride(NS::UInteger instanceDescriptorStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInstanceDescriptorStride_), instanceDescriptorStride);
}

/**
 * @brief Sets the layout/type of instance descriptors for this instance acceleration structure.
 *
 * @param instanceDescriptorType The `MTL::AccelerationStructureInstanceDescriptorType` value that specifies the format and layout of instance descriptors stored in the instance descriptor buffer.
 */
_MTL_INLINE void MTL4::InstanceAccelerationStructureDescriptor::setInstanceDescriptorType(MTL::AccelerationStructureInstanceDescriptorType instanceDescriptorType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInstanceDescriptorType_), instanceDescriptorType);
}

/**
 * @brief Configure the memory layout used for instance transformation matrices.
 *
 * Sets the layout format that the descriptor will interpret for per-instance
 * transformation matrices when reading instance data.
 *
 * @param instanceTransformationMatrixLayout The matrix layout to use for instance transformation matrices.
 */
_MTL_INLINE void MTL4::InstanceAccelerationStructureDescriptor::setInstanceTransformationMatrixLayout(MTL::MatrixLayout instanceTransformationMatrixLayout)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInstanceTransformationMatrixLayout_), instanceTransformationMatrixLayout);
}

/**
 * @brief Sets the buffer range that contains per-instance motion transform data.
 *
 * The provided BufferRange specifies the GPU buffer and offset/size used as the source
 * of motion transformation matrices for instances in this acceleration structure.
 *
 * @param motionTransformBuffer BufferRange describing the buffer, offset, and length
 *                              where instance motion transforms are stored.
 */
_MTL_INLINE void MTL4::InstanceAccelerationStructureDescriptor::setMotionTransformBuffer(const MTL4::BufferRange motionTransformBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionTransformBuffer_), motionTransformBuffer);
}

/**
 * @brief Set the number of motion transforms for instances in the acceleration-structure descriptor.
 *
 * @param motionTransformCount Number of motion transforms to associate with each instance.
 */
_MTL_INLINE void MTL4::InstanceAccelerationStructureDescriptor::setMotionTransformCount(NS::UInteger motionTransformCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionTransformCount_), motionTransformCount);
}

/**
 * @brief Sets the byte stride between consecutive motion transform entries.
 *
 * Sets the stride, in bytes, used to step between motion transform entries in the
 * motion transform buffer for this instance acceleration structure descriptor.
 *
 * @param motionTransformStride Byte stride between consecutive motion transform entries.
 */
_MTL_INLINE void MTL4::InstanceAccelerationStructureDescriptor::setMotionTransformStride(NS::UInteger motionTransformStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionTransformStride_), motionTransformStride);
}

/**
 * @brief Sets the transform type used for per-instance motion transforms.
 *
 * Specifies how motion transform data in the associated motion transform buffer(s)
 * is interpreted when building or updating the instance acceleration structure.
 *
 * @param motionTransformType The transform type to use for motion transforms.
 */
_MTL_INLINE void MTL4::InstanceAccelerationStructureDescriptor::setMotionTransformType(MTL::TransformType motionTransformType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionTransformType_), motionTransformType);
}

/**
 * @brief Allocate a new IndirectInstanceAccelerationStructureDescriptor instance.
 *
 * @return MTL4::IndirectInstanceAccelerationStructureDescriptor* A newly allocated descriptor object.
 */
_MTL_INLINE MTL4::IndirectInstanceAccelerationStructureDescriptor* MTL4::IndirectInstanceAccelerationStructureDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::IndirectInstanceAccelerationStructureDescriptor>(_MTL_PRIVATE_CLS(MTL4IndirectInstanceAccelerationStructureDescriptor));
}

/**
 * @brief Initialize an IndirectInstanceAccelerationStructureDescriptor instance.
 *
 * Performs object initialization and returns the initialized descriptor.
 *
 * @return IndirectInstanceAccelerationStructureDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL4::IndirectInstanceAccelerationStructureDescriptor* MTL4::IndirectInstanceAccelerationStructureDescriptor::init()
{
    return NS::Object::init<MTL4::IndirectInstanceAccelerationStructureDescriptor>();
}

/**
 * @brief Gets the buffer range that contains the instance count for an indirect instance acceleration structure.
 *
 * @return MTL4::BufferRange The buffer range containing the instance count used by the indirect instance acceleration structure.
 */
_MTL_INLINE MTL4::BufferRange MTL4::IndirectInstanceAccelerationStructureDescriptor::instanceCountBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(instanceCountBuffer));
}

/**
 * @brief Retrieves the buffer range that holds instance descriptors for the indirect instance acceleration structure.
 *
 * @return MTL4::BufferRange The buffer range containing instance descriptor data (buffer reference and offset/length).
 */
_MTL_INLINE MTL4::BufferRange MTL4::IndirectInstanceAccelerationStructureDescriptor::instanceDescriptorBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(instanceDescriptorBuffer));
}

/**
 * @brief Retrieve the byte stride between consecutive instance descriptors.
 *
 * @return NS::UInteger The stride, in bytes, between consecutive instance descriptors.
 */
_MTL_INLINE NS::UInteger MTL4::IndirectInstanceAccelerationStructureDescriptor::instanceDescriptorStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(instanceDescriptorStride));
}

/**
 * @brief Gets the instance descriptor type used by this indirect instance acceleration structure.
 *
 * @return MTL::AccelerationStructureInstanceDescriptorType The instance descriptor type for the acceleration structure.
 */
_MTL_INLINE MTL::AccelerationStructureInstanceDescriptorType MTL4::IndirectInstanceAccelerationStructureDescriptor::instanceDescriptorType() const
{
    return Object::sendMessage<MTL::AccelerationStructureInstanceDescriptorType>(this, _MTL_PRIVATE_SEL(instanceDescriptorType));
}

/**
 * @brief Obtains the layout used for instance transformation matrices.
 *
 * @return MTL::MatrixLayout The matrix layout that describes how instance transformation matrices are stored.
 */
_MTL_INLINE MTL::MatrixLayout MTL4::IndirectInstanceAccelerationStructureDescriptor::instanceTransformationMatrixLayout() const
{
    return Object::sendMessage<MTL::MatrixLayout>(this, _MTL_PRIVATE_SEL(instanceTransformationMatrixLayout));
}

/**
 * @brief Returns the maximum number of instances allowed by this descriptor.
 *
 * @return NS::UInteger The configured maximum instance count for the indirect instance acceleration structure descriptor.
 */
_MTL_INLINE NS::UInteger MTL4::IndirectInstanceAccelerationStructureDescriptor::maxInstanceCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxInstanceCount));
}

/**
 * @brief Maximum number of motion transforms allowed for instances in this descriptor.
 *
 * @return NS::UInteger The maximum motion transform count for instances.
 */
_MTL_INLINE NS::UInteger MTL4::IndirectInstanceAccelerationStructureDescriptor::maxMotionTransformCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(maxMotionTransformCount));
}

/**
 * @brief Returns the buffer range that contains per-instance motion transform data.
 *
 * The buffer range identifies the GPU memory region used to store motion transforms
 * for instances referenced by this indirect instance acceleration structure descriptor.
 *
 * @return MTL4::BufferRange The motion transform buffer range. If no motion transforms
 * are set, the returned range will be empty. 
 */
_MTL_INLINE MTL4::BufferRange MTL4::IndirectInstanceAccelerationStructureDescriptor::motionTransformBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(motionTransformBuffer));
}

/**
 * @brief Gets the buffer range containing per-instance motion transform counts.
 *
 * Each element in the returned buffer range specifies the number of motion transforms for the corresponding instance.
 *
 * @return MTL4::BufferRange Buffer and range that contain per-instance motion transform counts.
 */
_MTL_INLINE MTL4::BufferRange MTL4::IndirectInstanceAccelerationStructureDescriptor::motionTransformCountBuffer() const
{
    return Object::sendMessage<MTL4::BufferRange>(this, _MTL_PRIVATE_SEL(motionTransformCountBuffer));
}

/**
 * @brief Retrieves the byte stride between consecutive motion transform entries.
 *
 * @return NS::UInteger The stride, in bytes, between successive motion transform entries.
 */
_MTL_INLINE NS::UInteger MTL4::IndirectInstanceAccelerationStructureDescriptor::motionTransformStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(motionTransformStride));
}

/**
 * @brief Query the transform type used for motion transforms.
 *
 * @return The transform type applied to motion transform buffers.
 */
_MTL_INLINE MTL::TransformType MTL4::IndirectInstanceAccelerationStructureDescriptor::motionTransformType() const
{
    return Object::sendMessage<MTL::TransformType>(this, _MTL_PRIVATE_SEL(motionTransformType));
}

/**
 * @brief Sets the buffer that provides the indirect instance count for the descriptor.
 *
 * The provided buffer range is used to read the number of instances when building or updating
 * an indirect instance acceleration structure.
 *
 * @param instanceCountBuffer Buffer range containing the instance count value(s).
 */
_MTL_INLINE void MTL4::IndirectInstanceAccelerationStructureDescriptor::setInstanceCountBuffer(const MTL4::BufferRange instanceCountBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInstanceCountBuffer_), instanceCountBuffer);
}

/**
 * @brief Sets the buffer range that contains instance descriptors for the acceleration structure.
 *
 * @param instanceDescriptorBuffer BufferRange specifying the buffer and byte range holding the instance descriptor data.
 */
_MTL_INLINE void MTL4::IndirectInstanceAccelerationStructureDescriptor::setInstanceDescriptorBuffer(const MTL4::BufferRange instanceDescriptorBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInstanceDescriptorBuffer_), instanceDescriptorBuffer);
}

/**
 * @brief Set the byte stride between consecutive instance descriptors in the instance descriptor buffer.
 *
 * @param instanceDescriptorStride Number of bytes between the start of one instance descriptor and the next.
 */
_MTL_INLINE void MTL4::IndirectInstanceAccelerationStructureDescriptor::setInstanceDescriptorStride(NS::UInteger instanceDescriptorStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInstanceDescriptorStride_), instanceDescriptorStride);
}

/**
 * @brief Set the descriptor type used for instance descriptors in this indirect instance acceleration structure.
 *
 * @param instanceDescriptorType The AccelerationStructureInstanceDescriptorType value that determines the format/layout of instance descriptors.
 */
_MTL_INLINE void MTL4::IndirectInstanceAccelerationStructureDescriptor::setInstanceDescriptorType(MTL::AccelerationStructureInstanceDescriptorType instanceDescriptorType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInstanceDescriptorType_), instanceDescriptorType);
}

/**
 * @brief Set the layout used for instance transformation matrices.
 *
 * Configures how transformation matrices for instances are laid out in memory when reading
 * instance descriptor transformation data.
 *
 * @param instanceTransformationMatrixLayout The matrix layout to use for instance transformations.
 */
_MTL_INLINE void MTL4::IndirectInstanceAccelerationStructureDescriptor::setInstanceTransformationMatrixLayout(MTL::MatrixLayout instanceTransformationMatrixLayout)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setInstanceTransformationMatrixLayout_), instanceTransformationMatrixLayout);
}

/**
 * @brief Sets the maximum number of instances allowed for this indirect instance acceleration structure.
 *
 * @param maxInstanceCount The maximum number of instances the descriptor may reference.
 */
_MTL_INLINE void MTL4::IndirectInstanceAccelerationStructureDescriptor::setMaxInstanceCount(NS::UInteger maxInstanceCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxInstanceCount_), maxInstanceCount);
}

/**
 * @brief Set the maximum number of motion transforms for the indirect instance acceleration structure.
 *
 * @param maxMotionTransformCount The maximum number of motion transforms allowed.
 */
_MTL_INLINE void MTL4::IndirectInstanceAccelerationStructureDescriptor::setMaxMotionTransformCount(NS::UInteger maxMotionTransformCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMaxMotionTransformCount_), maxMotionTransformCount);
}

/**
 * @brief Sets the buffer range containing per-instance motion transforms.
 *
 * Configures the descriptor to use the provided BufferRange as the source of motion transform data for instances.
 *
 * @param motionTransformBuffer BufferRange that references the buffer and range holding motion transforms.
 */
_MTL_INLINE void MTL4::IndirectInstanceAccelerationStructureDescriptor::setMotionTransformBuffer(const MTL4::BufferRange motionTransformBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionTransformBuffer_), motionTransformBuffer);
}

/**
 * @brief Set the buffer range that supplies per-instance motion transform counts.
 *
 * The buffer specified by motionTransformCountBuffer is used to provide, for each instance,
 * the number of motion transforms associated with that instance.
 *
 * @param motionTransformCountBuffer BufferRange describing the buffer and range containing per-instance motion transform counts.
 */
_MTL_INLINE void MTL4::IndirectInstanceAccelerationStructureDescriptor::setMotionTransformCountBuffer(const MTL4::BufferRange motionTransformCountBuffer)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionTransformCountBuffer_), motionTransformCountBuffer);
}

/**
 * @brief Sets the byte stride between consecutive motion transform entries.
 *
 * @param motionTransformStride Byte distance, in bytes, from the start of one motion transform to the start of the next.
 */
_MTL_INLINE void MTL4::IndirectInstanceAccelerationStructureDescriptor::setMotionTransformStride(NS::UInteger motionTransformStride)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionTransformStride_), motionTransformStride);
}

/**
 * @brief Set the transform type used for per-instance motion transforms.
 *
 * Specifies how motion transforms are represented for instances in the indirect instance
 * acceleration structure (for example, matrix-based or dual-quaternion transforms).
 *
 * @param motionTransformType The transform representation to use for motion transforms.
 */
_MTL_INLINE void MTL4::IndirectInstanceAccelerationStructureDescriptor::setMotionTransformType(MTL::TransformType motionTransformType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setMotionTransformType_), motionTransformType);
}