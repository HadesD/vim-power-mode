#include "vpm/Window.hpp"

#include "vpm/Config.hpp"

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
  HDC hdc = nullptr;
  RECT rc = {0};
  PAINTSTRUCT ps;
  LRESULT CALLBACK WindowProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
    )
  {
    switch (uMsg)
    {
      case WM_PAINT:
        {
          hdc = BeginPaint(hwnd, &ps);
          GetClientRect(hwnd, &rc);
          FillRect(hdc, &rc, hb);
          EndPaint(hwnd, &ps);
        }
        break;
      case WM_DESTROY:
        {
          PostQuitMessage(0);
          Window::m_isClosed = true;
        }
        break;
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
      window.dy += 1;

      if (window.dy >= 20)
      {
        SendMessage(window.hwnd, WM_DESTROY, 0, 0);
        break;
      }
      SetWindowPos(
        window.hwnd, nullptr, window.x, window.y, 0, 0,
        SWP_NOSIZE|SWP_NOZORDER|SWP_NOOWNERZORDER
        );
    }
  }

  Window::Window()
  {
    POINT pt = {200, 200};
    char app[] = "Particle";

    // Window class {
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = ::GetModuleHandle(nullptr);
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

    hb = CreateSolidBrush(RGB(Config::r, Config::g, Config::b));
    for (auto& window : windows)
    {
      window.x = Config::x;
      window.y = Config::y;

      // Shuffle
      window.dx = (std::rand() % 10) - 5;
      window.dy = -5 - (std::rand() % 10);

      window.hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_NOACTIVATE,
        app, app, WS_POPUP,
        window.x, window.y, Config::width, Config::height,
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
        SetWindowRgn(window.hwnd, hrgn, 0);
      }

      ShowWindow(window.hwnd, 1);
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
    if (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
      // TODO: Catch VM_DESTROY here

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}

