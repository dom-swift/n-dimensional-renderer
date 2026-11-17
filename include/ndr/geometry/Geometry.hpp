#pragma once

#include "ndr/math/Matrix.hpp"
#include "ndr/math/Vector.hpp"
#include <vector>

namespace ndr::geometry {

struct TransformND {
  math::Matrix linear;
  math::Vector translation;
};

using math::dimension;

/*
 * Geometry is very similar to mesh, if naything its theoretically the same.
 * The difference is that geometry is like a higher dimensional mesh, that uses
 * ndr math. This way, Geometry is used for the apps projection and mesh is used
 * for the rendering, thus separating the 3d and the higher.
 */
class Geometry {
public:
  Geometry() = default;
  explicit Geometry(dimension dimensions, std::vector<math::Vector> &points,
                    const std::vector<dimension> &indices);

  dimension getDimensions() const;
  const std::vector<math::Vector> &getVerticies() const;
  std::vector<float> getRawVerticies() const;
  const std::vector<dimension> &getIndices() const;

  Geometry operator()(const TransformND &model) const;

private:
  dimension m_dimensions = 0;
  std::vector<math::Vector> m_points;
  std::vector<dimension> m_indices;
};

Geometry cube();
Geometry hypercube(dimension dimensions, float size = 1.0f);

} // namespace ndr::geometry
