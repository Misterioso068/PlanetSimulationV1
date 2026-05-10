#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float aspectRatio, float near, float far)
    : m_fov(fov), m_aspectRatio(aspectRatio), m_near(near), m_far(far),
      m_position(0.0f, 0.0f, 3.0f), m_target(0.0f, 0.0f, 0.0f) {}

glm::mat4 Camera::getView() const {
    return glm::lookAt(m_position, m_target, m_up);
}

glm::mat4 Camera::getProjection() const {
    return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
}

void Camera::setPosition(glm::vec3 position) {
    m_position = position;
}

void Camera::setTarget(glm::vec3 target) {
    m_target = target;
}

void Camera::setAspectRatio(float aspectRatio) {
    m_aspectRatio = aspectRatio;
}