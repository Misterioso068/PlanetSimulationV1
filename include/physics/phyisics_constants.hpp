// physics_constants.hpp
#pragma once

namespace PhysicsConstants {
    // The accurate G is 6.67430 × 10^-11,
    // but that would mean no movement visually for the simulation
    // so I will use 0.001f.
    constexpr float G = 0.001f;

    constexpr int PHYSICS_STEPS = 10;
    constexpr float TIME_SCALE = 10.0f;

    // Planet masses relative to Earth (Earth = 1.0)
    constexpr float EARTH_MASS = 1.0f;
    constexpr float SUN_MASS = 333000.0f;    // 333,000x Earth
    constexpr float MERCURY_MASS = 0.055f;   // 5.5% of Earth
    constexpr float VENUS_MASS = 0.815f;     // 81.5% of Earth
    constexpr float MARS_MASS = 0.107f;      // 10.7% of Earth
    constexpr float JUPITER_MASS = 317.8f;   // 317.8x Earth
    constexpr float SATURN_MASS = 95.2f;     // 95.2x Earth
    constexpr float URANUS_MASS = 14.5f;     // 14.5x Earth
    constexpr float NEPTUNE_MASS = 17.1f;    // 17.1x Earth

    
}