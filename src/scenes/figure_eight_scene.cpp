#include "scenes/figure_eight_scene.hpp"
#include "objects/planet.hpp"
#include "rendering/skybox.hpp"
#include "physics/phyisics_constants.hpp"

void FigureEightScene::load(MeshManager& meshManager, TextureManager& textureManager) {
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

    // figure-8 has no single light source — use ambient only
    setLightPos(glm::vec3(0.0f, 1000.0f, 0.0f));

    // all three bodies have equal mass
    const float mass = 1.0f;
    const float scale = 20.0f; // scale up positions for visibility

    // exact figure-8 initial conditions (Chenciner & Montgomery 2000)
    glm::vec3 posA = glm::vec3( 0.97000436f, -0.24308753f, 0.0f) * scale;
    glm::vec3 posB = glm::vec3(-0.97000436f,  0.24308753f, 0.0f) * scale;
    glm::vec3 posC = glm::vec3( 0.0f,         0.0f,        0.0f);

    glm::vec3 velA = glm::vec3( 0.46620369f,  0.43236573f, 0.0f);
    glm::vec3 velB = glm::vec3( 0.46620369f,  0.43236573f, 0.0f);
    glm::vec3 velC = glm::vec3(-0.93240737f, -0.86473146f, 0.0f);

    // body A — red
    auto bodyA = std::make_unique<Planet>();
    bodyA->setMesh(meshManager.load("assets/objects/sphere.obj"));
    bodyA->setTexture(textureManager.load("assets/textures/solar_system/mars_baseColor.jpg"));
    bodyA->setMass(mass);
    bodyA->setVelocity(velA);
    bodyA->translate(posA);
    bodyA->scale(2.0f);
    bodyA->setAtmosphereColor(glm::vec3(0.8f, 0.2f, 0.2f));
    addObject(std::move(bodyA));

    // body B — blue
    auto bodyB = std::make_unique<Planet>();
    bodyB->setMesh(meshManager.load("assets/objects/sphere.obj"));
    bodyB->setTexture(textureManager.load("assets/textures/solar_system/earth_baseColor.jpg"));
    bodyB->setMass(mass);
    bodyB->setVelocity(velB);
    bodyB->translate(posB);
    bodyB->scale(2.0f);
    bodyB->setAtmosphereColor(glm::vec3(0.2f, 0.4f, 0.8f));
    addObject(std::move(bodyB));

    // body C — yellow
    auto bodyC = std::make_unique<Planet>();
    bodyC->setMesh(meshManager.load("assets/objects/sphere.obj"));
    bodyC->setTexture(textureManager.load("assets/textures/solar_system/sun_baseColor.jpg"));
    bodyC->setEmissive(true);
    bodyC->setMass(mass);
    bodyC->setVelocity(velC);
    bodyC->translate(posC);
    bodyC->scale(2.0f);
    addObject(std::move(bodyC));
}

void FigureEightScene::unload() {
    m_objects.clear();
}