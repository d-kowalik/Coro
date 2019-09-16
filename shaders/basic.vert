#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 color;
out vec2 TexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main() {
    color = aColor;
    TexCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(position, 1.0f);
}