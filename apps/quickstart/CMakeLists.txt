cmake_minimum_required(VERSION 3.14)

add_executable(mgs_quickstart)

# find the app files
file(GLOB_RECURSE srcList main.c  apps/*.c gfx/legato/generated/*.c)

#filter_items(linuxSrcList ".*simulator.*")
filter_items(srcList ".*le_gen_harmony.*")
filter_items(mgsSrcList ".*gfx_canvas.*")

target_sources(mgs_quickstart PRIVATE ${srcList})
target_sources(mgs_quickstart PRIVATE ${mgsSrcList})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/apps)

# Platform-specific linking
if(PLATFORM_WINDOWS AND SDL2_FOUND)
    # Link only SDL2::SDL2, not SDL2main (we use SDL_MAIN_HANDLED in main.c)
    target_link_libraries(mgs_quickstart SDL2::SDL2)

    # Copy SDL2.dll from bundled SDK to output directory
    add_custom_command(TARGET mgs_quickstart POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/system/windows/sdl2/bin/SDL2.dll"
        $<TARGET_FILE_DIR:mgs_quickstart>)
endif()

install(TARGETS mgs_quickstart DESTINATION bin)
