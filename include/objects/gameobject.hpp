#pragma once

#include <glm/glm.hpp>
#include "rendering/mesh.hpp"
#include "rendering/texture.hpp"

class GameObject {
    public:
        virtual ~GameObject() = default;
        virtual void update(float deltaTime) {};
        virtual glm::vec3 getAtmosphereColor() const { return glm::vec3(0.0f); } // default no atmosphere

        void translate(glm::vec3 position);
        void rotate(float angle, glm::vec3 axis);
        void scale(float uniformScale);
        void scale(glm::vec3 scale); 

        void setMesh(Mesh* mesh) { m_mesh = mesh; }
        void setTexture(Texture* texture) { m_texture = texture; }
        void setColor(glm::vec3 color) { m_color = color; }
        void setEmissive(bool emissive) { m_emissive = emissive; }
        void setPosition(glm::vec3 position) { m_transform[3] = glm::vec4(position, 1.0f); }

        const Mesh* getMesh() const { return m_mesh; }
        const Texture* getTexture() const { return m_texture; }
        glm::vec3 getColor() const { return m_color; }
        glm::mat4 getTransform() const { return m_transform; }
        glm::vec3 getPosition() const { return glm::vec3(m_transform[3]); }

        bool isEmissive() const { return m_emissive; }

    protected:
        Mesh *m_mesh = nullptr;
        Texture *m_texture = nullptr;
        glm::vec3 m_color = glm::vec3(1.0f); // For none textured objects
        glm::mat4 m_transform = glm::mat4(1.0f);
        bool m_emissive = false;
};  