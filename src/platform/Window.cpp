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

  m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (m_window == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwSetWindowUserPointer(m_window, this);
  glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);

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

void Window::setResizeCallback(ResizeCallback callback) {
  m_resizeCallback = std::move(callback);
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(m_window) ||
         glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

void Window::swapBuffers() { glfwSwapBuffers(m_window); }

void Window::pollEvents() { glfwPollEvents(); }

void Window::onFramebufferResize(int width, int height) {
  if (m_resizeCallback) {
    m_resizeCallback(width, height);
  }
}

void Window::framebufferResizeCallback(GLFWwindow *window, int width,
                                       int height) {
  auto *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self != nullptr) {
    self->onFramebufferResize(width, height);
  }
}

} // namespace ndr::platform
