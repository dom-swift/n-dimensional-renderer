#include "ndr/render/ShaderProgram.hpp"

#include <glad/gl.h>

#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>

namespace ndr::render {
namespace {

std::string shaderLog(unsigned int shader) {
  int length = 0;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

  std::string log(static_cast<std::size_t>(length), '\0');
  int written = 0;
  glGetShaderInfoLog(shader, length, &written, log.data());
  log.resize(static_cast<std::size_t>(written));
  return log;
}

std::string programLog(unsigned int program) {
  int length = 0;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

  std::string log(static_cast<std::size_t>(length), '\0');
  int written = 0;
  glGetProgramInfoLog(program, length, &written, log.data());
  log.resize(static_cast<std::size_t>(written));
  return log;
}

unsigned int compileShader(unsigned int type, std::string_view source,
                           std::string_view name) {
  if (source.size() >
      static_cast<std::size_t>(std::numeric_limits<int>::max())) {
    throw std::runtime_error("Shader source is too large: " +
                             std::string(name));
  }

  const auto shader = glCreateShader(type);
  const auto *sourceData = source.data();
  const auto sourceLength = static_cast<int>(source.size());
  glShaderSource(shader, 1, &sourceData, &sourceLength);
  glCompileShader(shader);

  int compiled = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  if (compiled == GL_TRUE) {
    return shader;
  }

  const auto log = shaderLog(shader);
  glDeleteShader(shader);
  throw std::runtime_error("Failed to compile " + std::string(name) + ":\n" +
                           log);
}

} // namespace

ShaderProgram::ShaderProgram(std::string_view vertexSource,
                             std::string_view fragmentSource,
                             std::string_view vertexName,
                             std::string_view fragmentName) {
  const auto vertexShader =
      compileShader(GL_VERTEX_SHADER, vertexSource, vertexName);

  unsigned int fragmentShader = 0;
  try {
    fragmentShader =
        compileShader(GL_FRAGMENT_SHADER, fragmentSource, fragmentName);
  } catch (...) {
    glDeleteShader(vertexShader);
    throw;
  }

  m_program = glCreateProgram();
  glAttachShader(m_program, vertexShader);
  glAttachShader(m_program, fragmentShader);
  glLinkProgram(m_program);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  int linked = GL_FALSE;
  glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
  if (linked == GL_TRUE) {
    return;
  }

  const auto log = programLog(m_program);
  glDeleteProgram(m_program);
  m_program = 0;
  throw std::runtime_error("Failed to link shader program:\n" + log);
}

ShaderProgram::~ShaderProgram() { glDeleteProgram(m_program); }

void ShaderProgram::use() const { glUseProgram(m_program); }

void ShaderProgram::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(m_program, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}

} // namespace ndr::render
