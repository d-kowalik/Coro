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
#include <random>
#include "PixelRenderer.hpp"

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

void processInput(const Coro::Window& window, float delta) {
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
}

int main() {

	Coro::PixelRenderer renderer{W, H};

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.f, 1.f);

	float delta = 0.f;
	float last = 0.f;
	float acc = .0f;
	int fps = 0;
	while (!window.ShouldClose()) {
		const float current = glfwGetTime();
		delta = current - last;
		last = current;
		acc += delta;
		fps += 1;
		if (acc >= 1.0f) {
			std::cout << fps 
				<< "fps\nframetime " << ((acc/static_cast<float>(fps)) * 1000.f)
				<< "ms\ncurrent delta " << delta * 1000.f << "ms\n\n";
			acc = .0f;
			fps = 0;
		}

		processInput(window, delta);
		window.Clear();

		renderer.Begin();
		const float pixelSize = 32.f;
		for (int x = 0; x <= static_cast<float>(W) / pixelSize; x++) {
			for (int y = 0; y <= static_cast<float>(H) / pixelSize; y++) {
				renderer.Add(Coro::MakeRef<Coro::Pixel>(pixelSize, pixelSize, x * pixelSize,
					y * pixelSize, glm::vec3{ dist(gen), dist(gen), dist(gen), }));
			}
		}
		renderer.End();
		renderer.Draw();

		
		window.Update();
	}

	return 0;
}