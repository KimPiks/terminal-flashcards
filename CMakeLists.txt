cmake_minimum_required(VERSION 3.28)
project(terminal_flashcards)

set(CMAKE_CXX_STANDARD 26)

include_directories(${CMAKE_SOURCE_DIR}/extern/sqlite3)
include_directories(${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_SOURCE_DIR}/src/database
                    ${CMAKE_SOURCE_DIR}/src/ui)

set(SQLITE3_SRC ${CMAKE_SOURCE_DIR}/extern/sqlite3/sqlite3.c)
set(SOURCE_FILES src/main.cpp
        src/database/database.cpp
        src/database/database.h
        src/ui/UI.cpp
        src/ui/UI.h
        src/ui/Utils.cpp
        src/ui/Utils.h
        src/ui/Select.cpp
        src/ui/Select.h
        src/flashcards/Flashcards.cpp
        src/flashcards/Flashcards.h
        src/database/Sql.h
        src/database/models/Deck.h
        src/data/Deck.h
        src/data/Question.h
        src/files/Files.cpp
        src/files/Files.h
        src/data/Answer.h
)

add_executable(terminal_flashcards ${SOURCE_FILES} ${SQLITE3_SRC})
