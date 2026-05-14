#pragma once

#include "scenes/scene.hpp"
#include "objects/planet.hpp"
#include "physics/phyisics_constants.hpp"

class Physics {
    public:
        void update(Scene& scene, float deltaTime);
        
    private:
        glm::vec3 computeAcceleration(Planet* planetA, Planet* planetB);
};