cmake_minimum_required(VERSION "3.19.2")

add_subdirectory("thirdparty/SDL2")

project(Snake)

add_executable(Snake "SnakeCPP.cpp")

target_include_directories(Snake PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries(Snake PRIVATE SDL2 SDL2main)