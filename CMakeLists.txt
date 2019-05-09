cmake_minimum_required(VERSION 3.11)
project(exjson C)
set(CMAKE_C_STANDARD 99)

#add_executable(exjson main.c stack.h stack.c exjson.h exjson.c)
add_executable(exjson main.c lex.yy.c stack.c stack.h exjson.tab.c exjson.tab.h exjson.c exjson.h)


