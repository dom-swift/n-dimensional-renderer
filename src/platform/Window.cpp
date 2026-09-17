#include "ndr/platform/Window.hpp"
#include "GLFW/glfw3.h"

#include <glad/gl.h>
#include <stdexcept>

using namespace ndr::platform;

Window::Window(int width, int height, std::string title) {
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

  m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!m_window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(m_window);

  if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
    glfwDestroyWindow(m_window);
    m_window = nullptr;
    glfwTerminate();
    throw std::runtime_error("Failed to load OpenGL with GLAD");
  }
}

void Window::Destroy() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

bool Window::ShouldClose() {
  return glfwWindowShouldClose(m_window) ||
         glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

void Window::SwapBuffers() { glfwSwapBuffers(m_window); }

void Window::PollEvents() { glfwPollEvents(); }
