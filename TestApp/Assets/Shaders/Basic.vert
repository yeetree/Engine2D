#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 2) in vec4 color;

out vec4 outColor;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main() {
    outColor = color;
    gl_Position = u_ViewProjection * u_Transform * vec4(pos, 0.0, 1.0);
}