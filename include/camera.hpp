#pragma once

#include <glm/glm.hpp>

class Camera {
    public:
        Camera(float fov, float aspectRatio, float near, float far);
        
        glm::mat4 getView() const;
        glm::mat4 getProjection() const;
        
        void setPosition(glm::vec3 position);
        void setTarget(glm::vec3 target);
        void setAspectRatio(float aspectRatio);

    private:
        glm::vec3 m_position;
        glm::vec3 m_target;
        glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
        float m_fov;
        float m_aspectRatio;
        float m_near;
        float m_far;
};