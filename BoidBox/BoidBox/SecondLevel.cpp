//------------------------------------------------------------------------------
//
// File Name:	SecondLevel Scene.h
// Description:	Contains code for SecondLevel scene
// Author(s):	FirstName LastName (digipen Id)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "SecondLevel.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "OpenScene.h"
#include "PlatformSystem.h"
#include "SoundSystem.h"
#include "Goal.h"
#include "Obstacle.h"
#include "Boids.h"
#include "PlaceBlock.h"
#include "Mesh.h"
#include "Sprite.h"
#include "SpriteSource.h"

struct SecondLevelScene
{
	Scene base;

	Obstacle* obs1;
	Obstacle* obs2;
	Obstacle* taskbar;

	Goal* goal;
	BoidList* bList;
	PlaceBlock* pBlocks;
	Sound* placeSound;

	Sprite* backgroundSprite;
	Mesh* backgroundMesh;
	SpriteSource* backgroundSource;
	Transform* backgroundPos;


	SecondLevelScene(Scene _base) : base(_base)
	{
	}
};

Engine::ErrorCode SecondLevelSceneLoad(void);
Engine::ErrorCode SecondLevelSceneInit(void);
void SecondLevelSceneUpdate(float dt);
void SecondLevelSceneRender(void);
Engine::ErrorCode SecondLevelSceneExit(void);
Engine::ErrorCode SecondLevelSceneUnload(void);

SecondLevelScene instance(Scene("SecondLevel Scene", SecondLevelSceneLoad, SecondLevelSceneInit, SecondLevelSceneUpdate, SecondLevelSceneRender, SecondLevelSceneExit, SecondLevelSceneUnload));
Scene* SecondLevelGetInstance() { return &instance.base; }


Engine::ErrorCode SecondLevelSceneLoad(void)
{
	instance.backgroundMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Square Mesh", { 0.0f, 0.0f, 0.0f, 0.0f });
	instance.backgroundPos = CreateTransform(Vector2D(), Vector2D(960, 561));
	instance.backgroundSource = CreateSpriteSource();
	instance.backgroundSprite = CreateSprite();
	LoadSpriteSourceTexture(instance.backgroundSource, 1, 1, "./Assets/desktopBackgroundBLANK.png");
	SpriteSetMesh(instance.backgroundSprite, instance.backgroundMesh);
	SpriteSetSource(instance.backgroundSprite, instance.backgroundSource);

	instance.bList = CreateBoidlist();
	UpdateBoidlistParamaters(instance.bList, "./Data/BoidSettings.txt");

	Vector2D Screen(static_cast<float>(PlatformSystem::GetInstance()->GetWidth()), static_cast<float>(PlatformSystem::GetInstance()->GetHeight()));
	Vector2D BoidStart(-(Screen.X() / 2) + 130, (Screen.Y() / 2) - 470);
	Vector2D GoalStart((Screen.X() / 2) - 165, -(Screen.Y() / 2) + 550);

	for (int i = 0; i < 10; ++i)
	{
		AddBoidToList(instance.bList, BoidStart, Vector2D(0, 1000));
	}

	instance.obs1 = new Obstacle(CreateTransform(Vector2D(-180, -136), Vector2D(60, 200)), instance.bList, 10);
	instance.obs2 = new Obstacle(CreateTransform(Vector2D(120, 145), Vector2D(60, 270)), instance.bList, 10);
	instance.taskbar = new Obstacle("./Assets/taskbarColor.png", CreateTransform(Vector2D(0, -269), Vector2D(1000, 60)), instance.bList, 10);
	instance.goal = new Goal(CreateTransform(GoalStart, Vector2D(200, 200)), OpenSceneGetInstance(), instance.bList, 10);
	instance.pBlocks = CreatePlaceBlocks("Place Blocks", instance.bList, 15);
	instance.placeSound = SoundCreate("Block Place Sound", "./Assets/place.mp3");
	return Engine::NothingBad;
}

Engine::ErrorCode SecondLevelSceneInit(void)
{
	SpriteSetFrame(instance.backgroundSprite, 0);
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

	instance.goal->Reset();
	instance.obs1->Reset();
	instance.obs2->Reset();
	instance.taskbar->Reset();
	instance.base.mode = Scene::Mode::Place;
	return Engine::NothingBad;
}

void SecondLevelSceneUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes() || CheckRestart())
		return;
	if (instance.base.mode == Scene::Mode::Menu || instance.base.mode == Scene::Mode::Place)
	{
		UpdatePlaceBlocks(instance.pBlocks, instance.placeSound);
		if (DGL_Input_KeyTriggered('P'))
			instance.base.mode = Scene::Mode::Play;
	}
	if (instance.base.mode == Scene::Mode::Menu || instance.base.mode == Scene::Mode::Play)
	{
		RunBoids(instance.bList, dt);
		instance.goal->Update(dt);
		instance.obs1->Update();
		instance.obs2->Update();
		instance.taskbar->Update();
	}
}

void SecondLevelSceneRender(void)
{
	RenderSprite(instance.backgroundSprite, instance.backgroundPos);

	DrawPlacedBlocks(instance.pBlocks);
	RenderBoids(instance.bList);
	instance.goal->Render();
	instance.obs1->Render();
	instance.obs2->Render();
	instance.taskbar->Render();
}

Engine::ErrorCode SecondLevelSceneExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode SecondLevelSceneUnload(void)
{
	FreeSprite(&instance.backgroundSprite);
	freeMesh(&instance.backgroundMesh);
	DeleteTransform(&instance.backgroundPos);

	SoundCleanup(instance.placeSound);
	DestroyPlaceBlocks(&instance.pBlocks);
	DestroyBoidList(instance.bList);
	instance.bList = NULL;
	delete instance.obs1;
	delete instance.obs2;
	delete instance.taskbar;
	instance.obs1 = NULL;
	instance.obs2 = NULL;
	instance.taskbar = NULL;
	delete instance.goal;
	instance.goal = NULL;
	return Engine::NothingBad;
}
