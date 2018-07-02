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

    XSetWindowAttributes attribs;
    attribs.override_redirect = 1;
    attribs.background_pixel = 0x80808080;

    window = XCreateWindow(
      display,
      RootWindow(display, 0),
      x, y,
      width, height,
      0,
      CopyFromParent, CopyFromParent, CopyFromParent, CWOverrideRedirect,
      &attribs
      );

    // TODO: fix this

    XSetWindowBackground(display, window, 0x000000);

    XClearWindow(display, window);

    XMapWindow(display, window);
    XFlush(display);
  }

  Window::~Window()
  {
    std::cin.get();
    XUnmapWindow(display, window);
    XFlush(display);
    XCloseDisplay(display);
  }

  void Window::move(const unsigned int x, const unsigned int y)
  {
    XMoveWindow(display, window, 20, 20);
  }
}
