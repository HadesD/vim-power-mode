#ifndef VIM_POWER_MODE_WINDOW_HPP
#define VIM_POWER_MODE_WINDOW_HPP

namespace VPM
{
  constexpr unsigned int WINDOW_COUNT = 15;

  class Window
  {
    public:
      Window(
        unsigned int width, unsigned int height,
        unsigned int x, unsigned int y
        );
      ~Window();

    public:
      void updatePos();
      void setBackgroundColor(unsigned long rgb);
  };
}

#endif

