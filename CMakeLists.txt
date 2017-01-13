cmake_minimum_required(VERSION 3.6)
project(aal)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Point.h src/Face.h src/Tetrahedron.h src/Point.cpp src/Generator.cpp src/Generator.h src/ConvexHull.cpp src/ConvexHull.h src/Face.cpp)
add_executable(aal ${SOURCE_FILES})