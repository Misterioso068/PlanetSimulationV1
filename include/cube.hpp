#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "mesh.hpp"
#include "gameobject.hpp"

class Cube : public GameObject {
    public:
        Cube();
        void update(float deltaTime) override;

    private:
        float m_mass;
        glm::vec3 velocity;
};