# Specify the minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(QuickestPath)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Find and include the Boost library, which is required for this project
find_package(Boost REQUIRED)

# Include the directories for Boost and the project's header files
include_directories(${Boost_INCLUDE_DIRS} ./include)

# Set the directory for archive files (static libraries)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Set the directory for library files (shared libraries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Set the directory for executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Add an executable target named QPS with the specified source files
add_executable(QPSAPI api.cpp)