#include "ndr/app/Application.hpp"
#include "ndr/platform/Paths.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

int main() {
  try {
    const auto resourceRoot =
        ndr::platform::executableDirectory() / "resources";
    ndr::Application app(resourceRoot);
    return app.run();
  } catch (const std::exception &exception) {
    std::cerr << "Fatal error: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }
}
