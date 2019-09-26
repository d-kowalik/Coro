#pragma once 

namespace Coro {

class Pixel
{
private:
	
	glm::mat4 _model;
	glm::vec3 _translate{};
	glm::vec3 _scale{};

	glm::vec3 _color{};

	std::vector<unsigned> _indices{
		0, 1, 3,
		1, 2, 3
	};


public:
	Pixel(float w, float h, float x, float y, glm::vec3 const& color)
		: _color(color) {
		_model = glm::mat4(1.0f);
		_translate = glm::vec3{ x, y, .0f };
		_scale = glm::vec3{ w, h, 1.0f };
		_model = glm::translate(_model, _translate);
		_model = glm::scale(_model, _scale);
	}

	const glm::mat4& GetModel() const { return _model; }
	const glm::vec3& GetColor() const { return _color; }
	
};

}