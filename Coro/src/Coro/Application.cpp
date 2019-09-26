#include "Application.hpp"

namespace Coro {

Application::Application(const std::string& title, int width, int height) {
	_instance = this;
	_window = new Window(width, height, title);
	_renderer = new Coro::PixelRenderer(width, height);
}

Application::~Application() {
	delete _window;
	delete _renderer;
}

Application* Application::Get() {
	return _instance;
}

void Application::Run() {
	OnUserCreate();
	while (!_window->ShouldClose()) {
		_timer.Tick();
		const float delta = _timer.GetDelta();
		_window->UpdateTitle(_timer.GetFPS());

		_window->Clear();

		PrepareDraw();
		OnUserUpdate(delta);
		FinishPrepareDraw();
		Draw();
		
		_window->Update();
	}
}

void Application::Quit() {
	_window->Close();
}

void Application::PrepareDraw() {
	_renderer->Begin();
}

void Application::Draw() {
	_renderer->Draw();
}

void Application::FinishPrepareDraw() {
	_renderer->End();
	
}

void Application::DrawPixel(float w,float h, float x, float y, float r, float g, float b) {
	_renderer->Add(MakeRef<Pixel>(w, h, x, y, glm::vec3{ r, g, b }));
}

}
