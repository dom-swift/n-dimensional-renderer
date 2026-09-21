#include "ndr/render/Renderer.hpp"

#include <glad/gl.h>

namespace ndr::render {

Renderer::Renderer(int width, int height) { glViewport(0, 0, width, height); }

void Renderer::resize(int width, int height) {
  glViewport(0, 0, width, height);
}

void Renderer::clear() { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::render() {}

} // namespace ndr::render
