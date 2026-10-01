#include "ndr/render/Renderer.hpp"

#include <glad/gl.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
  if (width <= 0 || height <= 0) {
    return;
  }

  glm::mat4 projection = glm::perspective(
      glm::radians(45.0f),
      static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
  m_program.use();
  m_program.setMat4("projection", projection);
}

void Renderer::view(glm::mat4 view) {
  m_program.use();
  m_program.setMat4("view", view);
}

void Renderer::clear() {
  glClearColor(0.3f, 0.0f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render() {
  m_program.use();
  glm::mat4 model(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  m_program.setMat4("model", model);
  m_mesh.draw();
}

} // namespace ndr::render
