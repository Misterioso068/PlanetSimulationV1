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
};