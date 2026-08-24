# SDL2 CMake configuration for bundled SDK
# This config file allows building without external SDL2 installation

get_filename_component(SDL2_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
get_filename_component(SDL2_PREFIX "${SDL2_CMAKE_DIR}/../../.." ABSOLUTE)

set(SDL2_INCLUDE_DIR "${SDL2_PREFIX}/include/SDL2")
set(SDL2_INCLUDE_DIRS "${SDL2_PREFIX}/include;${SDL2_INCLUDE_DIR}")
set(SDL2_LIBDIR "${SDL2_PREFIX}/lib")
set(SDL2_BINDIR "${SDL2_PREFIX}/bin")

set(SDL2_LIBRARIES SDL2::SDL2)
set(SDL2_FOUND TRUE)

# Create SDL2::SDL2 imported target
if(NOT TARGET SDL2::SDL2)
    add_library(SDL2::SDL2 SHARED IMPORTED)
    set_target_properties(SDL2::SDL2 PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIR}"
        IMPORTED_IMPLIB "${SDL2_LIBDIR}/libSDL2.dll.a"
        IMPORTED_LOCATION "${SDL2_BINDIR}/SDL2.dll"
    )
endif()

# Create SDL2::SDL2main imported target (not used with SDL_MAIN_HANDLED)
if(NOT TARGET SDL2::SDL2main)
    add_library(SDL2::SDL2main STATIC IMPORTED)
    set_target_properties(SDL2::SDL2main PROPERTIES
        IMPORTED_LOCATION "${SDL2_LIBDIR}/libSDL2main.a"
    )
endif()
