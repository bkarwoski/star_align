cmake_minimum_required(VERSION 2.8.11)
project(STAR_STACK)

if(NOT CMAKE_BUILD_TYPE)
    MESSAGE("-- No build type specified; defaulting to CMAKE_BUILD_TYPE=Release")

set(CMAKE_CXX_FLAGS_RELEASE )