#include "window.hpp"

#include <chrono>
#include <thread>

int main(int argc, char *argv[]) {
  CTNM::Window win(CTNM::FB_Size{800, 600});

  while (!win.should_close()) {
    win.poll_events();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  return 0;
}
