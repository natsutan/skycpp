cmake_minimum_required(VERSION 3.19)
project(skycpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)

add_executable(skycpp
        inc/skycpp.h
        src/skycpp.cpp src/tokenizer.cpp)
