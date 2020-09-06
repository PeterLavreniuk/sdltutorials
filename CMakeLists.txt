cmake_minimum_required(VERSION 3.17)
project(sdltutorials)
set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED SDL2)

add_executable(sdltutorials main.cpp)

target_link_libraries(sdltutorials PRIVATE SDL2)