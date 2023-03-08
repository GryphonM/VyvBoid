//------------------------------------------------------------------------------
//
// File Name:	Stub Scene.h
// Description:	Contains code for Stub scene
// Author(s):	FirstName LastName (digipen Id)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "StubScene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "DGL.h"

struct StubScene
{
	Scene base;

	// Other Fings

	StubScene(Scene _base) : base(_base)
	{
	}
};

Engine::ErrorCode StubSceneLoad(void);
Engine::ErrorCode StubSceneInit(void);
void StubSceneUpdate(float dt);
void StubSceneRender(void);
Engine::ErrorCode StubSceneExit(void);
Engine::ErrorCode StubSceneUnload(void);

StubScene instance(Scene("Stub Scene", StubSceneLoad, StubSceneInit, StubSceneUpdate, StubSceneRender, StubSceneExit, StubSceneUnload));
Scene* StubSceneGetInstance() { return &instance.base; }


Engine::ErrorCode StubSceneLoad(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode StubSceneInit(void)
{
	return Engine::NothingBad;
}

void StubSceneUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes())
		return;
	if (instance.base.mode == Scene::Mode::Menu || instance.base.mode == Scene::Mode::Place)
	{	
		// Place Fings
		if (DGL_Input_KeyTriggered('P'))
			instance.base.mode = Scene::Mode::Play;
	}
	if (instance.base.mode == Scene::Mode::Menu || instance.base.mode == Scene::Mode::Play)
	{
		// Play Fings
	}
}

void StubSceneRender(void)
{
}

Engine::ErrorCode StubSceneExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode StubSceneUnload(void)
{
	return Engine::NothingBad;
}
