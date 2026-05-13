#pragma once

#include "scene.hpp"
#include "mesh_manager.hpp"
#include "texture_manager.hpp"

class SimulationScene : public Scene {
    public:
        void load(MeshManager& meshManger, TextureManager& textureManager) override;
        void unload() override;
};