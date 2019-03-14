cmake_minimum_required(VERSION 3.5)
project(portfolio C)

set(CMAKE_C_STANDARD 11)

add_library(includes STATIC movie.h fileio.c fileio.h trie.c trie.h)

add_executable(portfolio main.c)
target_link_libraries(portfolio includes)

add_executable(testing test.c)
