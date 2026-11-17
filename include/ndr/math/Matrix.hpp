#pragma once

#include "ndr/math/Vector.hpp"
#include <vector>

namespace ndr::math {

using math::dimension;

class Matrix {
public:
  Matrix() = default;
  Matrix(dimension size); // size x size
  Matrix(dimension rows, dimension columns);
  Matrix(std::vector<Vector> data);

  Vector &operator[](dimension column) const;

  Matrix operator*(const Matrix &mat) const;
  Vector operator*(const Vector &vec) const;

private:
  dimension m_rows;
  dimension m_columns; // AKA vector length

  std::unique_ptr<Vector[]> m_data;
};

Matrix identity(dimension n);
Matrix rotationPlane(dimension n, dimension a, dimension b, float angle);

} // namespace ndr::math
