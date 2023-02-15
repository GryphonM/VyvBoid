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
// #include "Resource.h"
// #include "DGL.h"
#include "Engine.h"
#include "SceneSystem.h"
#include "PlatformSystem.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    Engine* engine = Engine::GetInstance();
    engine->AddSystem(PlatformSystem::GetInstance(hInstance, nCmdShow));
    engine->AddSystem(SceneSystem::GetInstance());

    Engine::ErrorCode returnCode = engine->Start();

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
