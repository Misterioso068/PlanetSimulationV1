#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "rendering/shader.hpp"
#include "scenes/scene.hpp"
#include "rendering/camera.hpp"
#include "rendering/skybox.hpp"

class Renderer {
    public:
        bool init();
        void draw(const Scene& scene, const Camera& camera);

    private:
        Shader m_shader;
        GLint m_modelLoc;
        GLint m_viewLoc;
        GLint m_projLoc;
        GLint m_hasTextureLoc;
        GLint m_texLoc;
        GLint m_colorLoc;
        GLint m_isEmissiveLoc;
        GLint m_lightPosLoc;
        GLint m_viewPosLoc;
        GLint m_lightColorLoc;

        GLuint m_defaultTexture = 0;

        Shader m_skyboxShader;
        GLint m_skyboxViewLoc;
        GLint m_skyboxProjLoc;
        GLint m_skyboxTexLoc;

        // Planet specific
        GLint m_atmosphereColorLoc;

        void drawSkybox(const Skybox& skybox, const Camera& camera);
};