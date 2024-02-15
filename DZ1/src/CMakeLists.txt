cmake_minimum_required(VERSION 3.12)

project(ZipReader_main VERSION 0.0.1)

add_executable(main_zip main.c)

target_compile_features(main_zip PUBLIC c_std_11)
set_target_properties(main_zip PROPERTIES C_STANDARD_REQUIRED ON)
set_target_properties(main_zip PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(main_zip lib_zip)

if(MSVC)
    target_compile_options(main_zip PUBLIC /W4 /WX)
else()
    target_compile_options(main_zip PUBLIC -Wall -Wextra -Wpedantic)
endif()

add_custom_target(copyConfig
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/TestFiles/* ${CMAKE_BINARY_DIR}/testFiles
)

add_dependencies(main_zip copyConfig)
