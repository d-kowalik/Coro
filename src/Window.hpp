#pragma once

#include <string>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

class Window {
   private:
    GLFWwindow* _window;
    int _width, _height;
    std::string _title;

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

    friend void framebuffer_size_callback(GLFWwindow* window, int w, int h);
};