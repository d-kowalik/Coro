#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Core.hpp"
#include "ShaderProgram.hpp"
#include "Pixel.hpp"

namespace Coro {

class PixelRenderer
{
private:
	static const int SIZE = 60000;

	Coro::Ref<Coro::ShaderProgram> _program;
	unsigned _vao, _vbo, _ebo, _ivbo;
	unsigned _pixelCount = 0;

	glm::mat4 _view;
	glm::mat4 _projection;
	unsigned _indices[6]{
		0, 1, 3,
		1, 2, 3
	};
	glm::vec3 _vertices[4] = {
		{0.f, 1.f, 1.f},
		{1.f, 1.f, 1.f},
		{1.f, 0.f, 1.f},
		{0.f, 0.f, 1.f}
	};

	struct InstanceData
	{
		glm::vec3 color;
		glm::mat4 model;
	};

public:
	PixelRenderer(int w, int h);
	~PixelRenderer();

	void Begin() const {
		glBindBuffer(GL_ARRAY_BUFFER, _ivbo);
		_program->Use();
	}

	void End() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Add(const Coro::Ref<Pixel>& pixel);

	void Draw();
};

}