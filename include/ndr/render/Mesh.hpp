#pragma once

#include <vector>

namespace ndr::render {

class Mesh {
public:
  Mesh(std::vector<float> verticies, std::vector<unsigned int> indices);
  ~Mesh();

  Mesh() = default;

  void draw();

private:
  unsigned int m_vertexBuffer = 0;
  unsigned int m_elementBuffer = 0;
  unsigned int m_vertexArray = 0;

  int m_indexCount = 0;
};

} // namespace ndr::render
