cmake_minimum_required(VERSION 3.26)
project(Cupcake_POS_in_CPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(.)

add_executable(Cupcake_POS_in_CPP
        cupcake_pos.cpp
)