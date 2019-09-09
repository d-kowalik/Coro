#include <iostream>

#include "Shader.hpp"
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

    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                        0.0f,  0.0f,  0.5f, 0.0f};

    unsigned vbo;
    glGenBuffers(1, &vbo);

    pge::Shader vertShader{"shaders/basic.vert", GL_VERTEX_SHADER};
    pge::Shader fragShader{"shaders/basic.frag", GL_FRAGMENT_SHADER};

    unsigned shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader.GetId());
    glAttachShader(shaderProgram, fragShader.GetId());
    glLinkProgram(shaderProgram);
    // Check for errors
    glUseProgram(shaderProgram);

    vertShader.Delete();
    fragShader.Delete();

    // Bound to our VBO because we previously bound it
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          reinterpret_cast<void*>(0));

    // -1 bind this all to VAO
    unsigned vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // 0. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    // 2. use our shader program when we want to render an object
    glUseProgram(shaderProgram);
    // 3. now draw the object
    // someOpenGLFunctionThatDrawsOurTriangle();
    // We can bind that whole operation to a VAO if we specify it before all
    // this! Well, not shader.

    while (!window.ShouldClose()) {
        window.Clear();

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.Update();
    }

    glfwTerminate();
    return 0;
}