#pragma once

#include <type_traits>
#include <utility>

#ifdef __APPLE__

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

template <typename T> class MTL_Ptr {
private:
  T *m_ptr = nullptr;
  bool m_mark = false; /**
 * @brief Set the internal raw pointer to `nullptr`.
 *
 * Leaves the mark flag unchanged and does not perform any release or lifecycle calls.
 */

  void set_nullptr() { m_ptr = nullptr; }

public:
  /**
 * @brief Initializes the wrapper with a raw Metal object pointer.
 *
 * @param ptr Raw pointer to a Metal object; stored as-is. The constructor does not modify ownership semantics (it does not call `retain()` or perform lifecycle actions).
 */
MTL_Ptr(T *ptr) : m_ptr(ptr) {}

  /**
 * @brief Releases the managed Metal object and completes its encoding lifecycle if necessary.
 *
 * Performs any required final lifecycle operations for the wrapped Metal object (for example, committing
 * command buffers or ending encoders) and decrements the object's reference count before the wrapper is destroyed.
 */
~MTL_Ptr() { smart_release(); }

  /**
 * @brief Access the managed Metal object pointer.
 *
 * @return T* Raw pointer to the managed Metal object, or nullptr if no object is held.
 */
  T *get() const { return m_ptr; }
  /**
 * @brief Provide non-const access to the managed pointer.
 *
 * @return T* Pointer to the managed object, or nullptr if none is held.
 */
T *operator->() { return m_ptr; }
  /**
 * @brief Accesses the managed Metal object for read-only operations.
 *
 * @return const T* Pointer to the managed object, or `nullptr` if none.
 */
const T *operator->() const { return m_ptr; }

  /**
   * @brief Construct a new MTL_Ptr as a copy of another instance.
   *
   * Creates a new smart pointer that shares the same underlying Metal object and copies the mark state.
   *
   * @param other Source MTL_Ptr to copy; if it holds a non-null pointer, the underlying object's reference count is incremented.
   */
  MTL_Ptr(const MTL_Ptr &other) : m_ptr(other.m_ptr), m_mark(other.m_mark) {
    if (m_ptr)
      m_ptr->retain();
  }

  /**
   * @brief Copy-assigns from another MTL_Ptr, replacing the currently managed object.
   *
   * Releases the currently held Metal object if present, copies the raw pointer and mark
   * state from @p other, and increments the underlying object's reference count if the
   * copied pointer is non-null.
   *
   * @param other Source MTL_Ptr to copy from.
   * @return MTL_Ptr& Reference to this object.
   */
  MTL_Ptr &operator=(const MTL_Ptr &other) {
    if (this != &other) {
      smart_release();

      m_ptr = other.m_ptr;
      m_mark = other.m_mark;
      if (m_ptr)
        m_ptr->retain();
    }

    return *this;
  }

  /**
   * @brief Move-constructs an MTL_Ptr by transferring ownership and mark state from another instance.
   *
   * Transfers the managed pointer and the mark flag from `other` to the new object. After construction,
   * `other` is left with a null pointer and its mark cleared.
   *
   * @param other Source MTL_Ptr to move from.
   */
  MTL_Ptr(MTL_Ptr &&other) noexcept : m_ptr(other.m_ptr), m_mark(other.m_mark) {
    other.set_nullptr();
    other.m_mark = false;
  }

  /**
   * @brief Move-assigns from another MTL_Ptr, releasing the current resource and taking ownership of the source's pointer and mark.
   *
   * @param other Rvalue reference to the source MTL_Ptr; after assignment the source's pointer is null and its mark is false.
   * @return MTL_Ptr& Reference to this instance.
   */
  MTL_Ptr &operator=(MTL_Ptr &&other) noexcept {
    if (this != &other) {
      smart_release();

      m_ptr = std::exchange(other.m_ptr, nullptr);
      m_mark = other.m_mark;
      other.m_mark = false;
    }

    return *this;
  }

  /**
   * @brief Replace the currently managed Metal pointer with a new raw pointer.
   *
   * Releases the currently managed object (if any) and then stores `ptr` as the new managed pointer.
   *
   * @param ptr Raw Metal object pointer to adopt; its reference count is not modified by this call.
   * @return MTL_Ptr& Reference to this object after assignment.
   */
  MTL_Ptr &operator=(T *ptr) {
    smart_release();
    m_ptr = ptr;

    return *this;
  }

  /**
   * @brief Finalizes and releases the managed Metal object, performing any required lifecycle calls.
   *
   * If the stored pointer is non-null, performs a type-specific finalization: for `MTL::CommandBuffer` it calls
   * `commit()` if not already marked; for `MTL::AccelerationStructureCommandEncoder`, `MTL::ComputeCommandEncoder`,
   * or `MTL::RenderCommandEncoder` it calls `endEncoding()` if not already marked. In all cases it then calls
   * `release()` on the object, sets the internal pointer to `nullptr`, and marks the object as finalized when a
   * lifecycle call was performed.
   */
  void smart_release() {
    if (!m_ptr)
      return;

    if constexpr (std::is_same_v<T, MTL::CommandBuffer>) {
      if (!m_mark) {
        m_ptr->commit();
        m_mark = true;
      }
    }

    if constexpr (std::is_same_v<T, MTL::AccelerationStructureCommandEncoder> ||
                  std::is_same_v<T, MTL::ComputeCommandEncoder> ||
                  std::is_same_v<T, MTL::RenderCommandEncoder>) {
      if (!m_mark) {
        m_ptr->endEncoding();
        m_mark = true;
      }
    }

    m_ptr->release();
    m_ptr = nullptr;
  }

  /**
 * @brief Indicates whether the managed Metal object has been finalized (commit or endEncoding performed).
 *
 * @return `true` if the object has been finalized, `false` otherwise.
 */
bool get_mark() const { return m_mark; }
  /**
 * @brief Set the internal mark indicating whether the object's lifecycle action has been performed.
 *
 * @param value `true` to mark that the lifecycle action (e.g., commit or endEncoding) has been performed, `false` to clear the mark.
 *
 * This method only updates the mark flag and does not modify the managed pointer or invoke any Metal lifecycle calls.
 */
void set_mark(bool value) { m_mark = value; }
};

}; // namespace CTNM::RHI

#endif