cmake_minimum_required(VERSION 3.13)
project(Hash_Tables)

set(
    SOURCES
    hash_table.c
    hash.c
)

set (
    HEADERS
    hash_table.h
    hash.h
)
    add_executable(WordsCounter main.c ${SOURCES} ${HEADERS})
    option(OPEN_TYPE "ON for open type table OFF for chaining type table")
    if(OPEN_TYPE)
        target_compile_definitions(WordsCounter PRIVATE OPEN_TYPE)
    else()
        target_compile_definitions(WordsCounter PRIVATE CHAIN_TYPE)
    endif()

target_compile_features(WordsCounter PRIVATE c_std_11)
set_target_properties(WordsCounter PROPERTIES C_STANDARD_REQUIRED ON)

if(MSVC)
    target_compile_options(WordsCounter PUBLIC /W4 /WX)
else()
    target_compile_options(WordsCounter PUBLIC -Wall -Wextra -Wpedantic)
endif()
