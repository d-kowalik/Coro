#version 330 core

in vec3 color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixPercent;

void main() {
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixPercent) * vec4(color, 1.0f);
}