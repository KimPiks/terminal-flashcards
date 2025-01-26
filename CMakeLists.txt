cmake_minimum_required(VERSION 3.30)
project(terminal_flashcards)

set(CMAKE_CXX_STANDARD 26)

include_directories(${CMAKE_SOURCE_DIR}/extern/sqlite3)
include_directories(${CMAKE_SOURCE_DIR}/src)

set(SQLITE3_SRC ${CMAKE_SOURCE_DIR}/extern/sqlite3/sqlite3.c)
set(SOURCE_FILES src/main.cpp
        src/database/database.cpp
        src/database/database.h)

add_executable(terminal_flashcards ${SOURCE_FILES} ${SQLITE3_SRC})
