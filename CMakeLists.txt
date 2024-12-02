cmake_minimum_required(VERSION 3.29.6)
project(FabHeap)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Add other source files if needed
# add_executable(FabHeap main.cpp FibHeap.cpp)

set(CMAKE_CXX_STANDARD 26)

add_executable(FabHeap main.cpp
        FibHeap.cpp
        FibHeap.h
        Node.h
        Node.cpp)
