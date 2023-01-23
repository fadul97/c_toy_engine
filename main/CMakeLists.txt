project(ToyEngine)

add_executable(ToyEngine main.c)

target_include_directories(ToyEngine
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine)

target_link_libraries(ToyEngine CoreEngine)