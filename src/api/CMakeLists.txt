# Specify the minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(QuickestPath)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(APPLE)
    # macOS specific settings

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

    # Add an executable target named QPSAPI with the specified source files
    add_executable(QPSAPI api.cpp)

else()
    # Windows specific settings

    # Clear the cache
    cmake_policy(SET CMP0167 OLD)

    # Set Boost root path manually (adjust if necessary)
    set(Boost_NO_SYSTEM_PATHS ON)
    set(BOOST_ROOT "C:/Boost/boost_1_87_0")
    set(BOOST_INCLUDE_DIR "C:/Boost/boost_1_87_0")
    set(BOOST_LIBRARY_DIR "C:/Boost/boost_1_87_0/stage/lib")
    find_package(Boost REQUIRED COMPONENTS system thread filesystem)
    if(NOT Boost_FOUND)
        message(FATAL_ERROR "Boost not found! Check BOOST_LIBRARYDIR: ${BOOST_LIBRARYDIR}")
    endif()

    # Include the project's header files
    include_directories(./include)

    # Set the output directories
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

    # Add an executable target named QPSAPI with the specified source files
    add_executable(QPSAPI api.cpp)

    # Link Boost libraries to the executable
    target_link_libraries(QPSAPI PRIVATE Ws2_32 Mswsock Boost::system Boost::thread Boost::filesystem)
endif()