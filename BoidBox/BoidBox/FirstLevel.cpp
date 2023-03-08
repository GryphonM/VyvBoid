//------------------------------------------------------------------------------
//
// File Name:	FirstLevel.h
// Description:	Contains code for FirstLevel scene
// Author(s):	Gryphon McLaughlin(gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "FirstLevel.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "PlatformSystem.h"
#include "SoundSystem.h"
#include "Goal.h"
#include "Obstacle.h"
#include "Boids.h"
#include "PlaceBlock.h"
#include "Mesh.h"
#include "Sprite.h"
#include "SpriteSource.h"

struct FirstLevel
{
	Scene base;

	// Other Fings
	Obstacle* obstacle1;
	Obstacle* obstacle2;
	Goal* goal;
	BoidList* bList;
	PlaceBlock* pBlocks;
	Sound* placeSound;

	Sprite* backgroundSprite;

	Mesh* backgroundMesh;
	SpriteSource* backgroundSource;
	Transform* backgroundPos;

	FirstLevel(Scene _base) : base(_base), goal(NULL), bList(NULL), pBlocks(NULL), placeSound(NULL)
	{
	}
};

Engine::ErrorCode FirstLevelLoad(void);
Engine::ErrorCode FirstLevelInit(void);
void FirstLevelUpdate(float dt);
void FirstLevelRender(void);
Engine::ErrorCode FirstLevelExit(void);
Engine::ErrorCode FirstLevelUnload(void);

FirstLevel instance(Scene("Stub Scene", FirstLevelLoad, FirstLevelInit, FirstLevelUpdate, FirstLevelRender, FirstLevelExit, FirstLevelUnload));
Scene* FirstLevelGetInstance() { return &instance.base; }


Engine::ErrorCode FirstLevelLoad(void)
{
	instance.backgroundMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Square Mesh", { 0.0f, 0.0f, 0.0f, 0.0f });
	instance.backgroundPos = CreateTransform(Vector2D(), Vector2D(960, 561));
	instance.backgroundSource = CreateSpriteSource();
	LoadSpriteSourceTexture(instance.backgroundSource, 1, 1, "./Assets/desktopBackgroundBLANK.png");
	instance.backgroundSprite = CreateSprite();
	SpriteSetMesh(instance.backgroundSprite, instance.backgroundMesh);
	SpriteSetSource(instance.backgroundSprite, instance.backgroundSource);

	instance.bList = CreateBoidlist();
	UpdateBoidlistParamaters(instance.bList, "./Data/BoidSettings.txt");
	Vector2D Screen(static_cast<float>(PlatformSystem::GetInstance()->GetWidth()), static_cast<float>(PlatformSystem::GetInstance()->GetHeight()));
	Vector2D BoidStart(-(Screen.X() / 2) + 50, (Screen.Y() / 2) - 155);
	Vector2D GoalStart((Screen.X() / 2) - 20, -(Screen.Y() / 2) + 300);
	for (int i = 0; i < 10; ++i)
	{
		AddBoidToList(instance.bList, BoidStart, Vector2D(0, 1000));
	}
	instance.obstacle1 = new Obstacle(CreateTransform(Vector2D(0, -150), Vector2D(400, 171)), instance.bList, 10);
	instance.obstacle2 = new Obstacle(CreateTransform(Vector2D(0, 240), Vector2D(400, 170)), instance.bList, 10);
	instance.goal = new Goal(CreateTransform(GoalStart, Vector2D(200, 200)), instance.bList, 10);
	instance.pBlocks = CreatePlaceBlocks("Place Blocks", instance.bList);
	instance.placeSound = SoundCreate("Block Place Sound", "./Assets/place.mp3");
	return Engine::NothingBad;
}

Engine::ErrorCode FirstLevelInit(void)
{
	SpriteSetFrame(instance.backgroundSprite, 0);
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

	instance.goal->Reset();
	instance.obstacle1->Reset();
	instance.obstacle2->Reset();
	instance.base.mode = Scene::Mode::Place;
	return Engine::NothingBad;
}

void FirstLevelUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes())
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
		instance.goal->Update();
		instance.obstacle1->Update();
		instance.obstacle2->Update();
	}
}

void FirstLevelRender(void)
{
	RenderSprite(instance.backgroundSprite, instance.backgroundPos);

	DrawPlacedBlocks(instance.pBlocks);
	RenderBoids(instance.bList);
	instance.obstacle1->Render();
	instance.obstacle2->Render();
	instance.goal->Render();
}

Engine::ErrorCode FirstLevelExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode FirstLevelUnload(void)
{
	FreeSprite(&instance.backgroundSprite);
	freeMesh(&instance.backgroundMesh);
	DeleteTransform(&instance.backgroundPos);

	SoundCleanup(instance.placeSound);
	DestroyPlaceBlocks(&instance.pBlocks);
	DestroyBoidList(instance.bList);
	instance.bList = NULL;
	delete instance.obstacle1;
	delete instance.obstacle2;
	instance.obstacle1 = NULL;
	instance.obstacle2 = NULL;
	delete instance.goal;
	instance.goal = NULL;
	return Engine::NothingBad;
}
