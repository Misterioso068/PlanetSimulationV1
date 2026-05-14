#pragma once

#include "core/window.hpp"
#include "core/gamestates.hpp"
#include "rendering/renderer.hpp"
#include "rendering/camera.hpp"
#include "managers/scene_manager.hpp"
#include "managers/mesh_manager.hpp"
#include "managers/texture_manager.hpp"
#include "physics/physics.hpp"
#include "physics/phyisics_constants.hpp"

class Engine {
    public:
        Engine();
        ~Engine();

        void run();

    private:
        Window m_window;
        GameState m_gameState;
        Renderer m_renderer;
        Camera m_camera;
        SceneManager m_sceneManager;
        MeshManager m_meshManager;
        TextureManager m_textureManager;
        Physics m_physics;
        float m_deltaTime;

        void update();
        void render();
        void loadScene(const std::string& name);
};  