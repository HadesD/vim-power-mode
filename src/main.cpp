#include <iostream>
#include <cstring>

#include "vpm/Particle.hpp"
#include "vpm/Config.hpp"

int main(int argc, char* argv[])
{
  if (argc >= 2)
  {
    std::sscanf(
      argv[1], "%d,%d,%d,%d,%d",
      &VPM::Config::vimwnd,
      &VPM::Config::x,
      &VPM::Config::y,
      &VPM::Config::columns,
      &VPM::Config::lines
      );
    if (argc >= 3)
    {
      std::sscanf(
        argv[2], "%02x%02x%02x",
        &VPM::Config::r,
        &VPM::Config::g,
        &VPM::Config::b
        );
    }
  }

  VPM::Particle particle;

  return 0;
}

