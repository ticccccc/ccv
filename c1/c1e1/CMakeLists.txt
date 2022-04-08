cmake_minimum_required(VERSION 3.0.0)
project(c1e1 VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(draw draw.cpp)
add_executable(mouse mouse.cpp)

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(draw ${OpenCV_LIBS})
target_link_libraries(mouse ${OpenCV_LIBS})