#include "scene_manager.hpp"

void SceneManager::addScene(const std::string& name, std::unique_ptr<Scene> scene) {
    m_scenes[name] = std::move(scene);
}

void SceneManager::loadScene(const std::string& name, MeshManager& meshManager, TextureManager& textureManager) {
    if (m_currentScene) m_currentScene->unload();
    auto it = m_scenes.find(name);
    if (it != m_scenes.end()) {
        m_currentScene = it->second.get();
        m_currentScene->load(meshManager, textureManager);
    }
}