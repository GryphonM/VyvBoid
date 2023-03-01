//------------------------------------------------------------------------------
//
// File Name:	PlatformSystem.cpp
// Description:	Contains code that handles the system the game is on
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "PlatformSystem.h"
#include "SceneSystem.h"
#include "SoundSystem.h"
#include "Resource.h"
#include "Vector2D.h"

PlatformSystem* PlatformSystem::instance = new PlatformSystem();

Engine::ErrorCode PlatformSystem::Init()
{
    AudioInit();
    return Engine::NothingBad;
}

void PlatformSystem::Update(float dt)
{
    DGL_System_FrameControl();
    DGL_System_Update();
    AudioUpdate();

    if (DGL_Input_KeyTriggered(VK_ESCAPE) || !DGL_System_DoesWindowExist())
        throw(Engine::CloseWindow);
}

void PlatformSystem::Render() { }

Engine::ErrorCode PlatformSystem::Close()
{
    AudioCleanup();
    return Engine::NothingBad;
}

PlatformSystem* PlatformSystem::GetInstance(HINSTANCE hInstance, bool show) 
{
    DGL_SysInitInfo initInfo;
    initInfo.mAppInstance = hInstance;
    initInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;
    initInfo.mMaxFrameRate = 60;
    initInfo.mShow = show;
    initInfo.mWindowStyle = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME; // Resize but only diagonally?
    initInfo.mWindowTitle = DefaultName;
    initInfo.mWindowHeight = instance->windowHeight;
    initInfo.mWindowWidth = instance->windowWidth;
    initInfo.mCreateConsole = false;
    initInfo.pWindowsCallback = PlatformSystemCallback;
    initInfo.mWindowIcon = IDI_BOIDBOX;

    instance->winHandle = DGL_System_Init(&initInfo);

    if (instance->winHandle == NULL)
        throw(Engine::NullWindowHandle);

	return instance; 
}

PlatformSystem* PlatformSystem::GetInstance()
{
    return instance;
}

void PlatformSystem::ChangeTitle(const char* title)
{
    SetWindowTextA(winHandle, title);
}

int PlatformSystem::GetHeight() { return windowHeight; }
int PlatformSystem::GetWidth() { return windowWidth; }

Vector2D PlatformSystem::GetScreenSize() { return Vector2D(windowWidth, windowHeight); }

PlatformSystem::PlatformSystem() : BaseSystem("PlatformSystem"), windowHeight(600), windowWidth(960), winHandle(NULL) {}
PlatformSystem::~PlatformSystem() 
{
    if (instance)
        delete instance;
}

LRESULT CALLBACK PlatformSystemCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
