#include "rendering/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float aspectRatio, float near, float far)
    : m_fov(fov), m_aspectRatio(aspectRatio), m_near(near), m_far(far),
      m_worldUp(0.0f, 1.0f, 0.0f),
      m_position(0.0f, 10.0f, 20.0f),
      m_front(0.0f, 0.0f, -1.0f),
      m_yaw(-90.0f),
      m_pitch(0.0f),
      m_speed(20.0f),
      m_sens(0.5f)
{
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
    m_position += m_front * m_speed * deltaTime;
}

void Camera::moveBack(float deltaTime) {
    m_position -= m_front * m_speed * deltaTime;
}

void Camera::moveLeft(float deltaTime) {
    m_position -= m_right * m_speed * deltaTime;
}

void Camera::moveRight(float deltaTime) {
    m_position += m_right * m_speed * deltaTime;
}

void Camera::moveUp(float deltaTime) {
    m_position += m_cameraUp * m_speed * deltaTime;
}

void Camera::moveDown(float deltaTime) {
    m_position -= m_cameraUp * m_speed * deltaTime;
}

void Camera::rotate(float xoffset, float yoffset) {
    // Apply sensitivity
    xoffset *= m_sens;
    yoffset *= m_sens;

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
    return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
}

void Camera::setPosition(glm::vec3 position) {
    m_position = position;
}

void Camera::setFront(glm::vec3 front) {
    m_front = front;
}

void Camera::setAspectRatio(float aspectRatio) {
    m_aspectRatio = aspectRatio;
}