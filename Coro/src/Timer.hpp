#pragma once 
#include <GLFW/glfw3.h>
#include <iostream>

namespace Coro {

class Timer
{
	float _last = 0.f;
	float _now = 0.f;
	float _acc = 0.f;
	float _delta = 0.f;
	unsigned _fps = 0;

public:
	void Tick() {
		_now = static_cast<float>(glfwGetTime());
		_delta = _now - _last;
		_last = _now;
		_acc += _delta;
		_fps++;
		if (_acc >= 1.0f) {
			std::cout << _fps
				<< "fps\nframetime " << ((_acc / static_cast<float>(_fps)) * 1000.f)
				<< "ms\ncurrent delta " << _delta * 1000.f << "ms\n\n";
			_acc = 0.f;
			_fps = 0;
		}
	}

	float GetDelta() const {
		return _delta;
	}
	
};
	
}
