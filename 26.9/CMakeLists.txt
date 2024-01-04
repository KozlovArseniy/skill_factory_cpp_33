cmake_minimum_required(VERSION 3.25)
project(26_9)


set(CMAKE_CXX_STANDARD 20)

add_executable(26_9 main.cpp sum_array.cpp sum_array.h)

TARGET_LINK_LIBRARIES( 26_9 pthread )