#pragma once

#include "scenes/scene.hpp"
#include "managers/mesh_manager.hpp"
#include "managers/texture_manager.hpp"

class SimulationScene : public Scene {
    public:
        void load(MeshManager& meshManger, TextureManager& textureManager) override;
        void unload() override;
};