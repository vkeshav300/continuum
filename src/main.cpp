/*
 * TEMPORARY MAIN FILE
 */
#include <iostream>

#include "rhi/renderer.hpp"

/**
 * @brief Program entry point that initializes and runs the renderer.
 *
 * Prints the program version to standard output, constructs a CTNM::RHI::Renderer,
 * invokes its staging and rendering steps, and then exits.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return int `0` on successful termination.
 */
int main(int argc, char *argv[]) {
  std::cout << "Continuum v0.0.0\n";

  CTNM::RHI::Renderer renderer = CTNM::RHI::Renderer();
  renderer.stage();
  renderer.render();

  return 0;
}