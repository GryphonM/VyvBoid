//------------------------------------------------------------------------------
//
// File Name:	TylerDebug.h
// Description:	Public interface for Tyler's Debug scene
// Author(s):	Tyler dean (tyler.dean)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "TylerDebug.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Mesh.h"
#include <vector>
#include "Object.h"
#include "Boids.h"

struct TylerDebug
{
	Scene base;
	BoidList* boidList;
	// Other Fings

	TylerDebug(Scene _base) : base(_base), boidList(NULL)
	{
	}
};

Engine::ErrorCode TylerLoad(void);
Engine::ErrorCode TylerInit(void);
void TylerUpdate(float dt);
void TylerRender(void);
Engine::ErrorCode TylerExit(void);
Engine::ErrorCode TylerUnload(void);

TylerDebug level(Scene("Tyler Debug Scene", TylerLoad, TylerInit, TylerUpdate, TylerRender, TylerExit, TylerUnload));
Scene* TylerGetInstance() { return &level.base; }


Engine::ErrorCode TylerLoad(void)
{
	level.boidList = CreateBoidlist();
	AddBoidToList(level.boidList, Vector2D(30, 30));

	
	AddBoidToList(level.boidList, Vector2D(50, 70));
	AddBoidToList(level.boidList, Vector2D(30, 60));
	AddBoidToList(level.boidList, Vector2D(30, 60));
	AddBoidToList(level.boidList, Vector2D(30, 60));
	AddBoidToList(level.boidList, Vector2D(30, 60));
	AddBoidToList(level.boidList, Vector2D(30, 60));
	AddBoidToList(level.boidList, Vector2D(30, 60));
	AddBoidToList(level.boidList, Vector2D(30, 60));
	AddBoidToList(level.boidList, Vector2D(30, 60));
	

	return Engine::NothingBad;
}

Engine::ErrorCode TylerInit(void)
{
	UpdateBoidlistParamaters(level.boidList, "Assets/BoidSettings.txt");
	return Engine::NothingBad;
}

void TylerUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes() || CheckRestartGame())
		return;
	RunBoids(level.boidList, dt);
}

void TylerRender(void)
{
	RenderBoids(level.boidList);
}

Engine::ErrorCode TylerExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode TylerUnload(void)
{
	DestroyBoidList(level.boidList);
	return Engine::NothingBad;
}