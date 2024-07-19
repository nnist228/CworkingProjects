cmake_minimum_required(VERSION 3.20)
project(libcurl_project)

find_package(CURL REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCJSON REQUIRED libcjson)

include_directories(${CURL_INCLUDE_DIR} ${LIBCJSON_INCLUDE_DIRS})

add_executable(CurlProj main.c)
target_compile_features(CurlProj PRIVATE c_std_17)
set_target_properties(CurlProj PROPERTIES C_STANDARD_REQUIRED ON)
target_link_libraries(CurlProj ${CURL_LIBRARY} ${LIBCJSON_LIBRARIES})


if(MSVC)
    target_compile_options(CurlProj PUBLIC /W4 /WX)
else()
    target_compile_options(CurlProj PUBLIC -Wall -Wextra -Wpedantic)
endif()

