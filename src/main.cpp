#include <cmath>
#include <iostream>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Window.hpp"

constexpr int W = 1280;
constexpr int H = 720;
constexpr char TITLE[] = "Pixel Game Engine";

void processInput(const Window& window) {
    if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
        window.Close();
    } else if (window.IsKeyPressed(GLFW_KEY_1)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (window.IsKeyPressed(GLFW_KEY_2)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if (window.IsKeyPressed(GLFW_KEY_3)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
}

int main() {
    Window window{W, H, TITLE};

    std::vector<pge::Vertex> vertices1{
        {{-0.1f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},   // top right
        {{-0.1f, -0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}},  // bottom right
        {{-0.9f, -0.5f, 0.0f}, {1.0f, 0.0f, 1.0f}},  // bottom left
        {{-0.9f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.5f}}    // top left
    };

    std::vector<pge::Vertex> vertices2{
        {{0.1f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},  // top left
        {{0.1f, -0.5f, 0.0f}, {1.0f, .5f, .7f}},   // bottom left
        {{0.9f, -0.5f, 0.0f}, {.5f, 0.5f, 0.5f}},  // bottom right
        {{0.9f, 0.5f, 0.0f}, {.5f, 0.5f, 1.0f}}    // top right
    };

    std::vector<unsigned> indices{
        0, 1, 3,  // first triangle
        1, 2, 3,  // second triangle
    };

    pge::ShaderProgram program({{"shaders/basic.vert", GL_VERTEX_SHADER},
                                {"shaders/basic.frag", GL_FRAGMENT_SHADER}});

    pge::Mesh mesh1{vertices1, indices};
    pge::Mesh mesh2{vertices2, indices};

    while (!window.ShouldClose()) {
        window.Clear();
        processInput(window);

        mesh1.Draw(program);
        mesh2.Draw(program);

        window.Update();
    }

    return 0;
}