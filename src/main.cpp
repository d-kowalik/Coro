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
constexpr char TITLE[] = "Pixel Game Engine";
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
}
#include "cubevertices.hpp"
int main() {
    window.OnMouseMove += MoveCamera;

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

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

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

        window.Clear();
        processInput(window, delta);

        std::cout << glfwGetTime() << std::endl;

        program.Use();
        view = camera.GetViewMatrix();
        program.SetMat4("view", view);
        if (lastPercent != mixPercent) {
            program.SetFloat("mixPercent", mixPercent);
            lastPercent = mixPercent;
        }
        unsigned i = 0;
        for (const auto& pos : cubePositions) {
            glm::mat4 model(1.0f);
            float angle = i++ * 20.0f;
            model = glm::translate(model, pos);
            model = glm::rotate(model, glm::radians(angle),
                                glm::vec3(1.0f, .5f, .0f));
            program.SetMat4("model", model);
            texturedMesh.Draw(program);
        }

        window.Update();
    }

    return 0;
}