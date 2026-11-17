#include "ndr/geometry/Geometry.hpp"
#include "ndr/math/Vector.hpp"
#include <utility>
#include <vector>

namespace ndr::geometry {

using math::dimension;

Geometry::Geometry(dimension dimensions, std::vector<math::Vector> &points,
                   const std::vector<dimension> &indices)
    : m_dimensions(dimensions), m_points(std::move(points)),
      m_indices(indices) {}

dimension Geometry::getDimensions() const { return m_dimensions; }

const std::vector<math::Vector> &Geometry::getVerticies() const {
  return m_points;
}

std::vector<float> Geometry::getRawVerticies() const {
  std::vector<float> verticies;

  for (const auto &point : m_points) {
    for (dimension i = 0; i < point.getDimensions(); i++) {
      verticies.push_back(point[i]);
    }
  }

  return verticies;
}

const std::vector<dimension> &Geometry::getIndices() const { return m_indices; }

Geometry Geometry::operator()(const TransformND &model) const {
  std::vector<math::Vector> newPoints;
  newPoints.reserve(m_points.size());

  for (const auto &point : m_points) {
    auto transformed = model.linear * point;
    transformed += model.translation;
    newPoints.push_back(std::move(transformed));
  }

  return Geometry(m_dimensions, newPoints, m_indices);
}

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

  std::vector<unsigned int> indices = {0, 1, 0, 2, 1, 3, 2, 3, 4, 5, 4, 6,
                                       5, 7, 6, 7, 0, 4, 1, 5, 2, 6, 3, 7};

  return Geometry(3, points, indices);
}

Geometry hypercube(dimension dimensions, float size) {
  if (dimensions < 3)
    return Geometry();
  std::vector<math::Vector> points;
  unsigned int points_num = 1 << dimensions;

  // Make verticies
  for (unsigned int i = 0; i < points_num; i++) {
    math::Vector point(dimensions);
    for (dimension j = 0; j < dimensions; j++)
      point[j] = (static_cast<float>((i >> j) & 1u) - 0.5f) * size;
    points.push_back(std::move(point));
  }

  // Make edges (no idea if this works)
  std::vector<unsigned int> indices;
  for (unsigned int i = 0; i < points_num; i++) {
    for (dimension j = 0; j < dimensions; j++) {
      // Check if bit j is 0 to avoid adding same edge twice
      if (((i >> j) & 1) == 0) {
        unsigned int neighbor = i ^ (1 << j); // Flip bit j
        indices.push_back(i);
        indices.push_back(neighbor);
      }
    }
  }

  return Geometry(dimensions, points, indices);
}

} // namespace ndr::geometry
