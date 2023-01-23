cmake_minimum_required(VERSION 3.22)

project(ToyMath)

add_library(ToyMath INTERFACE .)

target_include_directories(ToyMath
    INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine)


target_link_libraries(ToyMath INTERFACE CoreEngine)
