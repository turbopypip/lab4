cmake_minimum_required(VERSION 3.26)
project(lab4)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab4 main.cpp
        BinaryTree.h
        Tests.h
        Tests.cpp
        Menu.h
        Menu.cpp)
