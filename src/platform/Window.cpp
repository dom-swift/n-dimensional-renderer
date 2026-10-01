#include "ndr/platform/Window.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <stdexcept>
#include <utility>

namespace ndr::platform {

Window::Window(int width, int height, const std::string &title) {
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined(__APPLE__)
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

  m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (m_window == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwSetWindowUserPointer(m_window, this);
  glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
  glfwSetKeyCallback(m_window, keyCallback);
  glfwSetCursorPosCallback(m_window, mouseCallback);

  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwMakeContextCurrent(m_window);

  if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
    glfwDestroyWindow(m_window);
    m_window = nullptr;
    glfwTerminate();
    throw std::runtime_error("Failed to load OpenGL with GLAD");
  }
}

Window::~Window() {
  if (m_window != nullptr) {
    glfwDestroyWindow(m_window);
    m_window = nullptr;
  }

  glfwTerminate();
}

double Window::deltaTime() { return m_deltaTime; }

void Window::setResizeCallback(ResizeCallback callback) {
  m_resizeCallback = std::move(callback);
}

void Window::setKeyCallback(KeyCallback callback) {
  m_keyCallback = std::move(callback);
}

void Window::setMouseCallback(MouseCallback callback) {
  m_mouseCallback = std::move(callback);
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(m_window) ||
         glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

FramebufferSize Window::framebufferSize() const {
  FramebufferSize size{};
  glfwGetFramebufferSize(m_window, &size.width, &size.height);
  return size;
}

void Window::swapBuffers() { glfwSwapBuffers(m_window); }

void Window::pollEvents() {
  glfwPollEvents();
  double time = glfwGetTime();
  static double lastTime = time;
  m_deltaTime = time - lastTime;
  lastTime = time;
}

void Window::onFramebufferResize(int width, int height) {
  if (m_resizeCallback) {
    m_resizeCallback(width, height);
  }
}

void Window::onKey(int key, int scancode, int action, int mods) {
  if (m_keyCallback) {
    m_keyCallback(key, scancode, action, mods);
  }
}

void Window::onMouse(double xpos, double ypos) {
  if (m_mouseCallback) {
    m_mouseCallback(xpos, ypos);
  }
}

void Window::framebufferResizeCallback(GLFWwindow *window, int width,
                                       int height) {
  auto *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self != nullptr) {
    self->onFramebufferResize(width, height);
  }
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {

  auto *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self != nullptr) {
    self->onKey(key, scancode, action, mods);
  }
}

void Window::mouseCallback(GLFWwindow *window, double xpos, double ypos) {
  auto *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self != nullptr) {
    self->onMouse(xpos, ypos);
  }
}

} // namespace ndr::platform
