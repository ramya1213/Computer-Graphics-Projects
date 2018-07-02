#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <sudoku.h>
#include <iostream>
#include <fstream>
GLuint base; // used for font

HGLRC hRC = NULL;  // rendering context
HDC   hDC = NULL;  // Device context
HWND  hWnd = NULL; // Handle for window
HINSTANCE hInstance;  // Instance of Program 
bool keys[256];
bool active = true;
bool fullscreen = true;
Sudoku SGame;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// props to nehe for this code
GLvoid BuildFont(GLvoid)
{
  HFONT font;
  HFONT oldfont;   // apparently good housekeeping

  base = glGenLists(96);
  font = CreateFont( -24,   // font height
                     0,     //width
                     0,     // angle of escapement ?? 
                     0,     // orientation of angle
                     FW_BOLD,   // weight
                     FALSE,     // italic
                     FALSE,     // underline
                     FALSE,     //  strikeout... baseball? ??
                     ANSI_CHARSET,  // character set identifier
                     OUT_TT_PRECIS, // output precision
                     CLIP_DEFAULT_PRECIS, // clip precision
                     ANTIALIASED_QUALITY, // output quality
                     FF_DONTCARE|DEFAULT_PITCH,
                     "Courier New");
  oldfont = (HFONT)SelectObject(hDC, font);
  wglUseFontBitmaps(hDC, 32, 96, base);
  SelectObject(hDC, oldfont);
  DeleteObject(font);
}

// props to nehe
GLvoid ShowMessage(const char *textpointer, ...)
{
  char text[256];
  va_list ap;
  
  if(textpointer == NULL)
    return;
  
  va_start(ap, textpointer);
    vsprintf(text, textpointer, ap);
  va_end(ap);

  glPushAttrib(GL_LIST_BIT);
  glListBase(base - 32);
  glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
  glPopAttrib();
}
                    
  
// props to nehe for this code
GLvoid ResizeWindow(GLsizei width, GLsizei height)
{
  if(height == 0)
    height = 1;
  glViewport(0, 0, width, height);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (GLfloat) width/(GLfloat) height, 0.1f, 1000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  SGame.LoadTextures();
}


// props to nehe for teaching this code
int InitiateGL(GLvoid)
{
  /*if(!LoadGLTextures())
  {
    MessageBox(NULL, "Failed to succesfully load Textures", "Load Error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }*/
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glEnable(GL_LIGHT1);
  BuildFont();
  return true;
}
// props to nehe for teaching this code
int RenderScene(GLvoid)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(SGame.Playing())
    SGame.Handle();
  return true;
}
// props to nehe for teaching this code
GLvoid KillGLWindow(GLvoid)
{
  if(fullscreen)
  {
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(true);
  }
  if(hRC)
  {
    if(!wglMakeCurrent(NULL, NULL))
      MessageBox(NULL, "Releasing Renderer from Device failed", "Shutdown Error!", MB_OK | MB_ICONINFORMATION);
    if(!wglDeleteContext(hRC))
      MessageBox(NULL, "Failed to release rendering context", "shutdown error", MB_OK | MB_ICONEXCLAMATION);
    hRC = NULL;
  }
  if(hDC && !ReleaseDC(hWnd, hDC))
  {
    MessageBox(NULL, "Device Not released", "shutdown error", MB_OK | MB_ICONEXCLAMATION);
    hDC = NULL;
  }
  if(hWnd && !DestroyWindow(hWnd))
  {
    MessageBox(NULL, "Cound not release handle", "shutdown error", MB_OK| MB_ICONEXCLAMATION);
    hWnd = NULL;
  }
  if(!UnregisterClass("OpenGL", hInstance))
  {
    MessageBox(NULL, "Could not unregister class", "shutdown error", MB_OK| MB_ICONEXCLAMATION);
    hInstance = NULL;
  }
  glDeleteLists(base, 96);
}
// props to nehe for teaching this code
bool InitiateWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
  GLuint PixelFormat;
  WNDCLASS wc;
  DWORD dwexstyle;
  DWORD dwstyle;
  RECT WindowRect;
  WindowRect.left = (long)0;
  WindowRect.right = (long)width;
  WindowRect.top = (long)0;
  WindowRect.bottom = (long)height;

  fullscreen = fullscreenflag;

  hInstance = GetModuleHandle(NULL);
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = (WNDPROC) WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "OpenGL";

  if(!RegisterClass(&wc))
  {
    MessageBox(NULL, "Failed to Register Window Class.", "boot error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }
  if(fullscreen)
  {
    DEVMODE dmScreenSettings;
    memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
    dmScreenSettings.dmSize = sizeof(dmScreenSettings);
    dmScreenSettings.dmPelsWidth = width;
    dmScreenSettings.dmPelsHeight = height;
    dmScreenSettings.dmBitsPerPel = bits;
    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
    
    if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
      if(MessageBox(NULL, "Fullscreen Failed. Would you like to use windowed mode?", "Initiation Failure", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
        fullscreen = false;
      else
      {
        MessageBox(NULL, "Peace out", "", MB_OK | MB_ICONEXCLAMATION);
        return false;
      }
    }
  }
  if(fullscreen)
  {
    dwexstyle = WS_EX_APPWINDOW;
    dwstyle = WS_POPUP;
    ShowCursor(false);
  }
  else
  {
    dwexstyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwstyle = WS_OVERLAPPEDWINDOW;
  }
  AdjustWindowRectEx(&WindowRect, dwstyle, false, dwexstyle);
  if(!(hWnd = CreateWindowEx(  dwexstyle,
                               "OpenGL",
                               title,
                               WS_CLIPSIBLINGS |
                               WS_CLIPCHILDREN |
                               dwstyle,
                               0, 0,
                               WindowRect.right-WindowRect.left,
                               WindowRect.bottom-WindowRect.top,
                               NULL,
                               NULL,
                               hInstance,
                               NULL)))
  {
    KillGLWindow();
    MessageBox(NULL, "Failed to Creat the Window", "initiation error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }
  static PIXELFORMATDESCRIPTOR pfd = 
  {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW |
    PFD_SUPPORT_OPENGL |
    PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    bits,
    0, 0, 0, 0, 0, 0, 
    0,
    0,
    0,
    0, 0, 0, 0, 
    16, 
    0,
    0,
    PFD_MAIN_PLANE,
    0, 
    0, 0, 0
  };
  if(!(hDC = GetDC(hWnd)))
  {
    KillGLWindow();
    MessageBox(NULL, "Failed to create Device", "initialization error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }
  if(!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
  {
    KillGLWindow();
    MessageBox(NULL, "Couldn't find a Pixel format", "initialization error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }
  if(!(SetPixelFormat(hDC, PixelFormat, &pfd)))
  {
    KillGLWindow();
    MessageBox(NULL, "Could not set pixel format", "initialization error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }
  if(!(hRC= wglCreateContext(hDC)))
  {
    KillGLWindow();
    MessageBox(NULL, "Failed to start rederer", "initialization error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }
  if(!wglMakeCurrent(hDC, hRC))
  {
    KillGLWindow();
    MessageBox(NULL, "Failed to activate renderer","initialization error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }
  ShowWindow(hWnd, SW_SHOW);
  SetForegroundWindow(hWnd);
  SetFocus(hWnd);
  ResizeWindow(width, height);
  if(!InitiateGL())
  {
    KillGLWindow();
    MessageBox(NULL, "Failed to initialize openGL", "initialization error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }
  return true;
}                               
//props to nehe for teaching this code
LRESULT CALLBACK WndProc(   HWND    hWnd,
                            UINT    uMsg,
                            WPARAM  wParam,
                            LPARAM  lParam)
{
  switch(uMsg)
  {
    case WM_ACTIVATE:
    {
      if(!HIWORD(wParam))
        active = true;
      else
        active = false;
      return 0;
    }
    case WM_SYSCOMMAND:
    {
      switch(wParam)
      {
        case SC_SCREENSAVE:
        case SC_MONITORPOWER:
        return 0;
      }
      break;
    }
    case WM_CLOSE:
    {
      PostQuitMessage(0);
      return 0;
    }
    case WM_KEYDOWN:
    {
      keys[wParam] = true;
      return 0;
    }
    case WM_KEYUP:
    {
      keys[wParam] = false;
      return 0;
    }
    case WM_SIZE:
    {
      ResizeWindow(LOWORD(lParam), HIWORD(lParam));
      return 0;
    }
  }
  return DefWindowProc(hWnd,uMsg,wParam, lParam);
}
// props to nehe for teaching this code
int WINAPI WinMain(  HINSTANCE    hInstance,
                     HINSTANCE    hPrevInstance,
                     LPSTR        lpCmdLine,
                     int          nCmdShow)
{
  srand((unsigned)time(0));
  MSG msg;
  bool done = false;
  if(MessageBox(NULL, "Would you like to run Fullscreen Mode?", "Start Fullscreen", MB_YESNO| MB_ICONQUESTION) == IDNO)
    fullscreen = false;
  SGame.Play();
  if(!InitiateWindow("JR's OpenGL", 1366, 768, 16, fullscreen))
    return 0;
  while(!done)
  {
    if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if(msg.message == WM_QUIT)
        done = true;
      else
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
    else
    {
      if(active)
      {
        if(keys[VK_ESCAPE])
          done = true;
        else
        {
          RenderScene();
          SwapBuffers(hDC);
        }
      }
      if(SGame.Playing())
        SGame.Events(keys);
      if(keys[VK_F1])
      {
        keys[VK_F1] = false;
        KillGLWindow();
        fullscreen = !fullscreen;
        if(!InitiateWindow("JR's OpenGL", 1366, 768, 16, fullscreen))
          return 0;
      }
        
    }
  }
  KillGLWindow();
  return (msg.wParam);
}                         

// All shoutouts to nehe for teaching openGL 
// Extra credit to www.cprogramming.com 
// google search CBoard to find an amazing forum of programmers
// Nehe can be found at nehe.gamedev.net
// thanks to Lazy Foo Productions as well
