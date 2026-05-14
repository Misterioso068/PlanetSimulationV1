#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "managers/mesh_manager.hpp"

class Skybox {
    public:
        bool load(MeshManager& meshManager, const std::vector<std::string>& faces);
        const Mesh* getMesh() const { return m_mesh; }
        GLuint getCubemap() const { return m_cubemapID; }
        ~Skybox();

    private:
        Mesh* m_mesh = nullptr;
        GLuint m_cubemapID;
};