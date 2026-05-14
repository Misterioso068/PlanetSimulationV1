#include <iostream>
#include <stb_image.h>
#include "renderer/skybox.hpp"

bool Skybox::load(MeshManager& meshManager, const std::vector<std::string>& faces) {
    m_mesh = meshManager.load("assets/objects/cube.obj");

    glGenTextures(1, &m_cubemapID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapID);

    // flip images vertically for correct orientation
    stbi_set_flip_vertically_on_load(false);

    for (int i = 0; i < faces.size(); i++) {
        int width, height, channels;
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
        if (!data) {
            std::cerr << "[ERROR] Failed to load skybox face: " << faces[i] << "\n";
            std::cerr << "[ERROR] Reason: " << stbi_failure_reason() << "\n";
            return false;
        }

        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, // right, left, top, bottom, front, back
            0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data
        );
        stbi_image_free(data);
    }

    // cubemap filtering and wrapping
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return true;
}

Skybox::~Skybox() {
    glDeleteTextures(1, &m_cubemapID);
}