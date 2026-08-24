cmake_minimum_required(VERSION 3.14)

add_executable(example_qwerty)

# Find app source files
file(GLOB_RECURSE srcList main.c apps/*.c gfx/legato/generated/*.c)

filter_items(srcList ".*le_gen_harmony.*")

target_sources(example_qwerty PRIVATE ${srcList})
target_sources(example_qwerty PRIVATE ${mgsSrcList})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/apps)

# Platform-specific linking
if(PLATFORM_WINDOWS AND SDL2_FOUND)
    target_link_libraries(example_qwerty SDL2::SDL2)

    add_custom_command(TARGET example_qwerty POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/system/windows/sdl2/bin/SDL2.dll"
        $<TARGET_FILE_DIR:example_qwerty>)
endif()

install(TARGETS example_qwerty DESTINATION bin)
