#include "ndr/app/Application.hpp"

int main() {
  int out;

  ndr::Application app;
  out = app.Run();
  app.Shutdown();

  return out;
}
