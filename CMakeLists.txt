cmake_minimum_required(VERSION 3.10)
project(yamibarai)

set(CMAKE_CXX_STANDARD 11)

add_executable(yamibarai yamibarai.cpp)
target_link_libraries(yamibarai ${CMAKE_SOURCE_DIR}/interception.lib)
