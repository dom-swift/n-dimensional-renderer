#include "ndr/render/Renderer.hpp"

#include <glad/gl.h>

namespace ndr::render {

Renderer::Renderer(const resources::ResourceLoader &resources)
    : m_program(resources.loadText("shaders/basic.vert"),
                resources.loadText("shaders/basic.frag"), "shaders/basic.vert",
                "shaders/basic.frag"),
      m_mesh({0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f,
              0.5f, 0.0f},
             {0, 1, 3, 1, 2, 3}) {}

Renderer::~Renderer() {}

void Renderer::resize(int width, int height) {
  glViewport(0, 0, width, height);
}

void Renderer::clear() {
  glClearColor(0.3f, 0.0f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render() {
  m_program.use();
  m_mesh.draw();
}

} // namespace ndr::render
