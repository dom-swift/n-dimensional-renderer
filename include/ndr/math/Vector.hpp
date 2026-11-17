#pragma once

#include <concepts>
#include <memory>
namespace ndr::math {

using dimension = unsigned int;

/*
 * I was planning on having the Vectors be templates but since my end game is to
 * render much hihger dimensional objects I wouldn't be able to do that easily
 * in runtime. This way I can do something at one point like spawn_hypercube(10)
 * and have that be any dimension.
 */

/*
 * Basic Vector class
 * Can operate in any whole positive dimension.
 */
class Vector {
public:
  // make_unique needs a default constructor, make sure to later call
  // initDimensions afterwards
  explicit Vector();
  explicit Vector(dimension dimensions);

  template <std::same_as<float>... Floats> explicit Vector(Floats... args) {
    initDimensions(sizeof...(args));
    std::size_t pos = 0;
    ((m_data[pos++] = args), ...);
  }

  dimension getDimensions() const;

  void initDimensions(dimension dimensions);

  void operator+=(const Vector &vec);

  float &operator[](dimension component) const;

  // Returns new vector of n-1 dimensions.
  // Does this by just truncating last component.
  Vector collapse() const;

private:
  dimension m_dimensions;

  /*
   * So, the actual data of the vector is stored in an array of pointers of
   * m_dimension size. This is done instead of a set array because otherwise I'd
   * need templates. And I don't want to work with vectors since the size of the
   * vector won't change.
   */
  std::unique_ptr<float[]> m_data;
};

} // namespace ndr::math
