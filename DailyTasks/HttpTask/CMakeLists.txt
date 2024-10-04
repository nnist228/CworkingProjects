cmake_minimum_required(VERSION 3.20)
project(Epoll_proj)



add_executable(epoll main.c)
target_compile_features(epoll PRIVATE c_std_17)
set_target_properties(epoll PROPERTIES C_STANDARD_REQUIRED ON)


if(MSVC)
    target_compile_options(epoll PUBLIC /W4 /WX)
else()
    target_compile_options(epoll PUBLIC -Wall -Wextra -Wpedantic)
endif()

