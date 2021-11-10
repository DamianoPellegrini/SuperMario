#version 460 core

layout (location = 0) in vec3 aPos;
out vec3 position;

void main() {
    position = aPos;
    gl_Position = vec4(position, 1.0);
}