#include "rendering/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float aspectRatio, CameraConfig config) 
    : m_aspectRatio(aspectRatio), m_config(config),
      m_worldUp(0.0f, 1.0f, 0.0f),
      m_position(0.0f, 10.0f, 20.0f),
      m_front(0.0f, 0.0f, -1.0f),
      m_yaw(-90.0f),
      m_pitch(0.0f)
{
    update();
}

void Camera::setConfig(const CameraConfig& config) {
    m_config = config;
    update();
}

void Camera::update() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_cameraUp = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::moveForward(float deltaTime) {
    m_position += m_front * m_config.speed * deltaTime;
}

void Camera::moveBack(float deltaTime) {
    m_position -= m_front * m_config.speed * deltaTime;
}

void Camera::moveLeft(float deltaTime) {
    m_position -= m_right * m_config.speed * deltaTime;
}

void Camera::moveRight(float deltaTime) {
    m_position += m_right * m_config.speed * deltaTime;
}

void Camera::moveUp(float deltaTime) {
    m_position += m_cameraUp * m_config.speed * deltaTime;
}

void Camera::moveDown(float deltaTime) {
    m_position -= m_cameraUp * m_config.speed * deltaTime;
}

void Camera::rotate(float xoffset, float yoffset) {
    // Apply sensitivity
    xoffset *= m_config.sensitivity;
    yoffset *= m_config.sensitivity;

    // Update yaw and pitch
    m_yaw += xoffset;
    m_pitch -= yoffset; // Reversed Y-axis for natural camera feel

    // Clamp pitch to avoid flipping
    if (m_pitch > 89.0f) m_pitch = 89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;
}

glm::mat4 Camera::getView() const {
        return glm::lookAt(m_position, m_position + m_front, m_cameraUp);
}

glm::mat4 Camera::getProjection() const {
        return glm::perspective(glm::radians(m_config.fov), m_aspectRatio, m_config.near, m_config.far);
}