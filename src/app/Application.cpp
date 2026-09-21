#include "ndr/app/Application.hpp"
#include "ndr/platform/Window.hpp"
#include "ndr/render/Renderer.hpp"

using namespace ndr;

Application::Application() : m_window(1280, 720, "NDR"), m_renderer(1280, 720) {
  m_window.SetResizeCallback(
      [this](int width, int height) { m_renderer.Resize(width, height); });
}

int Application::Run() {
  while (!m_window.ShouldClose()) {
    m_renderer.Clear();

    m_renderer.Render();

    m_window.SwapBuffers();

    // Not having this at the end causes a segfault
    // I haven't yet decided to figure out why
    m_window.PollEvents();
  }
  return 0;
}

void Application::Shutdown() { m_window.Destroy(); }
