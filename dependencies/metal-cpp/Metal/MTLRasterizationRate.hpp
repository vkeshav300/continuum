//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLRasterizationRate.hpp
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
#include "MTLTypes.hpp"

namespace MTL
{
class Buffer;
class Device;
class RasterizationRateLayerArray;
class RasterizationRateLayerDescriptor;
class RasterizationRateMapDescriptor;
class RasterizationRateSampleArray;

class RasterizationRateSampleArray : public NS::Referencing<RasterizationRateSampleArray>
{
public:
    static RasterizationRateSampleArray* alloc();

    RasterizationRateSampleArray*        init();

    NS::Number*                          object(NS::UInteger index);
    void                                 setObject(const NS::Number* value, NS::UInteger index);
};
class RasterizationRateLayerDescriptor : public NS::Copying<RasterizationRateLayerDescriptor>
{
public:
    static RasterizationRateLayerDescriptor* alloc();

    RasterizationRateSampleArray*            horizontal() const;
    float*                                   horizontalSampleStorage() const;

    RasterizationRateLayerDescriptor*        init();
    RasterizationRateLayerDescriptor*        init(MTL::Size sampleCount);
    RasterizationRateLayerDescriptor*        init(MTL::Size sampleCount, const float* horizontal, const float* vertical);

    Size                                     maxSampleCount() const;
    Size                                     sampleCount() const;
    void                                     setSampleCount(MTL::Size sampleCount);

    RasterizationRateSampleArray*            vertical() const;
    float*                                   verticalSampleStorage() const;
};
class RasterizationRateLayerArray : public NS::Referencing<RasterizationRateLayerArray>
{
public:
    static RasterizationRateLayerArray* alloc();

    RasterizationRateLayerArray*        init();

    RasterizationRateLayerDescriptor*   object(NS::UInteger layerIndex);
    void                                setObject(const MTL::RasterizationRateLayerDescriptor* layer, NS::UInteger layerIndex);
};
class RasterizationRateMapDescriptor : public NS::Copying<RasterizationRateMapDescriptor>
{
public:
    static RasterizationRateMapDescriptor* alloc();

    RasterizationRateMapDescriptor*        init();

    NS::String*                            label() const;

    RasterizationRateLayerDescriptor*      layer(NS::UInteger layerIndex);
    NS::UInteger                           layerCount() const;

    RasterizationRateLayerArray*           layers() const;

    static RasterizationRateMapDescriptor* rasterizationRateMapDescriptor(MTL::Size screenSize);
    static RasterizationRateMapDescriptor* rasterizationRateMapDescriptor(MTL::Size screenSize, const MTL::RasterizationRateLayerDescriptor* layer);
    static RasterizationRateMapDescriptor* rasterizationRateMapDescriptor(MTL::Size screenSize, NS::UInteger layerCount, const MTL::RasterizationRateLayerDescriptor* const* layers);

    Size                                   screenSize() const;

    void                                   setLabel(const NS::String* label);

    void                                   setLayer(const MTL::RasterizationRateLayerDescriptor* layer, NS::UInteger layerIndex);

    void                                   setScreenSize(MTL::Size screenSize);
};
class RasterizationRateMap : public NS::Referencing<RasterizationRateMap>
{
public:
    void         copyParameterDataToBuffer(const MTL::Buffer* buffer, NS::UInteger offset);

    Device*      device() const;

    NS::String*  label() const;

    NS::UInteger layerCount() const;

    Coordinate2D mapPhysicalToScreenCoordinates(MTL::Coordinate2D physicalCoordinates, NS::UInteger layerIndex);

    Coordinate2D mapScreenToPhysicalCoordinates(MTL::Coordinate2D screenCoordinates, NS::UInteger layerIndex);

    SizeAndAlign parameterBufferSizeAndAlign() const;

    Size         physicalGranularity() const;

    Size         physicalSize(NS::UInteger layerIndex);

    Size         screenSize() const;
};

}
/**
 * @brief Allocate a new RasterizationRateSampleArray instance.
 *
 * @return RasterizationRateSampleArray* Pointer to a newly allocated RasterizationRateSampleArray.
 */
_MTL_INLINE MTL::RasterizationRateSampleArray* MTL::RasterizationRateSampleArray::alloc()
{
    return NS::Object::alloc<MTL::RasterizationRateSampleArray>(_MTL_PRIVATE_CLS(MTLRasterizationRateSampleArray));
}

/**
 * @brief Initializes a RasterizationRateSampleArray instance.
 *
 * @return MTL::RasterizationRateSampleArray* Initialized instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::RasterizationRateSampleArray* MTL::RasterizationRateSampleArray::init()
{
    return NS::Object::init<MTL::RasterizationRateSampleArray>();
}

/**
 * @brief Retrieve the sample number at the given index.
 *
 * @param index Index of the sample to retrieve.
 * @return NS::Number* The sample stored at `index`.
 */
_MTL_INLINE NS::Number* MTL::RasterizationRateSampleArray::object(NS::UInteger index)
{
    return Object::sendMessage<NS::Number*>(this, _MTL_PRIVATE_SEL(objectAtIndexedSubscript_), index);
}

/**
 * @brief Sets the numeric value at the specified index in the sample array.
 *
 * @param value The number to store at the given index.
 * @param index The index at which to set the value.
 */
_MTL_INLINE void MTL::RasterizationRateSampleArray::setObject(const NS::Number* value, NS::UInteger index)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObject_atIndexedSubscript_), value, index);
}

/**
 * @brief Allocate a new RasterizationRateLayerDescriptor instance.
 *
 * @return RasterizationRateLayerDescriptor* A newly allocated (not yet initialized) RasterizationRateLayerDescriptor.
 */
_MTL_INLINE MTL::RasterizationRateLayerDescriptor* MTL::RasterizationRateLayerDescriptor::alloc()
{
    return NS::Object::alloc<MTL::RasterizationRateLayerDescriptor>(_MTL_PRIVATE_CLS(MTLRasterizationRateLayerDescriptor));
}

/**
 * @brief Access the horizontal sample array for this layer descriptor.
 *
 * @return MTL::RasterizationRateSampleArray* Array containing the per-sample horizontal rasterization rates for the layer.
 */
_MTL_INLINE MTL::RasterizationRateSampleArray* MTL::RasterizationRateLayerDescriptor::horizontal() const
{
    return Object::sendMessage<MTL::RasterizationRateSampleArray*>(this, _MTL_PRIVATE_SEL(horizontal));
}

/**
 * @brief Accesses the contiguous float storage for this layer's horizontal rasterization samples.
 *
 * The returned pointer refers to an array of horizontal sample values for the layer; the array length
 * corresponds to this descriptor's sampleCount().
 *
 * @return float* Pointer to the horizontal sample storage array.
 */
_MTL_INLINE float* MTL::RasterizationRateLayerDescriptor::horizontalSampleStorage() const
{
    return Object::sendMessage<float*>(this, _MTL_PRIVATE_SEL(horizontalSampleStorage));
}

/**
 * @brief Initializes a RasterizationRateLayerDescriptor instance.
 *
 * @return MTL::RasterizationRateLayerDescriptor* The initialized descriptor, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::RasterizationRateLayerDescriptor* MTL::RasterizationRateLayerDescriptor::init()
{
    return NS::Object::init<MTL::RasterizationRateLayerDescriptor>();
}

/**
 * @brief Initialize the rasterization rate layer descriptor with a sample count.
 *
 * @param sampleCount Number of samples for the layer.
 * @return MTL::RasterizationRateLayerDescriptor* The initialized descriptor instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::RasterizationRateLayerDescriptor* MTL::RasterizationRateLayerDescriptor::init(MTL::Size sampleCount)
{
    return Object::sendMessage<MTL::RasterizationRateLayerDescriptor*>(this, _MTL_PRIVATE_SEL(initWithSampleCount_), sampleCount);
}

/**
 * @brief Initialize a layer descriptor with a given sample count and sample arrays.
 *
 * @param sampleCount Number of samples to use for the descriptor.
 * @param horizontal Pointer to an array of horizontal sample values (length = sampleCount).
 * @param vertical Pointer to an array of vertical sample values (length = sampleCount).
 * @return MTL::RasterizationRateLayerDescriptor* Pointer to the initialized descriptor.
 */
_MTL_INLINE MTL::RasterizationRateLayerDescriptor* MTL::RasterizationRateLayerDescriptor::init(MTL::Size sampleCount, const float* horizontal, const float* vertical)
{
    return Object::sendMessage<MTL::RasterizationRateLayerDescriptor*>(this, _MTL_PRIVATE_SEL(initWithSampleCount_horizontal_vertical_), sampleCount, horizontal, vertical);
}

/**
 * @brief Query the maximum supported sample count for this rasterization rate layer.
 *
 * @return MTL::Size The maximum number of samples supported by the layer.
 */
_MTL_INLINE MTL::Size MTL::RasterizationRateLayerDescriptor::maxSampleCount() const
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(maxSampleCount));
}

/**
 * @brief Retrieves the current sample count for this rasterization-rate layer.
 *
 * @return MTL::Size The current sample count configured for the layer.
 */
_MTL_INLINE MTL::Size MTL::RasterizationRateLayerDescriptor::sampleCount() const
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(sampleCount));
}

/**
 * @brief Set the current number of samples for this layer descriptor.
 *
 * @param sampleCount The number of samples to use for the layer.
 */
_MTL_INLINE void MTL::RasterizationRateLayerDescriptor::setSampleCount(MTL::Size sampleCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSampleCount_), sampleCount);
}

/**
 * @brief Retrieve the vertical sample rate array for this layer.
 *
 * @return MTL::RasterizationRateSampleArray* The array containing vertical sample values for the layer.
 */
_MTL_INLINE MTL::RasterizationRateSampleArray* MTL::RasterizationRateLayerDescriptor::vertical() const
{
    return Object::sendMessage<MTL::RasterizationRateSampleArray*>(this, _MTL_PRIVATE_SEL(vertical));
}

/**
 * @brief Accesses the floating-point storage for vertical rasterization rate samples.
 *
 * Returns a pointer to the first element of the contiguous float array containing
 * vertical sample values for this layer descriptor.
 *
 * @return float* Pointer to the vertical sample storage array (first element).
 */
_MTL_INLINE float* MTL::RasterizationRateLayerDescriptor::verticalSampleStorage() const
{
    return Object::sendMessage<float*>(this, _MTL_PRIVATE_SEL(verticalSampleStorage));
}

/**
 * @brief Allocate a new RasterizationRateLayerArray instance.
 *
 * @return RasterizationRateLayerArray* A newly allocated, retained RasterizationRateLayerArray instance.
 */
_MTL_INLINE MTL::RasterizationRateLayerArray* MTL::RasterizationRateLayerArray::alloc()
{
    return NS::Object::alloc<MTL::RasterizationRateLayerArray>(_MTL_PRIVATE_CLS(MTLRasterizationRateLayerArray));
}

/**
 * @brief Initialize a RasterizationRateLayerArray instance.
 *
 * @return RasterizationRateLayerArray* An initialized instance, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL::RasterizationRateLayerArray* MTL::RasterizationRateLayerArray::init()
{
    return NS::Object::init<MTL::RasterizationRateLayerArray>();
}

/**
 * @brief Retrieve the layer descriptor at a given index.
 *
 * @param layerIndex Index of the layer to retrieve.
 * @return MTL::RasterizationRateLayerDescriptor* The descriptor for the specified layer index.
 */
_MTL_INLINE MTL::RasterizationRateLayerDescriptor* MTL::RasterizationRateLayerArray::object(NS::UInteger layerIndex)
{
    return Object::sendMessage<MTL::RasterizationRateLayerDescriptor*>(this, _MTL_PRIVATE_SEL(objectAtIndexedSubscript_), layerIndex);
}

/**
 * @brief Sets the layer descriptor at the specified index in the array.
 *
 * @param layer The rasterization rate layer descriptor to store.
 * @param layerIndex The index at which to set the descriptor.
 */
_MTL_INLINE void MTL::RasterizationRateLayerArray::setObject(const MTL::RasterizationRateLayerDescriptor* layer, NS::UInteger layerIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setObject_atIndexedSubscript_), layer, layerIndex);
}

/**
 * @brief Allocate a new RasterizationRateMapDescriptor object.
 *
 * @return RasterizationRateMapDescriptor* Pointer to the newly allocated descriptor instance.
 */
_MTL_INLINE MTL::RasterizationRateMapDescriptor* MTL::RasterizationRateMapDescriptor::alloc()
{
    return NS::Object::alloc<MTL::RasterizationRateMapDescriptor>(_MTL_PRIVATE_CLS(MTLRasterizationRateMapDescriptor));
}

/**
 * @brief Initializes a newly allocated RasterizationRateMapDescriptor.
 *
 * Performs object initialization and returns the initialized descriptor instance.
 *
 * @return MTL::RasterizationRateMapDescriptor* Pointer to the initialized descriptor, or `nullptr` if initialization failed.
 */
_MTL_INLINE MTL::RasterizationRateMapDescriptor* MTL::RasterizationRateMapDescriptor::init()
{
    return NS::Object::init<MTL::RasterizationRateMapDescriptor>();
}

/**
 * @brief Get the descriptor's human-readable label.
 *
 * @return NS::String* The label string, or `nullptr` if no label has been set.
 */
_MTL_INLINE NS::String* MTL::RasterizationRateMapDescriptor::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Returns the rasterization rate layer descriptor at the specified layer index.
 *
 * @param layerIndex Index of the layer to retrieve.
 * @return RasterizationRateLayerDescriptor* The descriptor for the layer at the given index.
 */
_MTL_INLINE MTL::RasterizationRateLayerDescriptor* MTL::RasterizationRateMapDescriptor::layer(NS::UInteger layerIndex)
{
    return Object::sendMessage<MTL::RasterizationRateLayerDescriptor*>(this, _MTL_PRIVATE_SEL(layerAtIndex_), layerIndex);
}

/**
 * @brief Get the number of layers defined in the rasterization-rate map descriptor.
 *
 * @return The number of layers in the descriptor.
 */
_MTL_INLINE NS::UInteger MTL::RasterizationRateMapDescriptor::layerCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(layerCount));
}

/**
 * @brief Accesses the array of rasterization rate layer descriptors.
 *
 * @return MTL::RasterizationRateLayerArray* Pointer to a RasterizationRateLayerArray containing the layer descriptors.
 */
_MTL_INLINE MTL::RasterizationRateLayerArray* MTL::RasterizationRateMapDescriptor::layers() const
{
    return Object::sendMessage<MTL::RasterizationRateLayerArray*>(this, _MTL_PRIVATE_SEL(layers));
}

/**
 * @brief Creates a rasterization rate map descriptor for a given screen size.
 *
 * @param screenSize Screen dimensions to associate with the descriptor.
 * @return MTL::RasterizationRateMapDescriptor* Pointer to a rasterization rate map descriptor configured with the provided screen size.
 */
_MTL_INLINE MTL::RasterizationRateMapDescriptor* MTL::RasterizationRateMapDescriptor::rasterizationRateMapDescriptor(MTL::Size screenSize)
{
    return Object::sendMessage<MTL::RasterizationRateMapDescriptor*>(_MTL_PRIVATE_CLS(MTLRasterizationRateMapDescriptor), _MTL_PRIVATE_SEL(rasterizationRateMapDescriptorWithScreenSize_), screenSize);
}

/**
 * @brief Creates a rasterization rate map descriptor for a given screen size with a single layer.
 *
 * @param screenSize The screen size to associate with the descriptor.
 * @param layer The layer descriptor to include as the descriptor's single layer.
 * @return MTL::RasterizationRateMapDescriptor* A descriptor configured with the provided screen size and layer.
 */
_MTL_INLINE MTL::RasterizationRateMapDescriptor* MTL::RasterizationRateMapDescriptor::rasterizationRateMapDescriptor(MTL::Size screenSize, const MTL::RasterizationRateLayerDescriptor* layer)
{
    return Object::sendMessage<MTL::RasterizationRateMapDescriptor*>(_MTL_PRIVATE_CLS(MTLRasterizationRateMapDescriptor), _MTL_PRIVATE_SEL(rasterizationRateMapDescriptorWithScreenSize_layer_), screenSize, layer);
}

/**
 * @brief Create a rasterization rate map descriptor configured for a specific screen size and layers.
 *
 * @param screenSize Screen size to associate with the descriptor.
 * @param layerCount Number of entries in `layers`.
 * @param layers Pointer to an array of `RasterizationRateLayerDescriptor` pointers representing each layer.
 * @return MTL::RasterizationRateMapDescriptor* A new descriptor initialized with the provided screen size and layer descriptors.
 */
_MTL_INLINE MTL::RasterizationRateMapDescriptor* MTL::RasterizationRateMapDescriptor::rasterizationRateMapDescriptor(MTL::Size screenSize, NS::UInteger layerCount, const MTL::RasterizationRateLayerDescriptor* const* layers)
{
    return Object::sendMessage<MTL::RasterizationRateMapDescriptor*>(_MTL_PRIVATE_CLS(MTLRasterizationRateMapDescriptor), _MTL_PRIVATE_SEL(rasterizationRateMapDescriptorWithScreenSize_layerCount_layers_), screenSize, layerCount, layers);
}

/**
 * @brief Retrieves the screen size associated with this rasterization rate map descriptor.
 *
 * @return MTL::Size The screen size for this descriptor.
 */
_MTL_INLINE MTL::Size MTL::RasterizationRateMapDescriptor::screenSize() const
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(screenSize));
}

/**
 * @brief Sets the human-readable label for this rasterization rate map descriptor.
 *
 * @param label The label to assign to the descriptor. Pass `nullptr` to clear any existing label.
 */
_MTL_INLINE void MTL::RasterizationRateMapDescriptor::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Set the layer descriptor at the specified index of this map descriptor.
 *
 * Replaces the layer descriptor for the given layer index with the provided descriptor.
 *
 * @param layer Descriptor to assign to the layer slot.
 * @param layerIndex Index of the layer to set.
 */
_MTL_INLINE void MTL::RasterizationRateMapDescriptor::setLayer(const MTL::RasterizationRateLayerDescriptor* layer, NS::UInteger layerIndex)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLayer_atIndex_), layer, layerIndex);
}

/**
 * @brief Set the screen size for this rasterization rate map descriptor.
 *
 * @param screenSize The screen dimensions to associate with the descriptor.
 */
_MTL_INLINE void MTL::RasterizationRateMapDescriptor::setScreenSize(MTL::Size screenSize)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setScreenSize_), screenSize);
}

/**
 * @brief Copies the rasterization-rate parameter data into a GPU buffer.
 *
 * Copies this map's parameter data into the provided MTL buffer starting at the specified byte offset.
 *
 * @param buffer Destination buffer to receive the parameter data.
 * @param offset Byte offset within `buffer` where the data will be written.
 */
_MTL_INLINE void MTL::RasterizationRateMap::copyParameterDataToBuffer(const MTL::Buffer* buffer, NS::UInteger offset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyParameterDataToBuffer_offset_), buffer, offset);
}

/**
 * @brief Gets the Metal device associated with this rasterization rate map.
 *
 * @return MTL::Device* The device that created or owns the rasterization rate map.
 */
_MTL_INLINE MTL::Device* MTL::RasterizationRateMap::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Retrieves the rasterization rate map's label.
 *
 * @return NS::String* The label string for the map, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::RasterizationRateMap::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Get the number of layers in the rasterization rate map.
 *
 * @return The number of layers in the map.
 */
_MTL_INLINE NS::UInteger MTL::RasterizationRateMap::layerCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(layerCount));
}

/**
 * @brief Map physical coordinates to screen coordinates for a specific rasterization layer.
 *
 * @param physicalCoordinates Physical coordinates in the map's physical coordinate space.
 * @param layerIndex Index of the rasterization layer to use when mapping.
 * @return MTL::Coordinate2D Screen-space coordinates corresponding to the provided physical coordinates for the specified layer.
 */
_MTL_INLINE MTL::Coordinate2D MTL::RasterizationRateMap::mapPhysicalToScreenCoordinates(MTL::Coordinate2D physicalCoordinates, NS::UInteger layerIndex)
{
    return Object::sendMessage<MTL::Coordinate2D>(this, _MTL_PRIVATE_SEL(mapPhysicalToScreenCoordinates_forLayer_), physicalCoordinates, layerIndex);
}

/**
 * Convert screen-space coordinates to physical (device) coordinates for a specified layer.
 *
 * @param screenCoordinates The coordinates in screen space to be mapped.
 * @param layerIndex The zero-based layer index whose mapping is used.
 * @return MTL::Coordinate2D The resulting physical coordinates corresponding to the provided screen coordinates.
 */
_MTL_INLINE MTL::Coordinate2D MTL::RasterizationRateMap::mapScreenToPhysicalCoordinates(MTL::Coordinate2D screenCoordinates, NS::UInteger layerIndex)
{
    return Object::sendMessage<MTL::Coordinate2D>(this, _MTL_PRIVATE_SEL(mapScreenToPhysicalCoordinates_forLayer_), screenCoordinates, layerIndex);
}

/**
 * @brief Retrieve the size and alignment requirements for the parameter buffer used by this rasterization rate map.
 *
 * @return MTL::SizeAndAlign A struct describing the required buffer size (in bytes) and alignment (in bytes).
 */
_MTL_INLINE MTL::SizeAndAlign MTL::RasterizationRateMap::parameterBufferSizeAndAlign() const
{
    return Object::sendMessage<MTL::SizeAndAlign>(this, _MTL_PRIVATE_SEL(parameterBufferSizeAndAlign));
}

/**
 * @brief Query the physical sampling granularity of this rasterization rate map.
 *
 * @return MTL::Size The physical sampling granularity for the map.
 */
_MTL_INLINE MTL::Size MTL::RasterizationRateMap::physicalGranularity() const
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(physicalGranularity));
}

/**
 * @brief Returns the physical size of a specific rasterization layer.
 *
 * @param layerIndex Index of the layer to query.
 * @return MTL::Size Physical size for the specified layer.
 */
_MTL_INLINE MTL::Size MTL::RasterizationRateMap::physicalSize(NS::UInteger layerIndex)
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(physicalSizeForLayer_), layerIndex);
}

/**
 * @brief Provide the screen size associated with this rasterization rate map.
 *
 * @return MTL::Size The screen size of the rasterization rate map.
 */
_MTL_INLINE MTL::Size MTL::RasterizationRateMap::screenSize() const
{
    return Object::sendMessage<MTL::Size>(this, _MTL_PRIVATE_SEL(screenSize));
}