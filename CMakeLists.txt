cmake_minimum_required(VERSION 3.10)
project(mp2_lab2_matrix)

# Явно указываем компилятор и стандарт
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Принудительно включаем C++11
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Include directories
include_directories(include gtest)

# Все исходные файлы
add_executable(utmatrix
    test/test_tvector.cpp
    test/test_tmatrix.cpp
    test/test_main.cpp
    gtest/gtest-all.cc
)

message(STATUS "Project configuration completed")