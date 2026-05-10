#pragma once

#include <glm/glm.hpp>
#include "mesh.hpp"

class GameObject {
    public:
        virtual ~GameObject() = default;
        virtual void update(float deltaTime) {};

        void translate(glm::vec3 position);
        void rotate(float angle, glm::vec3 axis);
        void scale(glm::vec3 scale);

        glm::mat4 getTransform() const { return m_transform; }
        const Mesh& getMesh() const { return m_mesh; }

    protected:
        Mesh m_mesh;
        glm::mat4 m_transform = glm::mat4(1.0f);
};  