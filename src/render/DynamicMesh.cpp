#include "ndr/render/DynamicMesh.hpp"
#include "ndr/projection/Perspective.hpp"
#include <utility>

namespace ndr::render {

DynamicMesh::DynamicMesh(const geometry::Geometry &geometry)
    : m_geometry(geometry) {}

void DynamicMesh::update(const geometry::TransformND &model) {
  auto projected = projection::perspective::reduceTo3D(m_geometry, model);
  auto vertices = projected.getRawVerticies();
  if (!m_initialized) {
    m_mesh = Mesh(std::move(vertices), projected.getIndices());
    m_initialized = true;
  } else {
    m_mesh.updateVertices(vertices);
  }
}

void DynamicMesh::draw() {
  if (m_initialized)
    m_mesh.draw();
}

} // namespace ndr::render
