#pragma once

#include <cstddef>
#include <vector>

namespace ndr::render {

/*
 *  Static mesh, doesn't store points for that reason.
 *  Used for any <=3 dimensional objects.
 * */
class Mesh {
public:
  Mesh(std::vector<float> verticies, std::vector<unsigned int> indices);
  ~Mesh();

  Mesh() = default;
  Mesh(const Mesh &) = delete;
  Mesh &operator=(const Mesh &) = delete;
  Mesh(Mesh &&other) noexcept;
  Mesh &operator=(Mesh &&other) noexcept;

  void draw();

private:
  friend class DynamicMesh;
  void updateVertices(const std::vector<float> &vertices);
  std::size_t m_vertexBytes = 0;

  unsigned int m_vertexBuffer = 0;
  unsigned int m_elementBuffer = 0;
  unsigned int m_vertexArray = 0;

  int m_indexCount = 0;
};

} // namespace ndr::render
