#include "physics/physics.hpp"

void Physics::update(Scene& scene, float deltaTime) {
    auto& objects = scene.getObjects();

    // store accelerations from previous frame
    for (auto& a : objects) {
        Planet* planetA = dynamic_cast<Planet*>(a.get());
        if (!planetA) continue;

        glm::vec3 acceleration(0.0f);
        for (auto& b : objects) {
            Planet* planetB = dynamic_cast<Planet*>(b.get());
            if (!planetB || planetA == planetB) continue;
            acceleration += computeAcceleration(planetA, planetB);
        }

        // velocity verlet position update
        glm::vec3 newPos = planetA->getPosition() 
                         + planetA->getVelocity() * deltaTime 
                         + 0.5f * acceleration * deltaTime * deltaTime;
        planetA->setPosition(newPos);
        planetA->setAcceleration(acceleration); // store for velocity update
    }

    // second pass — update velocities using average of old and new acceleration
    for (auto& a : objects) {
        Planet* planetA = dynamic_cast<Planet*>(a.get());
        if (!planetA) continue;

        glm::vec3 newAcceleration(0.0f);
        for (auto& b : objects) {
            Planet* planetB = dynamic_cast<Planet*>(b.get());
            if (!planetB || planetA == planetB) continue;
            newAcceleration += computeAcceleration(planetA, planetB);
        }

        // average old and new acceleration for velocity update
        glm::vec3 newVelocity = planetA->getVelocity() 
                              + 0.5f * (planetA->getAcceleration() + newAcceleration) * deltaTime;
        planetA->setVelocity(newVelocity);
    }
}

glm::vec3 Physics::computeAcceleration(Planet* planetA, Planet* planetB) {
    glm::vec3 dir = planetB->getPosition() - planetA->getPosition();
    float dist = glm::length(dir);
    float forceMag = m_config.G * planetB->getMass() / (dist * dist + m_config.softening * m_config.softening);
    return glm::normalize(dir) * forceMag;
}