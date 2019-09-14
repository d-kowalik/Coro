#include <stb_image/stb_image.h>
#include <cmath>
#include <iostream>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Window.hpp"

constexpr int W = 1280;
constexpr int H = 720;
constexpr char TITLE[] = "Pixel Game Engine";

float mixPercent = 0.2f;
void processInput(const Window& window) {
    if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
        window.Close();
    } else if (window.IsKeyPressed(GLFW_KEY_1)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (window.IsKeyPressed(GLFW_KEY_2)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if (window.IsKeyPressed(GLFW_KEY_3)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    } else if (window.IsKeyPressed(GLFW_KEY_UP)) {
        if (mixPercent >= 1.0f) return;
        mixPercent += 0.001f;
    } else if (window.IsKeyPressed(GLFW_KEY_DOWN)) {
        if (mixPercent <= 0.0f) return;
        mixPercent -= 0.001f;
    }
}

int main() {
    Window window{W, H, TITLE};

    std::vector<pge::Vertex> vertices{
        // positions          // colors           // texture coords
        {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},  // top right
        {{0.5f, -0.5f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {1.0f, 0.0f}},  // bottom right
        {{-0.5f, -0.5f, 0.0f},
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f}},                                          // bottom left
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}  // top left
    };

    std::vector<unsigned> indices{
        0, 1, 3,  // first triangle
        1, 2, 3,  // second triangle
    };

    pge::ShaderProgram program({{"shaders/basic.vert", GL_VERTEX_SHADER},
                                {"shaders/basic.frag", GL_FRAGMENT_SHADER}});

    pge::Mesh texturedMesh{
        vertices,
        indices,
        {{"textures/container.jpg", false}, {"textures/awesomeface.png"}}};

    float lastPercent = mixPercent;
    while (!window.ShouldClose()) {
        window.Clear();
        processInput(window);

        program.Use();
        if (lastPercent != mixPercent) {
            std::cout << "Mix percent: " << mixPercent << std::endl;
            program.Use();
            program.SetFloat("mixPercent", mixPercent);
            lastPercent = mixPercent;
        }
        texturedMesh.Draw(program);
        window.Update();
    }

    return 0;
}