#version 460 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iColor;
layout (location = 2) in vec2 iUv;

out vec3 vPos;
out vec4 vColor;

void main() {
    vPos = iPos;
    vColor = iColor;
    gl_Position = vec4(iPos, 1.0);
}

