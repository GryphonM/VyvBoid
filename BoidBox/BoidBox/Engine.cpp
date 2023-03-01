//------------------------------------------------------------------------------
//
// File Name:	Engine.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "Engine.h"
#include "BaseSystem.h"
#include "Level1.h"
#include "BoidTest.h"
#include "SoundTest.h"
#include "DGL.h"

Engine* Engine::instance = new Engine();

//------------------------------------------------------------------------------
// Public Functions
//------------------------------------------------------------------------------

Engine::ErrorCode Engine::Start()
{
	// Startup Fings
	for (int i = 0; i < systemCount; ++i)
	{
		try {
			systems[i]->Init();
		}
		catch (ErrorCode e) {
			return e;
		}
	}

	// Start the engine! Vrooom Vroom
	while (true)
	{
		ErrorCode code = NothingBad;

		if (!paused)
		{
			try {
				code = Update();
			}
			catch (ErrorCode e)
			{
				// Error Message
				return e;
			}
			if (code == CloseWindow)
				break;
		}

		try {
			code = Render();
		}
		catch (ErrorCode e)
		{
			// Error Message
			return e;
		}
		if (code == CloseWindow)
			break;
	}

	return Stop();
}

Engine::ErrorCode Engine::Stop()
{
	try {
		Shutdown();
	}
	catch (ErrorCode e) {
		return e;
	}

	return EngineExit;
}

void Engine::AddSystem(BaseSystem* sys)
{
	systems[systemCount++] = sys;
}

bool Engine::Paused() { return paused; }
void Engine::SetPause(bool pause) { paused = pause; }

Engine* Engine::GetInstance() { return instance; }

//------------------------------------------------------------------------------
// Private Functions
//------------------------------------------------------------------------------
Engine::Engine() : isRunning(false), systemCount(0), systems(), paused(false)
{
}

Engine::~Engine()
{
	if (instance != NULL)
		delete instance;
}

Engine::ErrorCode Engine::Initialize(DGL_SysInitInfo* initInfo)
{
	HWND windowsHandle = DGL_System_Init(initInfo);
	if (windowsHandle == NULL)
		throw(NullWindowHandle);

	// Other Intializing Things
	return NothingBad;
}

Engine::ErrorCode Engine::Update()
{
	float dt = static_cast<float>(DGL_System_GetDeltaTime());
	for (int i = 0; i < systemCount; ++i)
	{
		try {
			systems[i]->Update(dt);
		}
		catch (ErrorCode e)
		{
			switch (e)
			{
				case CloseWindow:
					return e;
				default:
					throw(e);
			}
		}
	}
	return NothingBad;
}

Engine::ErrorCode Engine::Render()
{
	DGL_Graphics_StartDrawing();
	for (int i = 0; i < systemCount; ++i)
	{
		systems[i]->Render();
	}
	DGL_Graphics_FinishDrawing();
	return NothingBad;
}

Engine::ErrorCode Engine::Shutdown()
{
	for (int i = systemCount - 1; i >= 0; --i)
	{
		systems[i]->Close();
	}
	if (DGL_System_Exit())
		throw SomethingBad;
	else
		return EngineExit;
}
