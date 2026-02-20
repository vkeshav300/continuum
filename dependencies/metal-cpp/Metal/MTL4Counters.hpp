//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4Counters.hpp
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
#include <cstdint>

#include <cstdint>

namespace MTL4
{
class CounterHeapDescriptor;
_MTL_ENUM(NS::Integer, CounterHeapType) {
    CounterHeapTypeInvalid,
    CounterHeapTypeTimestamp,
};

/**
 * @brief Specifies timestamp granularity options for timestamp counter heaps.
 */
 
/**
 * @brief Represents a single timestamp entry in a timestamp heap.
 *
 * The struct contains the raw timestamp value for one heap entry.
 */
 
/**
 * @brief Descriptor object for configuring a counter heap.
 */

/**
 * @brief Allocate a new CounterHeapDescriptor instance.
 *
 * @return CounterHeapDescriptor* Newly allocated descriptor instance.
 */

/**
 * @brief Get the configured number of counters.
 *
 * @return NS::UInteger The descriptor's counter count.
 */

/**
 * @brief Initialize the descriptor instance.
 *
 * @return CounterHeapDescriptor* The initialized descriptor, or nullptr on failure.
 */

/**
 * @brief Set the number of counters described by this descriptor.
 *
 * @param count The new counter count.
 */

/**
 * @brief Set the counter heap type for this descriptor.
 *
 * @param type The CounterHeapType to assign to the descriptor.
 */

/**
 * @brief Get the counter heap type configured on this descriptor.
 *
 * @return CounterHeapType The descriptor's counter heap type.
 */

/**
 * @brief Represents a counter heap backing storage and operations.
 */

/**
 * @brief Get the number of counters contained in the heap.
 *
 * @return NS::UInteger The heap's counter count.
 */

/**
 * @brief Invalidate a range of counters in the heap.
 *
 * @param range The range of counters to invalidate.
 */

/**
 * @brief Get the user-visible label for the heap.
 *
 * @return NS::String* The heap's label, or nullptr if none is set.
 */

/**
 * @brief Resolve and return the raw counter data for a specified range.
 *
 * @param range The range of counters to resolve.
 * @return NS::Data* The resolved counter data for the requested range.
 */

/**
 * @brief Set a user-visible label for the heap.
 *
 * @param label The label to assign to the heap.
 */

/**
 * @brief Get the type of this counter heap.
 *
 * @return CounterHeapType The heap's CounterHeapType.
 */
_MTL_ENUM(NS::Integer, TimestampGranularity) {
    TimestampGranularityRelaxed = 0,
    TimestampGranularityPrecise = 1,
};

struct TimestampHeapEntry
{
    uint64_t timestamp;
} _MTL_PACKED;

class CounterHeapDescriptor : public NS::Copying<CounterHeapDescriptor>
{
public:
    static CounterHeapDescriptor* alloc();

    NS::UInteger                  count() const;

    CounterHeapDescriptor*        init();

    void                          setCount(NS::UInteger count);

    void                          setType(MTL4::CounterHeapType type);
    CounterHeapType               type() const;
};
class CounterHeap : public NS::Referencing<CounterHeap>
{
public:
    NS::UInteger    count() const;
    void            invalidateCounterRange(NS::Range range);

    NS::String*     label() const;

    NS::Data*       resolveCounterRange(NS::Range range);

    void            setLabel(const NS::String* label);

    CounterHeapType type() const;
};

}

/**
 * @brief Allocates a new CounterHeapDescriptor instance.
 *
 * @return CounterHeapDescriptor* A newly allocated, uninitialized CounterHeapDescriptor instance.
 */
_MTL_INLINE MTL4::CounterHeapDescriptor* MTL4::CounterHeapDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::CounterHeapDescriptor>(_MTL_PRIVATE_CLS(MTL4CounterHeapDescriptor));
}

/**
 * @brief Get the number of counters described by this descriptor.
 *
 * @return NS::UInteger The number of counters configured for the descriptor.
 */
_MTL_INLINE NS::UInteger MTL4::CounterHeapDescriptor::count() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(count));
}

/**
 * @brief Initializes a CounterHeapDescriptor instance.
 *
 * @return Pointer to the initialized CounterHeapDescriptor, or `nullptr` if initialization fails.
 */
_MTL_INLINE MTL4::CounterHeapDescriptor* MTL4::CounterHeapDescriptor::init()
{
    return NS::Object::init<MTL4::CounterHeapDescriptor>();
}

/**
 * @brief Set the number of counters represented by the descriptor.
 *
 * @param count The number of counters the descriptor should represent.
 */
_MTL_INLINE void MTL4::CounterHeapDescriptor::setCount(NS::UInteger count)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCount_), count);
}

/**
 * @brief Sets the counter heap descriptor's type.
 *
 * @param type The CounterHeapType to assign to this descriptor.
 */
_MTL_INLINE void MTL4::CounterHeapDescriptor::setType(MTL4::CounterHeapType type)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setType_), type);
}

/**
 * @brief Get the descriptor's counter heap type.
 *
 * @return MTL4::CounterHeapType The descriptor's counter heap type.
 */
_MTL_INLINE MTL4::CounterHeapType MTL4::CounterHeapDescriptor::type() const
{
    return Object::sendMessage<MTL4::CounterHeapType>(this, _MTL_PRIVATE_SEL(type));
}

/**
 * @brief Retrieve the number of counters in the heap.
 *
 * @return NS::UInteger Number of counters contained in this CounterHeap.
 */
_MTL_INLINE NS::UInteger MTL4::CounterHeap::count() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(count));
}

/**
 * @brief Invalidate cached or stored counter values for a range of counters.
 *
 * Marks counters in the given range as invalid so subsequent queries will refresh or recompute their values.
 *
 * @param range The range of counters to invalidate (start index and length).
 */
_MTL_INLINE void MTL4::CounterHeap::invalidateCounterRange(NS::Range range)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(invalidateCounterRange_), range);
}

/**
 * @brief Returns the human-readable label for the counter heap.
 *
 * @return NS::String* The label string for the heap, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL4::CounterHeap::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Obtain the data containing counter values for the specified range.
 *
 * @param range The range of counters to resolve.
 * @return NS::Data* Pointer to an `NS::Data` object holding the counter contents for `range`.
 */
_MTL_INLINE NS::Data* MTL4::CounterHeap::resolveCounterRange(NS::Range range)
{
    return Object::sendMessage<NS::Data*>(this, _MTL_PRIVATE_SEL(resolveCounterRange_), range);
}

/**
 * @brief Set a descriptive label for the counter heap.
 *
 * @param label Descriptive label string for the counter heap.
 */
_MTL_INLINE void MTL4::CounterHeap::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Retrieves the counter heap's type.
 *
 * @return MTL4::CounterHeapType The heap's type as an `MTL4::CounterHeapType` enum value.
 */
_MTL_INLINE MTL4::CounterHeapType MTL4::CounterHeap::type() const
{
    return Object::sendMessage<MTL4::CounterHeapType>(this, _MTL_PRIVATE_SEL(type));
}