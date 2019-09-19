#include <stb_image/stb_image.h>
#include <cmath>
#include <iostream>

#include "Camera.hpp"
#include "Core.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Window.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr int W = 1280;
constexpr int H = 720;
constexpr char TITLE[] = "Coro";
Coro::Window window{W, H, TITLE};
Coro::Camera camera;

float lastX = W / 2;
float lastY = H / 2;

void MoveCamera(double xpos, double ypos) {
    static bool firstMouse = false;
    if (!window.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
        firstMouse = true;
        return;
    }
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMove(xoffset, yoffset);
};

void OnScroll(double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

float mixPercent = 0.2f;
void processInput(const Coro::Window& window, float delta) {
    const float cameraSpeed = 2.5f * delta;  // adjust accordingly
    if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
        window.Close();
    } else if (window.IsKeyPressed(GLFW_KEY_1)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (window.IsKeyPressed(GLFW_KEY_2)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if (window.IsKeyPressed(GLFW_KEY_3)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    } else if (window.IsKeyPressed(GLFW_KEY_UP)) {
        if (mixPercent >= 1.0f) return;
        mixPercent += 0.001f;
    } else if (window.IsKeyPressed(GLFW_KEY_DOWN)) {
        if (mixPercent <= 0.0f) return;
        mixPercent -= 0.001f;
    }
    if (window.IsKeyPressed(GLFW_KEY_W)) {
        camera.ProcessInput(Coro::Camera::CameraMovement::FORWARD, delta);
    }
    if (window.IsKeyPressed(GLFW_KEY_S)) {
        camera.ProcessInput(Coro::Camera::CameraMovement::BACKWARD, delta);
    }
    if (window.IsKeyPressed(GLFW_KEY_A)) {
        camera.ProcessInput(Coro::Camera::CameraMovement::LEFT, delta);
    }
    if (window.IsKeyPressed(GLFW_KEY_D)) {
        camera.ProcessInput(Coro::Camera::CameraMovement::RIGHT, delta);
    }
    if (window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
        camera.ProcessInput(Coro::Camera::CameraMovement::DOWN, delta);
    }
    if (window.IsKeyPressed(GLFW_KEY_SPACE)) {
        camera.ProcessInput(Coro::Camera::CameraMovement::UP, delta);
    }
}

#include "cubevertices.hpp"

int main() {
    window.OnMouseMove += MoveCamera;
    window.OnMouseScroll += OnScroll;

    std::vector<unsigned> indices{};
    indices.reserve(36);

    for (int j = 0; indices.size() < 36; j += 4) {
        indices.push_back(j);
        indices.push_back(j + 1);
        indices.push_back(j + 3);
        indices.push_back(j + 1);
        indices.push_back(j + 2);
        indices.push_back(j + 3);
    }

    auto basicVert =
        std::make_shared<Coro::Shader>("shaders/basic.vert", GL_VERTEX_SHADER);
    auto basicFrag = std::make_shared<Coro::Shader>("shaders/basic.frag",
                                                    GL_FRAGMENT_SHADER);

    Coro::ShaderProgram program({basicVert, basicFrag});

    auto containerTexture =
        std::make_shared<Coro::Texture>("textures/container.jpg", false);
    auto faceTexture =
        std::make_shared<Coro::Texture>("textures/awesomeface.png");

    Coro::Mesh texturedMesh{vertices, indices, {containerTexture, faceTexture}};

    glm::mat4 model(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, .0f, .0f));
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(70.0f),
                                  static_cast<float>(W) / static_cast<float>(H),
                                  .1f, 100.f);

    program.Use();
    program.SetMat4("model", model);
    program.SetMat4("view", view);
    program.SetMat4("projection", projection);

    float lastPercent = mixPercent;
    float delta = 0.f;
    float last = 0.f;

    while (!window.ShouldClose()) {
        float current = glfwGetTime();
        delta = current - last;
        last = current;

        processInput(window, delta);

        std::cout << delta * 1000 << std::endl;

        window.Clear();
        program.Use();
        view = camera.GetViewMatrix();
        program.SetMat4("view", view);
        if (lastPercent != mixPercent) {
            program.SetFloat("mixPercent", mixPercent);
            lastPercent = mixPercent;
        }
        glm::mat4 model(1.0f);
        model =
            glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, .0f, .0f));
        program.SetMat4("model", model);
        texturedMesh.Draw(program);

        window.Update();
    }

    return 0;
}