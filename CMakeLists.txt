cmake_minimum_required(VERSION 3.10)

# Project name and version
project(yanki VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(LLVM REQUIRED CONFIG)

# Set LLVM include directories and libraries
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Include directories for headers
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
)

add_definitions(${LLVM_DEFINITIONS})

# Properly map LLVM components to libnames

# Find all source files in the src directory
file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.c
)

# Create the main executable from the source files
add_executable(${PROJECT_NAME} ${SOURCES})

# Explicitly link required LLVM components
target_link_libraries(${PROJECT_NAME} PRIVATE LLVM-18)
