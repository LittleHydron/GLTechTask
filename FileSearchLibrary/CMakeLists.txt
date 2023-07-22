cmake_minimum_required(VERSION 3.10)
project(FileSearchLibrary)

add_library(FileSearchLibrary STATIC FileSearch.cpp)


target_include_directories(FileSearchLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
