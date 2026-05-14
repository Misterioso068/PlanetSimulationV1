#version 410 core
layout (location = 0) in vec3 a_position;

uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 v_texCoords;

void main() {
    v_texCoords = a_position; // position IS the texture coordinate for cubemaps
    vec4 pos = u_projection * u_view * vec4(a_position, 1.0);
    gl_Position = pos.xyww; // trick to always render at max depth
}