cmake_minimum_required(VERSION 3.15)
project(Coro)

include_directories(/usr/include/GLFW
        /usr/include/glm
        ${CMAKE_SOURCE_DIR}/vendor/glad/include
        ${CMAKE_SOURCE_DIR}/vendor/stb_image/include)

find_library(GLFW_LIBRARY glfw HINTS /usr/lib/x86_64-linux-gnu)

add_library(Coro SHARED
        src/Coro/Graphics/Mesh.cpp
        src/Coro/Graphics/Mesh.hpp
        src/Coro/Graphics/Pixel.hpp
        src/Coro/Graphics/PixelRenderer.cpp
        src/Coro/Graphics/PixelRenderer.hpp
        src/Coro/Graphics/Shader.cpp
        src/Coro/Graphics/Shader.hpp
        src/Coro/Graphics/ShaderProgram.cpp
        src/Coro/Graphics/ShaderProgram.hpp
        src/Coro/Graphics/Texture.cpp
        src/Coro/Graphics/Texture.hpp
        src/Coro/Graphics/Window.cpp
        src/Coro/Graphics/Window.hpp
        src/Coro/Input/Input.cpp
        src/Coro/Input/Input.hpp
        src/Coro/Input/Keycodes.hpp
        src/Coro/Util/Callback.hpp
        src/Coro/Util/FileUtils.hpp
        src/Coro/Util/Timer.hpp
        src/Coro/Application.cpp
        src/Coro/Application.hpp
        src/Coro/Camera.cpp
        src/Coro/Camera.hpp
        src/Coro/Core.hpp

        ../vendor/glad/src/glad.c ../vendor/stb_image/stb_image.cpp src/Coro/Coro.hpp)

target_link_libraries(Coro PUBLIC GL ${GLFW_LIBRARY} ${CMAKE_DL_LIBS})
