#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>

struct ObjData {
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    std::string mtlFile;
    std::string materialName;
};

class ObjLoader {
    public:
        static ObjData load(const std::string& filePath);
};