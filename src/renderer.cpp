#include "renderer.hpp"
#include "gameobject.hpp"

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

        glBindVertexArray(object->getMesh()->getVAO());
        glDrawElements(GL_TRIANGLES, object->getMesh()->getIndexCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}