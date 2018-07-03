#include "vpm/Window.hpp"

#include <X11/Xlib.h>
#include <unistd.h>

#include <iostream>
#include <ctime>
#include <array>

Display *display;

struct Windows
{
  Window hwnd;
  unsigned int x;
  unsigned int y;
  unsigned int dx;
  unsigned int dy;
  unsigned long rgb;
};

Windows windows[VPM::WINDOW_COUNT];

namespace VPM
{
  Window::Window(
    unsigned int width, unsigned int height,
    int x, int y
    )
  {
    std::srand(std::time(nullptr));

    display = XOpenDisplay(nullptr);

    XSetWindowAttributes attrs;
    attrs.override_redirect = 1;

    for (auto& window : windows)
    {
      // Shuffle
      window.x = x;
      window.y = y;
      window.dx = (std::rand() % 10) - 5;
      window.dy = -10 - (std::rand() % 10);

      window.hwnd = XCreateWindow(
        display,
        RootWindow(display, 0),
        window.x, window.y,
        width, height,
        0,
        CopyFromParent, CopyFromParent, CopyFromParent, CWOverrideRedirect,
        &attrs
        );
      XMapWindow(display, window.hwnd);
    }
  }

  Window::~Window()
  {
    // TODO: remove this
    std::cin.get();

    XFlush(display);
    XCloseDisplay(display);
  }

  void Window::updatePos()
  {
    for (auto& window : windows)
    {
      window.x += window.dx;
      window.y += window.dy;
      window.dy += 2;
      XMoveWindow(display, window.hwnd, window.x, window.y);
      XSetWindowBackground(display, window.hwnd, window.rgb);
      XClearWindow(display, window.hwnd);
      if (window.dy >= 30)
      {
        m_closedCount++;
        XUnmapWindow(display, window.hwnd);
      }
    }
    XFlush(display);
  }

  void Window::setBackgroundColor(unsigned long rgb)
  {
    for (auto& window : windows)
    {
      window.rgb = rgb;
      XSetWindowBackground(display, window.hwnd, window.rgb);
      XClearWindow(display, window.hwnd);
    }
    XFlush(display);
  }

  bool Window::isClosed() const
  {
    return m_closedCount == sizeof(windows);
  }
}

