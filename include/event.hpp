#pragma once

#include <mutex>
#include <utility>

#include <entt/signal/sigh.hpp>

namespace CTNM {

template <typename... Args> class Event {
public:
  using signal_t = entt::sigh<void(Args...)>;

  Event() = default;
  ~Event() { clear(); }

  template <auto connection, typename T> entt::connection connect(T &obj) {
    const std::lock_guard<std::mutex> lock(m_mtx);
    return m_sink.template connect<connection>(obj);
  }

  template <auto connection, typename T> void disconnect(T &obj) {
    const std::lock_guard<std::mutex> lock(m_mtx);
    m_sink.template disconnect<connection>(obj);
  }

  void clear() {
    const std::lock_guard<std::mutex> lock(m_mtx);
    m_sink.disconnect();
  }

  void fire(Args... args) {
    signal_t signal; // Prevent thread race cases
    {
      const std::lock_guard<std::mutex> lock(m_mtx);
      signal = m_signal;
    }

    signal.publish(std::forward<Args>(args)...);
  }

private:
  signal_t m_signal{};
  entt::sink<signal_t> m_sink{m_signal};
  std::mutex m_mtx;
};

} // namespace CTNM
