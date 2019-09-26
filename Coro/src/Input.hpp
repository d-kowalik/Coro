#pragma once

#include <utility>

#include "Keycodes.hpp"

namespace Coro {
	class Input
	{
	public:
		static bool IsKeyPressed(Key keycode);
		static bool IsMouseButtonPressed(MouseButton button);
		static std::pair<float, float> GetMousePos();
	};
}
