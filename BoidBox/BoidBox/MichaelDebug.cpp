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
#include "SoundSystem.h"
#include "Trace.h"

struct MichaelDebug
{
	Scene base;

	// Other Fings
	Sound* placeSound;
	Sound* jumpScare;
	
	Trace trace;

	PlaceBlock* place;

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

	return Engine::NothingBad;
}

Engine::ErrorCode MichaelInit(void)
{
	instance.placeSound = SoundCreate("test", "./Assets/place.mp3");
	instance.jumpScare = SoundCreate("scare", "./Assets/cloaker.ogg");
	instance.place = CreatePlaceBlocks(10, 0.5f, 0.5f, 1.0f, 1.0f, "block", "./Assets/catholicMario.jpg");
	return Engine::NothingBad;
}

void MichaelUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes() || CheckRestartGame())
		return;
	

	instance.trace.TraceMessage("played");
	UpdatePlaceBlocks(instance.place, instance.placeSound);
	if (DGL_Input_KeyTriggered('C'))
	{
		PlaySound(instance.jumpScare);
	}
}

void MichaelRender(void)
{
	DrawPlacedBlocks(instance.place);
}

Engine::ErrorCode MichaelExit(void)
{
	SoundCleanup(instance.placeSound);
	SoundCleanup(instance.jumpScare);
	return Engine::NothingBad;
}

Engine::ErrorCode MichaelUnload(void)
{
	DestroyPlaceBlocks(&instance.place);
	return Engine::NothingBad;
}
