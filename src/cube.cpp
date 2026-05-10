#include "cube.hpp"

Cube::Cube() {
    std::vector<float> vertices = {
        // x      y      z
        -0.5f, -0.5f, -0.5f,  // 0 back  bottom left
         0.5f, -0.5f, -0.5f,  // 1 back  bottom right
         0.5f,  0.5f, -0.5f,  // 2 back  top right
        -0.5f,  0.5f, -0.5f,  // 3 back  top left
        -0.5f, -0.5f,  0.5f,  // 4 front bottom left
         0.5f, -0.5f,  0.5f,  // 5 front bottom right
         0.5f,  0.5f,  0.5f,  // 6 front top right
        -0.5f,  0.5f,  0.5f   // 7 front top left
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,  2, 3, 0,  // back face
        4, 5, 6,  6, 7, 4,  // front face
        4, 0, 3,  3, 7, 4,  // left face
        1, 5, 6,  6, 2, 1,  // right face
        3, 2, 6,  6, 7, 3,  // top face
        0, 1, 5,  5, 4, 0   // bottom face
    };

    m_mesh.init(vertices, indices);
}

void Cube::update(float deltaTime) {
    rotate(deltaTime * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // rotate 50 degrees per second
}