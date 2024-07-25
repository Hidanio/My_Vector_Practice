cmake_minimum_required(VERSION 3.27)
project(My_Vector_Practice)

set(CMAKE_CXX_STANDARD 20)

add_executable(My_Vector_Practice main.cpp
        My_Vector.h
        My_Vector.cpp
        ObjectDestructionExperiment.h)

add_subdirectory(Google_tests)
