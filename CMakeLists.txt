cmake_minimum_required(VERSION 3.10)
project(cds)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(cds)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

target_sources(
    cds PRIVATE
    src/main.c
    src/flib_array.c
    src/flib_list.c
)