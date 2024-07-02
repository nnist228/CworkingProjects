cmake_minimum_required(VERSION 3.13)
project(Hash_Tables)

set(
    Sources
    hash_table_open.c
    hash_table_list.c
    hash.c
)

set (
    Headers
    hash_table.h
    hash.h
)
    add_executable(WordsCounter main.c ${Sources} ${Headers})
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
