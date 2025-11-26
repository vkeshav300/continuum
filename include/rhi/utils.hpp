#pragma once

#include <type_traits>
#include <utility>

#ifdef __APPLE__

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

template <typename T> class MTL_Ptr {
private:
  T *m_ptr = nullptr;
  bool m_mark = false; // For command buffer or encoders

  void set_nullptr() { m_ptr = nullptr; }

public:
  MTL_Ptr(T *ptr) : m_ptr(ptr) {}

  ~MTL_Ptr() { smart_release(); }

  /* Get */
  T *get() const { return m_ptr; }
  T *operator->() { return m_ptr; }
  const T *operator->() const { return m_ptr; }

  /* Copy */
  MTL_Ptr(const MTL_Ptr &other) {
    if (m_ptr)
      m_ptr->retain();
  }

  MTL_Ptr &operator=(const MTL_Ptr &other) {
    if (this != &other) {
      smart_release();

      m_ptr = other.m_ptr;
      if (m_ptr)
        m_ptr->retain();
    }

    return *this;
  }

  /* Move */
  MTL_Ptr(MTL_Ptr &&other) noexcept : m_ptr(other.m_ptr) {
    other.set_nullptr();
  }

  MTL_Ptr &operator=(MTL_Ptr &&other) noexcept {
    m_ptr = std::exchange(other.m_ptr, nullptr);

    return *this;
  }

  MTL_Ptr &operator=(T *ptr) {
    smart_release();
    m_ptr = ptr;

    return *this;
  }

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
                  std::is_same_v<T, MTL::ComputeCommandEncoder>) {
      if (!m_mark) {
        m_ptr->endEncoding();
        m_mark = true;
      }
    }

    m_ptr->release();
    m_ptr = nullptr;
  }

  bool get_mark() const { return m_mark; }
  void set_mark(bool value) { m_mark = value; }
};

}; // namespace CTNM::RHI

#endif
