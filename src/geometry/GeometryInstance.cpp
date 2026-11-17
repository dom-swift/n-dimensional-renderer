#include "ndr/geometry/GeometryInstance.hpp"
#include <stdexcept>
#include <utility>

namespace ndr::geometry {

GeometryInstance::GeometryInstance(std::shared_ptr<const Geometry> geometry)
    : m_geometry(std::move(geometry)) {
  if (!m_geometry || m_geometry->getDimensions() < 3)
    throw std::invalid_argument("Expected geometry with at least 3 dimensions");
  const auto n = m_geometry->getDimensions();
  m_model = {math::identity(n), math::Vector(n)};
}

const Geometry &GeometryInstance::getGeometry() const { return *m_geometry; }

void GeometryInstance::setModelCallback(ModelCallback callback) {
  m_modelCallback = std::move(callback);
  if (m_modelCallback)
    m_modelCallback(m_model);
}

void GeometryInstance::setModel(TransformND model) {
  m_model = std::move(model);
  if (m_modelCallback)
    m_modelCallback(m_model);
}

} // namespace ndr::geometry
