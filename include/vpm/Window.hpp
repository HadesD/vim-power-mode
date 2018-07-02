#ifndef VIM_POWER_MODE_WINDOW_HPP
#define VIM_POWER_MODE_WINDOW_HPP

namespace VPM
{
  class Window
  {
    public:
      Window(
        const unsigned int width, const unsigned int height,
        const unsigned int x, const unsigned int y
        );
      ~Window();

    public:
      void move(const unsigned int x, const unsigned int y);
  };
}

#endif

