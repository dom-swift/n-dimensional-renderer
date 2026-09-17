#ifndef NDR_APPLICATION
#define NDR_APPLICATION

#include "ndr/platform/Window.hpp"
#include "ndr/render/Renderer.hpp"

namespace ndr {

class Application {
private:
  platform::Window m_window;
  render::Renderer m_renderer;

public:
  Application();
  int Run();
  void Shutdown();
};

} // namespace ndr

#endif // !NDR_APPLICATION
