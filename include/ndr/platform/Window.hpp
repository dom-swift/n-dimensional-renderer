#ifndef NDR_WINDOW
#define NDR_WINDOW

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

namespace ndr::platform {

class Window {
private:
  GLFWwindow *m_window = nullptr;

public:
  Window(int width, int height, std::string title);
  void Destroy();

  bool ShouldClose();
  void SwapBuffers();
  void PollEvents();
};

} // namespace ndr::platform

#endif // !NDR_WINDOW
