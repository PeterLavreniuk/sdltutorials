cmake_minimum_required(VERSION 3.17)
project(sdltutorials)
set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED SDL2)

add_executable(sdltutorials lesson_9/lesson_9.cpp)

target_link_libraries(sdltutorials PRIVATE SDL2 SDL2_image)