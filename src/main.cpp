/*
 * TEMPORARY MAIN FILE
 */
#include <iostream>

#include "rhi/renderer.hpp"

int main(int argc, char *argv[]) {
  std::cout << "Continuum v0.0.0\n";

  CTNM::RHI::Renderer renderer = CTNM::RHI::Renderer(800, 700);
  renderer.stage();
  renderer.render_to_preview();

  return 0;
}
