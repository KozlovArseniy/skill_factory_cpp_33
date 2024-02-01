cmake_minimum_required(VERSION 3.27)
project(29_7)

set(CMAKE_CXX_STANDARD 17)

add_executable(29_7 main.cpp
        thread_safe_list.cpp
        thread_safe_list.hpp)
