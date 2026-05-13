#pragma once

#include "window.hpp"
#include "renderer.hpp"
#include "scene_manager.hpp"
#include "camera.hpp"
#include "mesh_manager.hpp"
#include "texture_manager.hpp"
#include "gamestates.hpp"

class Engine {
    public:
        Engine();
        ~Engine();

        void run();

    private:
        Window m_window;
        Renderer m_renderer;
        SceneManager m_sceneManager;
        Camera m_camera;
        MeshManager m_meshManager;
        TextureManager m_textureManager;
        GameState m_gameState;
        float m_deltaTime;

        void update();
        void render();
};  