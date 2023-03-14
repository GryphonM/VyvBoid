//------------------------------------------------------------------------------
//
// File Name:	GryphonDebug.cpp
// Description:	Contains the code to run Gryphon's Debug scene
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "GryphonDebug.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "PlatformSystem.h"
#include "Goal.h"
#include "Boids.h"
#include "PlaceBlock.h"
#include "Transform.h"

struct GryphonDebug
{
	Scene base;

	// Other Fings
	BoidList* boidList;
	PlaceBlock* pBlock;
	Goal* goal;

	GryphonDebug(Scene _base) : base(_base), goal(NULL), pBlock(NULL), boidList(NULL)
	{
	}
};

Engine::ErrorCode GryphonLoad(void);
Engine::ErrorCode GryphonInit(void);
void GryphonUpdate(float dt);
void GryphonRender(void);
Engine::ErrorCode GryphonExit(void);
Engine::ErrorCode GryphonUnload(void);

GryphonDebug grynstance(Scene("Gryphon Debug Scene", GryphonLoad, GryphonInit, GryphonUpdate, GryphonRender, GryphonExit, GryphonUnload));
Scene* GryphonGetInstance() { return &grynstance.base; }
Mesh* mesh;

Engine::ErrorCode GryphonLoad(void)
{
	grynstance.boidList = CreateBoidlist();
	UpdateBoidlistParamaters(grynstance.boidList, "Data/BoidSettings.txt");
	Vector2D BoidPos(0, -200);
	//Vector2D BoidPos(-(static_cast<float>(PlatformSystem::GetInstance()->GetWidth()) / 2) + 50, (static_cast<float>(PlatformSystem::GetInstance()->GetHeight()) / 2) - 50);
	for (int i = 0; i < 10; ++i)
	{
		AddBoidToList(grynstance.boidList, BoidPos, Vector2D(500, 0));
	}
	grynstance.pBlock = CreatePlaceBlocks("Place Blocks", grynstance.boidList);
	grynstance.goal = new Goal(CreateTransform(Vector2D(), Vector2D(100, 100)), &grynstance.base, grynstance.boidList, 10);
	return Engine::NothingBad;
}

Engine::ErrorCode GryphonInit(void)
{
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	DGL_Graphics_SetTexture(NULL);
	grynstance.goal->Reset();
	return Engine::NothingBad;
}

void GryphonUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes() || CheckRestart() || CheckRestartGame())
		return;
	UpdatePlaceBlocks(grynstance.pBlock, NULL);
	RunBoids(grynstance.boidList, dt);
	grynstance.goal->Update(dt);
}

void GryphonRender(void)
{
	DrawPlacedBlocks(grynstance.pBlock);
	RenderBoids(grynstance.boidList);
	grynstance.goal->Render();
}

Engine::ErrorCode GryphonExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode GryphonUnload(void)
{
	DestroyPlaceBlocks(&grynstance.pBlock);
	DestroyBoidList(grynstance.boidList);
	delete grynstance.goal;
	return Engine::NothingBad;
}
