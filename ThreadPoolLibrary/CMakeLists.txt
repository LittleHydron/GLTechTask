cmake_minimum_required(VERSION 3.10)
project(ThreadPoolLibrary)

add_library(ThreadPoolLibrary STATIC ThreadPool.cpp)
target_include_directories(ThreadPoolLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
