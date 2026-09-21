#pragma once

#include "ndr/platform/Window.hpp"
#include "ndr/render/Renderer.hpp"

namespace ndr {

class Application {
public:
  Application();

  int run();

private:
  platform::Window m_window;
  render::Renderer m_renderer;
};

} // namespace ndr
