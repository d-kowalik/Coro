#include <iostream>
#include <random>
#include "Application.hpp"
#include "Input.hpp"
#include "Keycodes.hpp"

constexpr int W = 1280;
constexpr int H = 720;
constexpr char TITLE[] = "Coro";

class SandboxApp : public Coro::Application
{
	using Application::Application;

	std::random_device _rd;
	std::mt19937 _gen{ _rd() };
	std::uniform_real_distribution<float> _dist{ 0.f, 1.f };

	bool OnUserCreate() override {
		return true;
	};
	
	bool OnUserUpdate(float delta) override {
		if (Coro::Input::IsKeyPressed(Coro::Key::ESCAPE)) {
			std::cout << "Escape pressed!" << std::endl;
		}
		
		static const char _map[] = "########"
			"#..##..#"
			"#..##..#"
			"########"
			"#.####.#"
			"##....##"
			"########"
			"########";
		
		static const float pixelSize = H/8.f;
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				DrawPixel(pixelSize, pixelSize, x * pixelSize, y * pixelSize, _map[8 * y + x] == '.' ? 0 : 1, .5f, .5f);
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