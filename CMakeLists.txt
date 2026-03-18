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
set(METAL_LANG_STANDARD "metal4.0" CACHE STRING
    "Metal shading language version passed to the metal compiler")
set(METAL_TOOLCHAIN "" CACHE STRING
    "Optional xcrun toolchain (for example: MetalToolchain)")

set(METAL_XCRUN_ARGS -sdk macosx)
if (METAL_TOOLCHAIN)
    set(METAL_XCRUN_ARGS --toolchain ${METAL_TOOLCHAIN} -sdk macosx)
endif()

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

# Build metal shaders into .metallib
file(GLOB METAL_SHADERS "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.metal")
set(AIR_FILES "")

foreach(SHADER ${METAL_SHADERS})
    get_filename_component(NAME ${SHADER} NAME_WE)
    set(AIR_FILE "${CMAKE_CURRENT_BINARY_DIR}/${NAME}.air")
    add_custom_command(
        OUTPUT ${AIR_FILE}
        COMMAND xcrun ${METAL_XCRUN_ARGS} metal -std=${METAL_LANG_STANDARD} -I${CMAKE_SOURCE_DIR}/include -c ${SHADER} -o ${AIR_FILE}
        DEPENDS ${SHADER}
        COMMENT "Building MTL object ${AIR_FILE}" # Make it look cool :)
        VERBATIM
    )
    list(APPEND AIR_FILES ${AIR_FILE})
endforeach()

set(METALLIB "${CMAKE_CURRENT_BINARY_DIR}/default.metallib")
execute_process(
    COMMAND xcrun ${METAL_XCRUN_ARGS} --find metallib
    RESULT_VARIABLE METALLIB_FIND_RESULT
    OUTPUT_VARIABLE METALLIB_EXECUTABLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

if (METALLIB_FIND_RESULT EQUAL 0 AND METALLIB_EXECUTABLE)
    set(METAL_LINK_TOOL metallib)
else()
    set(METAL_LINK_TOOL metal)
    message(STATUS "metallib tool not found; using metal for metallib linking")
endif()

add_custom_command(
    OUTPUT ${METALLIB}
    COMMAND xcrun ${METAL_XCRUN_ARGS} ${METAL_LINK_TOOL} ${AIR_FILES} -o ${METALLIB}
    DEPENDS ${AIR_FILES}
    COMMENT "Linking MTL library ${METALLIB}"
    VERBATIM
)

add_custom_target(metallib ALL
    DEPENDS ${METALLIB}
)

add_dependencies(${PROJECT_NAME} metallib)
