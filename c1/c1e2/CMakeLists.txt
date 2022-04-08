cmake_minimum_required(VERSION 3.0.0)
project(c1e2 VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(measure video.cpp)

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(measure ${OpenCV_LIBS})