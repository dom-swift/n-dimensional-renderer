#pragma once

#include <filesystem>

namespace ndr::platform {

[[nodiscard]] std::filesystem::path executableDirectory();

} // namespace ndr::platform
