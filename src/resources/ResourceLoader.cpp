#include "ndr/resources/ResourceLoader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace ndr::resources {

ResourceLoader::ResourceLoader(std::filesystem::path root)
    : m_root(std::move(root)) {
  if (m_root.empty()) {
    throw std::invalid_argument("Resource root cannot be empty");
  }
}

std::filesystem::path
ResourceLoader::resolve(const std::filesystem::path &relativePath) const {
  if (relativePath.empty() || relativePath.is_absolute()) {
    throw std::invalid_argument(
        "Resource paths must be non-empty and relative");
  }

  const auto normalized = relativePath.lexically_normal();
  if (*normalized.begin() == "..") {
    throw std::invalid_argument("Resource path escapes the resource root: " +
                                relativePath.string());
  }

  return m_root / normalized;
}

std::string
ResourceLoader::loadText(const std::filesystem::path &relativePath) const {
  const auto path = resolve(relativePath);
  std::ifstream stream(path, std::ios::binary);
  if (!stream.is_open()) {
    throw std::runtime_error("Failed to open resource: " + path.string());
  }

  std::ostringstream contents;
  contents << stream.rdbuf();
  if (stream.bad()) {
    throw std::runtime_error("Failed to read resource: " + path.string());
  }

  return contents.str();
}

} // namespace ndr::resources
