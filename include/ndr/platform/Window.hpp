#ifndef NDR_WINDOW
#define NDR_WINDOW

#include <functional>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

namespace ndr::platform {

class Window {
private:
  GLFWwindow *m_window = nullptr;

  using ResizeCallback = std::function<void(int, int)>;
  ResizeCallback m_resizeCallback;
  void OnFramebufferResize(int width, int height);

  static void FrameBufferResizeCallback(GLFWwindow *window, int width,
                                        int height);

public:
  Window(int width, int height, std::string title);
  void Destroy();

  void SetResizeCallback(ResizeCallback callback);

  bool ShouldClose();
  void SwapBuffers();
  void PollEvents();
};

} // namespace ndr::platform

#endif // !NDR_WINDOW
