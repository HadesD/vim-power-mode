#include "vim_power_mode/Particle.hpp"

Particle::Particle()
{

}

void Particle::setPosition(int x, int y)
{

}

unsigned long Particle::getHexColor() const
{
  return m_r << 16 | m_g << 8 | m_b;
}

