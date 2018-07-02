#include <X11/Xlib.h>
#include <iostream>

int main(int argc, char *argv[])
{
  Display *display = nullptr;
  Window window;
  XSetWindowAttributes attribs;

  display = XOpenDisplay(nullptr);
  if (!display)
  {
    std::cerr << "Can not create window" << std::endl;
    return 1;
  }

  attribs.override_redirect = 1;
  attribs.background_pixel = 0x80808080;
  // attribs.win_gravity = CenterGravity;

  window = XCreateWindow(
    display,
    RootWindow(display, 0),
    0, 0,
    10, 10,
    0,
    CopyFromParent, CopyFromParent, CopyFromParent, CWOverrideRedirect,
    &attribs
    );

  XSetWindowBackground(display, window, 0x000000);

  XMoveWindow(display, window, 20, 30);

  XClearWindow(display, window);

  XMapWindow(display, window);
  XFlush(display);

  std::cin.get();

  return 0;
}

