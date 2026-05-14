#include "core/engine.hpp"
#include "scenes/simulation_scene.hpp"
#include "scenes/binary_star_scene.hpp"
#include "scenes/figure_eight_scene.hpp"

Engine::Engine() : m_window("Planet Simulation", 800, 800, SDL_WINDOW_RESIZABLE), 
                   m_camera(1.0f), m_gameState(GameState::QUIT){}

Engine::~Engine() {}

void Engine::run() {
    if (!m_window.init()) return;
    if (!m_renderer.init()) return;

    m_sceneManager.addScene("simulation", std::make_unique<SimulationScene>());
    m_sceneManager.addScene("binary_star", std::make_unique<BinaryStarScene>());
    m_sceneManager.addScene("figure_eight", std::make_unique<FigureEightScene>());
    loadScene("simulation");

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

    // change scenes
    if (keys[SDL_SCANCODE_1]) loadScene("simulation");
    if (keys[SDL_SCANCODE_2]) loadScene("binary_star");
    if (keys[SDL_SCANCODE_3]) loadScene("figure_eight");

    Scene* currentScene = m_sceneManager.getCurrentScene();
    if (!currentScene) return; // no scene loaded, skip everything

    float timeScale = m_physics.getTimeScale();
    float physicsSteps = m_physics.getPhysicsSteps();

    // time scale control
    if (keys[SDL_SCANCODE_EQUALS]) 
        m_physics.setTimeScale(glm::max(1.0f, m_physics.getTimeScale() + 5.0f * m_deltaTime));
    if (keys[SDL_SCANCODE_MINUS]) 
        m_physics.setTimeScale(glm::max(1.0f, m_physics.getTimeScale() - 5.0f * m_deltaTime));

    // physics
    float physicsStep = (m_deltaTime * timeScale) / physicsSteps;
    for (int i = 0; i < physicsSteps; i++) {
        m_physics.update(*currentScene, physicsStep);
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
        currentScene->update(m_deltaTime * timeScale);
}

// engine.render()
void Engine::render() {
    m_window.clear();
    Scene* currentScene = m_sceneManager.getCurrentScene();
    if (currentScene)
        m_renderer.draw(*currentScene, m_camera);
    m_window.present();
}

void Engine::loadScene(const std::string& name) {
    m_sceneManager.loadScene(name, m_meshManager, m_textureManager);
    m_physics.setConfig(m_sceneManager.getCurrentScene()->getPhysicsConfig());
}