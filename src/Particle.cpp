#include "vpm/Particle.hpp"

#include "vpm/Window.hpp"

#include <iostream>
#include <thread>
#include <ctime>

namespace VPM
{
  Particle::Particle()
  {
    std::srand(std::time(nullptr));

    m_window = new Window();

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
}

