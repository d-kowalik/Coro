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
    while (!window.ShouldClose()) {
        window.Clear();
        window.Update();
    }

    glfwTerminate();
    return 0;
}