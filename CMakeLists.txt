cmake_minimum_required(VERSION 3.15)
project(CoroEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_subdirectory(Coro)
add_subdirectory(Sandbox)

