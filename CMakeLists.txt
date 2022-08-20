cmake_minimum_required(VERSION 3.19)
project(chess)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(
    chess
    src/main.cpp
)
target_link_libraries(
    chess
    sfml-graphics
    sfml-window
    sfml-audio
)
target_compile_options(chess PUBLIC -Werror=non-virtual-dtor)