#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

namespace ndr::render {

class Camera {
public:
  using ViewCallback = std::function<void(glm::mat4)>;

  Camera(glm::vec3 pos, float speed, float sensitivity);

  Camera() = delete;

  glm::mat4 view();

  // Set the callback that is called when camera moves or turns
  // Therefore, updating the view
  //
  // callback: function that takes a glm::mat4 and returns void
  void setViewCallback(ViewCallback callback);

  // Literally just calls the callback
  // Automatically called in camera movement functions !!
  void updateView();

  // Moves camera along its forward vector
  // Use negative deltaTime to move backwards
  void moveForward(double deltaTime);

  // Moves camera along its right vector
  // Use negative deltaTime to move left
  void moveRight(double deltaTime);

  // Turns the camera using the given x and y mouse inputs
  void turn(double x, double y);

private:
  glm::vec3 m_pos;
  glm::vec3 m_front;
  glm::vec3 m_up;

  double m_yaw;
  double m_pitch;

  float m_speed;
  float m_sensitivity;

  ViewCallback m_viewCallback;
};

} // namespace ndr::render
