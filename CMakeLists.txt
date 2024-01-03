cmake_minimum_required(VERSION 3.24)
project(kmeans)

set(CMAKE_CXX_STANDARD 17)

find_package(Raylib REQUIRED)

add_executable(kmeans kmean.cpp)
target_link_libraries(kmeans PRIVATE raylib)
