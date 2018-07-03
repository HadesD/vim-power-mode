#include "vpm/Window.hpp"

#include <X11/Xlib.h>

#include <unistd.h>
#include <iostream>
#include <array>

Display *display;
Window windows[VPM::WINDOW_COUNT];

namespace VPM
{
  Window::Window(
    unsigned int width, unsigned int height,
    unsigned int x, unsigned int y
    )
  {
    display = XOpenDisplay(nullptr);

    XSetWindowAttributes attrs;
    attrs.override_redirect = 1;

    for (auto& window : windows)
    {
      window = XCreateWindow(
        display,
        RootWindow(display, 0),
        x, y,
        width, height,
        0,
        CopyFromParent, CopyFromParent, CopyFromParent, CWOverrideRedirect,
        &attrs
        );
      XMapWindow(display, window);
    }
  }

  Window::~Window()
  {
    // TODO: remove this
    std::cin.get();

    for (const auto& window : windows)
    {
      XUnmapWindow(display, window);
    }

    XFlush(display);
    XCloseDisplay(display);
  }

  void Window::move(unsigned int x, unsigned int y)
  {
    for (const auto& window : windows)
    {
      XMoveWindow(display, window, x, y);
    }
    XFlush(display);
  }

  void Window::setBackgroundColor(unsigned long rgb)
  {
    for (const auto& window : windows)
    {
      XSetWindowBackground(display, window, rgb);
      XClearWindow(display, window);
    }
    XFlush(display);
  }
}

