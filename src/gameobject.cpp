#include "gameobject.hpp"
#include <glm/gtc/matrix_transform.hpp>

void GameObject::translate(glm::vec3 position) {
    m_transform = glm::translate(m_transform, position);
}

void GameObject::rotate(float angle, glm::vec3 axis) {
    m_transform = glm::rotate(m_transform, glm::radians(angle), axis);
}

void GameObject::scale(float uniformScale) {
    m_transform = glm::scale(m_transform, glm::vec3(uniformScale));
}

void GameObject::scale(glm::vec3 scale) {
    m_transform = glm::scale(m_transform, scale);
}