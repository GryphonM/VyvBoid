//------------------------------------------------------------------------------
//
// File Name:	Engine.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "Engine.h"
#include "Level1.h"
#include "BoidTest.h"
#include "SoundTest.h"

Engine* Engine::instance = new Engine();

//------------------------------------------------------------------------------
// Public Functions
//------------------------------------------------------------------------------

Engine::ErrorCode Engine::Start(DGL_SysInitInfo* initInfo)
{
	try {
		Initialize(initInfo);
	}
	catch(ErrorCode e) {
		return e;
	}

	// Other Startup Fings
	instance->SetLevel(SoundTestCreate("Sound Test"));
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	LevelInit(instance->soundtest);

	// Start the engine! Vrooom Vroom
	ErrorCode updateRet = Update();

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

Engine::ErrorCode Engine::SetLevel(Level1* level)
{
	level1 = level;
	return NothingBad;
}

Engine::ErrorCode Engine::SetLevel(TestLevel* level)
{
	testlevel = level;
	return NothingBad;
}

Engine::ErrorCode Engine::SetLevel(SoundTest* level)
{
	soundtest = level;
	return NothingBad;
}

Engine* Engine::GetInstance() { return instance; }

//------------------------------------------------------------------------------
// Private Functions
//------------------------------------------------------------------------------
Engine::Engine() : isRunning(false), level1(NULL)
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
	// Pre-loop things
	while (true)
	{
		DGL_System_FrameControl();
		DGL_System_Update();

		if (soundtest)
		{
			// Update Level
			LevelUpdate(soundtest, static_cast<float>(DGL_System_GetDeltaTime()));

			// Draw Level
			DGL_Graphics_StartDrawing();
			LevelDraw(soundtest);
			DGL_Graphics_FinishDrawing();
		}

		if (!DGL_System_DoesWindowExist())
			return WindowDoesntExist;
	}
}

Engine::ErrorCode Engine::Shutdown()
{
	DeleteLevel(soundtest);
	if (DGL_System_Exit())
		throw SomethingBad;
	else
		return EngineExit;
}
