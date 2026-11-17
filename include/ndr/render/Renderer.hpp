#pragma once

#include "ndr/geometry/GeometryInstance.hpp"
#include "ndr/render/DynamicMesh.hpp"
#include "ndr/render/ShaderProgram.hpp"
#include "ndr/resources/ResourceLoader.hpp"

namespace ndr::render {

class Renderer {
public:
  explicit Renderer(const resources::ResourceLoader &resources);
  ~Renderer();

  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;

  void resize(int width, int height);
  void view(glm::mat4 view);

  void clear();
  void render();
  void update(double deltaTime);

private:
  ShaderProgram m_program;
  geometry::GeometryInstance m_object;
  DynamicMesh m_mesh;
  float m_angle = 0.0f;
};

} // namespace ndr::render
