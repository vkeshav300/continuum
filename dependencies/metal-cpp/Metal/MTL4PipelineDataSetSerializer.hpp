//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTL4PipelineDataSetSerializer.hpp
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

namespace MTL4
{
class PipelineDataSetSerializerDescriptor;

/**
 * @brief Configuration flags for PipelineDataSetSerializer behavior.
 *
 * Flags that control what the serializer captures when producing outputs.
 *
 * - PipelineDataSetSerializerConfigurationCaptureDescriptors: Capture descriptor metadata.
 * - PipelineDataSetSerializerConfigurationCaptureBinaries: Capture binary data.
 */

/**
 * @brief Descriptor used to configure a PipelineDataSetSerializer.
 *
 * Produces and holds configuration settings used when creating or running a
 * PipelineDataSetSerializer.
 */

/**
 * @brief Allocates a new PipelineDataSetSerializerDescriptor instance.
 *
 * @return PipelineDataSetSerializerDescriptor* A newly allocated descriptor object.
 */

/**
 * @brief Returns the current configuration flags for the descriptor.
 *
 * @return PipelineDataSetSerializerConfiguration Current configuration flags.
 */

/**
 * @brief Initializes the descriptor instance.
 *
 * @return PipelineDataSetSerializerDescriptor* The initialized descriptor object.
 */

/**
 * @brief Sets the configuration flags for the descriptor.
 *
 * @param configuration Configuration flags to apply to the descriptor.
 */

/**
 * @brief Serializer for pipeline data sets.
 *
 * Produces serialized representations of pipeline datasets according to a
 * descriptor's configuration.
 */

/**
 * @brief Serialize the dataset as an archive and flush it to the specified URL.
 *
 * @param url Destination file URL where the archive will be written.
 * @param error Pointer to receive an NSError on failure.
 * @return `true` if serialization and flush succeeded, `false` otherwise.
 */

/**
 * @brief Serialize the dataset into a pipelines script and return it as data.
 *
 * @param error Pointer to receive an NSError on failure.
 * @return NS::Data* Data containing the pipelines script, or `nullptr` on failure.
 */
_MTL_OPTIONS(NS::UInteger, PipelineDataSetSerializerConfiguration) {
    PipelineDataSetSerializerConfigurationCaptureDescriptors = 1,
    PipelineDataSetSerializerConfigurationCaptureBinaries = 1 << 1,
};

class PipelineDataSetSerializerDescriptor : public NS::Copying<PipelineDataSetSerializerDescriptor>
{
public:
    static PipelineDataSetSerializerDescriptor* alloc();

    PipelineDataSetSerializerConfiguration      configuration() const;

    PipelineDataSetSerializerDescriptor*        init();

    void                                        setConfiguration(MTL4::PipelineDataSetSerializerConfiguration configuration);
};
class PipelineDataSetSerializer : public NS::Referencing<PipelineDataSetSerializer>
{
public:
    bool      serializeAsArchiveAndFlushToURL(const NS::URL* url, NS::Error** error);

    NS::Data* serializeAsPipelinesScript(NS::Error** error);
};

}
/**
 * @brief Allocate a new PipelineDataSetSerializerDescriptor instance.
 *
 * The returned object is allocated but not initialized; call `init()` on the result
 * before use.
 *
 * @return MTL4::PipelineDataSetSerializerDescriptor* Pointer to a newly allocated descriptor.
 */
_MTL_INLINE MTL4::PipelineDataSetSerializerDescriptor* MTL4::PipelineDataSetSerializerDescriptor::alloc()
{
    return NS::Object::alloc<MTL4::PipelineDataSetSerializerDescriptor>(_MTL_PRIVATE_CLS(MTL4PipelineDataSetSerializerDescriptor));
}

/**
 * @brief Gets the current pipeline dataset serializer configuration.
 *
 * @return PipelineDataSetSerializerConfiguration The configured flags for the serializer descriptor.
 */
_MTL_INLINE MTL4::PipelineDataSetSerializerConfiguration MTL4::PipelineDataSetSerializerDescriptor::configuration() const
{
    return Object::sendMessage<MTL4::PipelineDataSetSerializerConfiguration>(this, _MTL_PRIVATE_SEL(configuration));
}

/**
 * @brief Initializes a PipelineDataSetSerializerDescriptor instance.
 *
 * @return PipelineDataSetSerializerDescriptor* Pointer to the initialized descriptor, or `nullptr` on failure.
 */
_MTL_INLINE MTL4::PipelineDataSetSerializerDescriptor* MTL4::PipelineDataSetSerializerDescriptor::init()
{
    return NS::Object::init<MTL4::PipelineDataSetSerializerDescriptor>();
}

/**
 * @brief Set which dataset elements the serializer will capture.
 *
 * Configure the serializer descriptor with one or more PipelineDataSetSerializerConfiguration flags
 * to control captured content (for example, PipelineDataSetSerializerConfigurationCaptureDescriptors
 * and PipelineDataSetSerializerConfigurationCaptureBinaries).
 *
 * @param configuration Bitmask of PipelineDataSetSerializerConfiguration flags.
 */
_MTL_INLINE void MTL4::PipelineDataSetSerializerDescriptor::setConfiguration(MTL4::PipelineDataSetSerializerConfiguration configuration)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setConfiguration_), configuration);
}

/**
 * @brief Serialize the pipeline dataset as an archive and flush it to the specified URL.
 *
 * @param url Destination file URL where the archive will be written.
 * @param error If non-null and the operation fails, set to an NSError describing the failure; pass `nullptr` to ignore error details.
 * @return `true` if the archive was written and flushed successfully, `false` otherwise.
 */
_MTL_INLINE bool MTL4::PipelineDataSetSerializer::serializeAsArchiveAndFlushToURL(const NS::URL* url, NS::Error** error)
{
    return Object::sendMessage<bool>(this, _MTL_PRIVATE_SEL(serializeAsArchiveAndFlushToURL_error_), url, error);
}

/**
 * @brief Serializes the pipeline data set into a pipelines script.
 *
 * Attempts to produce a pipelines script representation of the receiver's pipeline data.
 *
 * @param error If non-null and serialization fails, set to an NSError describing the failure.
 * @return NS::Data* Binary data containing the pipelines script on success, `nullptr` on failure.
 */
_MTL_INLINE NS::Data* MTL4::PipelineDataSetSerializer::serializeAsPipelinesScript(NS::Error** error)
{
    return Object::sendMessage<NS::Data*>(this, _MTL_PRIVATE_SEL(serializeAsPipelinesScriptWithError_), error);
}