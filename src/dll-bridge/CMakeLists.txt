cmake_minimum_required(VERSION 3.21)
project(opsdn)

set(CMAKE_CXX_STANDARD 14)

set(source
        library.cpp
        opsdn.c
        )

include_directories("C:\\Users\\jia19\\AppData\\Local\\Programs\\Python\\Python38\\include")
link_directories("C:\\Users\\jia19\\AppData\\Local\\Programs\\Python\\Python38\\libs")
add_definitions(-DOPSDN_LIB)
add_library(opsdn SHARED ${source})
