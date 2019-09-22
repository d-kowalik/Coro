#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in mat4 aModel;

out vec3 Color;

uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * aModel * vec4(aPos, 1.0f);
	Color = aColor;
}