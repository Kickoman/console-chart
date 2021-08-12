cmake_minimum_required(VERSION 3.10)
project(ConsoleChart)

set(CMAKE_CXX_STANDARD 14)

add_executable(ConsoleChart
    kmisc/kfunction/kfunction.h
    kmisc/common/CommonUtils.h
    main.cpp
)

target_include_directories(ConsoleChart PRIVATE kmisc/kfunction/ kmisc/common)
