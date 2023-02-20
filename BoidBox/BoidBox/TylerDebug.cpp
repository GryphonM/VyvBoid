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
	UpdateBoidlistParamaters(level.boidList, "Data/BoidSettings.txt");
	for (int i = 0; i < 1000; i++)
	{
		AddBoidToList(level.boidList, Vector2D(10, 8));
	}

	AddAvoidToList(level.boidList, Vector2D(-400, 1));
	AddAvoidToList(level.boidList, Vector2D(-400, 100));
	AddAvoidToList(level.boidList, Vector2D(-400, 200));
	AddAvoidToList(level.boidList, Vector2D(-400, -200));
	AddAvoidToList(level.boidList, Vector2D(-400, -100));

	AddAvoidToList(level.boidList, Vector2D(400, 1));
	AddAvoidToList(level.boidList, Vector2D(400, 100));
	AddAvoidToList(level.boidList, Vector2D(400, 200));
	AddAvoidToList(level.boidList, Vector2D(400, -200));
	AddAvoidToList(level.boidList, Vector2D(400, -100));

	AddAvoidToList(level.boidList, Vector2D(1, -200));
	AddAvoidToList(level.boidList, Vector2D(200, -200));
	AddAvoidToList(level.boidList, Vector2D(-200, -200));
	AddAvoidToList(level.boidList, Vector2D(300, -200));
	AddAvoidToList(level.boidList, Vector2D(-300, -200));
	AddAvoidToList(level.boidList, Vector2D(100, -200));
	AddAvoidToList(level.boidList, Vector2D(-100, -200));

	AddAvoidToList(level.boidList, Vector2D(1, 200));
	AddAvoidToList(level.boidList, Vector2D(200, 200));
	AddAvoidToList(level.boidList, Vector2D(-200, 200));
	AddAvoidToList(level.boidList, Vector2D(300, 200));
	AddAvoidToList(level.boidList, Vector2D(-300, 200));
	AddAvoidToList(level.boidList, Vector2D(100, 200));
	AddAvoidToList(level.boidList, Vector2D(-100, 200));

	return Engine::NothingBad;
}

Engine::ErrorCode TylerInit(void)
{
	UpdateBoidlistParamaters(level.boidList, "Data/BoidSettings.txt");
	return Engine::NothingBad;
}

void TylerUpdate(float dt)
{ 
	if (DGL_Input_KeyTriggered('D'))
	{
		UpdateBoidlistParamaters(level.boidList, "Data/BoidSettings.txt");
	}
	if (CheckDebugScenes() || CheckGameScenes() || CheckRestartGame())
		return;
	RunBoids(level.boidList, dt);

}

void TylerRender(void)
{
	RenderBoids(level.boidList);
	RenderAvoids(level.boidList);
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