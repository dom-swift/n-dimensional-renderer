#pragma once

#include <string_view>

namespace ndr::render {

class ShaderProgram {
public:
  ShaderProgram(std::string_view vertexSource, std::string_view fragmentSource,
                std::string_view vertexName = "vertex shader",
                std::string_view fragmentName = "fragment shader");
  ~ShaderProgram();

  ShaderProgram(const ShaderProgram &) = delete;
  ShaderProgram &operator=(const ShaderProgram &) = delete;

  void use() const;

private:
  unsigned int m_program = 0;
};

} // namespace ndr::render
