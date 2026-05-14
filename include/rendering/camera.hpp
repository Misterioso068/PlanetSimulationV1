#pragma once

#include <glm/glm.hpp>
#include "rendering/camera_config.hpp"

class Camera {
    public:
        Camera(float aspectRatio, CameraConfig config = CameraConfig{});
        void setConfig(const CameraConfig& config);

        void update();
        void moveForward(float deltaTime);
        void moveBack(float deltaTime);
        void moveRight(float deltaTime);
        void moveLeft(float deltaTime);
        void moveUp(float deltaTime);
        void moveDown(float deltaTime);
        void rotate(float xoffset, float yoffset);

        float getSpeed() const { return m_config.speed; }
        float getSensitivity() const { return m_config.sensitivity; }
        float getFov() const { return m_config.fov; }
        void setSpeed(float speed) { m_config.speed = speed; }
        void setSensitivity(float sensitivity) { m_config.sensitivity = sensitivity; }
        void setFov(float fov) { m_config.fov = fov; }

        
        glm::mat4 getView() const;
        glm::mat4 getProjection() const;

        glm::vec3 getPosition() const { return m_position; }
    
        void setPosition(glm::vec3 position) { m_position = position; }
        void setFront(glm::vec3 front) { m_front = front; }
        void setAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; }

    private:
        CameraConfig m_config;

        float m_aspectRatio;
        glm::vec3 m_worldUp;
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_right;
        glm::vec3 m_cameraUp;
        float m_yaw;
        float m_pitch;
};