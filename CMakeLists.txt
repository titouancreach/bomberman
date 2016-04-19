cmake_minimum_required (VERSION 2.8)

project(Bomberman)

##
# Global options
#

# compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++17")


##
# Create librairies
#

# headers
include_directories(src/bomberman/headers/)

# files
file(
    GLOB
    source_files
    src/bomberman/cpp/map.cc
    src/bomberman/cpp/app.cc
    src/bomberman/cpp/tile.cc
    src/bomberman/cpp/animation.cc
    src/bomberman/cpp/animationHandler.cc
    src/bomberman/cpp/game.cc
    src/bomberman/cpp/gameStatePlay.cc
    src/bomberman/cpp/gameStateStart.cc
    src/bomberman/cpp/textureManager.cc
)

# external libs
include_directories(${sfml_include_dir})
link_directories(${sfml_lib_dir})

add_library(
    bomberman_lib
    STATIC
    ${source_files}
)

# linker
target_link_libraries(
    bomberman_lib
    ${sfml_libname_system}
    ${sfml_libname_window}
    ${sfml_libname_graphics}
)

# set output path
set_target_properties(
    bomberman_lib
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY bin/lib/${CMAKE_BUILD_TYPE}
)



##
# Create executable
#

file(
    GLOB
    main
    src/bomberman/cpp/main.cc
)

add_executable(
    bomberman
    ${main}
)

target_link_libraries(
    bomberman
    bomberman_lib
)

# change output path
set_target_properties(
    bomberman
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    bin/exe/${CMAKE_BUILD_TYPE}
)


##
# Unit test
#

# add test sources
file(
    GLOB
    source_files_test
    ${source_files}
    src/bomberman_test/cpp/test_quadtree.cc
)

include_directories(
    ${gtest_include_dir}
)

link_directories(
    ${gtest_lib_dir}
)


# test main method
file(
    GLOB
    main_test
    src/bomberman_test/cpp/test_main.cc
)

# create new executable
add_executable(
    bomberman_test
    ${source_files_test}
    ${main_test}
)

target_link_libraries(
    bomberman_test
    bomberman_lib
    ${gtest_libname}
    pthread
)

set_target_properties(
    bomberman_test
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY bin/test/${CMAKE_BUILD_TYPE}
)
