#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float xOffset;

void main() {
    vec3 temp = vec3(-aPos.x + xOffset, -aPos.y + xOffset, -aPos.z);
    gl_Position = vec4(temp, 1.0);
    ourColor = temp;
}
