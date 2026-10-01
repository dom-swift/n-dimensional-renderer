#pragma once

#include <functional>
#include <string>

struct GLFWwindow;

namespace ndr::platform {

struct FramebufferSize {
  int width;
  int height;
};

class Window {
public:
  using ResizeCallback = std::function<void(int, int)>;
  using KeyCallback = std::function<void(int, int, int, int)>;
  using MouseCallback = std::function<void(double, double)>;

  Window(int width, int height, const std::string &title);
  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  double deltaTime();

  void setResizeCallback(ResizeCallback callback);
  void setKeyCallback(KeyCallback callback);
  void setMouseCallback(MouseCallback callback);

  [[nodiscard]] bool shouldClose() const;
  [[nodiscard]] FramebufferSize framebufferSize() const;
  void swapBuffers();
  void pollEvents();

private:
  void onFramebufferResize(int width, int height);
  void onKey(int key, int scancode, int action, int mods);
  void onMouse(double xpos, double ypos);

  static void framebufferResizeCallback(GLFWwindow *window, int width,
                                        int height);
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
  static void mouseCallback(GLFWwindow *window, double xpos, double ypos);

  double m_deltaTime;

  GLFWwindow *m_window = nullptr;
  ResizeCallback m_resizeCallback;
  KeyCallback m_keyCallback;
  MouseCallback m_mouseCallback;
};

} // namespace ndr::platform
