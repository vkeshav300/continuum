#pragma once

#include <utility>

#ifdef __APPLE__

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

template <typename T> class MTL_Ptr {
private:
  T *m_ptr = nullptr;

  void set_nullptr() { m_ptr = nullptr; }

public:
  MTL_Ptr(T *ptr) : m_ptr(ptr) {}

  ~MTL_Ptr() { smart_release(); }

  T *get() const { return m_ptr; }

  T *operator->() { return m_ptr; }

  const T *operator->() const { return m_ptr; }

  MTL_Ptr(const MTL_Ptr &other) : m_ptr(other.m_ptr) {
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

  MTL_Ptr(MTL_Ptr &&other) noexcept : m_ptr(other.m_ptr) {
    other.set_nullptr();
  }

  MTL_Ptr &operator=(MTL_Ptr &&other) noexcept {
    if (this != &other) {
      smart_release();

      m_ptr = std::exchange(other.m_ptr, nullptr);
    }

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

    m_ptr->release();
    m_ptr = nullptr;
  }

  bool exists() const { return m_ptr; }
};

}; // namespace CTNM::RHI

#endif
