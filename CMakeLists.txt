cmake_minimum_required(VERSION 3.10)
project(cds)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)


add_executable(cds)
add_library(
    flib STATIC
    src/flib_array.c
    src/flib_list.c
)

target_include_directories(
    flib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_sources(
    cds PRIVATE
    src/main.c
)

target_link_libraries(
    cds PRIVATE
    flib
)

target_compile_options(
    flib PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-g -Wall>
)

target_compile_options(
    cds PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-g -Wall>
)