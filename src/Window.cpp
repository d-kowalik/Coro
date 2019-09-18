#include "Window.hpp"

#include <iostream>

using std::cout, std::endl;

namespace Coro {

void error_callback(int error, const char* description);

Window::Window(int width, int height, std::string title)
    : _width(width), _height(height), _title(title) {
    if (!InitializeGLFW()) {
        cout << "Failed to initialize GLFW" << endl;
        return;
    }
    if (!CreateWindow()) {
        cout << "Failed to create window" << endl;
        return;
    }
    if (!InitializeOpenGL()) {
        cout << "Failed to init OpenGL" << endl;
    }
}

Window::~Window() { glfwTerminate(); }

bool Window::InitializeGLFW() {
    if (!glfwInit()) return false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(error_callback);
    return true;
}

bool Window::CreateWindow() {
    _window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
    if (!_window) {
        cout << "Failed to create GLFW window" << endl;
        return false;
    }
    glfwMakeContextCurrent(_window);
    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
    glfwSetCursorPosCallback(_window, mouse_callback);

    return true;
}

bool Window::InitializeOpenGL() {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        return false;
    }

    glViewport(0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST);
    return true;
}

void Window::Resize(int w, int h) {
    _width = w;
    _height = h;
    glViewport(0, 0, w, h);
}

bool Window::ShouldClose() { return glfwWindowShouldClose(_window); }

void Window::Clear() {
    glClearColor(0.3f, 0.3f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update() {
    glfwSwapBuffers(_window);
    // process input
    glfwPollEvents();
}

void Window::Close() const { glfwSetWindowShouldClose(_window, true); }

glm::vec2 Window::GetMousePos() const { return _mousePos; }

bool Window::IsKeyPressed(int key) const {
    return glfwGetKey(_window, key) == GLFW_PRESS;
}

bool Window::IsMouseButtonPressed(int button) const {
    return glfwGetMouseButton(_window, button) == GLFW_PRESS;
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    win->Resize(w, h);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    win->_mousePos.x = xpos;
    win->_mousePos.y = ypos;
    win->OnMouseMove(xpos, ypos);
}

void error_callback(int error, const char* description) {
    cout << "GLFW Error: " << description << endl;
}

}  // namespace Coro