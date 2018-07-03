#ifndef VIM_POWER_MODE_WINDOW_HPP
#define VIM_POWER_MODE_WINDOW_HPP

namespace VPM
{
  constexpr unsigned int WINDOW_COUNT = 20;

  class Window
  {
    private:
      unsigned int m_closedCount;

    public:
      Window(
        unsigned int width, unsigned int height,
        int x, int y
        );
      ~Window();

    public:
      void updatePos();
      void setBackgroundColor(unsigned long rgb);
      bool isClosed() const;
  };
}

#endif

