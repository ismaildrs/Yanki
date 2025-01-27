cmake_minimum_required(VERSION 3.10)

# Project name and version
project(yanki VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for headers
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# Find all source files in the src directory
file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.c
)

# Create the main executable from the source files
add_executable(${PROJECT_NAME} ${SOURCES})