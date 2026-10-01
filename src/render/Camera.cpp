#include "ndr/render/Camera.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>

namespace ndr::render {

Camera::Camera(glm::vec3 pos, float speed, float sensitivity)
    : m_pos(pos), m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_up(glm::vec3(0.0f, 1.0f, 0.0f)), m_speed(speed),
      m_sensitivity(sensitivity) {}

glm::mat4 Camera::view() { return glm::lookAt(m_pos, m_pos + m_front, m_up); }

void Camera::setViewCallback(ViewCallback callback) {
  m_viewCallback = callback;
  updateView();
}

void Camera::updateView() {
  if (m_viewCallback)
    m_viewCallback(view());
}

void Camera::moveForward(double deltaTime) {
  m_pos += m_front * (m_speed * (float)deltaTime);
  updateView();
}

void Camera::moveRight(double deltaTime) {
  m_pos +=
      glm::normalize(glm::cross(m_front, m_up)) * (m_speed * (float)deltaTime);
  updateView();
}

// Adds mouse input to pitch and yaw (clamping pitch),
// Then recalculates m_front
void Camera::turn(double x, double y) {

  static double lastX = x;
  static double lastY = y;

  m_yaw += (x - lastX) * m_sensitivity;
  m_pitch += (lastY - y) * m_sensitivity;
  m_pitch = std::min(90.0, std::max(-90.0, m_pitch));

  lastX = x;
  lastY = y;

  glm::vec3 direction;
  direction.x =
      static_cast<float>(cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)));
  direction.y = static_cast<float>(sin(glm::radians(m_pitch)));
  direction.z =
      static_cast<float>(sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)));
  m_front = glm::normalize(direction);

  updateView();
}

} // namespace ndr::render
