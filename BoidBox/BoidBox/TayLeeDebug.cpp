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
#include "PlatformSystem.h"
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
	Hunters* hunter1;
	Hunters* hunter2;
	Hunters* hunter3;

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
	instance.hunter1 = HunterCreate();
	instance.hunter2 = HunterCreate();
	instance.hunter3 = HunterCreate();
	return Engine::NothingBad;
}

Engine::ErrorCode TayLeeInit(void)
{
	InitCrosshair(instance.hunter1, 2.0, 4.0, 30.0, {0, -300});
	InitCrosshair(instance.hunter2, 2.0, 4.0, 30.0, {-300, 300});
	InitCrosshair(instance.hunter3, 2.0, 4.0, 30.0, {300, 300});
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
	DrawCrosshair(instance.hunter1);
	DrawCrosshair(instance.hunter2);
	DrawCrosshair(instance.hunter3);
}

Engine::ErrorCode TayLeeExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode TayLeeUnload(void)
{
	FreeHunters(&instance.hunter1);
	FreeHunters(&instance.hunter2);
	FreeHunters(&instance.hunter3);
	//freeMesh(&instance.testMesh);
	return Engine::NothingBad;
}