cmake_minimum_required(VERSION 3.23)

project(cupid)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES "src/*/*.cpp")

add_executable(cupid test/polygon_test.cpp ${SOURCES})