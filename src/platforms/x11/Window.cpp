#include "vpm/Window.hpp"

#include "vpm/Config.hpp"

#include <X11/Xlib.h>
#include <unistd.h>

#include <iostream>
#include <array>

Display *display;

struct Wnd
{
  Window hwnd;
  int x;
  int y;
  int dx;
  int dy;
  unsigned long rgb;
};

Wnd windows[VPM::WINDOW_COUNT];

namespace VPM
{
  Window::Window()
  {
    display = XOpenDisplay(nullptr);

    XSetWindowAttributes attrs;
    attrs.override_redirect = 1;

    for (auto& window : windows)
    {
      window.x = Config::x;
      window.y = Config::y;

      // Shuffle
      window.dx = (std::rand() % 10) - 5;
      window.dy = -5 - (std::rand() % 10);

      window.hwnd = XCreateWindow(
        display,
        RootWindow(display, 0),
        window.x, window.y,
        Config::width, Config::height,
        0,
        CopyFromParent, CopyFromParent, CopyFromParent, CWOverrideRedirect,
        &attrs
        );
      XSetWindowBackground(
        display, window.hwnd,
        Config::r << 16 | Config::g << 8 | Config::b
        );
      XClearWindow(display, window.hwnd);
      XMapWindow(display, window.hwnd);
    }
  }

  Window::~Window()
  {
    XFlush(display);
    XCloseDisplay(display);
  }

  void Window::updatePos()
  {
    for (auto& window : windows)
    {
      window.x += window.dx;
      window.y += window.dy;
      window.dy += 1;
      XMoveWindow(display, window.hwnd, window.x, window.y);
      if (window.dy >= 20)
      {
        m_isClosed = true;
        break;
      }
    }
    XFlush(display);
  }
}

