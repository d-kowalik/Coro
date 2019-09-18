#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <GLFW/glfw3.h>

#include "Callback.hpp"

namespace Coro {

class Window {
   private:
    GLFWwindow* _window;
    int _width, _height;
    std::string _title;
    glm::vec2 _mousePos;

   public:
    Coro::Callback<double, double> OnMouseMove;

   private:
    bool InitializeGLFW();
    bool CreateWindow();
    bool InitializeOpenGL();
    void Resize(int w, int h);

   public:
    Window(int width, int height, std::string title);
    ~Window();

    bool ShouldClose();
    void Clear();
    void Update();
    void Close() const;

    bool IsKeyPressed(int key) const;  // temporary
    bool IsMouseButtonPressed(int button) const;

    glm::vec2 GetMousePos() const;

    friend void framebuffer_size_callback(GLFWwindow* window, int w, int h);
    friend void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};

}