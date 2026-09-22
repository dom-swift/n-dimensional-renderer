#pragma once

#include <filesystem>
#include <string>

namespace ndr::resources {

class ResourceLoader {
public:
  explicit ResourceLoader(std::filesystem::path root);

  [[nodiscard]] const std::filesystem::path &root() const noexcept;
  [[nodiscard]] std::filesystem::path
  resolve(const std::filesystem::path &relativePath) const;
  [[nodiscard]] std::string
  loadText(const std::filesystem::path &relativePath) const;

private:
  std::filesystem::path m_root;
};

} // namespace ndr::resources
