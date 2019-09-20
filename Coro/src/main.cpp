#include "Camera.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Window.hpp"
#include "Core.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ostream>
#include <iostream>

constexpr int W = 1280;
constexpr int H = 720;
constexpr char TITLE[] = "Coro";
Coro::Window window{ W, H, TITLE };
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

	const float xoffset = xpos - lastX;
	const float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMove(xoffset, yoffset);
};

void OnScroll(double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}

void processInput(const Coro::Window& window, float delta) {
	const float cameraSpeed = 2.5f * delta;  // adjust accordingly
	if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
		window.Close();
	}
	else if (window.IsKeyPressed(GLFW_KEY_1)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (window.IsKeyPressed(GLFW_KEY_2)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (window.IsKeyPressed(GLFW_KEY_3)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
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

	const auto indices = getIndices();

	const Coro::Mesh cube{ vertices, indices, {} };
	const auto lightningVert = Coro::MakeRef<Coro::Shader>("shaders/lightning.vert", GL_VERTEX_SHADER);
	const auto lightningFrag = Coro::MakeRef<Coro::Shader>("shaders/lightning.frag", GL_FRAGMENT_SHADER);
	const auto lightSourceFrag = Coro::MakeRef<Coro::Shader>("shaders/lightSource.frag", GL_FRAGMENT_SHADER);
	const Coro::ShaderProgram lightningProgram{ {lightningVert, lightningFrag} };
	const Coro::ShaderProgram lightSourceProgram{ {lightningVert, lightSourceFrag} };


	glm::vec3 lightPos{ 1.0f, 0.f, 2.f };
	const glm::vec3 lightColor{ 1.f, 1.f, 1.f };
	const glm::vec3 objectColor{ 1.f, .5f, .31f };

	lightningProgram.Use();
	lightningProgram.SetVec3("lightColor", lightColor);
	lightningProgram.SetVec3("objectColor", objectColor);
	lightningProgram.SetVec3("lightPos", lightPos);
	
	float delta = 0.f;
	float last = 0.f;
	float acc = .0f;
	int fps = 0;
	while (!window.ShouldClose()) {
		float current = glfwGetTime();
		delta = current - last;
		last = current;
		acc += delta;
		fps += 1;
		if (acc >= 1.0f) {
			std::cout << fps << "fps\ncurrent "
				<< current << "s\naverage delta " << ((acc/static_cast<float>(fps)) * 1000.f)
				<< "ms\ncurrent delta " << delta * 1000.f << "ms\n\n";
			acc = .0f;
			fps = 0;
		}

		processInput(window, delta);
		window.Clear();

		glm::mat4 model(1.0f);
		glm::mat4 view = camera.GetViewMatrix();
		const auto projection = glm::perspective(glm::radians(70.0f),
			static_cast<float>(W) / static_cast<float>(H),
			.1f, 100.f);
		
		lightningProgram.Use();
		lightningProgram.SetMat4("model", model);
		lightningProgram.SetMat4("view", view);
		lightningProgram.SetMat4("projection", projection);
		lightningProgram.SetVec3("viewPos", camera.GetPosition());
		lightPos.x += sin(current) * delta;
		lightPos.z += cos(current) * delta;
		lightningProgram.SetVec3("lightPos", lightPos);
		lightSourceProgram.Use();
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightningProgram.SetMat4("model", model);
		lightningProgram.SetMat4("view", view);
		lightningProgram.SetMat4("projection", projection);
		cube.Draw(lightningProgram);
		cube.Draw(lightSourceProgram);
		
		window.Update();
	}

	return 0;
}