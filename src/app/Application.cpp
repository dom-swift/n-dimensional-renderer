#include "ndr/app/Application.hpp"

#include <utility>

namespace ndr {

Application::Application(std::filesystem::path resourceRoot)
    : m_window(1280, 720, "NDR"), m_resources(std::move(resourceRoot)),
      m_renderer(m_resources) {
  m_window.setResizeCallback(
      [this](int width, int height) { m_renderer.resize(width, height); });

  const auto [width, height] = m_window.framebufferSize();
  m_renderer.resize(width, height);
}

int Application::run() {
  while (!m_window.shouldClose()) {
    m_renderer.clear();

    m_renderer.render();

    m_window.swapBuffers();
    m_window.pollEvents();
  }

  return 0;
}

} // namespace ndr
