#include <iostream>
#include <cstring>

#include "vpm/Particle.hpp"
#include "vpm/Config.hpp"

int main(int argc, char* argv[])
{
  if (argc > 1)
  {
    std::sscanf(
      argv[1], "%d,%d,%d,%d,%d",
      &VPM::Config::vimwnd,
      &VPM::Config::x,
      &VPM::Config::y,
      &VPM::Config::columns,
      &VPM::Config::lines
      );
  }
  VPM::Particle particle;

  return 0;
}

