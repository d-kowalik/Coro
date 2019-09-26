#include "Input.hpp"
#include "../Application.hpp"

namespace Coro {

	bool Input::IsKeyPressed(Key keycode) {
		const auto window = Application::Get()->GetWindow()->GetNativeWindow();
		const auto state = glfwGetKey(window, static_cast<int>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseButton button) {
		const auto window = Application::Get()->GetWindow()->GetNativeWindow();
		const auto state = glfwGetMouseButton(window, static_cast<int>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePos() {
		const auto window = Application::Get()->GetWindow()->GetNativeWindow();
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { x, y };
	}
	
}
