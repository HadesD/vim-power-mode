#include <stdio.h>
#include <X11/Xlib.h>

int main(int argc, char *argv[])
{
    Display *display = nullptr;
    Window window;
    XSetWindowAttributes attribs;

    display = XOpenDisplay(nullptr);
    if (!display)
    {
        printf( "Cannot to open display." );
        return 1;
    }

    attribs.override_redirect = 1;

    window = XCreateWindow(
      display,
      RootWindow(display, 0),
      20, 20,
      10, 10,
      0,
      CopyFromParent, CopyFromParent, CopyFromParent, CWOverrideRedirect,
      &attribs
      );

    XSetWindowBackground( display, window, 0x00F0FF );
    XClearWindow(display, window);

    XMapWindow(display, window);
    XFlush(display);

    getchar();

    return 0;
}

