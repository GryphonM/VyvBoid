//------------------------------------------------------------------------------
//
// File Name:	Engine.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once

struct DGL_SysInitInfo;

struct Level1;
struct TestLevel;
struct SoundTest;
class BaseSystem;

#define MAX_SYSTEMS 5

class Engine
{
public:
	enum ErrorCode { NullWindowHandle, WindowDoesntExist, AllScenesNull, CloseWindow, SomethingBad, NothingBad, EngineExit };

	ErrorCode Start();
	ErrorCode Stop();

	void AddSystem(BaseSystem*);

	bool Paused();
	void SetPause(bool pause);

	static Engine* GetInstance();
private:
	// Constructor and Destructor to prevent additional instantiation
	Engine();
	~Engine();

	// Delete copy constructor and assignment operator
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	// Private Functions
	ErrorCode Initialize(DGL_SysInitInfo* initInfo);
	ErrorCode Update();
	ErrorCode Render();
	ErrorCode Shutdown();

	// Singleton pointer
	static Engine* instance;

	// Systems array
	BaseSystem* systems[MAX_SYSTEMS];
	int systemCount;

	// Private variables
	bool isRunning;
	bool paused;
};
