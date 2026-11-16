#include "ndr/geometry/Geometry.hpp"
#include "ndr/math/Vector.hpp"
#include <vector>

namespace ndr::geometry {

using math::dimension;

Geometry::Geometry(dimension dimensions, std::vector<math::Vector> &points,
                   std::vector<dimension> &indices)
    : m_dimensions(dimensions), m_points(std::move(points)),
      m_indices(indices) {}

std::vector<float> Geometry::getVerticies() {
  std::vector<float> verticies;

  for (const auto &point : m_points) {
    for (dimension i = 0; i < point.getDimensions(); i++) {
      verticies.push_back(point[i]);
    }
  }

  return verticies;
}

std::vector<dimension> Geometry::getIndices() { return m_indices; }

/*
 *  This funciton calculates the verticies and indexes dynamically so I can
 * practice doing it for an n dimensional hypercube generator.
 * */
Geometry cube() {
  std::vector<math::Vector> points;

  // Make verticies
  for (int i = 0; i < 8; i++) {
    points.push_back(math::Vector((i & 1) - 0.5f, ((i >> 1) & 1) - 0.5f,
                                  ((i >> 2) & 1) - 0.5f));
  }

  std::vector<dimension> indices = {0, 1, 0, 2, 1, 3, 2, 3, 4, 5, 4, 6,
                                    5, 7, 6, 7, 0, 4, 1, 5, 2, 6, 3, 7};

  return Geometry(3, points, indices);
}

} // namespace ndr::geometry
