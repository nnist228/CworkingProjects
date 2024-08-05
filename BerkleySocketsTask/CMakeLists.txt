cmake_minimum_required(VERSION 3.20)
project(berkley_soc_proj)



add_executable(BSoc main.c)
target_compile_features(BSoc PRIVATE c_std_17)
set_target_properties(BSoc PROPERTIES C_STANDARD_REQUIRED ON)


if(MSVC)
    target_compile_options(BSoc PUBLIC /W4 /WX)
else()
    target_compile_options(BSoc PUBLIC -Wall -Wextra -Wpedantic)
endif()

