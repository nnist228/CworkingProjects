cmake_minimum_required(VERSION 3.13)
project(Hash_Tables)

set(
    Sources
    hash.c
    main.c
    list_hash.c
    open_hash.c
    hash_table_value.c
)

set (
    Headers
    hash.h
    list_hash.h
    open_hash.h
    hash_table_value.h
)

add_executable(WordsCounter ${Sources} ${Headers})

target_compile_features(WordsCounter PRIVATE c_std_11)
set_target_properties(WordsCounter PROPERTIES CXX_STANDARD_REQUIRED ON)

if(MSVC)
    target_compile_options(WordsCounter PUBLIC /W4 /WX)
else()
    target_compile_options(WordsCounter PUBLIC -Wall -Wextra -Wpedantic)
endif()
