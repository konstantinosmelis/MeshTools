cmake_minimum_required(VERSION 3.30)
project(MeshEdgeCollapsing)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE HEADERS Headers/*)
file(GLOB_RECURSE SOURCES Sources/*)

add_executable(MeshEdgeCollapsing
        ${HEADERS} ${SOURCES}
        main.cpp)
