//------------------------------------------------------------------------------
//
// File Name:	TayLeeDebug.h
// Description:	Public interface for TayLee's Debug scene
// Author(s):	TayLee Young (taylee.young)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include <vector>
#include "TayLeeDebug.h"
#include "Hunters.h"
#include "Mesh.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Scene.h"
#include "SceneSystem.h"

struct TayLeeDebug
{
	Scene base;

	// Other Fings
	//Mesh* testMesh;
	Sprite* OpenSprite;
	Hunters* hunter;

	TayLeeDebug(Scene _base) : base(_base), OpenSprite(NULL)
	{
		OpenSprite = CreateSprite();
		FreeSprite(&OpenSprite);
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
	//instance.testMesh = NULL;
	instance.hunter = HunterCreate();
	return Engine::NothingBad;
}

Engine::ErrorCode TayLeeInit(void)
{
	InitCrosshair(instance.hunter);
	return Engine::NothingBad;
}

void TayLeeUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes() || CheckRestartGame())
		return;
}

void TayLeeRender(void)
{
	//RenderMesh(instance.testMesh);
	DrawCrosshair(instance.hunter);
}

Engine::ErrorCode TayLeeExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode TayLeeUnload(void)
{
	FreeHunters(&instance.hunter);
	//freeMesh(&instance.testMesh);
	return Engine::NothingBad;
}