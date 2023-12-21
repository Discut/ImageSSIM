cmake_minimum_required(VERSION 3.0)
project(opencv_test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE debug)
set(OpenCV_DIR D:/Tools/opencv/build/x64/mybuild)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB LIB "D:/Tools/opencv/build/x64/mybuild/lib/*")

add_executable(main main.cpp)
target_link_libraries(main ${LIB})
