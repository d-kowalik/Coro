#include <stb_image/stb_image.h>
#include <cmath>
#include <iostream>

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

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float mixPercent = 0.2f;
void processInput(const Window& window, float delta) {
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
    if (window.IsKeyPressed(GLFW_KEY_W)) cameraPos += cameraSpeed * cameraFront;
    if (window.IsKeyPressed(GLFW_KEY_S)) cameraPos -= cameraSpeed * cameraFront;
    if (window.IsKeyPressed(GLFW_KEY_A))
        cameraPos -=
            glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (window.IsKeyPressed(GLFW_KEY_D))
        cameraPos +=
            glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
        cameraPos -= cameraSpeed * cameraUp;
    if (window.IsKeyPressed(GLFW_KEY_SPACE))
        cameraPos += cameraSpeed * cameraUp;
}
#include "cubevertices.hpp"
int main() {
    Window window{W, H, TITLE};

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
        std::make_shared<pge::Shader>("shaders/basic.vert", GL_VERTEX_SHADER);
    auto basicFrag =
        std::make_shared<pge::Shader>("shaders/basic.frag", GL_FRAGMENT_SHADER);

    pge::ShaderProgram program({basicVert, basicFrag});

    auto containerTexture =
        std::make_shared<pge::Texture>("textures/container.jpg", false);
    auto faceTexture =
        std::make_shared<pge::Texture>("textures/awesomeface.png");

    pge::Mesh texturedMesh{vertices, indices, {containerTexture, faceTexture}};

    glm::mat4 model(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, .0f, .0f));
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
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
    float lastX = W / 2;
    float lastY = H / 2;
    float yaw = -90.f;
    float pitch = 0.f;
    while (!window.ShouldClose()) {
        float current = glfwGetTime();
        delta = current - last;
        last = current;

        window.Clear();
        processInput(window, delta);

        auto mpos = window.GetMousePos();
        float xpos = mpos.x;
        float ypos = mpos.y;
        static bool firstMouse = false;
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.05;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);

        std::cout << glfwGetTime() << std::endl;

        program.Use();
        float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
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