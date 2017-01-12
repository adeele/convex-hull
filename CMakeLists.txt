cmake_minimum_required(VERSION 3.6)
project(aal)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Point.h Plane.h Tetrahedron.h Point.cpp)
add_executable(aal ${SOURCE_FILES})