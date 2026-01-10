cmake_minimum_required(VERSION 3.10)
project(aoc25)

add_executable(aoc25
    main.cpp
    common/utils.cpp
    days/day01.cpp
    days/day02.cpp
    days/day03.cpp
    days/day05.cpp
    days/day04.cpp
    days/day06.cpp
    days/day07.cpp
    days/day08.cpp
)

target_include_directories(aoc25
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
