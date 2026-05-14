#pragma once

#include "physics/phyisics_constants.hpp"

struct PhysicsConfig {
    float G = PhysicsConstants::G;
    float timeScale = PhysicsConstants::TIME_SCALE;
    float softening = PhysicsConstants::SOFTENING;
    int physicsSteps = PhysicsConstants::PHYSICS_STEPS;
};