#include "engine.hpp"
#include "simulation_scene.hpp"

Engine::Engine() : m_window("Planet Simulation", 800, 800, SDL_WINDOW_RESIZABLE), 
                   m_camera(45.0f, 800.0f / 800.0f, 0.1f, 100.0f), m_gameState(GameState::QUIT){}

Engine::~Engine() {
       
}

void Engine::run() {
    if (!m_window.init()) return;
    if (!m_renderer.init()) return;

    m_sceneManager.addScene("simulation", std::make_unique<SimulationScene>());
    m_sceneManager.loadScene("simulation");

    float lastTime = SDL_GetTicks() / 1000.0f;

    m_gameState = GameState::RUNNING;
    while (m_gameState != GameState::QUIT) {
        float currentTime = SDL_GetTicks() / 1000.0f;
        m_deltaTime = lastTime - currentTime;
        lastTime = currentTime;

        m_window.handleInput(m_gameState);
        if (m_gameState == GameState::PAUSED) continue;
        update();
        render();
    }
}

void Engine::update() {
    if (m_window.wasResized()) 
        m_camera.setAspectRatio((float)m_window.getWidth() / (float)m_window.getHeight());
    if (m_sceneManager.getCurrentScene())
        m_sceneManager.getCurrentScene()->update(m_deltaTime);
}

void Engine::render() {
    m_window.clear();
    m_renderer.draw(*m_sceneManager.getCurrentScene(), m_camera);
    m_window.present();
}