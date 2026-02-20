//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLArgument.hpp
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
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLTensor.hpp"
#include "MTLTexture.hpp"

namespace MTL
{
class Argument;
class ArrayType;
class PointerType;
class StructMember;
class StructType;
class TensorExtents;
class TensorReferenceType;
class TextureReferenceType;
class Type;
_MTL_ENUM(NS::UInteger, IndexType) {
    IndexTypeUInt16 = 0,
    IndexTypeUInt32 = 1,
};

_MTL_ENUM(NS::Integer, BindingType) {
    BindingTypeBuffer = 0,
    BindingTypeThreadgroupMemory = 1,
    BindingTypeTexture = 2,
    BindingTypeSampler = 3,
    BindingTypeImageblockData = 16,
    BindingTypeImageblock = 17,
    BindingTypeVisibleFunctionTable = 24,
    BindingTypePrimitiveAccelerationStructure = 25,
    BindingTypeInstanceAccelerationStructure = 26,
    BindingTypeIntersectionFunctionTable = 27,
    BindingTypeObjectPayload = 34,
    BindingTypeTensor = 37,
};

_MTL_ENUM(NS::UInteger, ArgumentType) {
    ArgumentTypeBuffer = 0,
    ArgumentTypeThreadgroupMemory = 1,
    ArgumentTypeTexture = 2,
    ArgumentTypeSampler = 3,
    ArgumentTypeImageblockData = 16,
    ArgumentTypeImageblock = 17,
    ArgumentTypeVisibleFunctionTable = 24,
    ArgumentTypePrimitiveAccelerationStructure = 25,
    ArgumentTypeInstanceAccelerationStructure = 26,
    ArgumentTypeIntersectionFunctionTable = 27,
};

/**
 * @brief Specifies read/write access semantics for bindings and arguments.
 *
 * Defines canonical access levels for resources used by shaders:
 * read-only, read-write, and write-only. Alias names for argument
 * access levels are provided for compatibility.
 */

/**
 * @brief Abstract representation of a type in the shader reflection system.
 *
 * Provides access to the underlying data type information for a reflected
 * type object.
 */

/**
 * @brief Description of a single member within a StructType.
 *
 * Exposes the member's name, offset, data type, and any nested type
 * references (array, pointer, struct, texture-reference, or tensor-reference),
 * along with the argument index when the member corresponds to an argument.
 */

/**
 * @brief Representation of a C-style struct type used in shader interfaces.
 *
 * Allows lookup of struct members by name and enumeration of all members.
 */

/**
 * @brief Representation of an array type in the shader reflection system.
 *
 * Exposes element type, element-specific type views (array, pointer, struct,
 * texture-reference, tensor-reference), array length and memory stride, and
 * the argument index stride for arrays of arguments.
 */

/**
 * @brief Description of a pointer type used by shader resources.
 *
 * Provides the pointer's access permissions, alignment and data size, and
 * views into the pointed-to element (primitive data type, struct, or array).
 * Also indicates whether the pointed element represents an argument buffer.
 */

/**
 * @brief Reference descriptor for a texture value used in shader interfaces.
 *
 * Describes the texture's type and data type, whether it represents a depth
 * texture, and the access permissions for the texture reference.
 */

/**
 * @brief Reference descriptor for a tensor value used in shader interfaces.
 *
 * Describes the tensor's data type, index type used for indexing, its
 * dimensional extents, and the access permissions for the tensor reference.
 */

/**
 * @brief Reflection representation of a function or kernel argument.
 *
 * Describes the argument's kind, name, index, access permissions, activity
 * status, and type-specific metadata such as buffer/texture/tensor details,
 * array length, and threadgroup memory properties.
 */

/**
 * @brief Abstract descriptor of a binding within a resource region.
 *
 * Provides the binding index, name, kind, access permissions, and usage
 * status. Includes deprecated compatibility aliases for older boolean flags.
 */

/**
 * @brief Binding specialization for buffer resources.
 *
 * Exposes buffer-specific metadata including alignment, data size,
 * data type, and pointer/struct views of the buffer's element.
 */

/**
 * @brief Binding specialization for threadgroup memory resources.
 *
 * Provides alignment and data size information for threadgroup memory.
 */

/**
 * @brief Binding specialization for texture resources.
 *
 * Describes texture-specific metadata including array length, whether it is
 * a depth texture, the texture data type, and the texture dimensionality.
 */

/**
 * @brief Binding specialization for object payload data.
 *
 * Provides alignment and data size for object-payload bindings.
 */

/**
 * @brief Binding specialization for tensor resources.
 *
 * Describes tensor binding dimensions, the index type used for addressing,
 * and the tensor's data type.
_MTL_ENUM(NS::UInteger, BindingAccess) {
    BindingAccessReadOnly = 0,
    BindingAccessReadWrite = 1,
    BindingAccessWriteOnly = 2,
    ArgumentAccessReadOnly = 0,
    ArgumentAccessReadWrite = 1,
    ArgumentAccessWriteOnly = 2,
};

class Type : public NS::Referencing<Type>
{
public:
    static Type* alloc();

    DataType     dataType() const;

    Type*        init();
};
class StructMember : public NS::Referencing<StructMember>
{
public:
    static StructMember*  alloc();

    NS::UInteger          argumentIndex() const;

    ArrayType*            arrayType();

    DataType              dataType() const;

    StructMember*         init();

    NS::String*           name() const;

    NS::UInteger          offset() const;

    PointerType*          pointerType();

    StructType*           structType();

    TensorReferenceType*  tensorReferenceType();

    TextureReferenceType* textureReferenceType();
};
class StructType : public NS::Referencing<StructType, Type>
{
public:
    static StructType* alloc();

    StructType*        init();

    StructMember*      memberByName(const NS::String* name);

    NS::Array*         members() const;
};
class ArrayType : public NS::Referencing<ArrayType, Type>
{
public:
    static ArrayType*     alloc();

    NS::UInteger          argumentIndexStride() const;

    NS::UInteger          arrayLength() const;

    ArrayType*            elementArrayType();

    PointerType*          elementPointerType();

    StructType*           elementStructType();

    TensorReferenceType*  elementTensorReferenceType();

    TextureReferenceType* elementTextureReferenceType();

    DataType              elementType() const;

    ArrayType*            init();

    NS::UInteger          stride() const;
};
class PointerType : public NS::Referencing<PointerType, Type>
{
public:
    BindingAccess       access() const;

    NS::UInteger        alignment() const;

    static PointerType* alloc();

    NS::UInteger        dataSize() const;

    ArrayType*          elementArrayType();

    bool                elementIsArgumentBuffer() const;

    StructType*         elementStructType();

    DataType            elementType() const;

    PointerType*        init();
};
class TextureReferenceType : public NS::Referencing<TextureReferenceType, Type>
{
public:
    BindingAccess                access() const;

    static TextureReferenceType* alloc();

    TextureReferenceType*        init();

    bool                         isDepthTexture() const;

    DataType                     textureDataType() const;

    TextureType                  textureType() const;
};
class TensorReferenceType : public NS::Referencing<TensorReferenceType, Type>
{
public:
    BindingAccess               access() const;

    static TensorReferenceType* alloc();

    TensorExtents*              dimensions() const;

    DataType                    indexType() const;

    TensorReferenceType*        init();

    TensorDataType              tensorDataType() const;
};
class Argument : public NS::Referencing<Argument>
{
public:
    BindingAccess access() const;

    [[deprecated("please use isActive instead")]]
    bool             active() const;

    static Argument* alloc();

    NS::UInteger     arrayLength() const;

    NS::UInteger     bufferAlignment() const;

    NS::UInteger     bufferDataSize() const;

    DataType         bufferDataType() const;

    PointerType*     bufferPointerType() const;

    StructType*      bufferStructType() const;

    NS::UInteger     index() const;

    Argument*        init();

    bool             isActive() const;

    bool             isDepthTexture() const;

    NS::String*      name() const;

    DataType         textureDataType() const;

    TextureType      textureType() const;

    NS::UInteger     threadgroupMemoryAlignment() const;

    NS::UInteger     threadgroupMemoryDataSize() const;

    ArgumentType     type() const;
};
class Binding : public NS::Referencing<Binding>
{
public:
    BindingAccess access() const;

    [[deprecated("please use isArgument instead")]]
    bool         argument() const;

    NS::UInteger index() const;

    bool         isArgument() const;

    bool         isUsed() const;

    NS::String*  name() const;

    BindingType  type() const;

    [[deprecated("please use isUsed instead")]]
    bool used() const;
};
class BufferBinding : public NS::Referencing<BufferBinding, Binding>
{
public:
    NS::UInteger bufferAlignment() const;

    NS::UInteger bufferDataSize() const;

    DataType     bufferDataType() const;

    PointerType* bufferPointerType() const;

    StructType*  bufferStructType() const;
};
class ThreadgroupBinding : public NS::Referencing<ThreadgroupBinding, Binding>
{
public:
    NS::UInteger threadgroupMemoryAlignment() const;

    NS::UInteger threadgroupMemoryDataSize() const;
};
class TextureBinding : public NS::Referencing<TextureBinding, Binding>
{
public:
    NS::UInteger arrayLength() const;

    [[deprecated("please use isDepthTexture instead")]]
    bool        depthTexture() const;
    bool        isDepthTexture() const;

    DataType    textureDataType() const;

    TextureType textureType() const;
};
class ObjectPayloadBinding : public NS::Referencing<ObjectPayloadBinding, Binding>
{
public:
    NS::UInteger objectPayloadAlignment() const;

    NS::UInteger objectPayloadDataSize() const;
};
class TensorBinding : public NS::Referencing<TensorBinding, Binding>
{
public:
    TensorExtents* dimensions() const;

    DataType       indexType() const;

    TensorDataType tensorDataType() const;
};

}
/**
 * @brief Allocates a new Type object.
 *
 * Allocates and returns a newly created MTL::Type instance ready for initialization.
 *
 * @return MTL::Type* Pointer to the newly allocated Type instance.
 */
_MTL_INLINE MTL::Type* MTL::Type::alloc()
{
    return NS::Object::alloc<MTL::Type>(_MTL_PRIVATE_CLS(MTLType));
}

/**
 * @brief Returns the data-type classification represented by this Type.
 *
 * @return MTL::DataType The underlying data type of the Type instance.
 */
_MTL_INLINE MTL::DataType MTL::Type::dataType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(dataType));
}

/**
 * @brief Initializes a newly allocated MTL::Type instance.
 *
 * @return MTL::Type* Pointer to the initialized Type instance, or `nullptr` on failure.
 */
_MTL_INLINE MTL::Type* MTL::Type::init()
{
    return NS::Object::init<MTL::Type>();
}

/**
 * @brief Allocates a new MTL::StructMember instance.
 *
 * @return MTL::StructMember* A newly allocated StructMember object.
 */
_MTL_INLINE MTL::StructMember* MTL::StructMember::alloc()
{
    return NS::Object::alloc<MTL::StructMember>(_MTL_PRIVATE_CLS(MTLStructMember));
}

/**
 * @brief Retrieve the argument index associated with this struct member.
 *
 * @return NS::UInteger The argument index of the struct member.
 */
_MTL_INLINE NS::UInteger MTL::StructMember::argumentIndex() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(argumentIndex));
}

/**
 * @brief Retrieves the array type associated with this struct member.
 *
 * If the struct member represents an array, returns its ArrayType; otherwise returns `nullptr`.
 *
 * @return MTL::ArrayType* Pointer to the member's ArrayType, or `nullptr` if the member is not an array.
 */
_MTL_INLINE MTL::ArrayType* MTL::StructMember::arrayType()
{
    return Object::sendMessage<MTL::ArrayType*>(this, _MTL_PRIVATE_SEL(arrayType));
}

/**
 * @brief Retrieve the declared classification of this struct member.
 *
 * @return MTL::DataType The declared data type of the struct member.
 */
_MTL_INLINE MTL::DataType MTL::StructMember::dataType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(dataType));
}

/**
 * @brief Initialize a newly allocated StructMember instance.
 *
 * @return MTL::StructMember* Pointer to the initialized StructMember.
 */
_MTL_INLINE MTL::StructMember* MTL::StructMember::init()
{
    return NS::Object::init<MTL::StructMember>();
}

/**
 * @brief Retrieves the name of this struct member.
 *
 * @return NS::String* The member's name as an `NS::String` object, or `nullptr` if no name is available.
 */
_MTL_INLINE NS::String* MTL::StructMember::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Byte offset of the member within its parent struct.
 *
 * @return NS::UInteger Offset in bytes from the start of the containing struct.
 */
_MTL_INLINE NS::UInteger MTL::StructMember::offset() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(offset));
}

/**
 * @brief Retrieve the pointer type associated with this struct member.
 *
 * @return MTL::PointerType* The pointer type for the member, or `nullptr` if the member is not a pointer type.
 */
_MTL_INLINE MTL::PointerType* MTL::StructMember::pointerType()
{
    return Object::sendMessage<MTL::PointerType*>(this, _MTL_PRIVATE_SEL(pointerType));
}

/**
 * @brief Get the StructType that contains this member.
 *
 * @return MTL::StructType* The parent StructType for this member, or `nullptr` if the member is not part of a struct.
 */
_MTL_INLINE MTL::StructType* MTL::StructMember::structType()
{
    return Object::sendMessage<MTL::StructType*>(this, _MTL_PRIVATE_SEL(structType));
}

/**
 * @brief Get the tensor reference type associated with this struct member.
 *
 * @return MTL::TensorReferenceType* The tensor reference type for the member, or `nullptr` if the member is not a tensor reference.
 */
_MTL_INLINE MTL::TensorReferenceType* MTL::StructMember::tensorReferenceType()
{
    return Object::sendMessage<MTL::TensorReferenceType*>(this, _MTL_PRIVATE_SEL(tensorReferenceType));
}

/**
 * @brief Retrieves the TextureReferenceType for this struct member when the member is a texture reference.
 *
 * @return MTL::TextureReferenceType* The texture reference type for the member, or `nullptr` if the member is not a texture reference.
 */
_MTL_INLINE MTL::TextureReferenceType* MTL::StructMember::textureReferenceType()
{
    return Object::sendMessage<MTL::TextureReferenceType*>(this, _MTL_PRIVATE_SEL(textureReferenceType));
}

/**
 * @brief Allocate a new StructType object.
 *
 * @return MTL::StructType* Pointer to a newly allocated, uninitialized StructType. Call `init()` on the returned object before use.
 */
_MTL_INLINE MTL::StructType* MTL::StructType::alloc()
{
    return NS::Object::alloc<MTL::StructType>(_MTL_PRIVATE_CLS(MTLStructType));
}

/**
 * @brief Initializes a StructType instance.
 *
 * @return MTL::StructType* Pointer to the initialized StructType.
 */
_MTL_INLINE MTL::StructType* MTL::StructType::init()
{
    return NS::Object::init<MTL::StructType>();
}

/**
 * @brief Retrieves a struct member by its name.
 *
 * @param name The name of the member to look up.
 * @return MTL::StructMember* Pointer to the matching StructMember, or `nullptr` if no member with the given name exists.
 */
_MTL_INLINE MTL::StructMember* MTL::StructType::memberByName(const NS::String* name)
{
    return Object::sendMessage<MTL::StructMember*>(this, _MTL_PRIVATE_SEL(memberByName_), name);
}

/**
 * @brief Retrieve the members of this struct type.
 *
 * @return NS::Array* An array of StructMember* objects describing the members of the struct; the array may be empty.
 */
_MTL_INLINE NS::Array* MTL::StructType::members() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(members));
}

/**
 * @brief Allocate a new ArrayType object.
 *
 * @return Pointer to the allocated ArrayType.
 */
_MTL_INLINE MTL::ArrayType* MTL::ArrayType::alloc()
{
    return NS::Object::alloc<MTL::ArrayType>(_MTL_PRIVATE_CLS(MTLArrayType));
}

/**
 * @brief Retrieves the stride, in argument indices, between consecutive elements of this array type.
 *
 * @return NS::UInteger The number of argument index slots to advance to reach the next element.
 */
_MTL_INLINE NS::UInteger MTL::ArrayType::argumentIndexStride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(argumentIndexStride));
}

/**
 * @brief Retrieves the number of elements described by this array type.
 *
 * @return NS::UInteger The length (number of elements) of the array type.
 */
_MTL_INLINE NS::UInteger MTL::ArrayType::arrayLength() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(arrayLength));
}

/**
 * @brief Retrieve the element's array type when the array's element itself is an array.
 *
 * @return MTL::ArrayType* Pointer to the element's ArrayType, or `nullptr` if the element is not an array.
 */
_MTL_INLINE MTL::ArrayType* MTL::ArrayType::elementArrayType()
{
    return Object::sendMessage<MTL::ArrayType*>(this, _MTL_PRIVATE_SEL(elementArrayType));
}

/**
 * @brief Returns the pointer type of the array's element.
 *
 * @return MTL::PointerType* PointerType representing the element's pointer type, or `nullptr` if the element is not a pointer type.
 */
_MTL_INLINE MTL::PointerType* MTL::ArrayType::elementPointerType()
{
    return Object::sendMessage<MTL::PointerType*>(this, _MTL_PRIVATE_SEL(elementPointerType));
}

/**
 * @brief Retrieves the struct type of this array's element.
 *
 * Returns the StructType that describes the array element when the element is a struct; returns `nullptr` if the element is not a struct type.
 *
 * @return MTL::StructType* The element's StructType, or `nullptr` if none.
 */
_MTL_INLINE MTL::StructType* MTL::ArrayType::elementStructType()
{
    return Object::sendMessage<MTL::StructType*>(this, _MTL_PRIVATE_SEL(elementStructType));
}

/**
 * @brief Retrieve the tensor reference type for the array element.
 *
 * Returns the element's TensorReferenceType when the array's element is a tensor reference; otherwise returns `nullptr`.
 *
 * @return MTL::TensorReferenceType* The tensor reference type for the element, or `nullptr` if the element is not a tensor reference.
 */
_MTL_INLINE MTL::TensorReferenceType* MTL::ArrayType::elementTensorReferenceType()
{
    return Object::sendMessage<MTL::TensorReferenceType*>(this, _MTL_PRIVATE_SEL(elementTensorReferenceType));
}

/**
 * @brief Get the texture reference type of the array element.
 *
 * @return MTL::TextureReferenceType* The texture reference type for the element, or `nullptr` if the element is not a texture reference.
 */
_MTL_INLINE MTL::TextureReferenceType* MTL::ArrayType::elementTextureReferenceType()
{
    return Object::sendMessage<MTL::TextureReferenceType*>(this, _MTL_PRIVATE_SEL(elementTextureReferenceType));
}

/**
 * @brief Retrieves the data type of elements contained by this array type.
 *
 * @return MTL::DataType The data type of the array's element. 
 */
_MTL_INLINE MTL::DataType MTL::ArrayType::elementType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(elementType));
}

/**
 * @brief Initialize this ArrayType instance.
 *
 * @return MTL::ArrayType* Pointer to the initialized ArrayType instance, or nullptr if initialization fails.
 */
_MTL_INLINE MTL::ArrayType* MTL::ArrayType::init()
{
    return NS::Object::init<MTL::ArrayType>();
}

/**
 * @brief Gets the byte stride between consecutive elements of the array type.
 *
 * @return NS::UInteger Number of bytes from the start of one element to the start of the next.
 */
_MTL_INLINE NS::UInteger MTL::ArrayType::stride() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(stride));
}

/**
 * @brief Retrieve the binding access for this pointer type.
 *
 * @return MTL::BindingAccess The access permissions (read/write/none) associated with the pointer type.
 */
_MTL_INLINE MTL::BindingAccess MTL::PointerType::access() const
{
    return Object::sendMessage<MTL::BindingAccess>(this, _MTL_PRIVATE_SEL(access));
}

/**
 * @brief Query the alignment, in bytes, required for the pointed-to data.
 *
 * @return NS::UInteger Alignment, in bytes, of the data referenced by this pointer type.
 */
_MTL_INLINE NS::UInteger MTL::PointerType::alignment() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(alignment));
}

/**
 * @brief Allocate a new PointerType instance.
 *
 * @return MTL::PointerType* Newly allocated PointerType object, or nullptr on allocation failure.
 */
_MTL_INLINE MTL::PointerType* MTL::PointerType::alloc()
{
    return NS::Object::alloc<MTL::PointerType>(_MTL_PRIVATE_CLS(MTLPointerType));
}

/**
 * @brief Query the size, in bytes, of the data referenced by this pointer type.
 *
 * @return NS::UInteger Size in bytes of the pointed-to data.
 */
_MTL_INLINE NS::UInteger MTL::PointerType::dataSize() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(dataSize));
}

/**
 * Retrieve the ArrayType describing the element referenced by this pointer if that element is an array.
 *
 * @return MTL::ArrayType* The ArrayType for the pointed-to element, or `nullptr` if the element is not an array.
 */
_MTL_INLINE MTL::ArrayType* MTL::PointerType::elementArrayType()
{
    return Object::sendMessage<MTL::ArrayType*>(this, _MTL_PRIVATE_SEL(elementArrayType));
}

/**
 * @brief Indicates whether the pointed-to element is an argument buffer.
 *
 * @return `true` if the element referenced by this pointer type is an argument buffer, `false` otherwise.
 */
_MTL_INLINE bool MTL::PointerType::elementIsArgumentBuffer() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(elementIsArgumentBuffer));
}

/**
 * @brief Gets the struct type of the pointer's pointed-to element.
 *
 * @return MTL::StructType* The StructType representing the element type, or `nullptr` if the element is not a struct.
 */
_MTL_INLINE MTL::StructType* MTL::PointerType::elementStructType()
{
    return Object::sendMessage<MTL::StructType*>(this, _MTL_PRIVATE_SEL(elementStructType));
}

/**
 * @brief Returns the data type of the element pointed to by this pointer type.
 *
 * @return MTL::DataType The `DataType` of the pointer's element.
 */
_MTL_INLINE MTL::DataType MTL::PointerType::elementType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(elementType));
}

/**
 * @brief Initializes a PointerType instance.
 *
 * @return MTL::PointerType* The initialized `PointerType` instance (self) or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::PointerType* MTL::PointerType::init()
{
    return NS::Object::init<MTL::PointerType>();
}

/**
 * @brief Get the access permissions for this texture reference.
 *
 * @return MTL::BindingAccess The access level of the texture reference: `BindingAccessReadOnly`, `BindingAccessReadWrite`, or `BindingAccessWriteOnly`.
 */
_MTL_INLINE MTL::BindingAccess MTL::TextureReferenceType::access() const
{
    return Object::sendMessage<MTL::BindingAccess>(this, _MTL_PRIVATE_SEL(access));
}

/**
 * @brief Allocates a new TextureReferenceType instance.
 *
 * @return MTL::TextureReferenceType* Pointer to the newly allocated TextureReferenceType.
 */
_MTL_INLINE MTL::TextureReferenceType* MTL::TextureReferenceType::alloc()
{
    return NS::Object::alloc<MTL::TextureReferenceType>(_MTL_PRIVATE_CLS(MTLTextureReferenceType));
}

/**
 * @brief Initialize a TextureReferenceType instance.
 *
 * @return MTL::TextureReferenceType* Pointer to the initialized TextureReferenceType instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::TextureReferenceType* MTL::TextureReferenceType::init()
{
    return NS::Object::init<MTL::TextureReferenceType>();
}

/**
 * @brief Indicates whether the texture reference represents a depth texture.
 *
 * @return `true` if the texture reference is a depth texture, `false` otherwise.
 */
_MTL_INLINE bool MTL::TextureReferenceType::isDepthTexture() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isDepthTexture));
}

/**
 * @brief Obtain the data type used by the referenced texture.
 *
 * @return MTL::DataType Describes the element/data format of the texture reference.
 */
_MTL_INLINE MTL::DataType MTL::TextureReferenceType::textureDataType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(textureDataType));
}

/**
 * @brief The texture type referenced by this TextureReferenceType.
 *
 * @return MTL::TextureType The referenced texture's dimensionality (for example `TextureType2D`, `TextureType3D`, `TextureTypeCube`).
 */
_MTL_INLINE MTL::TextureType MTL::TextureReferenceType::textureType() const
{
    return Object::sendMessage<MTL::TextureType>(this, _MTL_PRIVATE_SEL(textureType));
}

/**
 * @brief Get the access permissions for this tensor reference.
 *
 * @return MTL::BindingAccess The access mode for the tensor reference: `BindingAccessReadOnly`, `BindingAccessReadWrite`, or `BindingAccessWriteOnly`.
 */
_MTL_INLINE MTL::BindingAccess MTL::TensorReferenceType::access() const
{
    return Object::sendMessage<MTL::BindingAccess>(this, _MTL_PRIVATE_SEL(access));
}

/**
 * @brief Allocates a new TensorReferenceType instance.
 *
 * @return MTL::TensorReferenceType* A newly allocated TensorReferenceType instance.
 */
_MTL_INLINE MTL::TensorReferenceType* MTL::TensorReferenceType::alloc()
{
    return NS::Object::alloc<MTL::TensorReferenceType>(_MTL_PRIVATE_CLS(MTLTensorReferenceType));
}

/**
 * @brief Retrieves the extents (dimensions) of this tensor reference type.
 *
 * @return MTL::TensorExtents* An object describing the tensor's dimensions, or `nullptr` if not applicable.
 */
_MTL_INLINE MTL::TensorExtents* MTL::TensorReferenceType::dimensions() const
{
    return Object::sendMessage<MTL::TensorExtents*>(this, _MTL_PRIVATE_SEL(dimensions));
}

/**
 * @brief The data type used for indexing elements of this tensor reference.
 *
 * @return MTL::DataType The data type used to address/index the tensor's elements.
 */
_MTL_INLINE MTL::DataType MTL::TensorReferenceType::indexType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(indexType));
}

/**
 * @brief Initialize a TensorReferenceType instance.
 *
 * @return MTL::TensorReferenceType* The initialized instance, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::TensorReferenceType* MTL::TensorReferenceType::init()
{
    return NS::Object::init<MTL::TensorReferenceType>();
}

/**
 * @brief Returns the tensor data type described by this tensor reference.
 *
 * @return MTL::TensorDataType The data type of elements stored in the tensor reference.
 */
_MTL_INLINE MTL::TensorDataType MTL::TensorReferenceType::tensorDataType() const
{
    return Object::sendMessage<MTL::TensorDataType>(this, _MTL_PRIVATE_SEL(tensorDataType));
}

/**
 * @brief Query the access permissions of this argument's binding.
 *
 * @return BindingAccess Describes whether the argument is read-only, read-write, or write-only.
 */
_MTL_INLINE MTL::BindingAccess MTL::Argument::access() const
{
    return Object::sendMessage<MTL::BindingAccess>(this, _MTL_PRIVATE_SEL(access));
}

/**
 * @brief Deprecated alias for isActive; indicates whether the argument was active.
 *
 * @deprecated Use Argument::isActive() instead.
 * @return `true` if the argument was active, `false` otherwise.
 */
_MTL_INLINE bool MTL::Argument::active() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isActive));
}

/**
 * @brief Allocate a new MTL::Argument instance.
 *
 * @return MTL::Argument* A newly allocated Argument object; call `init()` on the returned object before use.
 */
_MTL_INLINE MTL::Argument* MTL::Argument::alloc()
{
    return NS::Object::alloc<MTL::Argument>(_MTL_PRIVATE_CLS(MTLArgument));
}

/**
 * @brief Retrieve the number of elements for this argument when it represents an array.
 *
 * @return NS::UInteger The number of elements in the argument's array; 0 if the argument is not an array.
 */
_MTL_INLINE NS::UInteger MTL::Argument::arrayLength() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(arrayLength));
}

/**
 * @brief Get the required alignment, in bytes, for this argument's buffer binding.
 *
 * @return NS::UInteger Alignment in bytes for the argument's buffer binding.
 */
_MTL_INLINE NS::UInteger MTL::Argument::bufferAlignment() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(bufferAlignment));
}

/**
 * @brief Get the size in bytes of the buffer data associated with this argument.
 *
 * @return NS::UInteger Size in bytes of the buffer data for this argument.
 */
_MTL_INLINE NS::UInteger MTL::Argument::bufferDataSize() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(bufferDataSize));
}

/**
 * @brief Gets the data type that describes the contents of this buffer argument.
 *
 * @return MTL::DataType The data type describing the buffer's contents.
 */
_MTL_INLINE MTL::DataType MTL::Argument::bufferDataType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(bufferDataType));
}

/**
 * @brief The pointer type describing this argument's buffer, if present.
 *
 * @return MTL::PointerType* PointerType for the argument's buffer, or `nullptr` if the argument has no buffer pointer type.
 */
_MTL_INLINE MTL::PointerType* MTL::Argument::bufferPointerType() const
{
    return Object::sendMessage<MTL::PointerType*>(this, _MTL_PRIVATE_SEL(bufferPointerType));
}

/**
 * Retrieves the StructType that describes this argument's buffer layout.
 *
 * @return MTL::StructType* The StructType describing the buffer's structure, or `nullptr` if the argument is not a buffer with a struct type.
 */
_MTL_INLINE MTL::StructType* MTL::Argument::bufferStructType() const
{
    return Object::sendMessage<MTL::StructType*>(this, _MTL_PRIVATE_SEL(bufferStructType));
}

/**
 * @brief Get the binding index of the argument within its function or argument buffer.
 *
 * @return NS::UInteger The zero-based index identifying this argument's slot.
 */
_MTL_INLINE NS::UInteger MTL::Argument::index() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(index));
}

/**
 * @brief Initialize a newly allocated Argument instance.
 *
 * @return MTL::Argument* Pointer to the initialized Argument object, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::Argument* MTL::Argument::init()
{
    return NS::Object::init<MTL::Argument>();
}

/**
 * @brief Indicates whether the argument is active in the function's argument list.
 *
 * @return bool `true` if the argument is active, `false` otherwise.
 */
_MTL_INLINE bool MTL::Argument::isActive() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isActive));
}

/**
 * @brief Indicates whether this argument represents a depth texture.
 *
 * Only meaningful for texture-type arguments; returns whether the texture is a depth texture.
 *
 * @return `true` if the argument is a depth texture, `false` otherwise.
 */
_MTL_INLINE bool MTL::Argument::isDepthTexture() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isDepthTexture));
}

/**
 * Retrieves the name of this argument.
 *
 * If the argument has no associated name, this returns nullptr.
 *
 * @return NS::String* The argument's name, or nullptr if none.
 */
_MTL_INLINE NS::String* MTL::Argument::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Returns the data type of this argument when it represents a texture.
 *
 * @return MTL::DataType The texture's data type.
 */
_MTL_INLINE MTL::DataType MTL::Argument::textureDataType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(textureDataType));
}

/**
 * @brief Retrieves the texture type for this argument.
 *
 * @return MTL::TextureType The texture type of the argument's texture.
 */
_MTL_INLINE MTL::TextureType MTL::Argument::textureType() const
{
    return Object::sendMessage<MTL::TextureType>(this, _MTL_PRIVATE_SEL(textureType));
}

/**
 * @brief Provides the alignment requirement, in bytes, for threadgroup memory associated with this argument.
 *
 * @return NS::UInteger Alignment in bytes required for the argument's threadgroup memory.
 */
_MTL_INLINE NS::UInteger MTL::Argument::threadgroupMemoryAlignment() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(threadgroupMemoryAlignment));
}

/**
 * @brief Retrieve the size in bytes of the threadgroup memory associated with this argument.
 *
 * @return NS::UInteger Size in bytes of the threadgroup memory for the argument.
 */
_MTL_INLINE NS::UInteger MTL::Argument::threadgroupMemoryDataSize() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(threadgroupMemoryDataSize));
}

/**
 * @brief Returns the kind of this argument.
 *
 * @return MTL::ArgumentType The argument's kind (for example: buffer, threadgroup memory, texture, sampler, imageblock, visible function table, primitive/instance/intersection acceleration structure).
 */
_MTL_INLINE MTL::ArgumentType MTL::Argument::type() const
{
    return Object::sendMessage<MTL::ArgumentType>(this, _MTL_PRIVATE_SEL(type));
}

/**
 * @brief Retrieve the access permissions for this binding.
 *
 * @return MTL::BindingAccess One of `BindingAccessReadOnly`, `BindingAccessReadWrite`, or `BindingAccessWriteOnly`
 */
_MTL_INLINE MTL::BindingAccess MTL::Binding::access() const
{
    return Object::sendMessage<MTL::BindingAccess>(this, _MTL_PRIVATE_SEL(access));
}

/**
 * @brief Indicates whether the binding represents an argument.
 *
 * @deprecated Use isArgument() instead.
 * @return `true` if the binding represents an argument, `false` otherwise.
 */
_MTL_INLINE bool MTL::Binding::argument() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isArgument));
}

/**
 * @brief Retrieve the binding's index within its resource layout.
 *
 * @return NS::UInteger The numeric index of this binding.
 */
_MTL_INLINE NS::UInteger MTL::Binding::index() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(index));
}

/**
 * @brief Indicates whether the binding represents an argument.
 *
 * @return `true` if the binding represents an argument, `false` otherwise.
 */
_MTL_INLINE bool MTL::Binding::isArgument() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isArgument));
}

/**
 * @brief Reports whether the binding is active in the shader.
 *
 * @return `true` if the binding is used by the compiled shader, `false` otherwise.
 */
_MTL_INLINE bool MTL::Binding::isUsed() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isUsed));
}

/**
 * @brief The binding's name.
 *
 * @return NS::String* The binding's name, or nullptr if the binding has no name.
 */
_MTL_INLINE NS::String* MTL::Binding::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Obtain the kind of this binding.
 *
 * @return MTL::BindingType The BindingType value describing this binding's kind.
 */
_MTL_INLINE MTL::BindingType MTL::Binding::type() const
{
    return Object::sendMessage<MTL::BindingType>(this, _MTL_PRIVATE_SEL(type));
}

/**
 * @brief Indicates whether the binding is marked as used.
 *
 * @deprecated Use isUsed() instead.
 * @return `true` if the binding is used, `false` otherwise.
 */
_MTL_INLINE bool MTL::Binding::used() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isUsed));
}

/**
 * @brief Query the required memory alignment for the buffer binding.
 *
 * @return NS::UInteger Alignment in bytes required for the buffer binding.
 */
_MTL_INLINE NS::UInteger MTL::BufferBinding::bufferAlignment() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(bufferAlignment));
}

/**
 * @brief Get the size in bytes of the buffer data associated with this buffer binding.
 *
 * @return NS::UInteger The size in bytes of the buffer data for the binding.
 */
_MTL_INLINE NS::UInteger MTL::BufferBinding::bufferDataSize() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(bufferDataSize));
}

/**
 * @brief Query the data type of the buffer binding's contents.
 *
 * @return MTL::DataType The data type used for the buffer binding.
 */
_MTL_INLINE MTL::DataType MTL::BufferBinding::bufferDataType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(bufferDataType));
}

/**
 * @brief Retrieves the pointer type describing this buffer binding's element pointer.
 *
 * @return Pointer to the MTL::PointerType that describes the buffer's pointer type, or `nullptr` if not applicable.
 */
_MTL_INLINE MTL::PointerType* MTL::BufferBinding::bufferPointerType() const
{
    return Object::sendMessage<MTL::PointerType*>(this, _MTL_PRIVATE_SEL(bufferPointerType));
}

/**
 * @brief Get the StructType that describes the buffer binding's element, if present.
 *
 * @return MTL::StructType* The StructType for the buffer binding's element, or `nullptr` if the buffer element is not a struct type.
 */
_MTL_INLINE MTL::StructType* MTL::BufferBinding::bufferStructType() const
{
    return Object::sendMessage<MTL::StructType*>(this, _MTL_PRIVATE_SEL(bufferStructType));
}

/**
 * @brief Retrieves the required alignment for a threadgroup memory binding.
 *
 * @return NS::UInteger Alignment in bytes for the threadgroup memory region.
 */
_MTL_INLINE NS::UInteger MTL::ThreadgroupBinding::threadgroupMemoryAlignment() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(threadgroupMemoryAlignment));
}

/**
 * @brief Retrieve the size in bytes of the threadgroup memory associated with this binding.
 *
 * @return NS::UInteger Size in bytes of the threadgroup memory for this binding.
 */
_MTL_INLINE NS::UInteger MTL::ThreadgroupBinding::threadgroupMemoryDataSize() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(threadgroupMemoryDataSize));
}

/**
 * @brief Retrieves the number of elements in the texture binding's array.
 *
 * @return NS::UInteger The length of the texture array for this binding.
 */
_MTL_INLINE NS::UInteger MTL::TextureBinding::arrayLength() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(arrayLength));
}

/**
 * @brief Reports whether the texture binding represents a depth texture.
 *
 * @deprecated Use isDepthTexture() instead.
 * @return `true` if this binding is a depth texture, `false` otherwise.
 */
_MTL_INLINE bool MTL::TextureBinding::depthTexture() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isDepthTexture));
}

/**
 * @brief Indicates whether the texture binding represents a depth texture.
 *
 * @return `true` if the texture binding is for a depth texture, `false` otherwise.
 */
_MTL_INLINE bool MTL::TextureBinding::isDepthTexture() const
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(isDepthTexture));
}

/**
 * @brief Retrieves the data type used by the texture bound to this binding.
 *
 * @return MTL::DataType The pixel/data type of the texture for this TextureBinding.
 */
_MTL_INLINE MTL::DataType MTL::TextureBinding::textureDataType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(textureDataType));
}

/**
 * @brief Returns the texture type for this binding, describing its dimensionality and classification.
 *
 * @return MTL::TextureType The texture type indicating dimensionality (e.g., 1D, 2D, 3D, cube), array status, and related classification.
 */
_MTL_INLINE MTL::TextureType MTL::TextureBinding::textureType() const
{
    return Object::sendMessage<MTL::TextureType>(this, _MTL_PRIVATE_SEL(textureType));
}

/**
 * @brief Gets the alignment requirement for the object payload binding.
 *
 * @return NS::UInteger Alignment, in bytes, required for the object payload data.
 */
_MTL_INLINE NS::UInteger MTL::ObjectPayloadBinding::objectPayloadAlignment() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(objectPayloadAlignment));
}

/**
 * @brief Retrieves the size, in bytes, of the object payload data for this binding.
 *
 * @return NS::UInteger Size in bytes of the object payload data.
 */
_MTL_INLINE NS::UInteger MTL::ObjectPayloadBinding::objectPayloadDataSize() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(objectPayloadDataSize));
}

/**
 * @brief Returns the dimensional extents of this tensor binding.
 *
 * @return MTL::TensorExtents* Pointer to a TensorExtents describing the binding's dimensions.
 */
_MTL_INLINE MTL::TensorExtents* MTL::TensorBinding::dimensions() const
{
    return Object::sendMessage<MTL::TensorExtents*>(this, _MTL_PRIVATE_SEL(dimensions));
}

/**
 * @brief Retrieves the data type used for indexing this tensor binding.
 *
 * @return MTL::DataType The numeric data type used to index elements of the tensor binding.
 */
_MTL_INLINE MTL::DataType MTL::TensorBinding::indexType() const
{
    return Object::sendMessage<MTL::DataType>(this, _MTL_PRIVATE_SEL(indexType));
}

/**
 * @brief Retrieves the data type used by the tensor binding.
 *
 * @return MTL::TensorDataType The element data type of the tensor described by this binding.
 */
_MTL_INLINE MTL::TensorDataType MTL::TensorBinding::tensorDataType() const
{
    return Object::sendMessage<MTL::TensorDataType>(this, _MTL_PRIVATE_SEL(tensorDataType));
}