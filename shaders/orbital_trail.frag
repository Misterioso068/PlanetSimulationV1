#version 410 core

uniform vec3 u_trailColor;
uniform float u_alpha;

out vec4 fragColor;

void main() {
    fragColor = vec4(u_trailColor, u_alpha);
}