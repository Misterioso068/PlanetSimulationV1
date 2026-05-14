#pragma once

#include <vector>
#include <memory>
#include "objects/gameobject.hpp"
#include "rendering/skybox.hpp"
#include "physics/physics_config.hpp"


class MeshManager;
class TextureManager;

class Scene {
    public:
        virtual void load(MeshManager& meshManger, TextureManager& textureManager) {}  // each scene overrides this to build itself
        virtual void unload() {}
        virtual PhysicsConfig getPhysicsConfig() const { return PhysicsConfig{}; } // default
        
        void update(float deltaTime);

        void setLightPos(glm::vec3 pos) { m_lightPos = pos; }
        glm::vec3 getLightPos() const { return m_lightPos; }

        void setSkybox(std::unique_ptr<Skybox> skybox) { m_skybox = std::move(skybox); }
        Skybox* getSkybox() const { return m_skybox.get(); }

        void addObject(std::unique_ptr<GameObject> object);
        const std::vector<std::unique_ptr<GameObject>>& getObjects() const { return m_objects; }

    protected:
        std::unique_ptr<Skybox> m_skybox;
        glm::vec3 m_lightPos = glm::vec3(0.0f);
        std::vector<std::unique_ptr<GameObject>> m_objects;
};