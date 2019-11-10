cmake_minimum_required(VERSION 3.15)
project(jit_compile)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD 11)

if(MINGW)
    set(GTEST_DISABLE_PTHREADS ON)
endif()

if(WIN32)
    set(WINDOWS_CMAKE_ARGS
            -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
            -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
            )
else(WIN32)
    set(WINDOWS_CMAKE_ARGS )
endif(WIN32)

add_executable(jit_compile main.cpp)
include_directories(.)

enable_testing()
add_subdirectory(Testing)