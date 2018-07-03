#include "vpm/Particle.hpp"

#include "vpm/Window.hpp"

namespace VPM
{
  Particle::Particle()
  {
    m_r = 0xFF;
    m_g = 0xFF;
    m_b = 0xFF;

    m_window = new Window(10, 10, 0, 0);
    m_window->setBackgroundColor(this->getHexColor());

    // TODO: Loop this
    m_window->updatePos();
  }

  Particle::~Particle()
  {
    delete m_window;
  }

  unsigned long Particle::getHexColor() const
  {
    return m_r << 16 | m_g << 8 | m_b;
  }
}

