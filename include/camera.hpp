#pragma once

#include <glm/glm.hpp>

class Camera {
    public:
        Camera(float fov, float aspectRatio, float near, float far);

        void update();
        void moveForward(float deltaTime);
        void moveBack(float deltaTime);
        void moveRight(float deltaTime);
        void moveLeft(float deltaTime);
        void moveUp(float deltaTime);
        void moveDown(float deltaTime);
        void rotate(float xoffset, float yoffset);

        
        glm::mat4 getView() const;
        glm::mat4 getProjection() const;

        glm::vec3 getPosition() const { return m_position; }
    
        void setPosition(glm::vec3 position);
        void setFront(glm::vec3 front);
        void setAspectRatio(float aspectRatio);

    private:
        float m_fov;
        float m_aspectRatio;
        float m_near;
        float m_far;

        glm::vec3 m_worldUp;
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_right;
        glm::vec3 m_cameraUp;

        float m_yaw;
        float m_pitch;
        float m_speed;
        float m_sens;
};