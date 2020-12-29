cmake_minimum_required(VERSION 2.8)
project(Hivek-Assembler)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(SOURCES
    src/HivekAssembler/HivekAssembler.cpp
    src/main.cpp
)

add_executable(hivek-as ${SOURCES})
