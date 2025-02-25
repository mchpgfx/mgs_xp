cmake_minimum_required(VERSION 3.14)
project(MGSLegato4Linux)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)

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

find_package(PkgConfig REQUIRED)

if((CMAKE_SYSTEM_PROCESSOR STREQUAL "armv5l") OR (CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7l"))
	pkg_check_modules(LIBDRM REQUIRED libdrm>=2.4.0)
	if(LIBDRM_FOUND)
		message("found libdrm")
		add_compile_definitions(USE_DRM_KMS)
		include_directories(${LIBDRM_INCLUDE_DIRS})
		link_libraries(${LIBDRM_LIBRARIES})
	endif()
endif()

option(WITH_SDL2 "enable/disable sdl2" ON)
if(WITH_SDL2)
	pkg_check_modules(SDL2 sdl2)   
	if(SDL2_FOUND)
		message("found sdl2")
		add_compile_definitions(USE_SDL2)
		include_directories(${SDL2_INCLUDE_DIRS})
		link_libraries(${SDL2_LIBRARIES})
	endif()
endif()

find_library(LIB_MATH m)
if(LIB_MATH)
message("found libmath")
include_directories(${LIB_MATH_INCLUDE_DIRS})
link_libraries(m)
endif()

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

# find the all source files from gfx folder
file(GLOB_RECURSE gfxSrcList gfx/middleware/legato/library/src/gfx/*.c ) 
file(GLOB_RECURSE SystemSrcList system/gfx/driver/*.c system/linux/input/*.c system/system_init.c system/linux/timer/*.c)
file(GLOB_RECURSE gfxCanvasList system/gfx/canvas/*.c) 
file(GLOB_RECURSE gfxDrmSrcList system/linux/display/drm/*.c) 
file(GLOB_RECURSE gfxFbdevSrcList system/linux/display/fbdev/*.c) 
file(GLOB_RECURSE gfxSdlSrcList system/linux/display/sdl2/*.c) 

filter_items(gfxSrcList ".*simulator.*")
filter_items(gfxSrcList ".*generated.*")
filter_items(gfxSrcList ".*le_gen_harmony.*")
filter_items(gfxSrcList ".*rtos.*")

include_directories(system/)
include_directories(system/linux)
include_directories(gfx/middleware/legato/library/src) 
#include_directories(.)

if(LIBDRM_FOUND)
	List(APPEND SystemSrcList ${gfxDrmSrcList})
endif()

if(SDL2_FOUND)
	List(APPEND SystemSrcList ${gfxSdlSrcList})
endif()

set(mgsSrcList ${gfxSrcList} ${SystemSrcList} ${gfxFbdevSrcList})

foreach(FILE_PATH ${gfxSdlSrcList})
    message(STATUS "  ${FILE_PATH}")
endforeach()

add_subdirectory(apps/quickstart)

include(cmake/AstyleFormatSource.cmake)

