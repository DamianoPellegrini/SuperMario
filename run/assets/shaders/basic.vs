#version 460 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iColor;
out vec3 position;
out vec3 vColor;

void main() {
    position = iPos;
    vColor = iColor;
    gl_Position = vec4(iPos, 1.0);
}
