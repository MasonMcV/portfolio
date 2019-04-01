cmake_minimum_required(VERSION 3.5)
project(portfolio C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_library(includes STATIC movie.h fileio.c fileio.h trie.c trie.h mybool.h nCursesHandler.c nCursesHandler.h)

add_executable(iMovieSearch main.c)
target_link_libraries(iMovieSearch includes ${CURSES_LIBRARIES})
