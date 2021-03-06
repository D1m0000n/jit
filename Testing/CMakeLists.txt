cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Testing)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

include(cmake/googletest.cmake)
fetch_googletest(
        cmake
        ${PROJECT_BINARY_DIR}/googletest
)

enable_testing()

# uncommet one of the following commands for running tests for structure with same name

add_subdirectory(TestHelpfulFunctions)
#add_subdirectory(TestMakeRpn)
#add_subdirectory(TestMakeMap)
#add_subdirectory(TestMakeUno)
#add_subdirectory(TestCountFunctionArgs)