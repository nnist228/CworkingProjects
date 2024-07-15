cmake_minimum_required(VERSION 3.20)
project(libcurl_project)


set(CURL_INCLUDE_DIR "C:/ProgramData/chocolatey/lib/curl/tools/curl-8.8.0_1-win64-mingw/include/curl/")
set(CURL_LIBRARY "C:/ProgramData/chocolatey/lib/curl/tools/curl-8.8.0_1-win64-mingw/bin/libcurl-x64.dll")

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)     
endif()

add_definitions(-DCURL_DYNAMICLIB)
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_executable(CurlProj main.c)
target_compile_features(CurlProj PRIVATE c_std_17)
set_target_properties(CurlProj PROPERTIES C_STANDARD_REQUIRED ON)
target_link_libraries(CurlProj ${CURL_LIBRARY})


if(MSVC)
    target_compile_options(CurlProj PUBLIC /W4 /WX)
else()
    target_compile_options(CurlProj PUBLIC -Wall -Wextra -Wpedantic)
endif()

