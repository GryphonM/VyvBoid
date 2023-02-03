//------------------------------------------------------------------------------
//
// File Name:	main.cpp
// Author(s):	Gryphon McLaughlin, Tyler Dean, Michael Howard, Taylee Young    
//              (gryphon.mclaughlin), (tyler.dean), (michael.howard), (taylee.young)
// Project:	    GAM 150 Game Project
// Course:	    GAM 150
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "Resource.h"
#include "DGL.h"
#include "Engine.h"
#include "Level1.h"

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
    initInfo.mWindowTitle = "Boid Box";
    initInfo.mWindowHeight = 768;
    initInfo.mWindowWidth = 1024;
    initInfo.mCreateConsole = false;
    initInfo.pWindowsCallback = WndProc;
    initInfo.mWindowIcon = IDI_BOIDBOX;

    Engine* instance = Engine::GetInstance();

    Engine::ErrorCode returnCode = instance->Start(&initInfo);
    switch (returnCode)
    {
    case Engine::NullWindowHandle:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
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
