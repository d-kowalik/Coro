#include "PixelRenderer.hpp"

namespace Coro {

PixelRenderer::PixelRenderer(int w, int h) {
	_program = Coro::MakeRef<Coro::ShaderProgram>(std::vector<Coro::Ref<Coro::Shader>>{
		Coro::Shader::Make("shaders/flatColor.vert", GL_VERTEX_SHADER),
			Coro::Shader::Make("shaders/flatColor.frag", GL_FRAGMENT_SHADER)
	});
	_view = glm::lookAt(glm::vec3{ 0.f, 0.f, 3.f },
		{ 0.f, 0.f, 0.f }, { 0.f, 1.f, 0.f });
	_projection = glm::ortho(0.f, static_cast<float>(w),
		0.f, static_cast<float>(h), 0.1f, 100.f);
	_program->Use();
	_program->SetMat4("view", _view);
	_program->SetMat4("projection", _projection);

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);
	glGenBuffers(1, &_ivbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices),
		_indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, _ivbo);
	glBufferData(GL_ARRAY_BUFFER, SIZE * sizeof(InstanceData), nullptr, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData),
		reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData),
		reinterpret_cast<void*>(sizeof(InstanceData::color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData),
		reinterpret_cast<void*>(sizeof(InstanceData::color) + sizeof(glm::vec4)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData),
		reinterpret_cast<void*>(sizeof(InstanceData::color) + (2 * sizeof(glm::vec4))));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData),
		reinterpret_cast<void*>(sizeof(InstanceData::color) + (3 * sizeof(glm::vec4))));
	glEnableVertexAttribArray(5);

	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

PixelRenderer::~PixelRenderer() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
}

void PixelRenderer::Add(const Coro::Ref<Pixel>& pixel) {
	glBufferSubData(GL_ARRAY_BUFFER, _pixelCount * sizeof(InstanceData),
		sizeof(InstanceData::color), &pixel->GetColor()[0]);
	glBufferSubData(GL_ARRAY_BUFFER, (_pixelCount * sizeof(InstanceData)) + sizeof(InstanceData::color),
		sizeof(InstanceData::model), glm::value_ptr(pixel->GetModel()));
	_pixelCount++;
}

void PixelRenderer::Draw() {
	glBindVertexArray(_vao);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, _pixelCount);
	glBindVertexArray(0);
	_pixelCount = 0;
}
	
}