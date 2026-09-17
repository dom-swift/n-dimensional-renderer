#ifndef NDR_RENDERER
#define NDR_RENDERER

#include <glad/gl.h>

namespace ndr::render {

class Renderer {
private:
  GLuint m_vertexBuffer;

public:
  Renderer();

  void Clear();
  void Render();
};

} // namespace ndr::render

#endif // !NDR_RENDERER
