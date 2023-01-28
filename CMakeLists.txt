cmake_minimum_required(VERSION 3.23)
project(calculate_rpn)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculate_rpn main.cpp mparser.cpp mparser.h)
