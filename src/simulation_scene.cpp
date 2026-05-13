#include "simulation_scene.hpp"
#include "planet.hpp"

void SimulationScene::load(MeshManager& meshManager, TextureManager& textureManager) {
    setLightPos(glm::vec3(0.0f, 0.0f, 0.0f));
    
    // Sun
    auto sun = std::make_unique<Planet>();
    sun->setMesh(meshManager.load("assets/objects/sphere.obj"));
    sun->setTexture(textureManager.load("assets/textures/sun_baseColor.jpg"));
    sun->setEmissive(true);
    sun->setMass(1.989e30f);
    sun->translate(glm::vec3(0.0f, 0.0f, 0.0f));
    sun->scale(10.0f);
    addObject(std::move(sun));

    // Mercury
    auto mercury = std::make_unique<Planet>();
    mercury->setMesh(meshManager.load("assets/objects/sphere.obj"));
    mercury->setTexture(textureManager.load("assets/textures/mercury_baseColor.jpg"));
    mercury->setMass(3.285e23f);
    mercury->translate(glm::vec3(20.0f, 0.0f, 0.0f));
    mercury->scale(0.4f);
    addObject(std::move(mercury));

    // Venus
    auto venus = std::make_unique<Planet>();
    venus->setMesh(meshManager.load("assets/objects/sphere.obj"));
    venus->setTexture(textureManager.load("assets/textures/venus_baseColor.jpg"));
    venus->setMass(4.867e24f);
    venus->translate(glm::vec3(35.0f, 0.0f, 0.0f));
    venus->scale(0.9f);
    addObject(std::move(venus));

    // Earth
    auto earth = std::make_unique<Planet>();
    earth->setMesh(meshManager.load("assets/objects/sphere.obj"));
    earth->setTexture(textureManager.load("assets/textures/earth_baseColor.jpg"));
    earth->setMass(5.972e24f);
    earth->translate(glm::vec3(50.0f, 0.0f, 0.0f));
    earth->scale(1.0f);
    addObject(std::move(earth));

    // Mars
    auto mars = std::make_unique<Planet>();
    mars->setMesh(meshManager.load("assets/objects/sphere.obj"));
    mars->setTexture(textureManager.load("assets/textures/mars_baseColor.jpg"));
    mars->setMass(6.39e23f);
    mars->translate(glm::vec3(70.0f, 0.0f, 0.0f));
    mars->scale(0.5f);
    addObject(std::move(mars));

    // Jupiter
    auto jupiter = std::make_unique<Planet>();
    jupiter->setMesh(meshManager.load("assets/objects/sphere.obj"));
    jupiter->setTexture(textureManager.load("assets/textures/jupiter_baseColor.jpg"));
    jupiter->setMass(1.898e27f);
    jupiter->translate(glm::vec3(110.0f, 0.0f, 0.0f));
    jupiter->scale(5.0f);
    addObject(std::move(jupiter));

    // Saturn
    auto saturn = std::make_unique<Planet>();
    saturn->setMesh(meshManager.load("assets/objects/sphere.obj"));
    saturn->setTexture(textureManager.load("assets/textures/saturn_baseColor.jpg"));
    saturn->setMass(5.683e26f);
    saturn->translate(glm::vec3(160.0f, 0.0f, 0.0f));
    saturn->scale(4.0f);
    addObject(std::move(saturn));

    // Uranus
    auto uranus = std::make_unique<Planet>();
    uranus->setMesh(meshManager.load("assets/objects/sphere.obj"));
    uranus->setTexture(textureManager.load("assets/textures/uranus_baseColor.jpg"));
    uranus->setMass(8.681e25f);
    uranus->translate(glm::vec3(200.0f, 0.0f, 0.0f));
    uranus->scale(2.5f);
    addObject(std::move(uranus));

    // Neptune
    auto neptune = std::make_unique<Planet>();
    neptune->setMesh(meshManager.load("assets/objects/sphere.obj"));
    neptune->setTexture(textureManager.load("assets/textures/neptune_baseColor.jpg"));
    neptune->setMass(1.024e26f);
    neptune->translate(glm::vec3(240.0f, 0.0f, 0.0f));
    neptune->scale(2.0f);
    addObject(std::move(neptune));
}

void SimulationScene::unload() {
    m_objects.clear();
}