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
    bool _keys[1024] = {};  // keyboard keys
    bool _buttons[32]{};    // mouse buttons
	mutable unsigned lastFps = 0;

   public:
    Coro::Callback<double, double> OnMouseMove;
    Coro::Callback<double, double> OnMouseScroll;
    Coro::Callback<int> OnKeyPressed;

   private:
    bool InitializeGLFW();
    bool CreateWindow();
    bool InitializeOpenGL();
    void Resize(int w, int h);

    void KeyPressed(int key);
    void KeyReleased(int key);
    void ButtonPressed(int button);
    void ButtonReleased(int button);

   public:
    Window(int width, int height, std::string title);
    ~Window();

    bool ShouldClose();
    void Clear();
    void Update() const;
    void Close() const;
	void UpdateTitle(unsigned fps) const;

    bool IsKeyPressed(int key) const;  // temporary
    bool IsMouseButtonPressed(int button) const;

    glm::vec2 GetMousePos() const;

    friend void framebuffer_size_callback(GLFWwindow* window, int w, int h);
    friend void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    friend void key_callback(GLFWwindow* window, int key, int scancode,
                             int action, int mods);
    friend void mouse_button_callback(GLFWwindow* window, int button,
                                      int action, int mods);
    friend void scroll_callback(GLFWwindow* window, double xoffset,
                                double yoffset);
};

}  // namespace Coro