#include "ndr/render/Camera.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>

namespace ndr::render {

Camera::Camera(glm::vec3 pos)
    : m_pos(pos), m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_up(glm::vec3(0.0f, 1.0f, 0.0f)) {}

glm::mat4 Camera::view() { return glm::lookAt(m_pos, m_pos + m_front, m_up); }

void Camera::setViewCallback(ViewCallback callback) {
  m_viewCallback = callback;
}

} // namespace ndr::render
