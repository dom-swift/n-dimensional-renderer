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

FramebufferSize Window::framebufferSize() const {
  FramebufferSize size{};
  glfwGetFramebufferSize(m_window, &size.width, &size.height);
  return size;
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
