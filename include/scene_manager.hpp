#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "scene.hpp"

class SceneManager {
    public:
        void addScene(const std::string& name, std::unique_ptr<Scene> scene);
        void loadScene(const std::string& name, MeshManager& meshManager, TextureManager& textureManager);        
        Scene* getCurrentScene() const {return m_currentScene;}
                
    private:
        std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
        Scene* m_currentScene = nullptr;
};