cmake_minimum_required(VERSION 3.0.0)
project(hijack VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(dummy dummy.c)
add_library(hijack SHARED PatternSearch.cpp hijack.cpp)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
