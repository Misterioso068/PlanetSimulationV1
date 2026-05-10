#pragma once

#include <vector>
#include <memory>
#include "gameobject.hpp"

class Scene {
    public:
        virtual void load() {}  // each scene overrides this to build itself
        virtual void unload() {}
        
        void addObject(std::unique_ptr<GameObject> object);
        const std::vector<std::unique_ptr<GameObject>>& getObjects() const { return m_objects; }
        void update(float deltaTime);

    protected:
        std::vector<std::unique_ptr<GameObject>> m_objects;
};