cmake_minimum_required(VERSION 3.8)
project(lab3)

set(CMAKE_CXX_STANDARD 14 )
set (CMAKE_CXX_FLAGS "-pthread")

set(SOURCE_FILES main.cpp semaphore.h)
add_executable(lab3 ${SOURCE_FILES})