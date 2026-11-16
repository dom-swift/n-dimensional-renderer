#pragma once

#include "ndr/math/Vector.hpp"
#include <vector>

namespace ndr::geometry {

using math::dimension;

class Geometry {
public:
  explicit Geometry(dimension dimensions, std::vector<math::Vector> &points,
                    std::vector<dimension> &indices);

  std::vector<float> getVerticies();
  std::vector<dimension> getIndices();

private:
  dimension m_dimensions;
  std::vector<math::Vector> m_points;
  std::vector<dimension> m_indices;
};

Geometry cube();

} // namespace ndr::geometry
