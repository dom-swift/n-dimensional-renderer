#pragma once

#include "ndr/geometry/Geometry.hpp"
#include "ndr/math/Vector.hpp"
namespace ndr::projection::perspective {

math::Vector projectPointOneDimension(const math::Vector &point,
                                      float distance);

geometry::Geometry reduceTo3D(const ndr::geometry::Geometry &geometry,
                              const geometry::TransformND &model);

geometry::Geometry project(math::dimension target, geometry::Geometry geometry);

} // namespace ndr::projection::perspective
