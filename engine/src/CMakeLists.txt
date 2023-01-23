project(ToyEngine)

add_library(CoreEngine engine.c error_list.c logger.c memory.c)

target_include_directories(CoreEngine
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../)

target_link_libraries(CoreEngine ToyPlatform)