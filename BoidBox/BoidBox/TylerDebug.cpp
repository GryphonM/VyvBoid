//------------------------------------------------------------------------------
//
// File Name:	TylerDebug.h
// Description:	Public interface for Tyler's Debug scene
// Author(s):	Tyler Howard (tyler.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "TylerDebug.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Mesh.h"

struct TylerDebug
{
	Scene base;

	// Other Fings

	TylerDebug(Scene _base) : base(_base)
	{
	}
};

Engine::ErrorCode TylerLoad(void);
Engine::ErrorCode TylerInit(void);
void TylerUpdate(float dt);
void TylerRender(void);
Engine::ErrorCode TylerExit(void);
Engine::ErrorCode TylerUnload(void);

TylerDebug tylerInstance(Scene("Tyler Debug Scene", TylerLoad, TylerInit, TylerUpdate, TylerRender, TylerExit, TylerUnload));
Scene* TylerGetInstance() { return &tylerInstance.base; }


Engine::ErrorCode TylerLoad(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode TylerInit(void)
{
	return Engine::NothingBad;
}

void TylerUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes())
		return;
}

void TylerRender(void)
{
}

Engine::ErrorCode TylerExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode TylerUnload(void)
{
	return Engine::NothingBad;
}

