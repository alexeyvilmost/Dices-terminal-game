cmake_minimum_required(VERSION 3.14)
project(KEK)

set(CMAKE_CXX_STANDARD 14)

add_executable(KEK
        sources/main.cpp sources/Dices.cpp includes/Dices.h sources/User.cpp sources/Game.cpp includes/Game.h sources/utility.cpp sources/print.cpp sources/utility.h)
