cmake_minimum_required(VERSION 3.25)
project(AmazonDupe)

set(CMAKE_CXX_STANDARD 17)

add_executable(AmazonDupe main.cpp n-ary.h n-ary.cpp HashMap.h HashMap.cpp)
