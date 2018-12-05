
// If we assume that this application will be ported to multiple platforms,
// where does the platform switch go? Here? Rendering is platform dependent
// but the game does not actually need the renderer to run

#include "mach/application.hpp"

int main(int argc, char* argv[])
{
  mach::Application l_application{ argc , argv };
  return l_application.execute();
}