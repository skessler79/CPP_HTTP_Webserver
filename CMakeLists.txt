cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(Webserver VERSION 0.1)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set debug build
set(CMAKE_BUILD_TYPE Debug)

# Set binary output directories
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include the /source directory globally
include_directories(${CMAKE_SOURCE_DIR}/source)

# Add subdirectories
add_subdirectory(source)
add_subdirectory(source/lib)
add_subdirectory(source/server)
add_subdirectory(source/http)
add_subdirectory(source/structures)

