#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

#ifdef __APPLE__

#include <AppKit/AppKit.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace CTNM::RHI::Bridges {

NS::Window *get_ns_win(GLFWwindow *win, CA::MetalLayer *layer);

void detach_ns_win(GLFWwindow *win);

} // namespace CTNM::RHI::Bridges

#endif
