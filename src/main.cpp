#include <cmath>
#include <iostream>

#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Window.hpp"

constexpr int W = 1280;
constexpr int H = 720;
constexpr char TITLE[] = "Pixel Game Engine";

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    Window window{W, H, TITLE};

    float vertices[] = {
        -0.1f, 0.5f,  0.0f, 1.0f, 0.0f, 0.0f,  // top right
        -0.1f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom right
        -0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  // bottom left
        -0.9f, 0.5f,  0.0f, 1.0f, 0.0f, 0.5f,  // top left
        0.1f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,  // top left
        0.1f,  -0.5f, 0.0f, 1.0f, .5f,  .7f,   // bottom left
        0.9f,  -0.5f, 0.0f, .5f,  0.5f, 0.5f,  // bottom right
        0.9f,  0.5f,  0.0f, .5f,  0.5f, 1.0f,  // top right
    };

    unsigned indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3,  // second triangle
    };

    pge::ShaderProgram program({{"shaders/basic.vert", GL_VERTEX_SHADER},
                                {"shaders/basic.frag", GL_FRAGMENT_SHADER}});

    unsigned vao, vbo, ebo, vao1, vbo1, ebo1;
    glGenVertexArrays(1, &vao);
    glGenVertexArrays(1, &vao1);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenBuffers(1, &vbo1);
    glGenBuffers(1, &ebo1);
    glBindVertexArray(vao);

    //
    //
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //
    //
    glBindVertexArray(vao1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          reinterpret_cast<void*>(4 * 6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
        reinterpret_cast<void*>((4 * 6 * sizeof(float)) + (3 * sizeof(float))));
    glEnableVertexAttribArray(1);

    // Unbind everything, VAO will bind it later.
    // Important: UNBIND EBO AFTER UNBINDING VAO OR IT WILL SAVE UNBINDING
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!window.ShouldClose()) {
        window.Clear();

        float timeValue = glfwGetTime();

        program.Use();
        glBindVertexArray(vao);
        program.SetUniform3f("color", 1.0f, 1.0f, 0.5f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(vao1);
        program.SetUniform3f("color", std::cos(timeValue), 0.7f,
                             std::sin(timeValue));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        window.Update();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    return 0;
}