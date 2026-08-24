cmake_minimum_required(VERSION 3.14)

add_executable(example_calendar)

# Find app source files
file(GLOB_RECURSE srcList main.c apps/*.c gfx/legato/generated/*.c)

filter_items(srcList ".*le_gen_harmony.*")

target_sources(example_calendar PRIVATE ${srcList})
target_sources(example_calendar PRIVATE ${mgsSrcList})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/apps)

# Platform-specific linking
if(PLATFORM_WINDOWS AND SDL2_FOUND)
    target_link_libraries(example_calendar SDL2::SDL2)

    add_custom_command(TARGET example_calendar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/system/windows/sdl2/bin/SDL2.dll"
        $<TARGET_FILE_DIR:example_calendar>)
endif()

install(TARGETS example_calendar DESTINATION bin)
