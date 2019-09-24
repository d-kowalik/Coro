#include "Application.hpp"

namespace Coro {

Application::Application(const std::string& title, int width, int height) {
	_instance = this;
	_window = new Window(width, height, title);
}

Application::~Application() {
	delete _window;
}

Application* Application::Get() {
	return _instance;
}

void Application::Run() {
	OnUserCreate();
	while (!_window->ShouldClose()) {
		timer.Tick();
		const float delta = timer.GetDelta();
		_window->UpdateTitle(timer.GetFPS());

		_window->Clear();

		OnUserUpdate();

		_window->Update();
	}
}

}
