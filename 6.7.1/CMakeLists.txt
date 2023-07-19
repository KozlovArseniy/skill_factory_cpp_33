cmake_minimum_required(VERSION 3.25)
project(6_7_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(6_7_1 main.cpp electronics/electronics.h laptop/laptop.cpp laptop/laptop.h electronics/electronics.cpp tablet/tablet.cpp tablet/tablet.h transformer/transformer.cpp transformer/transformer.h sold_electronics/sold_electronics.cpp sold_electronics/sold_electronics.h)
