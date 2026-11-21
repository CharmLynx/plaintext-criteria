cmake_minimum_required(VERSION 3.16)
project(plaintext_criteria LANGUAGES CXX)
find_package(ZLIB REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pcrit
    src/main.cpp
    src/alphabet.cpp
    src/preprocess.cpp
    src/ngram_stats.cpp
    src/report_writer.cpp
    src/sampler.cpp
    src/distortions.cpp
    src/language_model.cpp
    src/criteria/forbidden.cpp
    src/criteria/entropy_test.cpp
    src/criteria/empty_boxes.cpp
    src/compression.cpp
    src/criteria/structural.cpp
)

target_include_directories(pcrit PRIVATE include)
target_link_libraries(pcrit PRIVATE ZLIB::ZLIB)