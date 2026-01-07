cmake_minimum_required(VERSION 3.10)
project(tictactoe)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp" "src/*.h")

add_executable(prog ${SOURCES} ${HEADERS})

target_compile_options(prog PRIVATE -Wall -Wextra -Wpedantic -g)

target_link_libraries(prog SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)
