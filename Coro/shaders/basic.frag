#version 330 core

in vec3 color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float mixPercent;

void main() {
    FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), mixPercent) * vec4(color, 1.0f);
}