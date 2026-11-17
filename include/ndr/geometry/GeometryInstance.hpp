#pragma once

#include "ndr/geometry/Geometry.hpp"
#include <functional>
#include <memory>

namespace ndr::geometry {

// Instances share source vertices/edges, but have independent ND models.
class GeometryInstance {
public:
  using ModelCallback = std::function<void(const TransformND &)>;

  explicit GeometryInstance(std::shared_ptr<const Geometry> geometry);

  const Geometry &getGeometry() const;

  // Registration publishes the initial model, just like Camera.
  void setModelCallback(ModelCallback callback);
  void setModel(TransformND model);

private:
  std::shared_ptr<const Geometry> m_geometry;
  TransformND m_model;
  ModelCallback m_modelCallback;
};

} // namespace ndr::geometry
