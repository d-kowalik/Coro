#include "Camera.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Window.hpp"
#include "Core.hpp"
#include "PixelRenderer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ostream>
#include <iostream>
#include <random>
#include "Timer.hpp"

constexpr int W = 1280;
constexpr int H = 720;
constexpr char TITLE[] = "Coro";
Coro::Window window{ W, H, TITLE };
Coro::Camera camera;

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

	Coro::Timer timer;
	while (!window.ShouldClose()) {
		timer.Tick();
		const float delta = timer.GetDelta();
		window.UpdateTitle(timer.GetFPS());

		
		processInput(window, delta);
		window.Clear();

		renderer.Begin();
		const float pixelSize = 4.f;
		for (int x = 0; x <= static_cast<float>(W) / pixelSize; x++) {
			for (int y = 0; y <= static_cast<float>(H) / pixelSize; y++) {
				renderer.Add(Coro::MakeRef<Coro::Pixel>(pixelSize, pixelSize, x * pixelSize,
					y * pixelSize, glm::vec3{ dist(gen) < .5f ? 1 : 0,
						dist(gen) < .5f ? 1 : 0, dist(gen) < .5f ? 1 : 0 }));
			}
		}
		renderer.End();
		renderer.Draw();

		
		window.Update();
	}

	return 0;
}