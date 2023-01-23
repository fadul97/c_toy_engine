cmake_minimum_required(VERSION 3.22)
project(ToyPlatform)

add_subdirectory(include)

add_library(ToyPlatform platform.c input.c display_x11.c gl_context.c gl.c)

target_include_directories(ToyPlatform
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../engine)

if(UNIX)
	target_link_libraries(ToyPlatform -lX11 -lGL ToyMath CoreEngine)
endif()