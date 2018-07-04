#ifndef VIM_POWER_MODE_WINDOW_HPP
#define VIM_POWER_MODE_WINDOW_HPP

namespace VPM
{
  constexpr unsigned int WINDOW_COUNT = 4;

  class Window
  {
    public:
      static bool m_isClosed;

    public:
      Window();
      ~Window();

    public:
      void updatePos();
      bool getIsClosed() const;
  };
}

#endif

