//------------------------------------------------------------------------------
//
// File Name:	Engine.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once

#include "DGL.h"

struct Level1;
struct TestLevel;

class Engine
{
public:
	enum ErrorCode { NullWindowHandle, WindowDoesntExist, SomethingBad, NothingBad, EngineExit };

	ErrorCode Start(DGL_SysInitInfo* initInfo);
	ErrorCode Stop();

	ErrorCode SetLevel(TestLevel* level);
	ErrorCode SetLevel(Level1* level);

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
	ErrorCode Shutdown();

	// Singleton pointer
	static Engine* instance;

	// Current running level
	Level1* level1;

	// Private variables
	bool isRunning;
};
