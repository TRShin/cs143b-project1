cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
add_executable(MyProject
    src/main.cpp
    src/helpers.cpp
    src/operations.cpp
)

# Include directory so your .h files are found
target_include_directories(MyProject PRIVATE includes)