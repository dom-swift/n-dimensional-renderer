#pragma once

#include "ndr/platform/Window.hpp"
#include "ndr/render/Renderer.hpp"
#include "ndr/resources/ResourceLoader.hpp"

#include <filesystem>

namespace ndr {

class Application {
public:
  explicit Application(std::filesystem::path resourceRoot);

  int run();

private:
  platform::Window m_window;
  resources::ResourceLoader m_resources;
  render::Renderer m_renderer;
};

} // namespace ndr
