#pragma once

#include "Graphics/Window.hpp"
#include "Util/Timer.hpp"
#include "Graphics/PixelRenderer.hpp"

#include <string>


namespace Coro {

class Application
{
private:
	inline static Application* _instance = nullptr;
	Window* _window;
	Timer _timer;
	PixelRenderer* _renderer = nullptr;

public:
	explicit Application(const std::string& title, int width, int height);
	virtual ~Application();
	static Application* Get();

	virtual bool OnUserCreate() = 0;
	virtual bool OnUserUpdate(float delta) = 0;
	
	void DrawPixel(float w, float h, float x, float y, float r, float g, float b);
	void Run();
	void Quit();

	Window const* GetWindow() const { return _window;  }
	
private:
	void PrepareDraw();
	void Draw();
	void FinishPrepareDraw();
};

}