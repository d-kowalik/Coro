#pragma once
#include <utility>

namespace Coro {

class Input {
public:
	static bool IsKeyPressed(int keycode);
	static bool IsMouseButtonPressed(int button);
	static std::pair<float, float> GetMousePos();
};
}
