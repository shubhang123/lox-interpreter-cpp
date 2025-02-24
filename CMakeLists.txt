cmake_minimum_required(VERSION 3.13)

project(codecrafters-interpreter)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)

add_executable(interpreter ${SOURCE_FILES}
        src/scanner.cpp
        include/scanner.h
        include/utils.h
        src/utils.cpp
        include/parser.h
        src/parser.cpp
        include/token.h)