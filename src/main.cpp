#include <iostream>

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

    const char* vertexData = R"(
        #version 330 core
        layout (location=0) in vec3 aPos;

        void main() {
            gl_Position = vec4(aPos, 1.0f);
        }
    )";
    unsigned vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertexData, NULL);
    glCompileShader(vertShader);
    // Check for errors

    const char* fragmentData = R"(
        #version 330 core
        out vec4 FragColor;

        void main() {
            FragColor = vec4(0.8f, 0.1f, 0.3f, 1.0f);
        }
    )";
    unsigned fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragmentData, NULL);
    glCompileShader(fragShader);
    // Check for errors

    unsigned shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    // Check for errors

    glUseProgram(shaderProgram);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

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