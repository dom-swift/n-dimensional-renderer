#include "ndr/render/Renderer.hpp"
#include "ndr/geometry/Geometry.hpp"
#include "ndr/math/Matrix.hpp"

#include <glad/gl.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ndr::render {

Renderer::Renderer(const resources::ResourceLoader &resources)
    : m_program(resources.loadText("shaders/basic.vert"),
                resources.loadText("shaders/basic.frag"), "shaders/basic.vert",
                "shaders/basic.frag"),
      m_object(std::make_shared<geometry::Geometry>(geometry::hypercube(5))),
      m_mesh(m_object.getGeometry()) {
  m_object.setModelCallback(
      [this](const geometry::TransformND &model) { m_mesh.update(model); });
}

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
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::update(double deltaTime) {
  if (deltaTime <= 0.0)
    return;

  m_angle += 0.5f * static_cast<float>(deltaTime);
  m_object.setModel({math::rotationPlane(5, 0, 4, m_angle) *
                         math::rotationPlane(5, 2, 3, m_angle),
                     math::Vector(4u)});
}

void Renderer::render() {
  m_program.use();
  m_program.setMat4("model", glm::mat4(1.0f));
  m_mesh.draw();
}

} // namespace ndr::render
