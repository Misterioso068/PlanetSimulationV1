#include "objects/planet.hpp"

Planet::Planet() {}

Planet::~Planet() {}

void Planet::update(float deltaTime) {
    rotate(deltaTime * 10.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}