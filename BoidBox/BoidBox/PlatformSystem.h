//------------------------------------------------------------------------------
//
// File Name:	PlatformSystem.h
// Description:	System that handles things to do with the platform the game is on
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once

#include "BaseSystem.h"
#include "DGL.h"

#define DefaultName "Boid Box"
class Vector2D;

class PlatformSystem : public BaseSystem
{
public:
	Engine::ErrorCode Init();
	void Update(float dt);
	void Render();
	Engine::ErrorCode Close();

	static PlatformSystem* GetInstance(HINSTANCE, bool);
	static PlatformSystem* GetInstance();
	void ChangeTitle(const char* = DefaultName);
	int GetHeight();
	int GetWidth();
	Vector2D GetScreenSize();
private:
	PlatformSystem();
	~PlatformSystem();

	static PlatformSystem* instance;

	int windowHeight;
	int windowWidth;
	HWND winHandle;
};

LRESULT CALLBACK PlatformSystemCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
