cmake_minimum_required(VERSION 3.16)
project(plaintext_criteria LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pcrit
    src/main.cpp
)

target_include_directories(pcrit PRIVATE include)