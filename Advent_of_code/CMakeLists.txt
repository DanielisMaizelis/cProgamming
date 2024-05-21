cmake_minimum_required(VERSION 3.27)
project(Advent_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Advent_1 main.c
        Day1/day1Part1.c
        main.h
        Day1/day1Part2.c
        Lessons/mallocCalloc.c)
