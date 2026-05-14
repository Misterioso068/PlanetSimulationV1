#include "scenes/scene.hpp"

void Scene::addObject(std::unique_ptr<GameObject> object) {
    m_objects.push_back(std::move(object));
}

void Scene::update(float deltaTime) {
    for (auto& object : m_objects) {
        object->update(deltaTime);
    }
}