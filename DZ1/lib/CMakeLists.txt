cmake_minimum_required(VERSION 3.12)

project(ZIP_library VERSION 0.0.1)

set(SOURCES
    cfh.c
    eocdr.c
    readBits.c
)

set(HEADRS
    cfh.h
    eocdr.h
    readBits.h
)

add_library(lib_zip STATIC ${SOURCES} ${HEADRS})

target_compile_features(lib_zip PUBLIC c_std_11)
set_target_properties(lib_zip PROPERTIES C_STANDARD_REQUIRED ON)



if(MSVC)
    target_compile_options(lib_zip PUBLIC /W4 /WX)
else()
    target_compile_options(lib_zip PUBLIC -Wall -Wextra -Wpedantic)
endif()