# Min project version
cmake_minimum_required(VERSION 3.5.1)

# Project
project(TomAndJerry)

# Flags
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")

# Sources and Headers
set(SOURCES src/main.cpp)

# Include
include_directories(include)

# Library
add_executable(tomandjerry ${SOURCES})

# Link library
find_library(LIB_SIMPLE_CPP sprite HINT lib/)
find_library(LIB_X11 X11)

target_link_libraries(tomandjerry ${LIB_SIMPLE_CPP} ${LIB_X11})
