#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "gameobject.hpp"
#include "mesh.hpp"
#include "texture.hpp"

class Planet : public GameObject {
    public:
        Planet();
        void update(float deltaTime) override;
        void setMass(float mass);
        void setVelocity(glm::vec3 velocity);

    private:
        float m_mass;
        glm::vec3 m_velocity;
};