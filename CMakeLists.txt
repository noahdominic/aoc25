cmake_minimum_required(VERSION 3.10)
project(aoc25)

add_executable(aoc25
    main.cpp
    common/utils.cpp
)

target_include_directories(aoc25
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
