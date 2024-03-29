#include "Window.hpp"

#include <iostream>

using std::cout, std::endl;

namespace Coro {

void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode,
	int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button,
	int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset,
	double yoffset);

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
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(_window, key_callback);
    glfwSetMouseButtonCallback(_window, mouse_button_callback);
    glfwSetScrollCallback(_window, scroll_callback);
	
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

void Window::KeyPressed(int key) {
    OnKeyPressed(key);
}

void Window::KeyReleased(int key) {  }

void Window::ButtonPressed(int button) { }

void Window::ButtonReleased(int button) { }

bool Window::ShouldClose() { return glfwWindowShouldClose(_window); }

void Window::Clear() {
    glClearColor(0.3f, 0.3f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update() const {
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

void Window::Close() const { glfwSetWindowShouldClose(_window, true); }

void Window::UpdateTitle(unsigned fps) const {
	if (lastFps == fps) return;
	std::string newTitle{ _title + " | " + std::to_string(fps) + "fps" };
	glfwSetWindowTitle(_window, newTitle.c_str());
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    win->Resize(w, h);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    win->OnMouseMove(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    win->OnMouseScroll(xoffset, yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action,
                           int mods) {
    Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_PRESS)
        win->ButtonPressed(button);
    else if (action == GLFW_RELEASE)
        win->ButtonReleased(button);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods) {
    Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_PRESS)
        win->KeyPressed(key);
    else if (action == GLFW_RELEASE)
        win->KeyReleased(key);
}

void error_callback(int error, const char* description) {
    cout << "GLFW Error: " << description << endl;
}

}  // namespace Coro