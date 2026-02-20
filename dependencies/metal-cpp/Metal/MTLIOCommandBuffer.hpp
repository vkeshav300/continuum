//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLIOCommandBuffer.hpp
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
#include "MTLTypes.hpp"
#include <cstdint>

namespace MTL
{
class Buffer;
class IOCommandBuffer;
class IOFileHandle;
class SharedEvent;
class Texture;
/**
 * @brief IO command buffer execution status.
 *
 * Represents the lifecycle state of an IOCommandBuffer.
 */
 
/**
 * @brief Requests a barrier in the command buffer to establish ordering.
 */

/**
 * @brief Registers a completion handler block to be called when the command buffer finishes.
 *
 * @param block Block invoked with the completed IOCommandBuffer.
 */

/**
 * @brief Registers a completion handler function to be called when the command buffer finishes.
 *
 * @param function Function invoked with the completed IOCommandBuffer.
 */

/**
 * @brief Commits the command buffer for execution.
 */

/**
 * @brief Copies the command buffer's completion status into a GPU-accessible buffer.
 *
 * @param buffer Destination buffer receiving the status.
 * @param offset Byte offset within `buffer` where the status will be written.
 */

/**
 * @brief Enqueues the command buffer for execution by the device/queue.
 */

/**
 * @brief Returns an error describing why the command buffer failed, if any.
 *
 * @return NS::Error* Error object if the buffer failed, `nullptr` otherwise.
 */

/**
 * @brief Returns the command buffer's label.
 *
 * @return NS::String* Label string, or `nullptr` if none is set.
 */

/**
 * @brief Schedules loading a range of a GPU buffer from a file-backed IO handle.
 *
 * @param buffer Destination GPU buffer.
 * @param offset Byte offset within `buffer` where data will be placed.
 * @param size Number of bytes to load.
 * @param sourceHandle Source IOFileHandle to read from.
 * @param sourceHandleOffset Byte offset within the source handle from which to start reading.
 */

/**
 * @brief Schedules loading raw bytes into GPU memory from a file-backed IO handle.
 *
 * @param pointer CPU-side source memory containing the data to load.
 * @param size Number of bytes to load.
 * @param sourceHandle Source IOFileHandle to read from.
 * @param sourceHandleOffset Byte offset within the source handle from which to start reading.
 */

/**
 * @brief Schedules loading a texture region from a file-backed IO handle into a GPU texture.
 *
 * @param texture Destination GPU texture.
 * @param slice Texture slice index for array or 3D textures.
 * @param level Mipmap level index.
 * @param size Size (width, height, depth) of the region to load.
 * @param sourceBytesPerRow Number of bytes per row in the source image data.
 * @param sourceBytesPerImage Number of bytes per image (slice) in the source data.
 * @param destinationOrigin Origin (x,y,z) within `texture` where the data will be placed.
 * @param sourceHandle Source IOFileHandle to read from.
 * @param sourceHandleOffset Byte offset within the source handle from which to start reading.
 */

/**
 * @brief Ends the current debug group.
 */

/**
 * @brief Begins a new debug group with the provided label.
 *
 * @param string Label for the debug group.
 */

/**
 * @brief Sets the command buffer's label.
 *
 * @param label Label string to assign to the command buffer.
 */

/**
 * @brief Signals a shared event with the specified value when the command buffer reaches that point.
 *
 * @param event SharedEvent to signal.
 * @param value Value to signal on the event.
 */

/**
 * @brief Returns the current IO status of the command buffer.
 *
 * @return IOStatus One of IOStatusPending, IOStatusCancelled, IOStatusError, or IOStatusComplete.
 */

/**
 * @brief Attempts to cancel the command buffer's execution.
 */

/**
 * @brief Inserts a wait for a shared event to reach a specific value before proceeding.
 *
 * @param event SharedEvent to wait on.
 * @param value Value to wait for.
 */

/**
 * @brief Blocks the caller until the command buffer has completed execution.
 */
_MTL_ENUM(NS::Integer, IOStatus) {
    IOStatusPending = 0,
    IOStatusCancelled = 1,
    IOStatusError = 2,
    IOStatusComplete = 3,
};

using IOCommandBufferHandler = void (^)(MTL::IOCommandBuffer*);
using IOCommandBufferHandlerFunction = std::function<void(MTL::IOCommandBuffer*)>;

class IOCommandBuffer : public NS::Referencing<IOCommandBuffer>
{
public:
    void        addBarrier();

    void        addCompletedHandler(const MTL::IOCommandBufferHandler block);
    void        addCompletedHandler(const MTL::IOCommandBufferHandlerFunction& function);

    void        commit();

    void        copyStatusToBuffer(const MTL::Buffer* buffer, NS::UInteger offset);

    void        enqueue();

    NS::Error*  error() const;

    NS::String* label() const;

    void        loadBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger size, const MTL::IOFileHandle* sourceHandle, NS::UInteger sourceHandleOffset);

    void        loadBytes(const void* pointer, NS::UInteger size, const MTL::IOFileHandle* sourceHandle, NS::UInteger sourceHandleOffset);

    void        loadTexture(const MTL::Texture* texture, NS::UInteger slice, NS::UInteger level, MTL::Size size, NS::UInteger sourceBytesPerRow, NS::UInteger sourceBytesPerImage, MTL::Origin destinationOrigin, const MTL::IOFileHandle* sourceHandle, NS::UInteger sourceHandleOffset);

    void        popDebugGroup();

    void        pushDebugGroup(const NS::String* string);

    void        setLabel(const NS::String* label);

    void        signalEvent(const MTL::SharedEvent* event, uint64_t value);

    IOStatus    status() const;

    void        tryCancel();

    void        wait(const MTL::SharedEvent* event, uint64_t value);
    void        waitUntilCompleted();
};

}
/**
 * @brief Inserts a synchronization barrier into the IO command buffer.
 *
 * Ensures that IO operations scheduled before the barrier complete before
 * any operations scheduled after the barrier begin.
 */
_MTL_INLINE void MTL::IOCommandBuffer::addBarrier()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(addBarrier));
}

/**
 * @brief Registers a completion handler to be invoked when the command buffer finishes.
 *
 * The provided handler will be called with this IOCommandBuffer as its sole argument after the buffer
 * reaches a terminal state (completed, cancelled, or errored).
 *
 * @param block Handler to invoke on completion; receives a pointer to the completed IOCommandBuffer.
 */
_MTL_INLINE void MTL::IOCommandBuffer::addCompletedHandler(const MTL::IOCommandBufferHandler block)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(addCompletedHandler_), block);
}

/**
 * @brief Registers a completion callback to be invoked when the command buffer finishes.
 *
 * The provided function will be called with the completed IOCommandBuffer instance as its sole argument.
 *
 * @param function Callback invoked when the command buffer completes; receives the completed `MTL::IOCommandBuffer*`.
 */
_MTL_INLINE void MTL::IOCommandBuffer::addCompletedHandler(const MTL::IOCommandBufferHandlerFunction& function)
{
    __block MTL::IOCommandBufferHandlerFunction blockFunction = function;
    addCompletedHandler(^(MTL::IOCommandBuffer* pCommandBuffer) { blockFunction(pCommandBuffer); });
}

/**
 * @brief Commits the command buffer and schedules it for execution.
 *
 * After this call the command buffer is scheduled for execution and must not be modified.
 */
_MTL_INLINE void MTL::IOCommandBuffer::commit()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(commit));
}

/**
 * @brief Copies the command buffer's status data into a GPU buffer.
 *
 * Copies the current IOCommandBuffer status representation into the provided MTL::Buffer starting at byte offset `offset`.
 *
 * @param buffer Destination buffer that receives the status data.
 * @param offset Byte offset into `buffer` where the status will be written.
 */
_MTL_INLINE void MTL::IOCommandBuffer::copyStatusToBuffer(const MTL::Buffer* buffer, NS::UInteger offset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(copyStatusToBuffer_offset_), buffer, offset);
}

/**
 * @brief Schedules this IOCommandBuffer for execution.
 *
 * Places the command buffer onto the device's execution queue so its recorded IO operations
 * will be processed in order.
 */
_MTL_INLINE void MTL::IOCommandBuffer::enqueue()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(enqueue));
}

/**
 * @brief Retrieves the error associated with the command buffer, if one occurred.
 *
 * @return NS::Error* Pointer to an NS::Error describing the failure, or `nullptr` if no error occurred.
 */
_MTL_INLINE NS::Error* MTL::IOCommandBuffer::error() const
{
    return Object::sendMessage<NS::Error*>(this, _MTL_PRIVATE_SEL(error));
}

/**
 * @brief Retrieves the command buffer's label.
 *
 * @return NS::String* The label assigned to the command buffer, or `nullptr` if no label is set.
 */
_MTL_INLINE NS::String* MTL::IOCommandBuffer::label() const
{
    return Object::sendMessage<NS::String*>(this, _MTL_PRIVATE_SEL(label));
}

/**
 * @brief Schedules a transfer of bytes from an IOFileHandle into a GPU buffer.
 *
 * Copies `size` bytes from `sourceHandle` starting at `sourceHandleOffset` into `buffer` starting at `offset`.
 *
 * @param buffer Destination GPU buffer to receive the data.
 * @param offset Byte offset into `buffer` where the data will be placed.
 * @param size Number of bytes to transfer.
 * @param sourceHandle Source file handle providing the data.
 * @param sourceHandleOffset Byte offset within `sourceHandle` from which to begin copying.
 */
_MTL_INLINE void MTL::IOCommandBuffer::loadBuffer(const MTL::Buffer* buffer, NS::UInteger offset, NS::UInteger size, const MTL::IOFileHandle* sourceHandle, NS::UInteger sourceHandleOffset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(loadBuffer_offset_size_sourceHandle_sourceHandleOffset_), buffer, offset, size, sourceHandle, sourceHandleOffset);
}

/**
 * @brief Enqueues a request to load raw bytes from an IOFileHandle into a destination memory region.
 *
 * Enqueues an operation that copies `size` bytes starting at `sourceHandleOffset` from `sourceHandle`
 * into the memory pointed to by `pointer` as part of this IO command buffer's work.
 *
 * @param pointer Destination memory address where the loaded bytes will be written.
 * @param size Number of bytes to load.
 * @param sourceHandle Source IOFileHandle to read bytes from.
 * @param sourceHandleOffset Byte offset within `sourceHandle` at which to begin reading.
 */
_MTL_INLINE void MTL::IOCommandBuffer::loadBytes(const void* pointer, NS::UInteger size, const MTL::IOFileHandle* sourceHandle, NS::UInteger sourceHandleOffset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(loadBytes_size_sourceHandle_sourceHandleOffset_), pointer, size, sourceHandle, sourceHandleOffset);
}

/**
 * @brief Loads a region of image data from an IO file handle into a texture.
 *
 * Loads a rectangular region defined by `size` into `texture` at the specified `slice` and mipmap `level`, using the byte layout described by `sourceBytesPerRow` and `sourceBytesPerImage`, and placing the region at `destinationOrigin`.
 *
 * @param texture Destination texture to receive the loaded data.
 * @param slice Array slice index in the destination texture.
 * @param level Mipmap level in the destination texture.
 * @param size Dimensions (width, height, depth) of the region to load, in texels.
 * @param sourceBytesPerRow Number of bytes between successive rows in the source data.
 * @param sourceBytesPerImage Number of bytes between successive images (slices) in the source data.
 * @param destinationOrigin Origin within the destination texture where the region will be placed.
 * @param sourceHandle IO file handle to read the source image data from.
 * @param sourceHandleOffset Byte offset within `sourceHandle` where the image data begins.
 */
_MTL_INLINE void MTL::IOCommandBuffer::loadTexture(const MTL::Texture* texture, NS::UInteger slice, NS::UInteger level, MTL::Size size, NS::UInteger sourceBytesPerRow, NS::UInteger sourceBytesPerImage, MTL::Origin destinationOrigin, const MTL::IOFileHandle* sourceHandle, NS::UInteger sourceHandleOffset)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(loadTexture_slice_level_size_sourceBytesPerRow_sourceBytesPerImage_destinationOrigin_sourceHandle_sourceHandleOffset_), texture, slice, level, size, sourceBytesPerRow, sourceBytesPerImage, destinationOrigin, sourceHandle, sourceHandleOffset);
}

/**
 * @brief Ends the current debug group for the command buffer.
 *
 * Pops the most recently pushed debug group marker, restoring the previous debug group state.
 */
_MTL_INLINE void MTL::IOCommandBuffer::popDebugGroup()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(popDebugGroup));
}

/**
 * @brief Begins a new debug group with the given label.
 *
 * Subsequent debug commands are grouped until popDebugGroup() is called.
 *
 * @param string Label for the debug group; may be null to start an unnamed group.
 */
_MTL_INLINE void MTL::IOCommandBuffer::pushDebugGroup(const NS::String* string)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(pushDebugGroup_), string);
}

/**
 * @brief Sets the debug label for the command buffer.
 *
 * @param label Human-readable name used for identification and debugging; may be null to clear the label.
 */
_MTL_INLINE void MTL::IOCommandBuffer::setLabel(const NS::String* label)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setLabel_), label);
}

/**
 * @brief Schedules a signal for the specified SharedEvent with the given value when this command buffer executes.
 *
 * @param event The SharedEvent to signal.
 * @param value The 64-bit value to signal the event with.
 */
_MTL_INLINE void MTL::IOCommandBuffer::signalEvent(const MTL::SharedEvent* event, uint64_t value)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(signalEvent_value_), event, value);
}

/**
 * @brief Query the current status of the IO command buffer.
 *
 * @return MTL::IOStatus indicating the command buffer's current state: `IOStatusPending`, `IOStatusCancelled`, `IOStatusError`, or `IOStatusComplete`.
 */
_MTL_INLINE MTL::IOStatus MTL::IOCommandBuffer::status() const
{
    return Object::sendMessage<MTL::IOStatus>(this, _MTL_PRIVATE_SEL(status));
}

/**
 * @brief Requests cancellation of the command buffer.
 *
 * Signals that the command buffer should cancel execution. Pending or scheduled I/O operations may be aborted and the buffer's status may transition to MTL::IOStatusCancelled; registered completion handlers may still be invoked.
 */
_MTL_INLINE void MTL::IOCommandBuffer::tryCancel()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(tryCancel));
}

/**
 * @brief Waits for a shared event to reach a specified value.
 *
 * Blocks the caller until the provided SharedEvent's signaled value reaches the given value.
 *
 * @param event The shared event to observe.
 * @param value The target signaled value to wait for.
 */
_MTL_INLINE void MTL::IOCommandBuffer::wait(const MTL::SharedEvent* event, uint64_t value)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(waitForEvent_value_), event, value);
}

/**
 * @brief Blocks the current thread until the command buffer finishes execution.
 *
 * Waits until the command buffer reaches a terminal state (completed, cancelled, or errored).
 */
_MTL_INLINE void MTL::IOCommandBuffer::waitUntilCompleted()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(waitUntilCompleted));
}