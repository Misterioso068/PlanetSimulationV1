#pragma once

#include "scene.hpp"

class SimulationScene : public Scene {
    public:
        void load() override;
        void unload() override;
};