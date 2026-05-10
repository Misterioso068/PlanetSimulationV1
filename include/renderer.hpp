#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"
#include "scene.hpp"
#include "camera.hpp"

class Renderer {
    public:
        bool init();
        void draw(const Scene& scene, const Camera& camera);

    private:
        Shader m_shader;
};