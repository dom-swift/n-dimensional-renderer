#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

namespace ndr::render {

class Camera {
public:
  using ViewCallback = std::function<void(glm::mat4)>;

  Camera(glm::vec3 pos);

  Camera() = delete;

  glm::mat4 view();
  void setViewCallback(ViewCallback callback);

private:
  glm::vec3 m_pos;
  glm::vec3 m_front;
  glm::vec3 m_up;

  ViewCallback m_viewCallback;
};

} // namespace ndr::render
