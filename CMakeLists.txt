cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(Headers)

set(SRCS
    Cpp/Corner.cpp
    Cpp/Cube.cpp
    Cpp/Edge.cpp
    Cpp/main.cpp
    Cpp/App.cpp
    Cpp/AStarSolver.cpp
    Cpp/Node.cpp
    Cpp/Move.cpp
   )

# MyProject is the server. 
add_executable(MyProject ${SRCS})
