#include <X11/Xlib.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[])
{
  Display *display = XOpenDisplay(nullptr);
  if (!display)
  {
    return 1;
  }

  XSetWindowAttributes attribs;

  attribs.override_redirect = 1;
  attribs.background_pixel = 0x80808080;
  // attribs.win_gravity = CenterGravity;

  Window window = XCreateWindow(
    display,
    RootWindow(display, 0),
    0, 0,
    10, 10,
    0,
    CopyFromParent, CopyFromParent, CopyFromParent, CWOverrideRedirect,
    &attribs
    );

  XSetWindowBackground(display, window, 0x000000);

  XMoveWindow(display, window, 20, 20);

  XClearWindow(display, window);

  XMapWindow(display, window);
  XFlush(display);

  std::cin.get();
  // sleep(2);

  XUnmapWindow(display, window);
  XFlush(display);
  XCloseDisplay(display);

  return 0;
}

