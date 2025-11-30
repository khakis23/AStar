cmake_minimum_required(VERSION 3.31)
project(A_)

set(CMAKE_CXX_STANDARD 23)

add_executable(A_ main.cpp
        aStar/src/aStar.cpp
        aStar/include/PreDefinedGrids.h
        aStar/include/example.h)

target_include_directories(A_ PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/aStar/include
)
