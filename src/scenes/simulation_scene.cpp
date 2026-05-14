#include "scenes/simulation_scene.hpp"
#include "objects/planet.hpp"
#include "rendering/skybox.hpp"
#include "physics/phyisics_constants.hpp"

void SimulationScene::load(MeshManager& meshManager, TextureManager& textureManager) {
    namespace PC = PhysicsConstants;

    auto skybox = std::make_unique<Skybox>();
    skybox->load(meshManager, {
        "assets/textures/skybox/right.png",
        "assets/textures/skybox/left.png",
        "assets/textures/skybox/top.png",
        "assets/textures/skybox/bottom.png",
        "assets/textures/skybox/front.png",
        "assets/textures/skybox/back.png"
    });
    setSkybox(std::move(skybox));

    setLightPos(glm::vec3(0.0f, 0.0f, 0.0f));

    auto circularOrbitVelocity = [](float radius) {
        return sqrtf(PC::G * PC::SUN_MASS / radius);
    };

    // Sun — no trail
    auto sun = std::make_unique<Planet>();
    sun->setMesh(meshManager.load("assets/objects/sphere.obj"));
    sun->setTexture(textureManager.load("assets/textures/solar_system/sun_baseColor.jpg"));
    sun->setEmissive(true);
    sun->setMass(PC::SUN_MASS);
    sun->setVelocity(glm::vec3(0.0f));
    sun->translate(glm::vec3(0.0f, 0.0f, 0.0f));
    sun->scale(10.0f);
    addObject(std::move(sun));

    // Mercury — fast orbit, dense trail
    auto mercury = std::make_unique<Planet>();
    mercury->setMesh(meshManager.load("assets/objects/sphere.obj"));
    mercury->setTexture(textureManager.load("assets/textures/solar_system/mercury_baseColor.jpg"));
    mercury->setAtmosphereColor(glm::vec3(0.0f));
    mercury->setMass(PC::MERCURY_MASS);
    mercury->setVelocity(glm::vec3(0.0f, 0.0f, circularOrbitVelocity(20.0f)));
    mercury->translate(glm::vec3(20.0f, 0.0f, 0.0f));
    mercury->scale(1.0f);
    addObject(std::move(mercury));

    // Venus
    auto venus = std::make_unique<Planet>();
    venus->setMesh(meshManager.load("assets/objects/sphere.obj"));
    venus->setTexture(textureManager.load("assets/textures/solar_system/venus_baseColor.jpg"));
    venus->setAtmosphereColor(glm::vec3(0.9f, 0.7f, 0.3f));
    venus->setMass(PC::VENUS_MASS);
    venus->setVelocity(glm::vec3(0.0f, 0.0f, circularOrbitVelocity(35.0f)));
    venus->translate(glm::vec3(35.0f, 0.0f, 0.0f));
    venus->scale(0.9f);
    addObject(std::move(venus));

    // Earth
    auto earth = std::make_unique<Planet>();
    earth->setMesh(meshManager.load("assets/objects/sphere.obj"));
    earth->setTexture(textureManager.load("assets/textures/solar_system/earth_baseColor.jpg"));
    earth->setAtmosphereColor(glm::vec3(0.2f, 0.5f, 1.0f));
    earth->setMass(PC::EARTH_MASS);
    earth->setVelocity(glm::vec3(0.0f, 0.0f, circularOrbitVelocity(50.0f)));
    earth->translate(glm::vec3(50.0f, 0.0f, 0.0f));
    earth->scale(1.0f);
    addObject(std::move(earth));

    // Mars
    auto mars = std::make_unique<Planet>();
    mars->setMesh(meshManager.load("assets/objects/sphere.obj"));
    mars->setTexture(textureManager.load("assets/textures/solar_system/mars_baseColor.jpg"));
    mars->setAtmosphereColor(glm::vec3(0.8f, 0.4f, 0.2f));
    mars->setMass(PC::MARS_MASS);
    mars->setVelocity(glm::vec3(0.0f, 0.0f, circularOrbitVelocity(70.0f)));
    mars->translate(glm::vec3(70.0f, 0.0f, 0.0f));
    mars->scale(0.5f);
    addObject(std::move(mars));

    // Jupiter — slow orbit, sparse trail
    auto jupiter = std::make_unique<Planet>();
    jupiter->setMesh(meshManager.load("assets/objects/sphere.obj"));
    jupiter->setTexture(textureManager.load("assets/textures/solar_system/jupiter_baseColor.jpg"));
    jupiter->setAtmosphereColor(glm::vec3(0.7f, 0.5f, 0.3f));
    jupiter->setMass(PC::JUPITER_MASS);
    jupiter->setVelocity(glm::vec3(0.0f, 0.0f, circularOrbitVelocity(110.0f)));
    jupiter->translate(glm::vec3(110.0f, 0.0f, 0.0f));
    jupiter->scale(5.0f);
    addObject(std::move(jupiter));

    // Saturn
    auto saturn = std::make_unique<Planet>();
    saturn->setMesh(meshManager.load("assets/objects/sphere.obj"));
    saturn->setTexture(textureManager.load("assets/textures/solar_system/saturn_baseColor.jpg"));
    saturn->setAtmosphereColor(glm::vec3(0.8f, 0.7f, 0.4f));
    saturn->setMass(PC::SATURN_MASS);
    saturn->setVelocity(glm::vec3(0.0f, 0.0f, circularOrbitVelocity(160.0f)));
    saturn->translate(glm::vec3(160.0f, 0.0f, 0.0f));
    saturn->scale(4.0f);
    addObject(std::move(saturn));

    // Uranus
    auto uranus = std::make_unique<Planet>();
    uranus->setMesh(meshManager.load("assets/objects/sphere.obj"));
    uranus->setTexture(textureManager.load("assets/textures/solar_system/uranus_baseColor.jpg"));
    uranus->setAtmosphereColor(glm::vec3(0.4f, 0.8f, 0.9f));
    uranus->setMass(PC::URANUS_MASS);
    uranus->setVelocity(glm::vec3(0.0f, 0.0f, circularOrbitVelocity(200.0f)));
    uranus->translate(glm::vec3(200.0f, 0.0f, 0.0f));
    uranus->scale(2.5f);
    addObject(std::move(uranus));

    // Neptune — slowest orbit, most sparse trail
    auto neptune = std::make_unique<Planet>();
    neptune->setMesh(meshManager.load("assets/objects/sphere.obj"));
    neptune->setTexture(textureManager.load("assets/textures/solar_system/neptune_baseColor.jpg"));
    neptune->setAtmosphereColor(glm::vec3(0.1f, 0.3f, 0.9f));
    neptune->setMass(PC::NEPTUNE_MASS);
    neptune->setVelocity(glm::vec3(0.0f, 0.0f, circularOrbitVelocity(240.0f)));
    neptune->translate(glm::vec3(240.0f, 0.0f, 0.0f));
    neptune->scale(2.0f);
    addObject(std::move(neptune));
}

void SimulationScene::unload() {
    m_objects.clear();
}