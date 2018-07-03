#include "vpm/Window.hpp"

namespace VPM
{
  bool Window::m_isClosed = false;

  bool Window::getIsClosed() const
  {
    return m_isClosed;
  }
}

