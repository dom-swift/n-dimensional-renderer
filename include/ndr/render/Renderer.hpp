#pragma once

#include "ndr/render/Mesh.hpp"
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

private:
  ShaderProgram m_program;
  Mesh m_mesh;
};

} // namespace ndr::render
