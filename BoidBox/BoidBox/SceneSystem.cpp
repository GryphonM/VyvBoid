//------------------------------------------------------------------------------
//
// File Name:	SceneSystem.cpp
// Description:	Contains code that handles switching between scenes
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "SceneSystem.h"
#include "PlatformSystem.h"
#include "OpenScene.h"
#include "Scene.h"
#include "Engine.h"

SceneSystem* SceneSystem::instance = new SceneSystem();

Engine::ErrorCode SceneSystem::Init()
{
	instance->SetScene(OpenSceneGetInstance());
	return Engine::NothingBad;
}

void SceneSystem::Update(float dt)
{
	if (nextScene != NULL)
		ChangeScene();
	if (activeScene && !Engine::GetInstance()->Paused())
	{
		activeScene->Update(dt);
	}
}

void SceneSystem::Render()
{
	activeScene->Render();
}

Engine::ErrorCode SceneSystem::Close()
{
	if (activeScene)
	{
		activeScene->Exit();
		activeScene->Unload();
		activeScene = NULL;
	}
	return Engine::NothingBad;
}

void SceneSystem::SetScene(Scene* scene, bool debug)
{
	if (debug) 
	{
		PlatformSystem::GetInstance()->ChangeTitle(scene->name);
		inDebug = true;
	}
	else if (inDebug)
	{
		PlatformSystem::GetInstance()->ChangeTitle();
		inDebug = false;
	}
	nextScene = scene;
}

SceneSystem* SceneSystem::GetInstance()
{
	return instance;
}


SceneSystem::SceneSystem() : BaseSystem("SceneSystem"), activeScene(NULL), nextScene(NULL), isRestarting(false), inDebug(false)
{ }

SceneSystem::~SceneSystem()
{
	if (instance != NULL)
		delete instance;
}

void SceneSystem::ChangeScene()
{
	if (!nextScene)
		throw(Engine::AllScenesNull);

	if (!activeScene)
	{
		activeScene = nextScene;
		activeScene->Load();
	}
	else
	{
		activeScene->Exit();

		if (activeScene != nextScene)
		{
			activeScene->Unload();
			activeScene = nextScene;
			activeScene->Load();
		}
	}

	nextScene = NULL;
	activeScene->Init();
}
