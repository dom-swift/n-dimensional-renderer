#include "ndr/projection/Perspective.hpp"
#include "ndr/geometry/Geometry.hpp"
#include "ndr/math/Vector.hpp"
#include <stdexcept>
#include <vector>

namespace ndr::projection::perspective {

using math::dimension;

math::Vector projectPointOneDimension(const math::Vector &point,
                                      float distance) {
  dimension n = point.getDimensions();
  math::Vector projected(n - 1);

  float depth = distance - point[n - 1];
  float scale = distance / depth;

  for (dimension i = 0; i < n - 1; ++i)
    projected[i] = point[i] * scale;

  return projected;
}

geometry::Geometry reduceTo3D(const geometry::Geometry &geometry,
                              const geometry::TransformND &model) {
  if (geometry.getDimensions() < 3)
    throw std::invalid_argument("Expected at least 3 dimensions");

  return project(3, geometry(model));
}

geometry::Geometry project(math::dimension target,
                           geometry::Geometry geometry) {
  auto n = geometry.getDimensions();

  if (target < 3 || n < target)
    throw std::invalid_argument("Invalid projection dimensions");

  if (n == target)
    return geometry; // Owned parameter: implicitly moved.

  std::vector<math::Vector> projectedPoints;
  projectedPoints.reserve(geometry.getVerticies().size());

  for (const auto &point : geometry.getVerticies()) {
    projectedPoints.push_back(projectPointOneDimension(point, 3.0f));
  }

  geometry::Geometry projected(n - 1, projectedPoints, geometry.getIndices());

  return project(target, std::move(projected));
}

} // namespace ndr::projection::perspective
