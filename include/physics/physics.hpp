#pragma once

#include "scenes/scene.hpp"
#include "objects/planet.hpp"
#include "physics/physics_config.hpp"

class Physics {
    public:
        void update(Scene& scene, float deltaTime);
        void setConfig(const PhysicsConfig& config) { m_config = config; }
        
    private:
        PhysicsConfig m_config;
        glm::vec3 computeAcceleration(Planet* planetA, Planet* planetB);
};