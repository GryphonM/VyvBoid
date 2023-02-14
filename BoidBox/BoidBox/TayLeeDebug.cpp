//------------------------------------------------------------------------------
//
// File Name:	TayLeeDebug.h
// Description:	Public interface for TayLee's Debug scene
// Author(s):	TayLee Young (taylee.young)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "TayLeeDebug.h"
#include "Scene.h"
#include "SceneSystem.h"

struct TayLeeDebug
{
	Scene base;

	// Other Fings

	TayLeeDebug(Scene _base) : base(_base)
	{
	}
};

Engine::ErrorCode TayLeeLoad(void);
Engine::ErrorCode TayLeeInit(void);
void TayLeeUpdate(float dt);
void TayLeeRender(void);
Engine::ErrorCode TayLeeExit(void);
Engine::ErrorCode TayLeeUnload(void);

TayLeeDebug instance(Scene("TayLee Debug Scene", TayLeeLoad, TayLeeInit, TayLeeUpdate, TayLeeRender, TayLeeExit, TayLeeUnload));
Scene* TayLeeGetInstance() { return &instance.base; }


Engine::ErrorCode TayLeeLoad(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode TayLeeInit(void)
{
	return Engine::NothingBad;
}

void TayLeeUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes())
		return;
}

void TayLeeRender(void)
{
}

Engine::ErrorCode TayLeeExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode TayLeeUnload(void)
{
	return Engine::NothingBad;
}