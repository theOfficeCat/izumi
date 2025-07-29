cmake_minimum_required(VERSION 3.20)

project(izumi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -fsanitize=address,undefined")

file(STRINGS ".version" VERSION)
add_compile_definitions(VERSION="${VERSION}")

add_subdirectory(src)

