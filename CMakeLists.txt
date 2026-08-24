cmake_minimum_required(VERSION 3.14)
project(MGSLegatoXP)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)

# Platform detection
if(WIN32)
    set(PLATFORM_WINDOWS TRUE)
    message(STATUS "Building for Windows")
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_LINUX TRUE)
    message(STATUS "Building for Linux")
endif()

# Compiler flags - platform specific
if(MSVC)
    add_compile_options(/W4)
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra)
    add_compile_options(-Waggregate-return)
    add_compile_options(-Wbad-function-cast)
    add_compile_options(-Winline)
    add_compile_options(-Wmissing-noreturn)
    add_compile_options(-Wnested-externs)
    add_compile_options(-Wno-deprecated-declarations)
    add_compile_options(-Wpointer-arith)
    add_compile_options(-Wredundant-decls)
    add_compile_options(-Wshadow)
    add_compile_options(-Wundef)
    add_compile_options(-Wunreachable-code)
    add_compile_options(-Wwrite-strings)
    add_compile_options(-Wstrict-prototypes)
    add_compile_options(-Wformat)
endif()

# Remove strings matching given regular expression from a list.
# @param(in,out) aItems Reference of a list variable to filter.
# @param aRegEx Value of regular expression to match.
function (filter_items aItems aRegEx)
    # For each item in our list
    foreach (item ${${aItems}})
        # Check if our items matches our regular expression
        if ("${item}" MATCHES ${aRegEx})
            # Remove current item from our list
            list (REMOVE_ITEM ${aItems} ${item})
        endif ("${item}" MATCHES ${aRegEx})
    endforeach(item)
    # Provide output parameter
    set(${aItems} ${${aItems}} PARENT_SCOPE)
endfunction (filter_items)

# SDL2 - cross-platform
option(WITH_SDL2 "enable/disable sdl2" ON)

if(PLATFORM_WINDOWS)
    # Windows: Use bundled SDL2 from system/windows/sdl2
    if(WITH_SDL2)
        set(SDL2_DIR "${CMAKE_SOURCE_DIR}/system/windows/sdl2/lib/cmake/SDL2")
        find_package(SDL2 REQUIRED)
        if(SDL2_FOUND)
            message(STATUS "Found SDL2 (bundled)")
            add_compile_definitions(USE_SDL2)
            include_directories(${SDL2_INCLUDE_DIRS})
        endif()
    endif()
elseif(PLATFORM_LINUX)
    # Linux: Use pkg-config
    find_package(PkgConfig REQUIRED)

    # DRM/KMS - Linux ARM only
    if((CMAKE_SYSTEM_PROCESSOR STREQUAL "armv5l") OR (CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7l"))
        pkg_check_modules(LIBDRM REQUIRED libdrm>=2.4.0)
        if(LIBDRM_FOUND)
            message(STATUS "Found libdrm")
            add_compile_definitions(USE_DRM_KMS)
            include_directories(${LIBDRM_INCLUDE_DIRS})
            link_libraries(${LIBDRM_LIBRARIES})
        endif()
    endif()

    # SDL2 - Linux
    if(WITH_SDL2)
        pkg_check_modules(SDL2 sdl2)
        if(SDL2_FOUND)
            message(STATUS "Found SDL2")
            add_compile_definitions(USE_SDL2)
            include_directories(${SDL2_INCLUDE_DIRS})
            link_libraries(${SDL2_LIBRARIES})
        endif()
    endif()

    # Math library - Linux
    find_library(LIB_MATH m)
    if(LIB_MATH)
        message(STATUS "Found libmath")
        include_directories(${LIB_MATH_INCLUDE_DIRS})
        link_libraries(m)
    endif()

    # libinput and libudev - Linux only
    pkg_search_module(LIBINPUT REQUIRED IMPORTED_TARGET libinput)
    if(LIBINPUT_FOUND)
        include_directories(${LIBINPUT_INCLUDE_DIRS})
        link_libraries(${LIBINPUT_LIBRARIES})
    endif()

    pkg_search_module(LIBUDEV REQUIRED IMPORTED_TARGET libudev)
    if(LIBUDEV_FOUND)
        include_directories(${LIBUDEV_INCLUDE_DIRS})
        link_libraries(${LIBUDEV_LIBRARIES})
    endif()
endif()

# find the all source files from gfx folder
file(GLOB_RECURSE gfxSrcList gfx/middleware/legato/library/src/gfx/*.c)

filter_items(gfxSrcList ".*simulator.*")
filter_items(gfxSrcList ".*generated.*")
filter_items(gfxSrcList ".*le_gen_harmony.*")
filter_items(gfxSrcList ".*rtos.*")

# Platform-specific source files
if(PLATFORM_WINDOWS)
    file(GLOB_RECURSE SystemSrcList
        system/gfx/driver/*.c
        system/windows/timer/*.c
        system/system_init.c)
    file(GLOB_RECURSE gfxCanvasList system/gfx/canvas/*.c)

    if(SDL2_FOUND)
        file(GLOB_RECURSE gfxSdlSrcList system/windows/display/sdl2/*.c)
        list(APPEND SystemSrcList ${gfxSdlSrcList})
    endif()

    include_directories(${CMAKE_SOURCE_DIR}/system/)
    include_directories(${CMAKE_SOURCE_DIR}/system/windows)
    include_directories(${CMAKE_SOURCE_DIR}/gfx/middleware/legato/library/src)

    set(mgsSrcList ${gfxSrcList} ${SystemSrcList})

elseif(PLATFORM_LINUX)
    file(GLOB_RECURSE SystemSrcList
        system/gfx/driver/*.c
        system/linux/input/*.c
        system/system_init.c
        system/linux/timer/*.c)
    file(GLOB_RECURSE gfxCanvasList system/gfx/canvas/*.c)
    file(GLOB_RECURSE gfxDrmSrcList system/linux/display/drm/*.c)
    file(GLOB_RECURSE gfxFbdevSrcList system/linux/display/fbdev/*.c)
    file(GLOB_RECURSE gfxSdlSrcList system/linux/display/sdl2/*.c)

    include_directories(${CMAKE_SOURCE_DIR}/system/)
    include_directories(${CMAKE_SOURCE_DIR}/system/linux)
    include_directories(${CMAKE_SOURCE_DIR}/gfx/middleware/legato/library/src)

    if(LIBDRM_FOUND)
        list(APPEND SystemSrcList ${gfxDrmSrcList})
    endif()

    if(SDL2_FOUND)
        list(APPEND SystemSrcList ${gfxSdlSrcList})
    endif()

    set(mgsSrcList ${gfxSrcList} ${SystemSrcList} ${gfxFbdevSrcList})

    foreach(FILE_PATH ${gfxSdlSrcList})
        message(STATUS "  ${FILE_PATH}")
    endforeach()
endif()

add_subdirectory(apps/quickstart)

# Windows: Link SDL2 and copy DLL
if(PLATFORM_WINDOWS AND SDL2_FOUND)
    # Link SDL2 to the quickstart target (done in subdirectory CMakeLists.txt)
endif()

include(cmake/AstyleFormatSource.cmake)

