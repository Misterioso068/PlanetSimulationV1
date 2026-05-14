#include "renderer/renderer.hpp"
#include "objects/gameobject.hpp"

bool Renderer::init() {
    glEnable(GL_DEPTH_TEST);
    if (!m_shader.load("shaders/vertShader.vert", "shaders/fragShader.frag")) return false;
    
    m_shader.use();
    m_modelLoc = glGetUniformLocation(m_shader.getProgram(), "u_model");
    m_viewLoc = glGetUniformLocation(m_shader.getProgram(), "u_view");
    m_projLoc = glGetUniformLocation(m_shader.getProgram(), "u_projection");
    m_hasTextureLoc = glGetUniformLocation(m_shader.getProgram(), "u_hasTexture");
    m_texLoc = glGetUniformLocation(m_shader.getProgram(), "u_texture");
    m_colorLoc = glGetUniformLocation(m_shader.getProgram(), "u_color");
    m_isEmissiveLoc = glGetUniformLocation(m_shader.getProgram(), "u_isEmissive");
    m_lightPosLoc = glGetUniformLocation(m_shader.getProgram(), "u_lightPos");
    m_viewPosLoc = glGetUniformLocation(m_shader.getProgram(), "u_viewPos");
    m_lightColorLoc = glGetUniformLocation(m_shader.getProgram(), "u_lightColor");

    glGenTextures(1, &m_defaultTexture);
    glBindTexture(GL_TEXTURE_2D, m_defaultTexture);
    unsigned char white[] = {255, 255, 255, 255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (!m_skyboxShader.load("shaders/skybox.vert", "shaders/skybox.frag")) return false;
    m_skyboxShader.use();
    m_skyboxViewLoc = glGetUniformLocation(m_skyboxShader.getProgram(), "u_view");
    m_skyboxProjLoc = glGetUniformLocation(m_skyboxShader.getProgram(), "u_projection");
    m_skyboxTexLoc = glGetUniformLocation(m_skyboxShader.getProgram(), "u_skybox");

    // Planet specific
    m_atmosphereColorLoc = glGetUniformLocation(m_shader.getProgram(), "u_atmosphereColor");
        
    return true;
}

void Renderer::draw(const Scene& scene, const Camera& camera) {
    m_shader.use();

    glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getView()));
    glUniformMatrix4fv(m_projLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjection()));

    // lighting uniforms set once per frame
    glUniform3fv(m_lightPosLoc, 1, glm::value_ptr(scene.getLightPos()));
    glUniform3fv(m_viewPosLoc, 1, glm::value_ptr(camera.getPosition()));
    glUniform3f(m_lightColorLoc, 1.0f, 1.0f, 1.0f); // white light

    for (const auto& object : scene.getObjects()) {
        glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(object->getTransform()));
        glUniform1i(m_isEmissiveLoc, object->isEmissive() ? 1 : 0);

        bool hasTexture = object->getTexture() != nullptr;
        glUniform1i(m_hasTextureLoc, hasTexture ? 1 : 0);

        if (hasTexture) {
            object->getTexture()->bind(0);
            glUniform1i(m_texLoc, 0);
        } else {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_defaultTexture);
            glm::vec3 color = object->getColor();
            glUniform3f(m_colorLoc, color.r, color.g, color.b);
        }

        // Planet specific
        glUniform3fv(m_atmosphereColorLoc, 1, glm::value_ptr(object->getAtmosphereColor()));

        // Draw call
        glBindVertexArray(object->getMesh()->getVAO());
        glDrawElements(GL_TRIANGLES, object->getMesh()->getIndexCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    if (scene.getSkybox())
        drawSkybox(*scene.getSkybox(), camera);
}

void Renderer::drawSkybox(const Skybox& skybox, const Camera& camera) {
    // remove translation from view matrix so skybox stays centered on camera
    glm::mat4 view = glm::mat4(glm::mat3(camera.getView()));

    glDepthFunc(GL_LEQUAL); // pass depth test when equal to max depth
    m_skyboxShader.use();
    glUniformMatrix4fv(m_skyboxViewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(m_skyboxProjLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjection()));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getCubemap());
    glUniform1i(m_skyboxTexLoc, 0);

    glBindVertexArray(skybox.getMesh()->getVAO());
    glDrawElements(GL_TRIANGLES, skybox.getMesh()->getIndexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS); // reset depth func
}