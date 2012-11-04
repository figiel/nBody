//--------------------------------------------------------------------------
//
// nBody -v1.0
//
// Copyright (c) 2012, Mariusz Moczala and Tomasz Stachowiak
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// - Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the distribution.
// - Neither the name of the copyright holders nor the names of its
//   contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT
// HOLDERS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------

#include <windows.h>
#include <gl\gl.h>
#include "..\..\Skeleton\Skeleton.h"


//--------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------

// Window specific variables
volatile bool IsRunning;

// OpenGL interface variables
static HDC DC;
static HGLRC RC;


//--------------------------------------------------------------------------
// OpenGL initialization
//--------------------------------------------------------------------------

void OpenGLInit(HWND hWnd)
{
  // Prepare Przygotowujemy strukture opisujaca sposób wyswietlania
  static PIXELFORMATDESCRIPTOR _pfd = {
    sizeof(PIXELFORMATDESCRIPTOR), 1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 0,
    PFD_MAIN_PLANE, 0, 0, 0
  };

  // Set display format for current display context
  DC = GetDC(hWnd);
  int FormatIndex = ChoosePixelFormat(DC, &_pfd);
  SetPixelFormat(DC, FormatIndex, &_pfd);

  // Create display context for OpenGL
  RC = wglCreateContext(DC);
  wglMakeCurrent(DC, RC);
}


//--------------------------------------------------------------------------
// OpenGL deinitialization
//--------------------------------------------------------------------------

void OpenGLDeinit(HWND hWnd)
{
  // Deinitialize OpenGL
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(RC);
  ReleaseDC(hWnd, DC);
}


//--------------------------------------------------------------------------
// Windows message process loop
//--------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  PRECT WndSize;

  // Proces windows messages
  switch(Msg)
  {
    // Window show
    case WM_SHOWWINDOW:
      OpenGLInit(hWnd);
      CSkeleton::PostInit();
      IsRunning = true;
      return DefWindowProc(hWnd, Msg, wParam, lParam);

    // Window resize
    case WM_SIZING:
      WndSize = (PRECT) lParam;
      CSkeleton::Resize(WndSize->right - WndSize->left,
        WndSize->bottom - WndSize->top);
      return DefWindowProc(hWnd, Msg, wParam, lParam);

    // Window close
    case WM_CLOSE:
      IsRunning = false;
      CSkeleton::PreDeinit();
      OpenGLDeinit(hWnd);
      DestroyWindow(hWnd);
      return 0;

    // Window destroy
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    // Process all messages by default window procedure
    default:
      return DefWindowProc(hWnd, Msg, wParam, lParam);
  }
}


//--------------------------------------------------------------------------
// Software entry point
//--------------------------------------------------------------------------

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  // Initialize global variables
  IsRunning = false;

  // Execute pre-initialization function
  CSkeleton::PreInit();

  // Window class configuration
  WNDCLASSEX wc;
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = 0;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = TEXT("nBodyWindowClass");
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  // Register the window class
  if(!RegisterClassEx(&wc))
  {
    MessageBox(NULL, TEXT("Window registration failed!"),
      TEXT("nBody -v1.0"), MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  // Create the window
  HWND hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("nBodyWindowClass"),
    TEXT("nBody -v1.0"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
    CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
  if(hWnd == NULL)
  {
    MessageBox(NULL, TEXT("Window creation failed!"),
      TEXT("nBody -v1.0"), MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  // Show window
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  // Process messages
  MSG Msg;
  while(true)
  {
    // Execute code in idle
    if(IsRunning)
    {
      bool Repeat = false;
      switch(CSkeleton::Run())
      {
        // Exit application
        case CSkeleton::rmExit:
          SendMessage(hWnd, WM_CLOSE, NULL, NULL);
          break;

        // Repet without processing any massages
        case CSkeleton::rmRepeat:
          Repeat = true;
          break;

        // Process all messages and continue execution
        case CSkeleton::rmContinue:
          break;

        // Wait for messages and then continue
        case CSkeleton::rmGoForIdle:
          WaitMessage();
          break;
      }

      if(Repeat)
        continue;

      // Swap graphics
      SwapBuffers(DC);
    }

    // Process all available messages
    if(GetQueueStatus(QS_ALLINPUT))
    {
      while(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE));
      {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
      }

      // Terminate application
      if(Msg.message == WM_QUIT)
        break;
    }
  }

  // Execute post-deinitialization function
  CSkeleton::PostDeinit();

  // Return the application termination result
  return (int) Msg.wParam;
}


//--------------------------------------------------------------------------
