//------------------------------------------------------------------------------
//
// File Name:	Scene.h
// Description:	Base class for all scenes
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once
#include "Engine.h"

// Scene Class
// Contains function pointers to the functions needed to update different levels
class Scene
{
	typedef Engine::ErrorCode(*ErrorVoid)(void);
	typedef void (*VoidFloat)(float);
	typedef void (*VoidVoid)(void);
public:
	Scene(const char * _name, ErrorVoid load, ErrorVoid init, VoidFloat update, VoidVoid render, ErrorVoid exit, ErrorVoid unload);
	const char* name;
	ErrorVoid Load;
	ErrorVoid Init;
	VoidFloat Update;
	VoidVoid Render;
	ErrorVoid Exit;
	ErrorVoid Unload;
private:
};

// Checks if any of the Debug Scenes have been triggered to change to
// Returns true if they are, false if not
bool CheckDebugScenes();

// Checks if any of the Game Scenes have been triggered to change to
// Returns true if they are, false if not
bool CheckGameScenes();

