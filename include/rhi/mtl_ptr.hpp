#pragma once

#include <cstddef>
#include <utility>

#ifdef __APPLE__

#include <Metal/Metal.hpp>

namespace CTNM::RHI {

template <typename T> class MTL_Unique {
private:
  T *m_ptr = nullptr;

public:
  MTL_Unique() = default;
  MTL_Unique(std::nullptr_t) {}
  MTL_Unique(T *ptr) : m_ptr(ptr) {}

  ~MTL_Unique() { smart_release(); }

  MTL_Unique(const MTL_Unique &) = delete;
  MTL_Unique &operator=(const MTL_Unique &) = delete;

  MTL_Unique(MTL_Unique &&other) noexcept
      : m_ptr(std::exchange(other.m_ptr, nullptr)) {}

  MTL_Unique &operator=(MTL_Unique &&other) noexcept {
    if (this != &other) {
      smart_release();
      m_ptr = std::exchange(other.m_ptr, nullptr);
    }

    return *this;
  }

  MTL_Unique &operator=(T *ptr) {
    if (m_ptr != ptr) {
      smart_release();
      m_ptr = ptr;
    }

    return *this;
  }

  T *get() const { return m_ptr; }

  T *operator->() { return m_ptr; }

  const T *operator->() const { return m_ptr; }

  void smart_release() {
    if (!m_ptr)
      return;

    m_ptr->release();
    m_ptr = nullptr;
  }

  bool exists() const { return m_ptr != nullptr; }
};

template <typename T> class MTL_Shared {
private:
  T *m_ptr = nullptr;

public:
  MTL_Shared() = default;
  MTL_Shared(std::nullptr_t) {}
  MTL_Shared(T *ptr) : m_ptr(ptr) {}

  static MTL_Shared retained(T *ptr) {
    MTL_Shared shared;
    if (ptr)
      ptr->retain();
    shared.m_ptr = ptr;
    return shared;
  }

  ~MTL_Shared() { smart_release(); }

  MTL_Shared(const MTL_Shared &other) : m_ptr(other.m_ptr) {
    if (m_ptr)
      m_ptr->retain();
  }

  MTL_Shared &operator=(const MTL_Shared &other) {
    if (this != &other) {
      smart_release();
      m_ptr = other.m_ptr;
      if (m_ptr)
        m_ptr->retain();
    }

    return *this;
  }

  MTL_Shared(MTL_Shared &&other) noexcept
      : m_ptr(std::exchange(other.m_ptr, nullptr)) {}

  MTL_Shared &operator=(MTL_Shared &&other) noexcept {
    if (this != &other) {
      smart_release();
      m_ptr = std::exchange(other.m_ptr, nullptr);
    }

    return *this;
  }

  MTL_Shared &operator=(std::nullptr_t) {
    smart_release();
    return *this;
  }

  MTL_Shared &operator=(T *ptr) {
    if (m_ptr != ptr) {
      smart_release();
      m_ptr = ptr;
    }

    return *this;
  }

  T *get() const { return m_ptr; }

  T *operator->() { return m_ptr; }

  const T *operator->() const { return m_ptr; }

  void smart_release() {
    if (!m_ptr)
      return;

    m_ptr->release();
    m_ptr = nullptr;
  }

  bool exists() const { return m_ptr != nullptr; }
};

}; // namespace CTNM::RHI

#endif
