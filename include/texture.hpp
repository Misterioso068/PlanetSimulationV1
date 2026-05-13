#pragma once

#include <glad/glad.h>
#include <string>

class Texture {
    public:
        ~Texture();
        bool load(const std::string& path);
        void bind(GLuint slot) const;

    private:
        GLuint m_textureID;
};