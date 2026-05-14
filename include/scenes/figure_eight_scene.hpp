#pragma once

#include "scenes/scene.hpp"
#include "managers/mesh_manager.hpp"
#include "managers/texture_manager.hpp"

class FigureEightScene : public Scene {
    public:
        void load(MeshManager& meshManager, TextureManager& textureManager) override;
        void unload() override;
        PhysicsConfig getPhysicsConfig() const override { return PhysicsConfig{20.0f, 10.0f, 0.0001f, 10}; }
};