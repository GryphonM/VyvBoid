//------------------------------------------------------------------------------
//
// File Name:	MichaelDebug.cpp
// Description:	Contains the code for Michael's Debug Scene
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "DGL.h"
#include "MichaelDebug.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "PlaceBlock.h"
#include "BasicObstacles.h"
#include "SoundSystem.h"
#include "Trace.h"
#include "Boids.h"

struct MichaelDebug
{
	Scene base;

	// Other Fings
	Sound* placeSound;
	Sound* jumpScare;
	
	Obstacles* obstacle;
	Tower* tower;
	Gas* gas;
	
	Trace trace;

	PlaceBlock* place;

	BoidList* boids;

	int number;

	MichaelDebug(Scene _base) : base(_base)
	{
		placeSound = NULL;
		jumpScare = NULL;
		place = NULL;
	}
};

Engine::ErrorCode MichaelLoad(void);
Engine::ErrorCode MichaelInit(void);
void MichaelUpdate(float dt);
void MichaelRender(void);
Engine::ErrorCode MichaelExit(void);
Engine::ErrorCode MichaelUnload(void);

MichaelDebug instance(Scene("Michael Debug Scene", MichaelLoad, MichaelInit, MichaelUpdate, MichaelRender, MichaelExit, MichaelUnload));
Scene* MichaelGetInstance() { return &instance.base; }


Engine::ErrorCode MichaelLoad(void)
{
	instance.obstacle = CreateObstacles("obstacleContainer");
	instance.tower = CreateTower("tower");
	instance.gas = CreateGas("gas");
	AddTower(instance.obstacle, instance.tower);
	AddGas(instance.obstacle, instance.gas);

	instance.boids = CreateBoidlist();
	UpdateBoidlistParamaters(instance.boids, "Data/BoidSettings.txt");
	for (int i = 0; i < 1000; i++)
	{
		AddBoidToList(instance.boids, Vector2D(10, 8));
	}

	instance.place = CreatePlaceBlocks("/Assets/gunch.png", "block", instance.boids, 50);

	return Engine::NothingBad;
}

Engine::ErrorCode MichaelInit(void)
{
	instance.number = 0;
	UpdateBoidlistParamaters(instance.boids, "Data/BoidSettings.txt");

	instance.placeSound = SoundCreate("test", "./Assets/place.mp3");
	instance.jumpScare = SoundCreate("scare", "./Assets/cloaker.ogg");
	return Engine::NothingBad;
}

void MichaelUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes() || CheckRestart())
		return;

	UpdateGasPosition(instance.gas, -300.0f, 300.0f, dt);
	//	instance.trace.TraceMessage("played");
	ChangeVolume(instance.jumpScare, 0.0f);
	UpdatePlaceBlocks(instance.place, instance.placeSound);
	if (DGL_Input_KeyTriggered('C'))
	{
		PlaySound(instance.jumpScare);
	}
	if (DGL_Input_KeyTriggered(VK_LEFT) || instance.number == 1)
	{
		instance.number = 1;
		RunBoids(instance.boids, dt);
	}
}

void MichaelRender(void)
{
	RenderAvoids(instance.boids);
	DrawObstacles(instance.obstacle);
	DrawPlacedBlocks(instance.place);

	RenderBoids(instance.boids);
}

Engine::ErrorCode MichaelExit(void)
{
	SoundCleanup(instance.placeSound);
	SoundCleanup(instance.jumpScare);
	return Engine::NothingBad;
}

Engine::ErrorCode MichaelUnload(void)
{
	DestroyObstacles(&instance.obstacle);
	DestroyPlaceBlocks(&instance.place);
	DestroyBoidList(instance.boids);
	return Engine::NothingBad;
}
