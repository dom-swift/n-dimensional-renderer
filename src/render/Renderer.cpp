#include "ndr/render/Renderer.hpp"
#include "ndr/resources/ResourceLoader.hpp"

#include <glad/gl.h>

namespace ndr::render {

Renderer::Renderer(const resources::ResourceLoader &resources)
    : m_program(resources.loadText("shaders/basic.vert"),
                resources.loadText("shaders/basic.frag"), "shaders/basic.vert",
                "shaders/basic.frag") {
  const float vertices[] = {
      -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
  };

  glGenVertexArrays(1, &m_vertexArray);
  glGenBuffers(1, &m_vertexBuffer);

  glBindVertexArray(m_vertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        reinterpret_cast<void *>(0));
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

Renderer::~Renderer() {
  glDeleteBuffers(1, &m_vertexBuffer);
  glDeleteVertexArrays(1, &m_vertexArray);
}

void Renderer::resize(int width, int height) {
  glViewport(0, 0, width, height);
}

void Renderer::clear() {
  glClearColor(0.3f, 0.0f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render() {
  m_program.use();
  glBindVertexArray(m_vertexArray);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

} // namespace ndr::render
