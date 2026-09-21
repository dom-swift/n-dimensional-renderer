#pragma once

namespace ndr::render {

class Renderer {
public:
  Renderer(int width, int height);

  void resize(int width, int height);

  void clear();
  void render();
};

} // namespace ndr::render
