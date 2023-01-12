// DGLDemoProject.cpp : Defines the entry point for the application.
//

#include "Resource.h"
#include "DGL.h"
#include "stdio.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
  DGL_SysInitInfo initInfo;
  initInfo.mAppInstance = hInstance;
  initInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;
  initInfo.mMaxFrameRate = 60;
  initInfo.mShow = nCmdShow;
  initInfo.mWindowStyle = WS_OVERLAPPEDWINDOW;
  initInfo.mWindowTitle = "Game Window";          // Change to your window title
  initInfo.mWindowHeight = 768;                   // Change to your window height
  initInfo.mWindowWidth = 1024;                   // Change to your window width
  initInfo.mCreateConsole = FALSE;
  initInfo.pWindowsCallback = WndProc;
  initInfo.mWindowIcon = IDI_DGLDEMOPROJECT;

  HWND windowHandle = DGL_System_Init(&initInfo);
  const char* error = DGL_System_GetLastError();
  if (windowHandle == NULL)
    return 1;

  int running = TRUE;
  while (running)
  {
    DGL_System_FrameControl();
    DGL_System_Update();

    DGL_Graphics_StartDrawing();

    DGL_Graphics_FinishDrawing();

    if (!DGL_System_DoesWindowExist())
      running = FALSE;
  }

  DGL_System_Exit();

  return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int result;
  if (DGL_System_HandleWindowsMessage(message, wParam, lParam, &result))
    return result;

  switch (message)
  {

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

//DGL_Mesh* CreateMesh()
//{
//  float width = 1.0f;
//  float height = 1.0f;
//
//  // Save the half width and height values
//  float halfWidth = width / 2.0f;
//  float halfHeight = width / 2.0f;
//
//  // Tell DGL that we are starting a new mesh
//  DGL_Graphics_StartMesh();
//
//  // All vertices will use this color
//  // You could change it between adding vertices to interpolate colors across the mesh
//  DGL_Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
//
//  // First triangle
//
//  // Add a vertex at the bottom-left corner
//  DGL_Vec2 pos = { -halfWidth, -halfHeight };
//  DGL_Vec2 uv = { 0.0f, 1.0f };
//  DGL_Graphics_AddVertex(&pos, &color, &uv);
//
//  // Add a vertex at the top-left corner
//  pos = (DGL_Vec2){ -halfWidth, halfHeight };
//  uv = (DGL_Vec2){ 0.0f, 0.0f };
//  DGL_Graphics_AddVertex(&pos, &color, &uv);
//
//  // Add a vertex at the top-right corner
//  pos = (DGL_Vec2){ halfWidth, halfHeight };
//  uv = (DGL_Vec2){ 1.0f, 0.0f };
//  DGL_Graphics_AddVertex(&pos, &color, &uv);
//
//  // Second triangle
//
//  // Add a vertex at the bottom-left corner
//  pos = (DGL_Vec2){ -halfWidth, -halfHeight };
//  uv = (DGL_Vec2){ 0.0f, 1.0f };
//  DGL_Graphics_AddVertex(&pos, &color, &uv);
//
//  // Add a vertex at the top-right corner
//  pos = (DGL_Vec2){ halfWidth, halfHeight };
//  uv = (DGL_Vec2){ 1.0f, 0.0f };
//  DGL_Graphics_AddVertex(&pos, &color, &uv);
//
//  // Add a vertex at the bottom-right corner
//  pos = (DGL_Vec2){ halfWidth, -halfHeight };
//  uv = (DGL_Vec2){ 1.0f, 1.0f };
//  DGL_Graphics_AddVertex(&pos, &color, &uv);
//
//  // Tell DGL we are done adding vertices and save the mesh object
//  return DGL_Graphics_EndMesh();
//}
