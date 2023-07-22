cmake_minimum_required(VERSION 3.10)
project(MyProject)

add_library(searchLibrary STATIC search.cpp)
target_include_directories(searchLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
