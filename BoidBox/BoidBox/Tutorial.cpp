//------------------------------------------------------------------------------
//
// File Name:	Tutorial.h
// Description:	Contains code for Tutorial scene
// Author(s):	Gryphon McLaughlin(gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "Tutorial.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "PlatformSystem.h"
#include "SoundSystem.h"
#include "Goal.h"
#include "Boids.h"
#include "PlaceBlock.h"

struct Tutorial
{
	Scene base;

	// Other Fings
	Goal* goal;
	BoidList* bList;
	PlaceBlock* pBlocks;
	Sound* placeSound;

	Tutorial(Scene _base) : base(_base), goal(NULL), bList(NULL), pBlocks(NULL), placeSound(NULL)
	{
	}
};

Engine::ErrorCode TutorialLoad(void);
Engine::ErrorCode TutorialInit(void);
void TutorialUpdate(float dt);
void TutorialRender(void);
Engine::ErrorCode TutorialExit(void);
Engine::ErrorCode TutorialUnload(void);

Tutorial instance(Scene("Stub Scene", TutorialLoad, TutorialInit, TutorialUpdate, TutorialRender, TutorialExit, TutorialUnload));
Scene* TutorialGetInstance() { return &instance.base; }


Engine::ErrorCode TutorialLoad(void)
{
	instance.bList = CreateBoidlist();
	UpdateBoidlistParamaters(instance.bList, "./Data/BoidSettings.txt");
	Vector2D Screen(static_cast<float>(PlatformSystem::GetInstance()->GetWidth()), static_cast<float>(PlatformSystem::GetInstance()->GetHeight()));
	Vector2D BoidStart(-(Screen.X() / 2) + 50, (Screen.Y() / 2) - 50);
	Vector2D GoalStart((Screen.X() / 2)-20, -(Screen.Y() / 2)+20);
	for (int i = 0; i < 10; ++i)
	{
		AddBoidToList(instance.bList, BoidStart, Vector2D(0, 1000));
	}
	instance.goal = new Goal(CreateTransform(GoalStart, Vector2D(200, 200)), instance.bList, 10);
	instance.pBlocks = CreatePlaceBlocks("Place Blocks", instance.bList);
	instance.placeSound = SoundCreate("Block Place Sound", "./Assets/place.mp3");
	return Engine::NothingBad;
}

Engine::ErrorCode TutorialInit(void)
{
	instance.goal->Reset();
	return Engine::NothingBad;
}

void TutorialUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes())
		return;
	UpdatePlaceBlocks(instance.pBlocks, instance.placeSound);
	RunBoids(instance.bList, dt);
	instance.goal->Update();
}

void TutorialRender(void)
{
	DrawPlacedBlocks(instance.pBlocks);
	RenderBoids(instance.bList);
	instance.goal->Render();
}

Engine::ErrorCode TutorialExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode TutorialUnload(void)
{
	SoundCleanup(instance.placeSound);
	DestroyPlaceBlocks(&instance.pBlocks);
	DestroyBoidList(instance.bList);
	instance.bList = NULL;
	delete instance.goal;
	instance.goal = NULL;
	return Engine::NothingBad;
}