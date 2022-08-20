cmake_minimum_required(VERSION 3.19)
project(chess)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(
    chess
    src/main.cpp
    src/Board.cpp

    src/pieces/Piece.cpp
    src/pieces/Bishop.cpp
    src/pieces/King.cpp
    src/pieces/Knight.cpp
    src/pieces/Pawn.cpp
    src/pieces/Queen.cpp
    src/pieces/Rook.cpp
)
target_link_libraries(
    chess
    sfml-graphics
    sfml-window
    sfml-audio
)
target_compile_options(chess PUBLIC -Werror=non-virtual-dtor)