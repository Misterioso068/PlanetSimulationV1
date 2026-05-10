#include "mesh.hpp"

bool Mesh::init(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
    m_indexCount = indices.size();

    // create objects
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    // bind VAO first — it records everything that follows
    glBindVertexArray(m_VAO);

    // upload vertex data to GPU
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // upload index data to GPU
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // tell VAO how to interpret the vertex data
    // attribute 0 = position (x,y,z) = 3 floats
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind
    glBindVertexArray(0);

    return true;
}