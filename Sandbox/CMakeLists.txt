cmake_minimum_required(VERSION 3.15)
project(Sandbox)

include_directories(/usr/include/GLFW
        /usr/include/glm
        ${CMAKE_SOURCE_DIR}/vendor/glad/include
        ${CMAKE_SOURCE_DIR}/vendor/stb_image/include
        ${CMAKE_SOURCE_DIR}/Coro/src)

find_library(GLFW_LIBRARY glfw HINTS /usr/lib/x86_64-linux-gnu)

add_executable(Sandbox
        src/main.cpp)

target_link_libraries(Sandbox PUBLIC GL ${GLFW_LIBRARY} ${CMAKE_DL_LIBS} Coro)
