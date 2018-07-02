#include "vpm/Particle.hpp"

#include "vpm/Window.hpp"

namespace VPM
{
  Particle::Particle()
  {
    m_window = new Window(10, 10, 0, 0);
  }

  Particle::~Particle()
  {
    delete m_window;
  }

  void Particle::setPosition(const unsigned int x, const unsigned int y)
  {
    m_window->move(x, y);
  }

  unsigned long Particle::getHexColor() const
  {
    return m_r << 16 | m_g << 8 | m_b;
  }
}
