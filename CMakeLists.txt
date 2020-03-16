cmake_minimum_required(VERSION 3.10)
project(ConsoleChart)

set(CMAKE_CXX_STANDARD 14)

add_executable(ConsoleChart main.cpp)

add_subdirectory(kmisc/)

target_link_libraries(ConsoleChart kmisc)
