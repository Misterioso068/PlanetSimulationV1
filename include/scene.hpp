#pragma once

#include <vector>
#include <memory>
#include "gameobject.hpp"

class MeshManager;
class TextureManager;

class Scene {
    public:
        virtual void load(MeshManager& meshManger, TextureManager& textureManager) {}  // each scene overrides this to build itself
        virtual void unload() {}
        
        void update(float deltaTime);
        
        void addObject(std::unique_ptr<GameObject> object);
        const std::vector<std::unique_ptr<GameObject>>& getObjects() const { return m_objects; }
        void setLightPos(glm::vec3 pos) { m_lightPos = pos; }
        glm::vec3 getLightPos() const { return m_lightPos; }

    protected:
        std::vector<std::unique_ptr<GameObject>> m_objects;
        glm::vec3 m_lightPos = glm::vec3(0.0f);
};