#pragma once

#include "Window.hpp"
#include "Timer.hpp"

#include <string>


namespace Coro {

class Application
{
private:
	inline static Application* _instance = nullptr;
	Window* _window;
	Timer timer;

public:
	Application(const std::string& title, int width, int height);
	virtual ~Application();
	static Application* Get();

	virtual bool OnUserCreate() = 0;
	virtual bool OnUserUpdate() = 0;
	
	void Run();
};

}