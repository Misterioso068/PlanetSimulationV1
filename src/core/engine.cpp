#include "core/engine.hpp"
#include "scenes/simulation_scene.hpp"

Engine::Engine() : m_window("Planet Simulation", 800, 800, SDL_WINDOW_RESIZABLE), 
                   m_camera(90.0f, 800.0f / 800.0f, 0.1f, 1000.0f), m_gameState(GameState::QUIT){}

Engine::~Engine() {
       
}

void Engine::run() {
    if (!m_window.init()) return;
    if (!m_renderer.init()) return;

    m_sceneManager.addScene("simulation", std::make_unique<SimulationScene>());
    m_sceneManager.loadScene("simulation", m_meshManager, m_textureManager);

    float lastTime = SDL_GetTicks() / 1000.0f;

    m_gameState = GameState::RUNNING;
    while (m_gameState != GameState::QUIT) {
        float currentTime = SDL_GetTicks() / 1000.0f;
        m_deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        m_window.handleInput(m_gameState);
        if (m_gameState == GameState::PAUSED) continue;
        update();
        render();
    }
}

void Engine::update() {
    int numKeys;
    const bool* keys = m_window.getKeyboardState(&numKeys);

    // time scale control
    if (keys[SDL_SCANCODE_EQUALS]) m_timeScale += 5.0f * m_deltaTime;
    if (keys[SDL_SCANCODE_MINUS]) m_timeScale -= 5.0f * m_deltaTime;
    m_timeScale = glm::max(1.0f, m_timeScale);

    // physics
    float physicsStep = (m_deltaTime * m_timeScale) / PhysicsConstants::PHYSICS_STEPS;
    for (int i = 0; i < PhysicsConstants::PHYSICS_STEPS; i++) {
        m_physics.update(*m_sceneManager.getCurrentScene(), physicsStep);
    }

    // camera
    glm::vec2 mouseDelta = m_window.getMouseDelta();
    m_camera.rotate(mouseDelta.x, mouseDelta.y);
    m_camera.update();

    if (keys[SDL_SCANCODE_W]) m_camera.moveForward(m_deltaTime);
    if (keys[SDL_SCANCODE_S]) m_camera.moveBack(m_deltaTime);
    if (keys[SDL_SCANCODE_A]) m_camera.moveLeft(m_deltaTime);
    if (keys[SDL_SCANCODE_D]) m_camera.moveRight(m_deltaTime);
    if (keys[SDL_SCANCODE_SPACE]) m_camera.moveUp(m_deltaTime);
    if (keys[SDL_SCANCODE_LSHIFT]) m_camera.moveDown(m_deltaTime);

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