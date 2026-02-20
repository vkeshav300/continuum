//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLIOCompressor.hpp
//
// Copyright 2020-2024 Apple Inc.
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

#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLDevice.hpp"

#include "../Foundation/Foundation.hpp"

namespace MTL
{
using IOCompressionContext=void*;

/**
 * @brief Status values returned by IOFlushAndDestroyCompressionContext.
 *
 * Represents whether flushing and destruction of a compression context completed successfully.
 */
 
/**
 * @brief Returns the recommended default chunk size for compression contexts.
 *
 * @return size_t Default chunk size in bytes to use when creating a compression context.
 */

/**
 * @brief Creates a new compression context for writing compressed data to the given path.
 *
 * @param path Filesystem path or destination identifier where compressed output will be written.
 * @param type Compression method to use.
 * @param chunkSize Chunk size in bytes to use for internal buffering; use 0 to accept the default.
 * @return IOCompressionContext A new compression context on success, or `nullptr` if creation is unavailable or fails.
 */

/**
 * @brief Appends a block of input data to an existing compression context.
 *
 * @param context Compression context returned by IOCreateCompressionContext.
 * @param data Pointer to the input bytes to append.
 * @param size Number of bytes at `data` to append.
 */

/**
 * @brief Flushes any pending compressed data and destroys the compression context.
 *
 * @param context Compression context to flush and destroy.
 * @return IOCompressionStatus `IOCompressionStatusComplete` if flushing and destruction succeeded, `IOCompressionStatusError` otherwise.
 */
_MTL_ENUM(NS::Integer, IOCompressionStatus) {
    IOCompressionStatusComplete = 0,
    IOCompressionStatusError = 1,
};

size_t IOCompressionContextDefaultChunkSize();

IOCompressionContext IOCreateCompressionContext(const char* path, IOCompressionMethod type, size_t chunkSize);

void IOCompressionContextAppendData(IOCompressionContext context, const void* data, size_t size);

IOCompressionStatus IOFlushAndDestroyCompressionContext(IOCompressionContext context);

}

#if defined(MTL_PRIVATE_IMPLEMENTATION)

namespace MTL::Private {

MTL_DEF_FUNC(MTLIOCompressionContextDefaultChunkSize, size_t (*)(void));

MTL_DEF_FUNC( MTLIOCreateCompressionContext, void* (*)(const char*, MTL::IOCompressionMethod, size_t) );

MTL_DEF_FUNC( MTLIOCompressionContextAppendData, void (*)(void*, const void*, size_t) );

MTL_DEF_FUNC( MTLIOFlushAndDestroyCompressionContext, MTL::IOCompressionStatus (*)(void*) );

}

_NS_EXPORT size_t MTL::IOCompressionContextDefaultChunkSize()
{
    return MTL::Private::MTLIOCompressionContextDefaultChunkSize();
}

_NS_EXPORT void* MTL::IOCreateCompressionContext(const char* path, IOCompressionMethod type, size_t chunkSize)
{
    if ( MTL::Private::MTLIOCreateCompressionContext )
    {
        return MTL::Private::MTLIOCreateCompressionContext( path, type, chunkSize );
    }
    return nullptr;
}

_NS_EXPORT void MTL::IOCompressionContextAppendData(void* context, const void* data, size_t size)
{
    if ( MTL::Private::MTLIOCompressionContextAppendData )
    {
        MTL::Private::MTLIOCompressionContextAppendData( context, data, size );
    }
}

_NS_EXPORT MTL::IOCompressionStatus MTL::IOFlushAndDestroyCompressionContext(void* context)
{
    if ( MTL::Private::MTLIOFlushAndDestroyCompressionContext )
    {
        return MTL::Private::MTLIOFlushAndDestroyCompressionContext( context );
    }
    return MTL::IOCompressionStatusError;
}

#endif