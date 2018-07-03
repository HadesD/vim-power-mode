#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "Shell32.lib")
#undef __STRICT_ANSI__
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cwchar>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#ifndef DEBUG
#  define DEBUG
static std::string catched;
#endif
#undef DEBUG

struct Particle
{
  HWND hwnd;
  int x;
  int y;
  int dx;
  int dy;
};

static std::vector<Particle> p(4, {NULL, 0, 0, 0, 0});
static HBRUSH hb = NULL;

LRESULT CALLBACK WindowProc(
  HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
  )
{
  HDC hdc = NULL;
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
  for (std::size_t i = 0; i < p.size(); i++)
  {
    p[i].x += p[i].dx;
    p[i].y += p[i].dy;
    p[i].dy += 2;
    if (p[i].dy >= 30)
    {
      DestroyWindow(p[i].hwnd);
      break;
    }
    SetWindowPos(
      p[i].hwnd, NULL, p[i].x, p[i].y, 0, 0,
      SWP_NOSIZE|SWP_NOZORDER|SWP_NOOWNERZORDER
      );
  }
}

int WINAPI WinMain(
  HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpszCmdLine, int nCmdShow
  )
{
  TCHAR app[] = TEXT("particle");
  MSG msg;
  WNDCLASSEX wc;
  int argc;
  LPWSTR *argv;
  int r = 0xff, g = 0xff, b = 0xff;
  RECT rc = {0};
  POINT pt = {200, 200};
  HWND hwnd = NULL;
  int w = 0, h = 0;
  wchar_t *pos = NULL;
  HRGN hrgn = NULL;

  std::srand(time(nullptr));

  argv = CommandLineToArgvW(GetCommandLineW(), &argc);

  if (argc >= 2)
  {
    pos = wcschr(argv[1], ',');
    if (pos) *pos++ = 0;
    // hwnd = reinterpret_cast<HWND>(argv[1]);
    hwnd = (HWND) _wtoi64(argv[1]);
  }
  if (hwnd == NULL) hwnd = GetForegroundWindow();

  if (pos && swscanf(pos, L"%d,%d,%d,%d", &pt.x, &pt.y, &w, &h) == 4)
  {
    GetWindowRect(hwnd, &rc);
    pt.x = (rc.right - rc.left) / w * pt.x;
    pt.y = (rc.bottom - rc.top) / h * pt.y;
    ClientToScreen(hwnd, &pt);
    // MessageBox(NULL, std::to_string(argv[1]).c_str(), std::to_string(pt.y).c_str(), 0);
  }
  else
  {
    if (GetWindowRect(hwnd, &rc))
    {
      pt.x = (rc.left + rc.right) / 2 + rand() % 200 - 100;
      pt.y = (rc.top + rc.bottom) / 2 + rand() % 200 - 100;
      ClientToScreen(hwnd, &pt);
    }
  }

  if (argc >= 3)
  {
    swscanf(argv[2], L"%02x%02x%02x", &r, &g, &b);
  }
  else
  {
    r = rand() % 256;
    g = rand() % 256;
    b = rand() % 256;
  }

  wc.cbSize        = sizeof(WNDCLASSEX);
  wc.style         = 0;
  wc.lpfnWndProc   = WindowProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hinst;
  wc.hIcon         = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED);
  wc.hCursor       = (HCURSOR)LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = app;
  wc.hIconSm       = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED);
  try
  {
    if (!RegisterClassEx(&wc))
    {
      throw std::runtime_error("Can't register class");
    }
    if (p.size() <= 0)
    {
      throw std::runtime_error("Vector p empty");
    }

    hb = CreateSolidBrush(RGB(r, g, b));
    for (std::size_t i = 0; i < p.size(); i++)
    {
      p[i].hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_NOACTIVATE,
        app, app, WS_POPUP,
        CW_USEDEFAULT, CW_USEDEFAULT, 10, 10,
        // 1009, 1009, 10000, 1000,
        NULL, NULL, hinst, NULL
        );
      if (p[i].hwnd == NULL)
      {
        throw std::runtime_error("Window not found");
      }
      SetLayeredWindowAttributes(p[i].hwnd, RGB(0xFF, 0xFF, 0xFF), 70, LWA_ALPHA);

      p[i].x = pt.x;
      p[i].y = pt.y;
      p[i].dx = (rand() % 10) - 5;
      p[i].dy = -10 - (rand() % 10);

      hrgn = CreateEllipticRgn(0, 0, 10, 10);
      if (hrgn != NULL)
      {
        SetWindowRgn(p[i].hwnd, hrgn, TRUE);
      }
      ShowWindow(p[i].hwnd, nCmdShow);
      UpdateWindow(p[i].hwnd);
    }
    SetTimer(NULL, 0, 1, UpdateProc);
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
#ifdef DEBUG
  catch (std::exception &e)
  {
    catched = e.what();
  }
#endif
  catch (...)
  {
#ifdef DEBUG
    catched = "Error not found";
#endif
  }

#ifdef DEBUG
  if (!catched.empty())
  {
    MessageBox(NULL, catched.c_str(), "ERROR", 0);
  }
#endif

  if (argv)
  {
    LocalFree(argv);
  }

  return 0;
}

/* vim:set et sw=2: */

