#include "simulation_scene.hpp"
#include "cube.hpp"

void SimulationScene::load() {
    addObject(std::make_unique<Cube>());
    // add planets, skybox etc
}

void SimulationScene::unload() {
    m_objects.clear();
}