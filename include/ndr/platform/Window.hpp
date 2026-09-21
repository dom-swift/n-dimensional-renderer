#pragma once

#include <functional>
#include <string>

struct GLFWwindow;

namespace ndr::platform {

class Window {
public:
  using ResizeCallback = std::function<void(int, int)>;

  Window(int width, int height, const std::string &title);
  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  void setResizeCallback(ResizeCallback callback);

  [[nodiscard]] bool shouldClose() const;
  void swapBuffers();
  void pollEvents();

private:
  void onFramebufferResize(int width, int height);

  static void framebufferResizeCallback(GLFWwindow *window, int width,
                                        int height);

  GLFWwindow *m_window = nullptr;
  ResizeCallback m_resizeCallback;
};

} // namespace ndr::platform
