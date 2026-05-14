#include "scenes/scene.hpp"
#include "managers/mesh_manager.hpp"
#include "managers/texture_manager.hpp"

class BinaryStarScene : public Scene {
    public:
        void load(MeshManager& meshManager, TextureManager& textureManager) override;
        void unload() override;
        PhysicsConfig getPhysicsConfig() const override { return PhysicsConfig{1.0f, 1.0f, 1.0f, 50}; } // different G and timeScale
};