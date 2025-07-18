cmake_minimum_required(VERSION 3.20)

project(izumi)

find_package(Curses)
if(Curses_FOUND AND NOT TARGET Curses::Curses)
    add_library(Curses::Curses INTERFACE IMPORTED)
    set_target_properties(
    Curses::Curses
    PROPERTIES
        INTERFACE_LINK_LIBRARIES "${CURSES_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${CURSES_INCLUDE_DIRS}"
    )
else()
    message(FATAL_ERROR ncurses not found)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -fsanitize=address,undefined")

file(STRINGS ".version" VERSION)
add_compile_definitions(VERSION="${VERSION}")

add_subdirectory(src)

