# Courtesy of AI

# - Try to find EnTT
# Once done, this will define:
#   EnTT_FOUND          - system has EnTT
#   EnTT_INCLUDE_DIRS   - the EnTT include directory
#   EnTT::EnTT          - imported INTERFACE target

# -----------------------------------------------------------------------------
# Search paths
# -----------------------------------------------------------------------------
set(_ENTT_HINTS
    ${EnTT_ROOT}
    $ENV{EnTT_ROOT}
    /usr/local/include
    /usr/include
    /opt/homebrew/include
    /opt/local/include
    ${CMAKE_SOURCE_DIR}/external/entt/include
    ${CMAKE_SOURCE_DIR}/third_party/entt/include
)

find_path(EnTT_INCLUDE_DIR
    NAMES entt/entt.hpp
    HINTS ${_ENTT_HINTS}
)

# -----------------------------------------------------------------------------
# Create the imported target if found
# -----------------------------------------------------------------------------
if(EnTT_INCLUDE_DIR)
    set(EnTT_FOUND TRUE)
    set(EnTT_INCLUDE_DIRS ${EnTT_INCLUDE_DIR})

    if(NOT TARGET EnTT::EnTT)
        add_library(EnTT::EnTT INTERFACE IMPORTED)
        set_target_properties(EnTT::EnTT PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${EnTT_INCLUDE_DIR}"
        )
    endif()

    message(STATUS "Found EnTT: ${EnTT_INCLUDE_DIR}")

else()
    set(EnTT_FOUND FALSE)
    message(STATUS "Could not find EnTT (entt/entt.hpp)")
endif()

mark_as_advanced(EnTT_INCLUDE_DIR)

