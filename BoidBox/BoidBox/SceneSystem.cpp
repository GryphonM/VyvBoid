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
#include "Scene.h"
#include "Engine.h"
#include "DGL.h"

#include "OpenScene.h"
#include "Tutorial.h"
#include "FirstLevel.h"

#include "GryphonDebug.h"
#include "MichaelDebug.h"
#include "TayLeeDebug.h"
#include "TylerDebug.h"

SceneSystem* SceneSystem::instance = new SceneSystem();

Engine::ErrorCode SceneSystem::Init()
{
	instance->SetScene(DefaultSceneInstance());
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

void SceneSystem::RestartCurrentScene()
{
	SetScene(activeScene);
}

SceneSystem* SceneSystem::GetInstance()
{
	return instance;
}


SceneSystem::SceneSystem() : BaseSystem("SceneSystem"), DefaultSceneInstance(OpenSceneGetInstance), activeScene(NULL), nextScene(NULL), isRestarting(false), inDebug(false)
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

		//if (activeScene != nextScene || isRestarting)
		//{
			activeScene->Unload();
			activeScene = nextScene;
			activeScene->Load();
		//}
		isRestarting = false;
	}

	nextScene = NULL;
	activeScene->Init();
}

bool CheckDebugScenes()
{
	if (DGL_Input_KeyTriggered('I'))
		SceneSystem::GetInstance()->SetScene(GryphonGetInstance(), true);
	else if (DGL_Input_KeyTriggered('L'))
		SceneSystem::GetInstance()->SetScene(MichaelGetInstance(), true);
	else if (DGL_Input_KeyTriggered('Q'))
		SceneSystem::GetInstance()->SetScene(TayLeeGetInstance(), true);
	else if (DGL_Input_KeyTriggered('H'))
		SceneSystem::GetInstance()->SetScene(TylerGetInstance(), true);
	else
		return false;
	return true;
}

bool CheckGameScenes()
{
	if (DGL_Input_KeyTriggered('0'))
		SceneSystem::GetInstance()->SetScene(OpenSceneGetInstance());
	else if (DGL_Input_KeyTriggered('1'))
		SceneSystem::GetInstance()->SetScene(TutorialGetInstance());
	else if (DGL_Input_KeyTriggered('2'))
		SceneSystem::GetInstance()->SetScene(FirstLevelGetInstance());
	else
		return false;
	return true;
}

bool CheckRestartGame()
{
	if (DGL_Input_KeyTriggered('R'))
	{
		SceneSystem* instance = SceneSystem::GetInstance();
		instance->isRestarting = true;
		instance->SetScene(instance->DefaultSceneInstance());
		return true;
	}
	return false;
}
