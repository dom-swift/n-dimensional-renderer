#include "ndr/math/Matrix.hpp"
#include "ndr/math/Vector.hpp"
#include <cmath>
#include <memory>
#include <vector>

namespace ndr::math {

using math::dimension;

Matrix::Matrix(dimension size) : Matrix(size, size) {}

Matrix::Matrix(dimension rows, dimension columns)
    : m_rows(rows), m_columns(columns) {
  m_data = std::make_unique<Vector[]>(m_columns);

  for (dimension i = 0; i < m_columns; i++)
    m_data[i].initDimensions(m_rows);
}

Matrix::Matrix(std::vector<Vector> data)
    : m_rows(data[0].getDimensions()), m_columns((dimension)data.size()) {
  // TODO: Check if every vector is of equal length.
  m_data = std::make_unique<Vector[]>(m_columns);
  for (unsigned long i = 0; i < m_columns; i++) {
    m_data[i] = std::move(data[i]);
  }
}

Vector &Matrix::operator[](dimension column) const { return m_data[column]; }

Matrix Matrix::operator*(const Matrix &mat) const {
  if (m_columns != mat.m_rows)
    return Matrix();

  Matrix out(m_rows, mat.m_columns);

  for (dimension col = 0; col < out.m_columns; col++) {
    out[col] = *this * mat[col];
  }

  return out;
}

Vector Matrix::operator*(const Vector &vec) const {
  if (vec.getDimensions() != m_columns)
    return Vector();

  Vector out(m_rows);

  for (dimension i = 0; i < out.getDimensions(); i++)
    for (dimension j = 0; j < m_columns; j++)
      out[i] += m_data[j][i] * vec[j];

  return out;
}

Matrix identity(dimension n) {
  Matrix out(n);

  for (dimension i = 0; i < n; i++)
    out[i][i] = 1.0f;

  return out;
}

Matrix rotationPlane(dimension n, dimension a, dimension b, float angle) {
  Matrix rotation = identity(n);

  float c = std::cos(angle);
  float s = std::sin(angle);

  rotation[a][a] = c;
  rotation[b][a] = -s;
  rotation[a][b] = s;
  rotation[b][b] = c;

  return rotation;
}

} // namespace ndr::math
