#pragma once

#include <vector>
#include <glad/glad.h>

class Mesh {
    public:
        ~Mesh();

        bool load(const std::string& filePath);
        GLuint getVAO() const {return m_VAO;}
        GLint getIndexCount() const {return m_indexCount;}

    private:
        GLuint m_VAO, m_VBO, m_EBO;
        GLint m_indexCount;
};