#include "ndr/platform/Paths.hpp"

#include <cstdint>
#include <stdexcept>
#include <system_error>
#include <vector>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

namespace ndr::platform {

std::filesystem::path executableDirectory() {
#if defined(_WIN32)
  std::vector<wchar_t> buffer(256);

  while (true) {
    const auto length = GetModuleFileNameW(nullptr, buffer.data(),
                                           static_cast<DWORD>(buffer.size()));
    if (length == 0) {
      throw std::system_error(static_cast<int>(GetLastError()),
                              std::system_category(),
                              "Failed to locate the executable");
    }

    if (length < buffer.size()) {
      return std::filesystem::path(buffer.data(), buffer.data() + length)
          .parent_path();
    }

    buffer.resize(buffer.size() * 2);
  }
#elif defined(__linux__)
  std::error_code error;
  const auto executable =
      std::filesystem::read_symlink("/proc/self/exe", error);
  if (error) {
    throw std::filesystem::filesystem_error("Failed to locate the executable",
                                            "/proc/self/exe", error);
  }

  return executable.parent_path();
#elif defined(__APPLE__)
  std::uint32_t size = 0;
  _NSGetExecutablePath(nullptr, &size);

  std::vector<char> buffer(size);
  if (_NSGetExecutablePath(buffer.data(), &size) != 0) {
    throw std::runtime_error("Failed to locate the executable");
  }

  return std::filesystem::weakly_canonical(buffer.data()).parent_path();
#else
#error "Executable path discovery is not implemented for this platform"
#endif
}

} // namespace ndr::platform
