cmake_minimum_required(VERSION 2.6)

project(SimpleReflexion)

file(GLOB_RECURSE source_files src/* main.cpp)

include_directories(include/)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_executable(SimpleReflexion ${source_files} )