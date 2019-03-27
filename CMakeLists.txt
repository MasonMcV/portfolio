cmake_minimum_required(VERSION 3.5)
project(portfolio C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_library(includes STATIC movie.h fileio.c fileio.h trie.c trie.h lettermap.c lettermap.h mybool.h nCursesHandler.c nCursesHandler.h)

add_executable(portfolio main.c)
target_link_libraries(portfolio includes ${CURSES_LIBRARIES})

add_executable(testing test.c)
target_link_libraries(testing ${CURSES_LIBRARIES})
