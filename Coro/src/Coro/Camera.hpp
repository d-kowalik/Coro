#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace Coro {

class Window;
class Camera {
	glm::vec3 _pos = { 0.f, 0.f, 3.f };
	glm::vec3 _up = { 0.f, 1.f, 0.f };
	glm::vec3 _front = { 0.f, 0.f, -1.f };
	glm::vec3 _right;
	glm::vec3 _worldUp = _up;
	
    float _yaw = -90.f;  // default
    float _pitch = 0.f;  // default
    float _speed = 2.5f;
    float _sensitivity = .1f;
    float _fov = 45.f;

   public:
    enum class CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

    Camera();
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch,
           float speed);

    void ProcessMouseMove(double xoffset, double yoffset);
    void ProcessInput(CameraMovement direction, float delta);
    void ProcessMouseScroll(float yoffset);

    glm::mat4 GetViewMatrix() const;
	const glm::vec3& GetPosition() const { return _pos; }

   private:
    void UpdateVectors();
};

}  // namespace Coro