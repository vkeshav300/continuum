/*
 * TEMPORARY MAIN FILE
 */
#include <iostream>

#include "rhi/renderer.hpp"

int main(int argc, char *argv[]) {
  std::cout << "Continuum v0.0.0\n";

  CTNM::RHI::Renderer renderer = CTNM::RHI::Renderer();
  renderer.stage();
  renderer.render();

  return 0;
}
