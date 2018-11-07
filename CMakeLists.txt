cmake_minimum_required(VERSION 3.12)
project(algo)

set(CMAKE_CXX_STANDARD 14)

include_directories(library)

add_executable(algo main.cpp library/library.cpp)