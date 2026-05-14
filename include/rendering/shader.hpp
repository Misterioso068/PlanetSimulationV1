#pragma once

#include <string>
#include <glad/glad.h>

class Shader {
    public:
        ~Shader();
        bool load(const std::string& vertPath, const std::string& fragPath);
        void use();
        GLuint getProgram() const { return m_program; }
        
    private:
        GLuint m_program;
        GLuint compileShader(const std::string& path, GLenum type);
};