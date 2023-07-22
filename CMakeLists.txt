cmake_minimum_required(VERSION 3.0)

project(MyProject)

add_subdirectory(ThreadPoolLibrary)
add_subdirectory(FileSearchLibrary)
add_subdirectory(app)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThreadPoolLibrary)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/FileSearchLibrary)
