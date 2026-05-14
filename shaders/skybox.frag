#version 410 core

in vec3 v_texCoords;

uniform samplerCube u_skybox;

out vec4 fragColor;

void main() {
    fragColor = texture(u_skybox, v_texCoords);
}