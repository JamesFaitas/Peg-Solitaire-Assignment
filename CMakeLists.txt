cmake_minimum_required(VERSION 3.6)
project(V4Complete)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c my_strings.h my_pyramid_game.h pyramid_helpers.h pyramid_helpers.c my_strings.c my_pyramid_game.c board.h dfs.c board.c)
add_executable(V4Complete ${SOURCE_FILES})