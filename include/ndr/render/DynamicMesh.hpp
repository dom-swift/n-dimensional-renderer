#pragma once

#include "ndr/geometry/Geometry.hpp"
#include "ndr/render/Mesh.hpp"

namespace ndr::render {

// Projects an ND geometry only when update() is called. draw() only draws.
// The source geometry must outlive this mesh; its topology stays fixed.
class DynamicMesh {
public:
  explicit DynamicMesh(const geometry::Geometry &geometry);

  void update(const geometry::TransformND &model);
  void draw();

private:
  const geometry::Geometry &m_geometry;
  Mesh m_mesh;
  bool m_initialized = false;
};

} // namespace ndr::render
