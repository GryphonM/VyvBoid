//------------------------------------------------------------------------------
//
// File Name:	OpenScene.cpp
// Description:	Contains code for the scene that opens on startup
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "OpenScene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Engine.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Mesh.h"
#include "SoundSystem.h"

struct OpenScene
{
	Scene base;

	// Other Fings
	Sprite* OpenSprite;

	Sprite* titleSprite;
	Mesh* titleMesh;
	SpriteSource* titleSource;
	Transform* titlePos;

	Sound* scare;

	// Constructor (Actually used this time)
	OpenScene(Scene _base) : base(_base), OpenSprite(NULL)
	{
	}
};

Engine::ErrorCode OpenSceneLoad(void);
Engine::ErrorCode OpenSceneInit(void);
void OpenSceneUpdate(float dt);
void OpenSceneRender(void);
Engine::ErrorCode OpenSceneExit(void);
Engine::ErrorCode OpenSceneUnload(void);

Mesh* squareMesh;
SpriteSource* source;
Transform* pos;
OpenScene instance(Scene("Open Scene", OpenSceneLoad, OpenSceneInit, OpenSceneUpdate, OpenSceneRender, OpenSceneExit, OpenSceneUnload));

Scene* OpenSceneGetInstance() { return &(instance.base); }

Engine::ErrorCode OpenSceneLoad(void)
{
	instance.titleMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Square Mesh", { 0.0f, 0.0f, 0.0f, 0.0f });
	instance.titlePos = CreateTransform(Vector2D(0, -9), Vector2D(1000, 600));;
	instance.titleSource = CreateSpriteSource();
	LoadSpriteSourceTexture(instance.titleSource, 1, 1, "./Assets/desktopBackgroundTITLE.png");
	instance.titleSprite = CreateSprite();
	SpriteSetMesh(instance.titleSprite, instance.titleMesh);
	SpriteSetSource(instance.titleSprite, instance.titleSource);
	instance.scare = SoundCreate("scare", "./Assets/cloaker.ogg");
	
	return Engine::NothingBad;
}

Engine::ErrorCode OpenSceneInit(void)
{
	SpriteSetFrame(instance.titleSprite, 0);
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	DGL_Graphics_SetTexture(NULL);
	//PlaySound(instance.scare);
	return Engine::NothingBad;
}

void OpenSceneUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes() || CheckRestartGame())
		return;
	// Other Things on Open
}

void OpenSceneRender(void)
{
	RenderSprite(instance.titleSprite, instance.titlePos);

	//RenderSprite(instance.OpenSprite, pos);
}

Engine::ErrorCode OpenSceneExit(void)
{
	SoundCleanup(instance.scare);
	return Engine::NothingBad;
}

Engine::ErrorCode OpenSceneUnload(void)
{
	FreeSprite(&instance.titleSprite);
	freeMesh(&instance.titleMesh);
	DeleteTransform(&instance.titlePos);
	//FreeSprite(&instance.OpenSprite);
	//freeMesh(&squareMesh);
	//DeleteTransform(&pos);
	return Engine::NothingBad;
}
