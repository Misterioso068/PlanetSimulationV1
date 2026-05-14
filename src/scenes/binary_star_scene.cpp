#include "scenes/binary_star_scene.hpp"
#include "objects/planet.hpp"
#include "rendering/skybox.hpp"
#include "physics/phyisics_constants.hpp"

void BinaryStarScene::load(MeshManager& meshManager, TextureManager& textureManager) {
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

    namespace PC = PhysicsConstants;

    // two stars orbiting each other
    const float starMass = PC::SUN_MASS;
    const float starDistance = 40.0f;
    const float orbitalVelocity = sqrtf(PC::G * starMass / (4.0f * starDistance));

    // star A — blue/white hot star
    auto starA = std::make_unique<Planet>();
    starA->setMesh(meshManager.load("assets/objects/sphere.obj"));
    starA->setTexture(textureManager.load("assets/textures/solar_system/sun_baseColor.jpg"));
    starA->setEmissive(true);
    starA->setMass(starMass);
    starA->translate(glm::vec3(-starDistance, 0.0f, 0.0f));
    starA->setVelocity(glm::vec3(0.0f, 0.0f, orbitalVelocity * 20.0f));
    starA->scale(6.0f);
    addObject(std::move(starA));

    // star B — orange/red cooler star
    auto starB = std::make_unique<Planet>();
    starB->setMesh(meshManager.load("assets/objects/sphere.obj"));
    starB->setTexture(textureManager.load("assets/textures/solar_system/mars_baseColor.jpg"));
    starB->setEmissive(true);
    starB->setMass(starMass);
    starB->translate(glm::vec3(starDistance, 0.0f, 0.0f));
    starB->setVelocity(glm::vec3(0.0f, 0.0f, -orbitalVelocity * 20.0f));
    starB->scale(5.0f);
    addObject(std::move(starB));

    // planet orbiting the binary system from far out
    auto planet = std::make_unique<Planet>();
    planet->setMesh(meshManager.load("assets/objects/sphere.obj"));
    planet->setTexture(textureManager.load("assets/textures/solar_system/earth_baseColor.jpg"));
    planet->setAtmosphereColor(glm::vec3(0.2f, 0.5f, 1.0f));
    planet->setMass(PC::EARTH_MASS);
    planet->translate(glm::vec3(150.0f, 0.0f, 0.0f));
    planet->setVelocity(glm::vec3(0.0f, 0.0f, sqrtf(PC::G * starMass * 2.0f / 150.0f)) * 30.0f);
    planet->scale(10.0f);
    addObject(std::move(planet));

    // set light pos to midpoint between stars
    setLightPos(glm::vec3(0.0f, 0.0f, 0.0f));
}

void BinaryStarScene::unload() {
    m_objects.clear();
}