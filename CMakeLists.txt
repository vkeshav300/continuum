# Validity checks
if (NOT APPLE)
	message(FATAL_ERROR "This project is only supported on macOS")
endif()

# CMake config
cmake_minimum_required(VERSION 3.31.6)

# Debug config
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DDEBUG)
	message(STATUS "Debug mode enabled")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
endif()

# Project config
project(
	continuum
	LANGUAGES CXX
)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(EXTERNAL_HEADERS_DIR "${CMAKE_SOURCE_DIR}/dependencies")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Config
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Exports data which enables some LSPs

# Find packages
find_package(GLFW3 REQUIRED)
find_package(EnTT REQUIRED)

# Process source files 
file(GLOB_RECURSE SOURCES
	"${SOURCE_DIR}/*.cpp"
	"${SOURCE_DIR}/*.mm"
)

add_executable(
	${PROJECT_NAME}
	${SOURCES}
)

# Process header files
target_include_directories(
	${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${GLFW3_INCLUDE_DIRS}
    ${EnTT_INCLUDE_DIRS}
	${EXTERNAL_HEADERS_DIR}/metal-cpp
	${EXTERNAL_HEADERS_DIR}/metal-cpp-extensions
	${EXTERNAL_HEADERS_DIR}/stb
)

# Link external packages / libraries
target_link_libraries(
	${PROJECT_NAME} PUBLIC
	${GLFW3_LIBRARIES}
    EnTT::EnTT
	"-framework Metal"
	"-framework Foundation"
	"-framework Quartzcore"
	"-framework IOKit"
	"-framework Cocoa"
	"-framework CoreGraphics"
	"-framework AppKit"
	"-framework MetalKit"
	objc
)
