#pragma once

#include <string>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "../Util/Callback.hpp"

namespace Coro {

class Window {
   private:
    GLFWwindow* _window;
    int _width, _height;
    std::string _title;
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

	GLFWwindow* GetNativeWindow() const { return _window; }

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