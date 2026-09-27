#include "ndr/render/Mesh.hpp"

#include <glad/gl.h>

namespace ndr::render {

Mesh::Mesh(std::vector<float> verticies, std::vector<unsigned int> indices)
    : m_indexCount(static_cast<GLsizei>(indices.size())) {

  glGenVertexArrays(1, &m_vertexArray);
  glGenBuffers(1, &m_vertexBuffer);
  glGenBuffers(1, &m_elementBuffer);

  glBindVertexArray(m_vertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float),
               verticies.data(), GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        reinterpret_cast<void *>(0));
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

Mesh::~Mesh() {
  glDeleteBuffers(1, &m_vertexBuffer);
  glDeleteBuffers(1, &m_elementBuffer);
  glDeleteVertexArrays(1, &m_vertexArray);
}

void Mesh::draw() {
  glBindVertexArray(m_vertexArray);

  glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
}

} // namespace ndr::render
