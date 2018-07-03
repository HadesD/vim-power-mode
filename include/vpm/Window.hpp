#ifndef VIM_POWER_MODE_WINDOW_HPP
#define VIM_POWER_MODE_WINDOW_HPP

namespace VPM
{
  constexpr unsigned int WINDOW_COUNT = 4;

  class Window
  {
    public:
      Window(
        unsigned int width, unsigned int height,
        unsigned int x, unsigned int y
        );
      ~Window();

    public:
      void move(unsigned int x, unsigned int y);
      void setBackgroundColor(unsigned long rgb);
  };
}

#endif

