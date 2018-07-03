#include "vpm/Window.hpp"

#include <Windows.h>

#include <iostream>
#include <string>
#include <ctime>

struct Wnd
{
  HWND hwnd;
  int x;
  int y;
  int dx;
  int dy;
};

Wnd windows[VPM::WINDOW_COUNT];

namespace VPM
{
  HBRUSH hb = nullptr;

  LRESULT CALLBACK WindowProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
    )
  {
    HDC hdc = nullptr;
    RECT rc = {0};
    PAINTSTRUCT ps;

    switch (uMsg)
    {
      case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rc);
        FillRect(hdc, &rc, hb);
        EndPaint(hwnd, &ps);
        return 0;
      case WM_DESTROY:
        {
          PostQuitMessage(0);
        }
        return 0;
      default:
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }

  void CALLBACK UpdateProc(
    HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime
    )
  {
    for (auto& window : windows)
    {
      window.x += window.dx;
      window.y += window.dy;
      window.dy += 2;

      if (window.dy >= 20)
      {
        SendMessage(window.hwnd, WM_DESTROY, 0, 0);
        break;
      }
      SetWindowPos(
        window.hwnd, NULL, window.x, window.y, 0, 0,
        SWP_NOSIZE|SWP_NOZORDER|SWP_NOOWNERZORDER
        );
    }
  }

  Window::Window(
    unsigned int width, unsigned int height,
    int x, int y
    )
  {
    m_isClosed = false;

    std::srand(time(nullptr));

    POINT pt = {200, 200};
    char app[] = "Particle";

    // Window class {
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = nullptr;
    wc.hIcon = static_cast<HICON>(LoadImage(
        nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED
        ));
    wc.hCursor = static_cast<HCURSOR>(LoadImage(
        nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED
        ));
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = app;
    wc.hIconSm = static_cast<HICON>(LoadImage(
        nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED
        ));
    // }

    if (!RegisterClassEx(&wc))
    {
      m_isClosed = true;
      return;
    }

    for (auto& window : windows)
    {
      window.x = x;
      window.y = y;

      // Shuffle
      window.dx = (std::rand() % 10) - 5;
      window.dy = -5 - (std::rand() % 10);

      window.hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_NOACTIVATE,
        app, app, WS_POPUP,
        window.x, window.y, width, height,
        nullptr, nullptr, nullptr, nullptr
        );
      if (!window.hwnd)
      {
        m_isClosed = true;
        return;
      }
      SetLayeredWindowAttributes(
        window.hwnd, RGB(0xFF, 0xFF, 0xFF), 70, LWA_ALPHA
        );

      HRGN hrgn = CreateEllipticRgn(0, 0, 10, 10);
      if (hrgn)
      {
        SetWindowRgn(window.hwnd, hrgn, true);
      }
      ShowWindow(window.hwnd, false);
      UpdateWindow(window.hwnd);
    }

    SetTimer(nullptr, 0, 1, UpdateProc);
  }

  Window::~Window()
  {
    for (auto& window : windows)
    {
      DestroyWindow(window.hwnd);
    }
  }

  MSG msg;
  void Window::updatePos()
  {
    std::cout << msg.message << std::endl;
    std::cout << "Destroy: " << WM_DESTROY << std::endl;
    std::cout << "Close: " << WM_CLOSE << std::endl;
    if (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
      if (msg.message == WM_DESTROY)
      {
        std::cout << "Closing" << std::endl;
        m_isClosed = true;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  void Window::setBackgroundColor(unsigned long rgb)
  {
    hb = CreateSolidBrush(rgb);
  }
}

