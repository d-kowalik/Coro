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

    float vertices[] = {
        -0.1f, 0.5f,  0.0f,  // top right
        -0.1f, -0.5f, 0.0f,  // bottom right
        -0.9f, -0.5f, 0.0f,  // bottom left
        -0.9f, 0.5f,  0.0f,  // top left
        0.1f,  0.5f,  0.0f,  // top left
        0.1f,  -0.5f, 0.0f,  // bottom left
        0.9f,  -0.5f, 0.0f,  // bottom right
        0.9f,  0.5f,  0.0f   // top right
    };

    unsigned indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3,  // second triangle
        4, 5, 7,  // first triangle second square
        5, 6, 7   // second triangle second square
    };

    pge::Shader vertShader{"shaders/basic.vert", GL_VERTEX_SHADER};
    pge::Shader fragShader{"shaders/basic.frag", GL_FRAGMENT_SHADER};

    unsigned shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader.GetId());
    glAttachShader(shaderProgram, fragShader.GetId());
    glLinkProgram(shaderProgram);
    // Check for errors

    vertShader.Delete();
    fragShader.Delete();

    unsigned vbo, ebo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    // -1 bind this all to VAO
    glBindVertexArray(vao);
    // 0. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);
    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    // 2. use our shader program when we want to render an object\
    // 3. now draw the object
    // someOpenGLFunctionThatDrawsOurTriangle();
    // We can bind that whole operation to a VAO if we specify it before all
    // this! Well, not shader.

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!window.ShouldClose()) {
        window.Clear();

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        window.Update();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    return 0;
}