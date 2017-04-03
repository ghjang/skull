cmake_minimum_required(VERSION 3.0.0)
project(skull_test VERSION 0.0.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(BOOST_ROOT "../../boost_1_63_0")
find_package(Boost 1.63.0)
if(Boost_FOUND)
    include_directories(${BOOST_ROOT})
else()
    message(FATAL_ERROR "Could not find boost!")
endif()

set(SKULL_ROOT "../include")
include_directories(${SKULL_ROOT})

set(CMAKE_C_COMPILER  "/Users/gilhojang/clang/clang+llvm-4.0.0-x86_64-apple-darwin/bin/clang")
set(CMAKE_CXX_COMPILER  "/Users/gilhojang/clang/clang+llvm-4.0.0-x86_64-apple-darwin/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

set(SOURCE_FILES
        id_test.cpp
        main.cpp)

add_executable(skull_test ${SOURCE_FILES})
