#include "ndr/app/Application.hpp"

namespace ndr {

Application::Application() : m_window(1280, 720, "NDR"), m_renderer(1280, 720) {
  m_window.setResizeCallback(
      [this](int width, int height) { m_renderer.resize(width, height); });
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
