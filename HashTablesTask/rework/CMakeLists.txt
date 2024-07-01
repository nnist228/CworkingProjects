cmake_minimum_required(VERSION 3.13)
project(Hash_Tables)

set(
    Sources
    forward_list.c
    open_hash_struct.c
    hash_table_open.c
    hash_table_list.c
    hash.c
)

set (
    Headers
    forward_list.h
    open_hash_struct.h
    hash_table.h
    hash.h
)

if(UTEST)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(cmocka REQUIRED cmocka)
    add_executable(WordsCounter Tests.c ${Sources} ${Headers})
    target_link_libraries(WordsCounter PRIVATE ${cmocka_LIBRARIES})
    target_include_directories(WordsCounter PRIVATE ${cmocka_INCLUDE_DIRS})
    target_compile_options(WordsCounter PRIVATE ${cmocka_CFLAGS_OTHER})
else()
    add_executable(WordsCounter main.c ${Sources} ${Headers})

endif()

target_compile_features(WordsCounter PRIVATE c_std_11)
set_target_properties(WordsCounter PROPERTIES C_STANDARD_REQUIRED ON)

if(MSVC)
    target_compile_options(WordsCounter PUBLIC /W4 /WX)
else()
    target_compile_options(WordsCounter PUBLIC -Wall -Wextra -Wpedantic)
endif()
