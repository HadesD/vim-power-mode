#include "vim_power_mode/Particle.hpp"

Particle::Particle()
{
}

void Particle::setPosition(const unsigned int x, const unsigned int y)
{
  // TODO: Move window
}

unsigned long Particle::getHexColor() const
{
  return m_r << 16 | m_g << 8 | m_b;
}

