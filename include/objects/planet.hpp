#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "objects/gameobject.hpp"
#include "renderer/mesh.hpp"
#include "renderer/texture.hpp"

class Planet : public GameObject {
    public:
        Planet();

        void update(float deltaTime) override;

        void setMass(float mass) { m_mass = mass; }
        void setVelocity(glm::vec3 velocity) { m_velocity = velocity; }
        void setAcceleration(glm::vec3 acceleration) { m_acceleration = acceleration; }
        void setAtmosphereColor(glm::vec3 color) { m_atmosphereColor = color; }

        float getMass() { return m_mass; }
        glm::vec3 getVelocity() { return m_velocity; }
        glm::vec3 getAcceleration() { return m_acceleration; }
        glm::vec3 getAtmosphereColor() const override { return m_atmosphereColor; }

    private:
        float m_mass = 0.0f;
        glm::vec3 m_velocity = glm::vec3(0.0f);
        glm::vec3 m_acceleration = glm::vec3(0.0f);
        glm::vec3 m_atmosphereColor = glm::vec3(1.0f);
};