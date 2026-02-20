//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLCounters.hpp
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
#include "MTLResource.hpp"
#include <cstdint>

namespace MTL
{
class CounterSampleBufferDescriptor;
class CounterSet;
class Device;
/**
 * @brief Errors returned when creating or using a counter sample buffer.
 */
 
/**
 * @brief Alias for a common counter identifier string.
 */
 
/**
 * @brief Alias for a common counter set identifier string.
 */
 
/**
 * @brief Special value indicating an error when reading a counter (all bits set).
 */
 
/**
 * @brief Special value indicating a sample index that should not be taken.
 */
 
/**
 * @brief Error domain for counter-related NSError objects.
 */
 
/**
 * @brief Common counter identifier: timestamp.
 */
 
/**
 * @brief Common counter identifier: tessellation input patch count.
 */
 
/**
 * @brief Common counter identifier: vertex invocation count.
 */
 
/**
 * @brief Common counter identifier: post-tessellation vertex invocation count.
 */
 
/**
 * @brief Common counter identifier: clipper invocation count.
 */
 
/**
 * @brief Common counter identifier: clipper primitives out count.
 */
 
/**
 * @brief Common counter identifier: fragment invocation count.
 */
 
/**
 * @brief Common counter identifier: fragments passed count.
 */
 
/**
 * @brief Common counter identifier: compute kernel invocation count.
 */
 
/**
 * @brief Common counter identifier: total GPU cycles.
 */
 
/**
 * @brief Common counter identifier: vertex-stage GPU cycles.
 */
 
/**
 * @brief Common counter identifier: tessellation-stage GPU cycles.
 */
 
/**
 * @brief Common counter identifier: post-tessellation vertex-stage GPU cycles.
 */
 
/**
 * @brief Common counter identifier: fragment-stage GPU cycles.
 */
 
/**
 * @brief Common counter identifier: render-target write GPU cycles.
 */
 
/**
 * @brief Common counter set identifier: timestamp set.
 */
 
/**
 * @brief Common counter set identifier: stage utilization set.
 */
 
/**
 * @brief Common counter set identifier: statistic counters set.
 */
 
/**
 * @brief Timestamp counter result payload.
 *
 * Contains a single 64-bit timestamp value in the implementation's timebase.
 */
 
/**
 * @brief Stage utilization counter result payload.
 *
 * Contains cycle counts attributed to stages and totals for a sampled interval.
 */
 
/**
 * @brief Statistic counter result payload.
 *
 * Contains various invocation and primitive counts for a sampled interval.
 */
 
/**
 * @brief Represents a single hardware or common counter.
 *
 * Provides access to the counter's name.
 */
 
/**
 * @brief Returns the counter's name.
 *
 * @return NS::String* The counter name.
 */
 
/**
 * @brief Represents a set of counters.
 *
 * Provides access to the counters contained in the set and the set's name.
 */
 
/**
 * @brief Returns the array of counters in this set.
 *
 * @return NS::Array* An array of Counter objects in the set.
 */
 
/**
 * @brief Returns the counter set's name.
 *
 * @return NS::String* The name of the counter set.
 */
 
/**
 * @brief Descriptor object configuring the creation of a counter sample buffer.
 *
 * Configure counter set, sample count, label, and storage mode prior to allocation.
 */
 
/**
 * @brief Allocates a new descriptor instance.
 *
 * @return CounterSampleBufferDescriptor* A newly allocated descriptor.
 */
 
/**
 * @brief Returns the counter set configured for the descriptor.
 *
 * @return CounterSet* The counter set to be sampled.
 */
 
/**
 * @brief Initializes the descriptor.
 *
 * @return CounterSampleBufferDescriptor* The initialized descriptor instance.
 */
 
/**
 * @brief Returns the descriptor's label.
 *
 * @return NS::String* The user-visible label for the descriptor.
 */
 
/**
 * @brief Returns the configured sample count.
 *
 * @return NS::UInteger The number of samples this descriptor will reserve.
 */
 
/**
 * @brief Sets the counter set to be sampled by buffers created from this descriptor.
 *
 * @param counterSet The CounterSet to sample.
 */
 
/**
 * @brief Sets the descriptor's label.
 *
 * @param label The user-visible label for the descriptor.
 */
 
/**
 * @brief Sets the number of samples to reserve in buffers created from this descriptor.
 *
 * @param sampleCount The sample count to configure.
 */
 
/**
 * @brief Sets the storage mode for buffers created from this descriptor.
 *
 * @param storageMode The MTL::StorageMode to use for the sample buffer's backing storage.
 */
 
/**
 * @brief Returns the configured storage mode.
 *
 * @return StorageMode The storage mode configured on the descriptor.
 */
 
/**
 * @brief Represents an allocated counter sample buffer.
 *
 * Provides access to the device, label, sample count and resolved counter data.
 */
 
/**
 * @brief Returns the device that created this counter sample buffer.
 *
 * @return Device* The device associated with the buffer.
 */
 
/**
 * @brief Returns the buffer's label.
 *
 * @return NS::String* The user-visible label for the sample buffer.
 */
 
/**
 * @brief Resolves and returns the raw counter data for a range of samples.
 *
 * @param range The NS::Range of sample indices to resolve.
 * @return NS::Data* A data object containing the resolved counter bytes for the specified range.
 */
 
/**
 * @brief Returns the configured sample count for this buffer.
 *
 * @return NS::UInteger The number of samples reserved in the buffer.
 */
_MTL_ENUM(NS::Integer, CounterSampleBufferError) {
    CounterSampleBufferErrorOutOfMemory = 0,
    CounterSampleBufferErrorInvalid = 1,
    CounterSampleBufferErrorInternal = 2,
};

using CommonCounter = NS::String*;
using CommonCounterSet = NS::String*;

static const NS::UInteger CounterErrorValue = static_cast<NS::UInteger>(~0ULL);
static const NS::UInteger CounterDontSample = static_cast<NS::UInteger>(-1);
_MTL_CONST(NS::ErrorDomain, CounterErrorDomain);
_MTL_CONST(CommonCounter, CommonCounterTimestamp);
_MTL_CONST(CommonCounter, CommonCounterTessellationInputPatches);
_MTL_CONST(CommonCounter, CommonCounterVertexInvocations);
_MTL_CONST(CommonCounter, CommonCounterPostTessellationVertexInvocations);
_MTL_CONST(CommonCounter, CommonCounterClipperInvocations);
_MTL_CONST(CommonCounter, CommonCounterClipperPrimitivesOut);
_MTL_CONST(CommonCounter, CommonCounterFragmentInvocations);
_MTL_CONST(CommonCounter, CommonCounterFragmentsPassed);
_MTL_CONST(CommonCounter, CommonCounterComputeKernelInvocations);
_MTL_CONST(CommonCounter, CommonCounterTotalCycles);
_MTL_CONST(CommonCounter, CommonCounterVertexCycles);
_MTL_CONST(CommonCounter, CommonCounterTessellationCycles);
_MTL_CONST(CommonCounter, CommonCounterPostTessellationVertexCycles);
_MTL_CONST(CommonCounter, CommonCounterFragmentCycles);
_MTL_CONST(CommonCounter, CommonCounterRenderTargetWriteCycles);
_MTL_CONST(CommonCounterSet, CommonCounterSetTimestamp);
_MTL_CONST(CommonCounterSet, CommonCounterSetStageUtilization);
_MTL_CONST(CommonCounterSet, CommonCounterSetStatistic);
struct CounterResultTimestamp
{
    uint64_t timestamp;
} _MTL_PACKED;

struct CounterResultStageUtilization
{
    uint64_t totalCycles;
    uint64_t vertexCycles;
    uint64_t tessellationCycles;
    uint64_t postTessellationVertexCycles;
    uint64_t fragmentCycles;
    uint64_t renderTargetCycles;
} _MTL_PACKED;

struct CounterResultStatistic
{
    uint64_t tessellationInputPatches;
    uint64_t vertexInvocations;
    uint64_t postTessellationVertexInvocations;
    uint64_t clipperInvocations;
    uint64_t clipperPrimitivesOut;
    uint64_t fragmentInvocations;
    uint64_t fragmentsPassed;
    uint64_t computeKernelInvocations;
} _MTL_PACKED;

class Counter : public NS::Referencing<Counter>
{
public:
    NS::String* name() const;
};
class CounterSet : public NS::Referencing<CounterSet>
{
public:
    NS::Array*  counters() const;

    NS::String* name() const;
};
class CounterSampleBufferDescriptor : public NS::Copying<CounterSampleBufferDescriptor>
{
public:
    static CounterSampleBufferDescriptor* alloc();

    CounterSet*                           counterSet() const;

    CounterSampleBufferDescriptor*        init();

    NS::String*                           label() const;

    NS::UInteger                          sampleCount() const;

    void                                  setCounterSet(const MTL::CounterSet* counterSet);

    void                                  setLabel(const NS::String* label);

    void                                  setSampleCount(NS::UInteger sampleCount);

    void                                  setStorageMode(MTL::StorageMode storageMode);
    StorageMode                           storageMode() const;
};
class CounterSampleBuffer : public NS::Referencing<CounterSampleBuffer>
{
public:
    Device*      device() const;

    NS::String*  label() const;

    NS::Data*    resolveCounterRange(NS::Range range);

    NS::UInteger sampleCount() const;
};

}

_MTL_PRIVATE_DEF_CONST(NS::ErrorDomain, CounterErrorDomain);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterTimestamp);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterTessellationInputPatches);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterVertexInvocations);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterPostTessellationVertexInvocations);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterClipperInvocations);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterClipperPrimitivesOut);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterFragmentInvocations);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterFragmentsPassed);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterComputeKernelInvocations);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterTotalCycles);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterVertexCycles);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterTessellationCycles);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterPostTessellationVertexCycles);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterFragmentCycles);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounter, CommonCounterRenderTargetWriteCycles);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounterSet, CommonCounterSetTimestamp);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounterSet, CommonCounterSetStageUtilization);
_MTL_PRIVATE_DEF_CONST(MTL::CommonCounterSet, CommonCounterSetStatistic);

/**
 * @brief Retrieves the counter's name.
 *
 * @return NS::String* The counter's name.
 */
_MTL_INLINE NS::String* MTL::Counter::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Returns the counters that belong to this counter set.
 *
 * @return NS::Array* Array of MTL::Counter objects contained in the set.
 */
_MTL_INLINE NS::Array* MTL::CounterSet::counters() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(counters));
}

/**
 * @brief The counter set's name.
 *
 * @return NS::String* The name of the counter set.
 */
_MTL_INLINE NS::String* MTL::CounterSet::name() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(name));
}

/**
 * @brief Allocate a new CounterSampleBufferDescriptor.
 *
 * @return CounterSampleBufferDescriptor* A newly allocated CounterSampleBufferDescriptor instance.
 */
_MTL_INLINE MTL::CounterSampleBufferDescriptor* MTL::CounterSampleBufferDescriptor::alloc()
{
    return NS::Object::alloc<MTL::CounterSampleBufferDescriptor>(_MTL_PRIVATE_CLS(MTLCounterSampleBufferDescriptor));
}

/**
 * @brief Retrieves the counter set associated with this descriptor.
 *
 * @return MTL::CounterSet* The associated counter set, or `nullptr` if no counter set is assigned.
 */
_MTL_INLINE MTL::CounterSet* MTL::CounterSampleBufferDescriptor::counterSet() const
{
    return Object::sendMessage<MTL::CounterSet*>(this, _MTL_PRIVATE_SEL(counterSet));
}

/**
 * @brief Initializes the counter sample buffer descriptor.
 *
 * @return CounterSampleBufferDescriptor* Pointer to the initialized descriptor instance.
 */
_MTL_INLINE MTL::CounterSampleBufferDescriptor* MTL::CounterSampleBufferDescriptor::init()
{
    return NS::Object::init<MTL::CounterSampleBufferDescriptor>();
}

/**
 * @brief Fetches the label of the counter sample buffer descriptor.
 *
 * @return NS::String* The descriptor's label string, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::CounterSampleBufferDescriptor::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Retrieves the number of counter samples configured for this descriptor.
 *
 * @return The configured sample count.
 */
_MTL_INLINE NS::UInteger MTL::CounterSampleBufferDescriptor::sampleCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(sampleCount));
}

/**
 * @brief Associates this descriptor with the given counter set.
 *
 * @param counterSet Counter set to assign to the descriptor.
 */
_MTL_INLINE void MTL::CounterSampleBufferDescriptor::setCounterSet(const MTL::CounterSet* counterSet)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCounterSet_), counterSet);
}

/**
 * @brief Set the human-readable label for the counter sample buffer descriptor.
 *
 * @param label The label string to assign to the descriptor; may be nullptr to clear the label.
 */
_MTL_INLINE void MTL::CounterSampleBufferDescriptor::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Set the number of samples the counter sample buffer will store.
 *
 * @param sampleCount Number of samples to allocate in the sample buffer.
 */
_MTL_INLINE void MTL::CounterSampleBufferDescriptor::setSampleCount(NS::UInteger sampleCount)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setSampleCount_), sampleCount);
}

/**
 * @brief Sets the storage mode for the counter sample buffer descriptor.
 *
 * @param storageMode Storage mode to use for the sample buffer memory.
 */
_MTL_INLINE void MTL::CounterSampleBufferDescriptor::setStorageMode(MTL::StorageMode storageMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStorageMode_), storageMode);
}

/**
 * @brief Retrieves the storage mode configured for this counter sample buffer descriptor.
 *
 * @return MTL::StorageMode The storage mode currently set on the descriptor.
 */
_MTL_INLINE MTL::StorageMode MTL::CounterSampleBufferDescriptor::storageMode() const
{
    return Object::sendMessage<MTL::StorageMode>(this, _MTL_PRIVATE_SEL(storageMode));
}

/**
 * @brief The device that created this counter sample buffer.
 *
 * @return MTL::Device* The device associated with this counter sample buffer.
 */
_MTL_INLINE MTL::Device* MTL::CounterSampleBuffer::device() const
{
    return Object::sendMessage<MTL::Device*>(this, _MTL_PRIVATE_SEL(device));
}

/**
 * @brief Gets the human-readable label assigned to the counter sample buffer.
 *
 * @return NS::String* The label string, or `nullptr` if no label has been set.
 */
_MTL_INLINE NS::String* MTL::CounterSampleBuffer::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Returns a data object containing resolved counter samples for the given sample index range.
 *
 * @param range Range of sample indices to resolve.
 * @return NS::Data* Binary data containing the resolved counter results for the specified range.
 */
_MTL_INLINE NS::Data* MTL::CounterSampleBuffer::resolveCounterRange(NS::Range range)
{
    return Object::sendMessage<NS::Data*>(this, _MTL_PRIVATE_SEL(resolveCounterRange_), range);
}

/**
 * @brief Retrieve the number of samples contained in this counter sample buffer.
 *
 * @return NS::UInteger The number of samples in the buffer.
 */
_MTL_INLINE NS::UInteger MTL::CounterSampleBuffer::sampleCount() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(sampleCount));
}