cmake_minimum_required(VERSION 3.10)
project(CrowExample)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ./include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

add_executable(QPSAPI main.cpp)