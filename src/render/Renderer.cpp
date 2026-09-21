#include "ndr/render/Renderer.hpp"
#include "glad/gl.h"

using namespace ndr::render;

Renderer::Renderer(int width, int height) { glViewport(0, 0, width, height); }

void Renderer::Resize(int width, int height) {
  glViewport(0, 0, width, height);
}

void Renderer::Clear() { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::Render() {}
