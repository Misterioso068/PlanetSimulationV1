#include "renderer.hpp"
#include "gameobject.hpp"

bool Renderer::init() {
    glEnable(GL_DEPTH_TEST);
    
    if (!m_shader.load("shaders/vertShader.vert", "shaders/fragShader.frag")) {
        return false;
    }

    return true;
}

void Renderer::draw(const Scene& scene, const Camera& camera) {
    m_shader.use();

    GLint viewLoc = glGetUniformLocation(m_shader.getProgram(), "u_view");
    GLint projLoc = glGetUniformLocation(m_shader.getProgram(), "u_projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getView()));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjection()));

    for (const auto& object : scene.getObjects()) {
        GLint modelLoc = glGetUniformLocation(m_shader.getProgram(), "u_model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(object->getTransform()));
        glBindVertexArray(object->getMesh().getVAO());
        glDrawElements(GL_TRIANGLES, object->getMesh().getIndexCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}