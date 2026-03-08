cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(astream)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # Required by clangd

find_package(PortAudio)
find_package(LibSndFile)
find_package(LibSamplerate)

add_subdirectory(src)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_subdirectory(libs/Catch2)
  add_subdirectory(tests)
endif()


