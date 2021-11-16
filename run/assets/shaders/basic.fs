#version 460 core

in vec3 position;
in vec3 vColor;

out vec4 color;

void main() {
    // color = vec4(position + 0.5, 1.0);
    color = vec4(vColor, 1.0);
}
