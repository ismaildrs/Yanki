cmake_minimum_required(VERSION 3.28)

project(yanki)

# Define the source files for the executable
add_executable(YANKI src/main.cpp)

# Define additional files (this is more typical for documentation or data files)
set(FILES docs/start.yy)

# Include directories
target_include_directories(YANKI PUBLIC include)
