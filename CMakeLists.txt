cmake_minimum_required(VERSION 3.16)
project(new_engine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -march=native -flto=12 -fomit-frame-pointer -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -Og -march=native -flto=12 -fomit-frame-pointer -fdiagnostics-color=always -g")

# Collect all .cpp files recursively, excluding eigen/
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

# Create the executable
add_executable(main ${SRC_FILES})