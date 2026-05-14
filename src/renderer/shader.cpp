#include "renderer/shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

// reads file into a string
static std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Failed to open shader file: " << path << "\n";
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compileShader(const std::string& path, GLenum type) {
    std::string source = readFile(path);
    if (source.empty()) return 0;

    const char* src = source.c_str();
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // check for compile errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "[ERROR] Shader compilation failed: " << path << "\n" << log << "\n";
        return 0;
    }

    return shader;
}

bool Shader::load(const std::string& vertPath, const std::string& fragPath) {
    GLuint vert = compileShader(vertPath, GL_VERTEX_SHADER);
    if (!vert) return false;

    GLuint frag = compileShader(fragPath, GL_FRAGMENT_SHADER);
    if (!frag) return false;

    // link into a program
    m_program = glCreateProgram();
    glAttachShader(m_program, vert);
    glAttachShader(m_program, frag);
    glLinkProgram(m_program);

    // check for link errors
    int success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(m_program, 512, nullptr, log);
        std::cerr << "[ERROR] Shader linking failed:\n" << log << "\n";
        return false;
    }

    // shaders are linked into program, no longer need them
    glDeleteShader(vert);
    glDeleteShader(frag);

    return true;
}

void Shader::use() {
    glUseProgram(m_program);
}

Shader::~Shader() {
    glDeleteProgram(m_program);
}