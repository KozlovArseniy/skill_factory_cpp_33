cmake_minimum_required(VERSION 3.18)
project(current)

set(CMAKE_CXX_STANDARD 17)

add_executable(current main.cpp VendingMachine/vending_machine.h VendingMachine/vending_machine.cpp Snack/snack.cpp Snack/snack.h SnackSlot/snack_slot.cpp SnackSlot/snack_slot.h)
