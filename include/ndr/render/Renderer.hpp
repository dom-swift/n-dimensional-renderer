#pragma once

#include "ndr/render/ShaderProgram.hpp"

namespace ndr::resources {
class ResourceLoader;
}

namespace ndr::render {

class Renderer {
public:
  explicit Renderer(const resources::ResourceLoader &resources);
  ~Renderer();

  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;

  void resize(int width, int height);

  void clear();
  void render();

private:
  ShaderProgram m_program;
  unsigned int m_vertexBuffer = 0;
  unsigned int m_vertexArray = 0;
};

} // namespace ndr::render
