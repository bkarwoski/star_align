cmake_minimum_required(VERSION 2.8.11)
project(
    STAR_STACK
    DESCRIPTION "Star photo alignment"
    LANGUAGES CXX)


if(NOT CMAKE_BUILD_TYPE)
    MESSAGE("-- No build type specified; defaulting to CMAKE_BUILD_TYPE=Release")
    set(CMAKE_BUILD_TYPE Release CACHE STRING
    "Choose the type of build, options are: Debug Release"  FORCE)
    else()
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        MESSAGE("\n${line}")
        MESSAGE("\n-- Build type: Debug. Performance will be terrible!")
        MESSAGE("-- Add -DCMAKE_BUILD_TYPE=Release to the CMake command line to get an optimized build.")
        MESSAGE("\n${line}")
    endif()
endif()

set(CMAKE_CXX_FLAGS_DEBUG " -pg -g -rdynamic ") # dynamic is for the improved asserts
set(CMAKE_CXX_FLAGS_RELEASE " -O3 -DNDEBUG")

add_definitions("-std=c++17")
include_directories(${PROJECT_SOURCE_DIR})
message("\n -- Project source dir: ${PROJECT_SOURCE_DIR}")

include_directories("/home/bkarwoski/star_align/deps/install/include/eigen3")
message("\n -- Found Eigen Version: ${Eigen_VERSION}")
message("\n -- Eigen_INCLUDE_DIRS: ${EIGEN_INCLUDE_DIRS}")

set(OpenCV_DIR "/home/bkarwoski/star_align/deps/install/share/OpenCV")
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui calib3d tracking)
include_directories(${OpenCV_INCLUDE_DIRS}) # not needed for opencv>=4.0
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# set(Ceres_DIR "/home/bkarwoski/star_align/deps/install/include/ceres")
find_package(Ceres REQUIRED)

add_executable(main main.cpp)
target_include_directories(main PRIVATE ${OpenCV_INCLUDE_DIRS} ${CERES_INCLUDES})
target_link_libraries(main ${OpenCV_LIBS} ${CERES_LIBRARIES})

#can this go in CMAKE_CXX_FLAGS_RELEASE?
target_compile_options(main PRIVATE -Wall -Wextra -Werror -Wfatal-errors)
