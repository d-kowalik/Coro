#include "Camera.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Window.hpp"
#include "Core.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ostream>
#include <iostream>
#include <random>

constexpr int W = 1280;
constexpr int H = 720;
constexpr char TITLE[] = "Coro";
Coro::Window window{ W, H, TITLE };
Coro::Camera camera;

float lastX = W / 2;
float lastY = H / 2;

void MoveCamera(double xpos, double ypos) {
	static bool firstMouse = false;
	if (!window.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
		firstMouse = true;
		return;
	}
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	const float xoffset = xpos - lastX;
	const float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMove(xoffset, yoffset);
};

void processInput(const Coro::Window& window, float delta) {
	const float cameraSpeed = 2.5f * delta;  // adjust accordingly
	if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
		window.Close();
	}
	else if (window.IsKeyPressed(GLFW_KEY_1)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (window.IsKeyPressed(GLFW_KEY_2)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (window.IsKeyPressed(GLFW_KEY_3)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}

	if (window.IsKeyPressed(GLFW_KEY_W)) {
		camera.ProcessInput(Coro::Camera::CameraMovement::FORWARD, delta);
	}
	if (window.IsKeyPressed(GLFW_KEY_S)) {
		camera.ProcessInput(Coro::Camera::CameraMovement::BACKWARD, delta);
	}
	if (window.IsKeyPressed(GLFW_KEY_A)) {
		camera.ProcessInput(Coro::Camera::CameraMovement::LEFT, delta);
	}
	if (window.IsKeyPressed(GLFW_KEY_D)) {
		camera.ProcessInput(Coro::Camera::CameraMovement::RIGHT, delta);
	}
	if (window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
		camera.ProcessInput(Coro::Camera::CameraMovement::DOWN, delta);
	}
	if (window.IsKeyPressed(GLFW_KEY_SPACE)) {
		camera.ProcessInput(Coro::Camera::CameraMovement::UP, delta);
	}
}

class Pixel
{
private:
	glm::vec3 _translate{};
	glm::vec3 _scale{};
	std::vector<glm::vec3> _positions{
		{ -.5f, .5f, 1.f },
		{.5f, .5f, 1.f},
		{ .5f, -.5f, 1.f },
		{ -.5f, -.5f, 1.f }
	};

public:
	struct Vertex {
		glm::vec3 position;
	};
	
	glm::vec3 _color{};
	glm::mat4 _model;
	std::vector<Vertex> _vertices{
		{{ -.5f, .5f, 1.f }},
		{{.5f, .5f, 1.f}},
		{{ .5f, -.5f, 1.f }},
		{{ -.5f, -.5f, 1.f }}
	};
	
	std::vector<unsigned> _indices {
		0, 1, 3,
		1, 2, 3
	};


public:
	Pixel(float w, float h, float x, float y, glm::vec3 const& color) {
		_model = glm::mat4(1.0f);
		_translate = glm::vec3{ x, y, .0f };
		_scale = glm::vec3{ w, h, 1.0f };
		_model = glm::translate(_model, _translate);
		_model = glm::scale(_model, _scale);
		_color = color;
	
	}
};

class PixelRenderer
{
	unsigned _vao, _vbo, _ebo, _ivbo;
	Coro::Ref<Coro::ShaderProgram> _program;
private:
	static const int SIZE = 3800;

	glm::mat4 _view;
	glm::mat4 _projection;
	unsigned _indices[6*SIZE];

	struct InstanceData
	{
		glm::vec3 color;
		glm::mat4 model;
	};
public:
	PixelRenderer() {
		_program = Coro::MakeRef<Coro::ShaderProgram>(std::vector<Coro::Ref<Coro::Shader>>{
			Coro::Shader::Make("shaders/flatColor.vert", GL_VERTEX_SHADER),
				Coro::Shader::Make("shaders/flatColor.frag", GL_FRAGMENT_SHADER)
		});
		_view = glm::lookAt(glm::vec3{ 0.f, 0.f, 3.f },
			{ 0.f, 0.f, 0.f }, { 0.f, 1.f, 0.f });
		_projection = glm::ortho(0.f, static_cast<float>(W), 
				0.f, static_cast<float>(H), 0.1f, 100.f);
		_program->Use();
		_program->SetMat4("view", _view);
		_program->SetMat4("projection", _projection);

		int j = 0;
		for (int i = 0; i < 6*SIZE; i += 6) {
			_indices[i] = j;
			_indices[i+1] = j+1;
			_indices[i+2] = j+3;
			_indices[i+3] = j+1;
			_indices[i+4] = j+2;
			_indices[i+5] = j+3;
			j += 4;
		}
		
		
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
		glGenBuffers(1, &_ebo);
		glGenBuffers(1, &_ivbo);
		
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, SIZE * 4 * sizeof(Pixel::Vertex), NULL, GL_DYNAMIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, SIZE * 6 * sizeof(unsigned),
			_indices, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Pixel::Vertex), static_cast<void*>(nullptr));
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, _ivbo);
		glBufferData(GL_ARRAY_BUFFER, SIZE * sizeof(InstanceData), NULL, GL_DYNAMIC_DRAW);

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
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	~PixelRenderer() {
		glDeleteVertexArrays(1, &_vao);
		glDeleteBuffers(1, &_vbo);
		glDeleteBuffers(1, &_ebo);
	}

	void Add(const Coro::Ref<Pixel>& pixel) {
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 4 * _pixels.size() * sizeof(Pixel::Vertex),
			4 * sizeof(Pixel::Vertex), &pixel->_vertices[0]);
		glBindBuffer(GL_ARRAY_BUFFER, _ivbo);
		glBufferSubData(GL_ARRAY_BUFFER, _pixels.size() * sizeof(InstanceData),
			sizeof(InstanceData::color), &pixel->_color[0]);
		glBufferSubData(GL_ARRAY_BUFFER, (_pixels.size() * sizeof(InstanceData)) + sizeof(InstanceData::color),
			sizeof(InstanceData::model), glm::value_ptr(pixel->_model));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		_pixels.push_back(pixel);
	}

	void Draw() {
		_program->Use();
		glBindVertexArray(_vao);
		glDrawElementsInstanced(GL_TRIANGLES, 6 * _pixels.size(), GL_UNSIGNED_INT, NULL, _pixels.size());
		glBindVertexArray(0);
	}
};

int main() {

	PixelRenderer renderer;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.f, 1.f);
	const float pixelSize = 32.f;
	for (int x = 0; x <= (float)W/pixelSize; x++) {
		for (int y = 0; y <= (float)H/pixelSize; y++) {
			std::cout << "Adding pixel at position (" << pixelSize * x << ", " << pixelSize * y << ")\n";
			renderer.Add(Coro::MakeRef<Pixel>(pixelSize, pixelSize, x * pixelSize,
				y * pixelSize, glm::vec3{ dist(gen), dist(gen), dist(gen), }));
		}
	}

	float delta = 0.f;
	float last = 0.f;
	float acc = .0f;
	int fps = 0;
	while (!window.ShouldClose()) {
		float current = glfwGetTime();
		delta = current - last;
		last = current;
		acc += delta;
		fps += 1;
		if (acc >= 1.0f) {
			std::cout << fps << "fps\ncurrent "
				<< current << "s\naverage delta " << ((acc/static_cast<float>(fps)) * 1000.f)
				<< "ms\ncurrent delta " << delta * 1000.f << "ms\n\n";
			acc = .0f;
			fps = 0;
		}

		std::cout << delta << std::endl;
		
		processInput(window, delta);
		window.Clear();

		renderer.Draw();
		for (const auto& pixel : renderer._pixels) {
			pixel->_color = { dist(gen), dist(gen), dist(gen) };
		}
		renderer.Update();
		
		window.Update();
	}

	return 0;
}