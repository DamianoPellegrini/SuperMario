#version 460 core

in vec3 vPos;
in vec3 vColor;

out vec4 color;

void main() {
    color = vec4(vColor, 1.0);
}
