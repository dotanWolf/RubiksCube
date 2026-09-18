cmake_minimum_required(VERSION 3.10)
project(MyProject)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(backend/Headers)

set(SRCS
    backend/Cpp/Corner.cpp
    backend/Cpp/Cube.cpp
    backend/Cpp/Edge.cpp
    backend/Cpp/main.cpp
    backend/Cpp/App.cpp
    backend/Cpp/AStarSolver.cpp
    backend/Cpp/SearchNode.cpp
    backend/Cpp/Move.cpp
    backend/Cpp/MoveFactory.cpp
    backend/Cpp/Piece.cpp
    backend/Cpp/CubieCube.cpp
   )

# MyProject is the server. 
add_executable(MyProject ${SRCS})
