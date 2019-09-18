#include "Camera.hpp"

#include <iostream>

namespace Coro {

Camera::Camera() { UpdateVectors(); }

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch,
               float speed)
    : _pos(position), _up(up), _yaw(yaw), _pitch(pitch), _speed(speed) {
    UpdateVectors();
}

void Camera::ProcessMouseMove(double xoffset, double yoffset) {
    xoffset *= _sensitivity;
    yoffset *= _sensitivity;

    _yaw += xoffset;
    _pitch += yoffset;

    if (_pitch > 89.0f) _pitch = 89.0f;
    if (_pitch < -89.0f) _pitch = -89.0f;

    UpdateVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(_pos, _pos + _front, _up);
}

void Camera::UpdateVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    _right = glm::normalize(glm::cross(
        _front, _worldUp));  // Normalize the vectors, because their length gets
                             // closer to 0 the more you look up or down which
                             // results in slower movement.
    _up = glm::normalize(glm::cross(_right, _front));
}

}  // namespace Coro
