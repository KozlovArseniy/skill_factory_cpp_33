cmake_minimum_required(VERSION 3.25)
project(20_11)


set(CMAKE_CXX_STANDARD 20)

add_executable(20_11 main.cpp Listener/listener.cpp Sender/sender.cpp)

TARGET_LINK_LIBRARIES( 20_11 pthread )