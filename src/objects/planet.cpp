#include "objects/planet.hpp"

Planet::Planet() {}

void Planet::update(float deltaTime) {
    rotate(deltaTime * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}