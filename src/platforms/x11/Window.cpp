#include "vpm/Window.hpp"

#include <X11/Xlib.h>
#include <unistd.h>
#include <iostream>

Display *display;
Window window;

namespace VPM
{
  Window::Window(
    const unsigned int width, const unsigned int height,
    const unsigned int x, const unsigned int y
    )
  {
    display = XOpenDisplay(nullptr);

    XSetWindowAttributes attrs;
    attrs.override_redirect = 1;

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

  Window::~Window()
  {
    // TODO: remove this
    std::cin.get();

    XUnmapWindow(display, window);
    XFlush(display);
    XCloseDisplay(display);
  }

  void Window::move(const unsigned int x, const unsigned int y)
  {
    XMoveWindow(display, window, x, y);
  }

  void Window::setBackgroundColor(const unsigned long rgb)
  {
    XSetWindowBackground(display, window, rgb);
    XClearWindow(display, window);
    XFlush(display);
  }
}

