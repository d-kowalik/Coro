#include "Camera.hpp"
#include "ShaderProgram.hpp"
#include "Window.hpp"

#include <glm/glm.hpp>
#include <iostream>
#include <random>
#include "Application.hpp"

constexpr int W = 1280;
constexpr int H = 720;
constexpr char TITLE[] = "Coro";

class SandboxApp : public Coro::Application
{
	using Application::Application;
	
	std::random_device _rd;
	std::mt19937 _gen{_rd()};
	std::uniform_real_distribution<float> _dist{ 0.f, 1.f };

	bool OnUserCreate() override {
		return true;
	};
	
	bool OnUserUpdate(float delta) override {
		
		static const float pixelSize = 4.f;
		for (int x = 0; x <= static_cast<float>(W) / pixelSize; x++) {
			for (int y = 0; y <= static_cast<float>(H) / pixelSize; y++) {
				DrawPixel(pixelSize, pixelSize, x * pixelSize,
					y * pixelSize,  _dist(_gen) < .5f ? 1 : 0,
						_dist(_gen) < .5f ? 1 : 0, _dist(_gen) < .5f ? 1 : 0 );
			}
		}

		return true;
	};

};

int main() {
	SandboxApp app{ TITLE, W, H };
	app.Run();
	
	return 0;
}