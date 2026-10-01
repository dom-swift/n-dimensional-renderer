#pragma once

#include "ndr/platform/Window.hpp"
#include "ndr/render/Camera.hpp"
#include "ndr/render/Renderer.hpp"
#include "ndr/resources/ResourceLoader.hpp"

#include <filesystem>
#include <unordered_map>

namespace ndr {

class Application {
public:
  explicit Application(std::filesystem::path resourceRoot);

  int run();

private:
  void processInput(int key, int scancode, int action, int mods);
  void processMouse(double xpos, double ypos);
  void moveCamera(double deltaTime);

  platform::Window m_window;
  resources::ResourceLoader m_resources;
  render::Renderer m_renderer;
  render::Camera m_camera;

  std::unordered_map<int, bool> m_inputs;
};

} // namespace ndr
