#include "ndr/math/Vector.hpp"
#include <memory>

namespace ndr::math {

using math::dimension;

Vector::Vector() : m_dimensions(0) {}

Vector::Vector(dimension dimensions) { initDimensions(dimensions); }

dimension Vector::getDimensions() const { return m_dimensions; }

void Vector::initDimensions(dimension dimensions) {
  m_data.reset();
  m_dimensions = dimensions;
  m_data = std::make_unique<float[]>(dimensions);
}

float Vector::operator[](dimension component) const {
  return m_data[component];
}

} // namespace ndr::math
