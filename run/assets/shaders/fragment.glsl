#version 460 core

in vec3 position;
out vec4 color;

void main() {
    color = vec4(position + 0.5, 1.0);
}