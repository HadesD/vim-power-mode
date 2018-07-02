#include "vim_power_mode/Window.hpp"

#include <X11/Xlib.h>
#include <unistd.h>

Display *display;
Window window;

namespace VPM
{
  Window::Window()
  {
    display = XOpenDisplay(nullptr);

    XSetWindowAttributes attribs;
    attribs.override_redirect = 1;
    attribs.background_pixel = 0x80808080;

    window = XCreateWindow(
      display,
      RootWindow(display, 0),
      0, 0,
      10, 10,
      0,
      CopyFromParent, CopyFromParent, CopyFromParent, CWOverrideRedirect,
      &attribs
      );

    // TODO: fix this

    XSetWindowBackground(display, window, 0x000000);

    XMoveWindow(display, window, 20, 20);

    XClearWindow(display, window);

    XMapWindow(display, window);
    XFlush(display);
  }

  Window::~Window()
  {
    XUnmapWindow(display, window);
    XFlush(display);
    XCloseDisplay(display);
  }
}
