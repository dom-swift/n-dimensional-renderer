#include "ndr/app/Application.hpp"

#include <utility>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace ndr {

Application::Application(std::filesystem::path resourceRoot)
    : m_window(1280, 720, "NDR"), m_resources(std::move(resourceRoot)),
      m_renderer(m_resources),
      m_camera(glm::vec3(0.0f, 0.0f, -3.0f), 2.5f, 0.2f) {
  m_window.setResizeCallback(
      [this](int width, int height) { m_renderer.resize(width, height); });
  m_window.setKeyCallback([this](int key, int scancode, int action, int mods) {
    processInput(key, scancode, action, mods);
  });
  m_window.setMouseCallback(
      [this](double xpos, double ypos) { processMouse(xpos, ypos); });
  m_camera.setViewCallback([this](glm::mat4 view) { m_renderer.view(view); });

  const auto [width, height] = m_window.framebufferSize();
  m_renderer.resize(width, height);
}

int Application::run() {
  while (!m_window.shouldClose()) {
    m_renderer.clear();

    m_renderer.render();

    m_window.swapBuffers();
    m_window.pollEvents();

    double deltaTime = m_window.deltaTime();
    moveCamera(deltaTime);
  }

  return 0;
}

void Application::processInput(int key, int scancode, int action, int mods) {
  m_inputs[key] = action != GLFW_RELEASE;
}

void Application::processMouse(double xpos, double ypos) {
  m_camera.turn(xpos, ypos);
}

void Application::moveCamera(double deltaTime) {

  if (m_inputs[GLFW_KEY_W])
    m_camera.moveForward(deltaTime);
  if (m_inputs[GLFW_KEY_S])
    m_camera.moveForward(-deltaTime);
  if (m_inputs[GLFW_KEY_D])
    m_camera.moveRight(deltaTime);
  if (m_inputs[GLFW_KEY_A])
    m_camera.moveRight(-deltaTime);
}

} // namespace ndr
