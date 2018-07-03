#include "vpm/Particle.hpp"

#include "vpm/Window.hpp"

#include <iostream>
#include <thread>

namespace VPM
{
  Particle::Particle()
  {
    m_r = 0xFF;
    m_g = 0xFF;
    m_b = 0xFF;

    m_window = new Window(10, 10, 100, 100);
    m_window->setBackgroundColor(this->getHexColor());

    // TODO: Loop this
    while (!m_window->getIsClosed())
    {
      m_window->updatePos();
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
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

